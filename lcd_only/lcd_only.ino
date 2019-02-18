
#define RESTORE_SPI_GPIO() SPCR = 0

#include <SPI.h>            

#include <SD.h>             

#include <Adafruit_GFX.h>   
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#if defined(ESP32) 
#define SD_CS     5
#else
#define SD_CS     5 //10          
#endif
#define NAMEMATCH1 "green.bmp"        
#define NAMEMATCH2 "yellow.bmp"
#define NAMEMATCH3 "red.bmp"

#define PALETTEDEPTH   0     


char namebuf[32] = "/";   
//char namebuf[32] = "/bitmaps/";  

File root;
int pathlen;
int A = 2;
int B = 3;

void setup()
{
    uint16_t ID;
    Serial.begin(9600);
    Serial.print("Show BMP files on TFT with ID:0x");
    ID = tft.readID();
    Serial.println(ID, HEX);
    if (ID == 0x0D3D3) ID = 0x9481;
    tft.begin(ID);
    tft.fillScreen(0x001F);
    tft.setTextColor(0xFFFF, 0x0000);
    bool good = SD.begin(SD_CS);
    if (!good) {
        Serial.print(F("cannot start SD"));
        while (1);
    }
    root = SD.open(namebuf);
    pathlen = strlen(namebuf);
    pinMode (A, INPUT);
    pinMode (B, INPUT);
}

void loop()
{
    char *nm = namebuf + pathlen;
    File f = root.openNextFile();
    uint8_t ret;
    uint32_t start;
    if (f != NULL) {
#ifdef USE_SDFAT
        f.getName(nm, 32 - pathlen);
#else
        strcpy(nm, (char *)f.name());
#endif
        f.close();
        RESTORE_SPI_GPIO();
        strlwr(nm);

        int a = digitalRead(A);
        int b = digitalRead(B);
        Serial.println("Vrijednost A:");
        Serial.println(a);
        Serial.println("Vrijednost B:");
        Serial.println(b);
        
        
        if(a==LOW && b==LOW){
        if (strstr(nm, ".bmp") != NULL && strstr(nm, NAMEMATCH1) != NULL) {
            Serial.print(namebuf);
            //Serial.print(F(" - "));
            tft.fillScreen(0);
            //start = millis();
            ret = showBMP(namebuf, 5, 5);
           
        }}
        
        if(a==LOW && b==HIGH) {
        if (strstr(nm, ".bmp") != NULL && strstr(nm, NAMEMATCH2) != NULL) {
            Serial.print(namebuf);
            //Serial.print(F(" - "));
            tft.fillScreen(0);
            //start = millis();
            ret = showBMP(namebuf, 5, 5);
           
        }}

        if(a==HIGH && b==LOW) {
        if (strstr(nm, ".bmp") != NULL && strstr(nm, NAMEMATCH2) != NULL) {
            Serial.print(namebuf);
            //Serial.print(F(" - "));
            tft.fillScreen(0);
            //start = millis();
            ret = showBMP(namebuf, 5, 5);
           
        }}
        
        if(a==HIGH && b==HIGH){
        if (strstr(nm, ".bmp") != NULL && strstr(nm, NAMEMATCH3) != NULL) {
            Serial.print(namebuf);
            //Serial.print(F(" - "));
            tft.fillScreen(0);
            //start = millis();
            ret = showBMP(namebuf, 5, 5);
           
        }}
    }
    
}

#define BMPIMAGEOFFSET 54

#define BUFFPIXEL      20

uint16_t read16(File& f) {
    uint16_t result;         
    f.read((uint8_t*)&result, sizeof(result));
    return result;
}

uint32_t read32(File& f) {
    uint32_t result;
    f.read((uint8_t*)&result, sizeof(result));
    return result;
}

uint8_t showBMP(char *nm, int x, int y)
{
    File bmpFile;
    int bmpWidth, bmpHeight;    
    uint8_t bmpDepth;           
    uint32_t bmpImageoffset;    
    uint32_t rowSize;           
    uint8_t sdbuffer[3 * BUFFPIXEL];    
    uint16_t lcdbuffer[(1 << PALETTEDEPTH) + BUFFPIXEL], *palette = NULL;
    uint8_t bitmask, bitshift;
    boolean flip = true;        
    int w, h, row, col, lcdbufsiz = (1 << PALETTEDEPTH) + BUFFPIXEL, buffidx;
    uint32_t pos;               
    boolean is565 = false;      

    uint16_t bmpID;
    uint16_t n;                 
    uint8_t ret;

    if ((x >= tft.width()) || (y >= tft.height()))
        return 1;               // off screen

    bmpFile = SD.open(nm);      
    bmpID = read16(bmpFile);    
    (void) read32(bmpFile);     
    (void) read32(bmpFile);     
    bmpImageoffset = read32(bmpFile);      
    (void) read32(bmpFile);     
    bmpWidth = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    n = read16(bmpFile);        
    bmpDepth = read16(bmpFile); 
    pos = read32(bmpFile);     
    if (bmpID != 0x4D42) ret = 2; 
    else if (n != 1) ret = 3;  
    else if (pos != 0 && pos != 3) ret = 4; 
    else if (bmpDepth < 16 && bmpDepth > PALETTEDEPTH) ret = 5;
    else {
        bool first = true;
        is565 = (pos == 3);             
        
        rowSize = (bmpWidth * bmpDepth / 8 + 3) & ~3;
        if (bmpHeight < 0) {             
            bmpHeight = -bmpHeight;
            flip = false;
        }

        w = bmpWidth;
        h = bmpHeight;
        RESTORE_SPI_GPIO();
        tft.setRotation(w > h ? 1 : 0);   
        if ((x + w) >= tft.width())      
            w = tft.width() - x;
        if ((y + h) >= tft.height())     
            h = tft.height() - y;

        if (bmpDepth <= PALETTEDEPTH) {  
            bmpFile.seek(BMPIMAGEOFFSET); 
            bitmask = 0xFF;
            if (bmpDepth < 8)
                bitmask >>= bmpDepth;
            bitshift = 8 - bmpDepth;
            n = 1 << bmpDepth;
            lcdbufsiz -= n;
            palette = lcdbuffer + lcdbufsiz;
            for (col = 0; col < n; col++) {
                pos = read32(bmpFile);    
                palette[col] = ((pos & 0x0000F8) >> 3) | ((pos & 0x00FC00) >> 5) | ((pos & 0xF80000) >> 8);
            }
        }

        RESTORE_SPI_GPIO();
        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x + w - 1, y + h - 1);
        for (row = 0; row < h; row++) {
            
            uint8_t r, g, b, *sdptr;
            int lcdidx, lcdleft;
            if (flip)   
                pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
            else      
                pos = bmpImageoffset + row * rowSize;
            if (bmpFile.position() != pos) { 
                bmpFile.seek(pos);
                buffidx = sizeof(sdbuffer); 
            }

            for (col = 0; col < w; ) {  
                lcdleft = w - col;
                if (lcdleft > lcdbufsiz) lcdleft = lcdbufsiz;
                for (lcdidx = 0; lcdidx < lcdleft; lcdidx++) { 
                    uint16_t color;
                    
                    if (buffidx >= sizeof(sdbuffer)) { 
                        bmpFile.read(sdbuffer, sizeof(sdbuffer));
                        buffidx = 0; 
                        r = 0;
                    }
                    switch (bmpDepth) {       
                        case 24:
                            b = sdbuffer[buffidx++];
                            g = sdbuffer[buffidx++];
                            r = sdbuffer[buffidx++];
                            color = tft.color565(r, g, b);
                            break;
                        case 16:
                            b = sdbuffer[buffidx++];
                            r = sdbuffer[buffidx++];
                            if (is565)
                                color = (r << 8) | (b);
                            else
                                color = (r << 9) | ((b & 0xE0) << 1) | (b & 0x1F);
                            break;
                        case 1:
                        case 4:
                        case 8:
                            if (r == 0)
                                b = sdbuffer[buffidx++], r = 8;
                            color = palette[(b >> bitshift) & bitmask];
                            r -= bmpDepth;
                            b <<= bmpDepth;
                            break;
                    }
                    lcdbuffer[lcdidx] = color;

                }
                RESTORE_SPI_GPIO();
                tft.pushColors(lcdbuffer, lcdidx, first);
                first = false;
                col += lcdidx;
            }           
        }               
        tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1);
        ret = 0;        
    }
    bmpFile.close();
    RESTORE_SPI_GPIO();
  return (ret);
}

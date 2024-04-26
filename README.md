# esp-idf-m5stickC-Plus
Example code for driving M5StickC-Plus/Plus2 ST7789V2 display using ESP-IDF's SPI driver.

![M5StickC-Plus2](https://github.com/nopnop2002/esp-idf-m5stickC-Plus/assets/6020549/ca0e2687-a557-40b5-b712-5f3f578ddf75)

# Software requirements
esp-idf v4.4/v5.x.   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-m5stickC-Plus
cd esp-idf-m5stickC-Plus/screen
idf.py set-target esp32
idf.py menuconfig
idf.py flash -b 115200 monitor
```

__You need to specify Baud rate for flashing.__   


# Configuration
![config-top](https://github.com/nopnop2002/esp-idf-m5stickC-Plus/assets/6020549/143cc5c4-0265-42b2-93eb-3f11aa0d4cb0)
![config-app-1](https://github.com/nopnop2002/esp-idf-m5stickC-Plus/assets/6020549/1b00b76d-bca2-424d-86f1-1ef27b56b96c)
![config-app-2](https://github.com/nopnop2002/esp-idf-m5stickC-Plus/assets/6020549/d717051b-74aa-4453-afbd-bac6f418227c)


# Graphic support
![M5StickC-Plus-2](https://user-images.githubusercontent.com/6020549/100176342-73e1e400-2f13-11eb-9b03-0ec912228ce5.JPG)

![M5StickC-Plus-3](https://user-images.githubusercontent.com/6020549/100176344-75131100-2f13-11eb-80f9-cf35e85fddef.JPG)

![M5StickC-Plus-4](https://user-images.githubusercontent.com/6020549/100176347-76443e00-2f13-11eb-8e47-3b63f884062b.JPG)

# Fonts support
It's possible to text rotation and invert.   
![M5StickC-Plus-5](https://user-images.githubusercontent.com/6020549/100175720-45afd480-2f12-11eb-9acb-8d4244a2a910.JPG)

![M5StickC-Plus-6](https://user-images.githubusercontent.com/6020549/100175721-46e10180-2f12-11eb-8cdb-cd4add269dcd.JPG)

![M5StickC-Plus-7](https://user-images.githubusercontent.com/6020549/100175724-48aac500-2f12-11eb-9329-d3ca8267432a.JPG)

It's possible to indicate more than one font at the same time.   
![M5StickC-Plus-11](https://user-images.githubusercontent.com/6020549/100176463-a986cd00-2f13-11eb-8a96-89a01ff7edbe.JPG)


# Image support
BMP file   
![M5StickC-Plus-8](https://user-images.githubusercontent.com/6020549/100175767-5d875880-2f12-11eb-8cae-991e73e1f93b.JPG)
JPEG file   
![M5StickC-Plus-9](https://user-images.githubusercontent.com/6020549/100175770-5eb88580-2f12-11eb-90d3-43d06675bb99.JPG)
PNG file    
![M5StickC-Plus-10](https://user-images.githubusercontent.com/6020549/100175773-5fe9b280-2f12-11eb-9043-55abc8e72a2e.JPG)


# Font File   
You can add your original font file.   
The format of the font file is the FONTX format.   
Your font file is put in font directory.   
Your font file is uploaded to SPIFFS partition using meke flash.   

Please refer [this](http://elm-chan.org/docs/dosv/fontx_e.html) page about FONTX format.   

```
FontxFile yourFont[2];
InitFontx(yourFont,"/spiffs/your_font_file_name","");
uint8_t ascii[10];
strcpy((char *)ascii, "MyFont");
lcdDrawString(dev, yourFont, x, y, ascii, color);
```

# How to add your color   
Change here.   
```
#define RED    rgb565(255,   0,   0) // 0xf800
#define GREEN  rgb565(  0, 255,   0) // 0x07e0
#define BLUE   rgb565(  0,   0, 255) // 0x001f
#define BLACK  rgb565(  0,   0,   0) // 0x0000
#define WHITE  rgb565(255, 255, 255) // 0xffff
#define GRAY   rgb565(128, 128, 128) // 0x8410
#define YELLOW rgb565(255, 255,   0) // 0xFFE0
#define CYAN   rgb565(  0, 156, 209) // 0x04FA
#define PURPLE rgb565(128,   0, 128) // 0x8010
```

# Reference   
https://github.com/nopnop2002/esp-idf-m5stickC

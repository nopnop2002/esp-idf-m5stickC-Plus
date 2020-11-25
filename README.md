# esp-idf-m5stickC-Plus
Example code for driving M5StickC-Plus ST7789V2 display using ESP-IDF's SPI driver.

![M5StickC-Plus-1](https://user-images.githubusercontent.com/6020549/100175622-1a2cea00-2f12-11eb-8d3d-37aa5525856b.JPG)

```
git clone https://github.com/nopnop2002/esp-idf-m5stickC-Plus
cd esp-idf-m5stickC-Plus/
make menuconfig
make flash
```

\*There is no MENU ITEM where this application is peculiar.   


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



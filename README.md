# esp-idf-m5stickC-Plus
Example code for driving M5StickC-Plus ST7789V2 display using ESP-IDF's SPI driver.

![M5StickC-Plus-1](https://user-images.githubusercontent.com/6020549/100174258-6aef1380-2f0f-11eb-83d9-af3385b6949a.JPG)

```
git clone https://github.com/nopnop2002/esp-idf-m5stickC-Plus
cd esp-idf-m5stickC-Plus/
make menuconfig
make flash
```

\*There is no MENU ITEM where this application is peculiar.   


# Graphic support
![M5StickC-Plus-2](https://user-images.githubusercontent.com/6020549/100174338-91ad4a00-2f0f-11eb-9333-e501fdb5758b.JPG)

![M5StickC-Plus-3](https://user-images.githubusercontent.com/6020549/100174339-9245e080-2f0f-11eb-98cf-870e170516d6.JPG)

![M5StickC-Plus-4](https://user-images.githubusercontent.com/6020549/100174336-907c1d00-2f0f-11eb-8ea1-36f50047731d.JPG)

# Fonts support
It's possible to text rotation and invert.   
![M5StickC-Plus-5](https://user-images.githubusercontent.com/6020549/100174388-ab4e9180-2f0f-11eb-9528-18aa13add27a.JPG)

![M5StickC-Plus-6](https://user-images.githubusercontent.com/6020549/100174391-ac7fbe80-2f0f-11eb-87da-3b4b752f79ac.JPG)

![M5StickC-Plus-7](https://user-images.githubusercontent.com/6020549/100174384-aa1d6480-2f0f-11eb-8fa2-7e86dc5575d1.JPG)

It's possible to indicate more than one font at the same time.   
![M5StickC-Plus-11](https://user-images.githubusercontent.com/6020549/100174404-b4d7f980-2f0f-11eb-8bf6-01addd8b23e0.JPG)


# Image support
BMP file   
![M5StickC-Plus-8](https://user-images.githubusercontent.com/6020549/100174487-e355d480-2f0f-11eb-96df-5ae2a33a22b7.JPG)
JPEG file   
![M5StickC-Plus-9](https://user-images.githubusercontent.com/6020549/100174489-e4870180-2f0f-11eb-8a37-b174608aef55.JPG)
PNG file    
![M5StickC-Plus-10](https://user-images.githubusercontent.com/6020549/100174484-e224a780-2f0f-11eb-9f51-b21f0d0d2716.JPG)


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



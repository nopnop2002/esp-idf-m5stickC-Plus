# esp-idf-m5stickC-Plus
Example code for driving M5StickC-Plus/Plus2 ST7789V2 display using ESP-IDF's SPI driver.   
M5StickC-Plus/Plus2 has 135x240 ST7789V2 tft.   

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
This project uses the following as default fonts:   
- font/ILGH16XB.FNT // 8x16Dot Gothic
- font/ILGH24XB.FNT // 12x24Dot Gothic
- font/ILGH32XB.FNT // 16x32Dot Gothic
- font/ILMH16XB.FNT // 8x16Dot Mincyo
- font/ILMH24XB.FNT // 12x24Dot Mincyo
- font/ILMH32XB.FNT // 16x32Dot Mincyo

From 0x00 to 0x7f, the characters image of Alphanumeric are stored.   
From 0x80 to 0xff, the characters image of Japanese are stored.   
Changing this file will change the font.

You can add your original font file.   
The format of the font file is the FONTX format.   
Your font file is put in font directory.   
When you build the firmware, the font files are uploaded to the SPIFFS partition.   

Please refer [this](http://elm-chan.org/docs/dosv/fontx_e.html) page about FONTX format.   

# Font File Editor(FONTX Editor)   
[There](http://elm-chan.org/fsw/fontxedit.zip) is a font file editor.   
This can be done on Windows 10.   
Developer page is [here](http://elm-chan.org/fsw_e.html).   

![fontx-editor-1](https://github.com/user-attachments/assets/76a8c96f-74c3-4583-a4f1-5664f0e81f3a)

# Convert from TTF font to FONTX font  
step1)   
Download WFONTX64.exe from [here](https://github.com/nemuisan/WFONTX64/releases).
Developer page is [here](https://github.com/nemuisan/WFONTX64).   

step2)   
Select ttf font.   
___Please note that if you select a proportional font, some fonts may not convert correctly.___   
If you select a proportional font, some fonts will need to be modified using fontxedit.exe.   
Monospaced fonts can be converted correctly.   
![WFONTX64-1](https://github.com/user-attachments/assets/2193a3c4-021c-48e6-8486-2ce500bdac36)

step3)   
Enter Height, Width, FontX2 name.   
Specify half of Height for Width.   
Specify your favorite font name in the FontX2 name field using up to 8 characters.   
![WFONTX64-2](https://github.com/user-attachments/assets/c87a9ec9-8e28-4d34-8475-60b15a47fb22)


step4)   
Specify the file name to save.   
![WFONTX64-3](https://github.com/user-attachments/assets/9715d4bf-e460-41a6-9a4b-38c0f10020f7)

step5)   
Specify the font style as required.   
![WFONTX64-4](https://github.com/user-attachments/assets/0ff3072d-6a78-48ae-b855-60c692f8d771)

step6)   
Press the RUN button to convert TTF fonts to FONTX format.   
![WFONTX64-5](https://github.com/user-attachments/assets/d9797e3d-1fd6-4504-b161-c1280f1242c0)

step7)   
upload your font file to $HOME/esp-idf-m5stickC-Plus/fonts directory.   

step8)   
add font to use   
```
    FontxFile fx16G[2];
    FontxFile fx24G[2];
    FontxFile fx32G[2];
    //InitFontx(fx16G,"/fonts/ILGH16XB.FNT",""); // 8x16Dot Gothic
    //InitFontx(fx24G,"/fonts/ILGH24XB.FNT",""); // 12x24Dot Gothic
    //InitFontx(fx32G,"/fonts/ILGH32XB.FNT",""); // 16x32Dot Gothic
    InitFontx(fx16G,"/fonts/Gigi16.FNT",""); // 8x16Dot Gigi
    InitFontx(fx24G,"/fonts/Gigi24.FNT",""); // 12x24Dot Gigi
    InitFontx(fx32G,"/fonts/Gigi32.FNT",""); // 16x32Dot Gigi
```

![TTF_FONT](https://github.com/user-attachments/assets/5904c317-5c83-47f3-a49a-240ab7296961)

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

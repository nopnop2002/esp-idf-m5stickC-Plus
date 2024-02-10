# imu
Example code for driving M5StickC-Plus/Plus2 MPU6886 6-Axis posture sensor using ESP-IDF's i2c driver.   
I used [this](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino) I2Cdev library collection by Jeff Rowberg.   

![imu](https://github.com/nopnop2002/esp-idf-m5stickC-Plus/assets/6020549/e9148d7e-3469-47b6-8d80-8c2c365524b3)

# Software requirements
esp-idf v4.4/v5.x.   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-m5stickC-Plus
cd esp-idf-m5stickC-Plus/imu
idf.py set-target esp32
idf.py menuconfig
idf.py flash -b 115200 monitor
```

__You need to specify Baud rate for flashing.__   

# How to use
The circle moves when you tilt the M5Stick.   
Press the button to change the color of the circle.   

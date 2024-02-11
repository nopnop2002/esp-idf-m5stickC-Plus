# pose
Example code for driving M5StickC-Plus/Plus2 MPU6886 6-Axis posture sensor using ESP-IDF's i2c driver.   
I used [this](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino) I2Cdev library collection by Jeff Rowberg.   

![pose-1](https://github.com/nopnop2002/esp-idf-m5stickC-Plus/assets/6020549/57da219c-de51-4c54-acef-99d27f1b87e3)
![pose-2](https://github.com/nopnop2002/esp-idf-m5stickC-Plus/assets/6020549/3f06eb43-eead-4901-9e16-3b3e39266867)

# Software requirements
esp-idf v4.4/v5.x.   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-m5stickC-Plus
cd esp-idf-m5stickC-Plus/pose
idf.py set-target esp32
idf.py menuconfig
idf.py flash -b 115200 monitor
```

__You need to specify Baud rate for flashing.__   

# How to use
When you turn M5Stick vertically or horizontally, the pose of M5Stick will be displayed.   
If you want to see more details, you can use this.   
https://github.com/nopnop2002/esp-idf-mpu6050-dmp/tree/main/MPU6050_KALMAN   
https://github.com/nopnop2002/esp-idf-mpu6050-dmp/tree/main/MPU6050_MADGWICK   

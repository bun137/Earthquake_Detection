# Earthquake_Detection

## Hardware

- Arduino Mega
- MPU6050
- HC-05 (Bluetooth Module)

## How it works

The MPU6050 module gives us acceleration and gyroscope values. We only make use of the acceleration values in x,y and z direction. A change of 0.5 m/s<sup>2</sup> in any direction is considered as an earthquake. 

These modules are kept in remote locations where there is not much activity. Multiple modules are kept in different locations to form a net of detection modules. As soon as an earthquake is detected, we send a telegram notification. This is ideally supposed to be an emergency notification (like the one we got on our phones throughout the week)

## Development

1. Aproach the maintainer for the hardware
2. Upload the arduino code `earthquake-detector.ino` to the arduino via the USB serial cable
3. Run `telegram_register.py` to register people from the telegram bot. This file is only run when you want to register users for the alert. Once you're done, stop execution of this file with a `ctrl+c` (it's a `ctrl + c` on mac too) 
4. Run the `send-earthquake.py` parallely while the arduino is powered on. Make sure you've connected to the `HC-05` bluetooth module on your laptop
5. Now when the module is shook, it should send an alert to every user ID in the `user_id.txt` file.

## Maintainer

1. [Shreya Gurram](https://github.com/bun137) 
[gurram13775@gmail.com](mailto:gurram13775@gmail.com) 9901618209

2. [Anurag Rao](https://github.com/anuragrao04)
[raoanu2004@gmail.com](mailto:raoanu2004@gmail.com) 9663006833


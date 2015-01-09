Gait_Measurement
================

arduino code, python codes to visualise and plot data

bluetooth_main.ino - This is the main code that needs to be loaded on to the Arduino Yun. It sets up the bluetooth communication between the phone and bluetooth LE module. It also prints the sensor data on the serial terminal if the arduino is connected to the same network as the laptop.

** serial_plot.py is used to visualise the sensor readings in real time and save the data in a text file. In the code, it is necessary to specify the serial port and filename before running. (Modify lines 50 and 74)

** plotcode.py is used to plot the sensor data from the saved text file. The filename needs to be modified before running. (Modify line 4)




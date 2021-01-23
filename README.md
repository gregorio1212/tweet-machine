# tweet-machine
In this repository it is located my final project for the course Microprocessor Technology 2 from the department 
of Computer Science, Electronics and Telecommunications at AGH University of Science and Technology.

Hardware components used:
- Laptop;
- FRDM-KL05Z board;
- 4x4 keypad;
- 16x2 LCD screen with I2C driver

Brief intro:
The project consists of a text editor which makes use of a LCD screen to show the typed text. A Python script 
opens a serial connection between the FRDM-KL05Z board and the laptop. This UART connection makes it possible
to send the text typed on the LCD screen to the laptop. Through a Python script, this message sent to the 
laptop is turned into a tweet automatically. In the Python script is also possible to set a limit of tweets which
makes it a good machine for those having issues with overtweeting.

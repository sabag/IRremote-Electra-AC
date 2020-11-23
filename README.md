# IRremote-Electra-AC
This code enables ESP32 modules to read and decode the Electra AC remote control.


This is yet another modified version of the great [IRremote library](https://github.com/z3t0/Arduino-IRremote) .
The ino file is an example of how to use the library.

This work was inspired and made available due to the magnificent work of two other repositories:
* [https://github.com/nryhbhue/Electra-AC-Remote](https://github.com/nryhbhue/Electra-AC-Remote) - Thank you very much for the clear and detailed explanation, I was unable to do without it. Thank you @nryhbhue.
* [https://github.com/barakwei/IRelectra](https://github.com/barakwei/IRelectra) - Excellent and clear code to understand this remote. Thank you @barakwei.

### Electra AC Remote
![Electra AC Remote Control](https://user-images.githubusercontent.com/11669278/99955545-35222180-2d8d-11eb-9838-2bbdce8b226e.jpg)


after almost three months (on and off) of work, i was able to make this available.

### Installation:
1. copy the IRremote folder to the sketchbook/libraries folder. make sure **not** to overwrite your already existing IRremote library. Either rename the library or overwrite.
2. create a sketch in the Arduino IDE with the .ino file 
3. get an ESP32 module and connect the IR receiver module to it (pin D15).

### Hardware:
I used both "Wemos D1 Mini ESP32" and "ESP32 DEVKIT V1", with IR receiver module connected on pin D15 (next to the 3v3 and GND on the DEVKIT module)

### Reference:
[https://en.wikipedia.org/wiki/Manchester_code](https://en.wikipedia.org/wiki/Manchester_code)

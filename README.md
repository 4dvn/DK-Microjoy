# DK-Microjoy
MICROJOY is a miniscule MIDI controller with an analog joystick that is great for manipulating any two musical parameters at once, like an XY pad. Each axis has an indicator light that changes color to show the position of the joystick in low-light environments.

![Microjoy MIDI Controller](/images/microjoy1.jpg)

## About
This was a customer request for a simple MIDI joystick less than 4 inches square. It met their needs nicely and is available in my
[Etsy Store: Circuits & Sawdust](https://www.etsy.com/listing/520197772/Microjoy-handmade-usb-midi-program).

![Microjoy MIDI Controller](/images/microjoy2.jpg)

## How it works
This is an inexpensive Arduino Pro Micro based USB MIDI controller. I've been moving away from [Teensy](https://www.pjrc.com/teensy/)  based MIDI controllers recently due to lower costs and better availability. Any of the newer Arduino boards with an ATmega32u4 chip can support the equivalent [MIDIUSB library](https://www.arduino.cc/en/Reference/MIDIUSB), like the Sparkfun Pro Micro and generic clones.

The joystick has two potentiometers, one for each axis, along with a [Neopixel](https://github.com/adafruit/Adafruit_NeoPixel) addressable RGB LED with customizable color fading algorithms. This uses my standard analog knob code to smooth the MIDI values sent over USB to any computer music software.

![Microjoy MIDI Controller](/images/microjoy3.jpg)
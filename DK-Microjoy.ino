#include <Adafruit_NeoPixel.h>
#include <KnobDK.h>

#include "MIDIUSB.h" // new library for MEGA32U4 chips

#define midiChannel 1

//#define DEBUG


// Controller knobs (analogPin, midiCC, analogMin, analogMax)
#define knobCount 2
KnobDK knob[knobCount] = {
  KnobDK(A0, 74, 0, 1023), // X
  KnobDK(A1, 75, 1023, 0), // Y
};

#define neopixelPIN 3
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(2, neopixelPIN, NEO_RGB + NEO_KHZ800);

void setup() {

  pixels.begin();
}

void loop() {

  // Analog inputs loop
  for (int i=0; i < knobCount; i++)
  {
    // Refresh controller value
    bool activity = knob[i].refresh();
    
    if(activity)
    {
      #ifdef DEBUG
        Serial.print("Knob ");
        Serial.print(i);
        Serial.print(" is ");
        Serial.print(knob[i].val());
        Serial.print(" sent ");
        Serial.print(knob[i].ccVal());
        Serial.print(" on CC ");
        Serial.println(knob[i].ccNum());
      #endif
      
      // Send MIDI CC value
      controlChange(midiChannel, knob[i].ccNum(), knob[i].ccVal());

      // Update LEDs
      if(i == 0) {
        // blue -> orange -> blue for left-center-right
        int val = map(knob[i].val(), 0, 1023, -127, 127);
        pixels.setPixelColor(i, pixels.Color(127 - abs(val), (127 - abs(val)) / 6, abs(val)));
      } else {
        // red -> orange -> blue for up-center-down
        int val = map(knob[i].val(), 0, 1023, -127, 127);
        pixels.setPixelColor(i, pixels.Color(175 + (val < 0 ? val : -1 * val), (127 - abs(val)) / 6, (val > 0 ? val : 0)));      
      }


    } 
  }

  // Send the updated pixel color to the hardware
  pixels.show();

  // Ensure all MIDI is sent over usb
  MidiUSB.flush();

  // MIDI controllers need to discard incoming MIDI messages to clear buffer
  MidiUSB.read();

  // Reduce analog sampling rate for smoother action
  delay(20);
}


// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

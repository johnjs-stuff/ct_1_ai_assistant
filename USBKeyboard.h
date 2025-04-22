#ifndef USBKEYBOARD_H
#define USBKEYBOARD_H

#include <Arduino.h>

class USBKeyboard {
  public:
    USBKeyboard();

    // Flush any entered keys, timers and partially read keys.
    void reset();

    // Setup the keyboard input pins
    void begin(uint8_t clockPin, uint8_t dataPin);

    // Get the code for the next entered key
    uint32_t getCode();
};

#endif /* USBKEYBOARD_H */

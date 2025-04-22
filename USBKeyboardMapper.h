#ifndef USBKEYBOARDMAPPER_H
#define USBKEYBOARDMAPPER_H

#define KEYMAP_SIZE 256

// Some control keys that can be used
#define USB_KBD_BS      0x08    // Backspace
#define USB_KBD_HT      0x09    // (Horizontal) TAB 
#define USB_KBD_CR      0x0D    // Carriage Return
#define USB_KBD_ESC     0x1B    // Escape

#include <Arduino.h>

class USBKeyboardMapper {
  private:
    char _keyMap[KEYMAP_SIZE];

  public:
    USBKeyboardMapper();
    // Translate the keyboard scan code to an ASCII character
    char translate(uint32_t code);
};

#endif /* USBKEYBOARDMAPPER_H */

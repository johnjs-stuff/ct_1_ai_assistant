#include "USBKeyboardMapper.h"

USBKeyboardMapper::USBKeyboardMapper() {
  // First draft of the keyboard scan code mapper. The bare essentials.
  // Just enough to get a sensible string ot text to send to OpenAI.
  // This is the mapping for the keyboard I used, a very old USB keyboard with the branding "XTIME" and no other model or manufacturer.
  char newKeyMap[KEYMAP_SIZE] = {
    0, 0, 0, 0, 0, ',', 0, 0, 0, 'c', 0, 0, 0, 0, 0, 0,   // 0x00 - 0x0F
    0, 0, 0, 0, 0, 0, 0, 0, 'n', 0, 0, 0, 0, 0, 0, 0,   // 0x10 - 0x1F
    0, 0, 0, 0, '.', 0, 0, 0, ' ', 0, 0, 0, 0, 0, 0, 0,   // 0x20 - 0x2F
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // 0x30 - 0x3F
    0, 0, 0, 0, '0', 'o', 0, 0, '4', 'e', 0, 0, 0, 0, 0, 0,   // 0x40 - 0x4F
    'q', 0, 0, 0, '[', '=', 0, 0, 'g', 'y', 0, 0, 0, 0, 0, 0,   // 0x50 - 0x5F
    USB_KBD_HT, 0, 0, 0, ';', 'p', 0, 0, 't', 'r', 0, 0, 0, 0, 0, 0,   // 0x60 - 0x6F
    'a', 'w', 0, 0, '\\', 0, 0, 0, '7', 'u', 0, 0, 0, 0, 0, 0,   // 0x70 - 0x7F
    0, 0, 0, 0, 'i', 'k', 0, 0, 'd', 'x', 0, 0, 0, 0, 0, 0,   // 0x80 - 0x8F
    0, 0, 0, 0, '\'', 0, 0, 0, 'b', 'h', 0, 0, 0, 0, 0, 0,   // 0x90 - 0x9F
    0, 0, 0, 0, '/', 'l', 0, 0, 'v', 'f', 0, 0, 0, 0, 0, 0,   // 0xA0 - 0xAF
    'z', 's', 0, 0, ']', USB_KBD_CR, 0, 0, 'j', 'm', 0, 0, 0, 0, 0, 0,   // 0xB0 - 0xBF
    0, 0, 0, 0, '9', 0, 0, 0, '3', 0, 0, 0, 0, USB_KBD_BS, 0, 0,   // 0xC0 - 0xCF
    '1', 0, 0, 0, 0, 0, 0, 0, 0, '6', 0, 0, USB_KBD_ESC, 0, 0, 0,   // 0xD0 - 0xDF
    '`', 0, 0, 0, 0, '-', 0, 0, 0, '5', 0, 0, 0, 0, 0, 0,   // 0xE0 - 0xEF
    0, '2', 0, 0, 0, 0, 0, 0, '8', 0, 0, 0, 0, 0, 0, 0    // 0xF0 - 0xFF
  };
  std::copy(newKeyMap, newKeyMap + KEYMAP_SIZE, _keyMap);
}

char USBKeyboardMapper::translate(uint32_t code) {
  if (code >= KEYMAP_SIZE) {
    return 0;
  }
  return _keyMap[code];
}

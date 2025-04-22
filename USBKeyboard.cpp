#include "USBKeyboard.h"

#define KEYBOARD_BUFFER_SIZE    16        // Maximum number of key entries to store in buffer
#define USB_CHAR_GAP_MS         16        // Timeout in milliseconds for deciding if the code for a key has been completely read
#define MAX_SCAN_CODE_BITS      32        // Maximum number of bits to read for a single key
#define CHAR_MASK               0xFF      // Bit mask to remove start and stop bits from key code

static uint8_t  _kbdClockPin = 0;
static uint8_t  _kbdDataPin = 0;

static uint32_t _prevCheckMs;             // Time of last check for end of key code
static uint32_t _partialScanCode;         // Storage for bits of key code read so far
static uint16_t _bitCount;                // Number of bits read for current key code

typedef struct {                          // Structure used for storing key codes in array
  uint32_t    data;
  uint16_t    size;
} KeyboardData;

// Array of key key codes read. Key codes are removed from position 0 of this array
KeyboardData    _kbdData[KEYBOARD_BUFFER_SIZE];
uint16_t        _kbdDataCount = 0;        // Number of key codes currently sotred in array


// Check if the last bit of the key code has been read from the USB port
static void IRAM_ATTR _checkForEndOfCode() {
  if ((millis() - _prevCheckMs) > USB_CHAR_GAP_MS) {
    if (_bitCount > 0) {
      _kbdData[_kbdDataCount].data = _partialScanCode;
      _kbdData[_kbdDataCount++].size = (_bitCount < MAX_SCAN_CODE_BITS) ? _bitCount : MAX_SCAN_CODE_BITS;
      _partialScanCode = 0;
      _bitCount = 0;
    }
  }
  _prevCheckMs = millis();
}

// Clock pin interrupt handler.
// Read bit from the data input pin and add to the ppartial character
static void IRAM_ATTR _USBClockInterrupt()
{
  _checkForEndOfCode();
  if (_bitCount < MAX_SCAN_CODE_BITS) {
    _partialScanCode <<= 1;
    _partialScanCode |= digitalRead(_kbdDataPin);
    _bitCount++;
  }
}

USBKeyboard::USBKeyboard() {}

// Initialise input pins used and setup interrupt handler
void USBKeyboard::begin(uint8_t clockPin, uint8_t dataPin) {
  _kbdClockPin = clockPin;
  pinMode(_kbdClockPin, INPUT);
  _kbdDataPin = dataPin;
  pinMode(_kbdDataPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(_kbdClockPin), _USBClockInterrupt, FALLING);
  reset();
}

// Reset everything
void USBKeyboard::reset() {
  _prevCheckMs = millis();
  _kbdDataCount = 0;
  _partialScanCode = 0;
  _bitCount = 0;
  delay(100);
}

// Get the code for the next key that was pressed
uint32_t USBKeyboard::getCode() {
  uint32_t  retValue = 0;
  uint32_t  dataMask = 0;

  _checkForEndOfCode();
  if (_kbdDataCount > 0) {
    retValue = _kbdData[0].data >> 1;
    int maskSize = _kbdData[0].size - 3;
    for (int ix = 0; ix < maskSize; ix++) {
      dataMask <<= 1;
      dataMask |= 1;
    }
    retValue &= dataMask;
    for (uint16_t ix = 0; ix < _kbdDataCount - 1; ix++) {
      _kbdData[ix].data = _kbdData[ix + 1].data;
      _kbdData[ix].size = _kbdData[ix + 1].size;
    }
    _kbdDataCount--;
  }
  return retValue;
}

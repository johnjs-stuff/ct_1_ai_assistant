#define CLOCK_PIN 37 //D-
#define DATA_PIN 38  //D+

const char *CURSOR_STR = "_";
const char *BLANK_CURSOR_STR = " ";

#include "SPI.h"
#include "TFT_eSPI.h"

#include "USBKeyboard.h"
#include "USBKeyboardMapper.h"
#include "PromptHandler.h"
#include "OpenAIClient.h"
#include "ResponseHandler.h"

#include "MySecrets.h"                                // Change the values in this file to set the values of the secrets you really shouldn't share with the internet
char *ssid = WIFI_SSID;
char *password = WIFI_PASSWORD;
char *apiKey = OPENAI_APIKEY;

bool isCursorShowing = false;                         // Flag to assist with blinking cursor effect

USBKeyboard kbd = USBKeyboard();                      // USB keyboard reader class
USBKeyboardMapper mapper = USBKeyboardMapper();       // Class to map keyboard scancode to ASCII character
PromptHandler prompt = PromptHandler();               // Class to handle the prompt entered using the keyboard
OpenAIClient aiClient = OpenAIClient();               // OpenAI client
ResponseHandler responseHandler = ResponseHandler();  // Class to handle extracting reply message from response returned by OPenAI
TFT_eSPI tft = TFT_eSPI();                            // TFT screen handler

void setup() {
  Serial.begin(115200);

  // Setup the USB keyboard reader
  kbd.begin(CLOCK_PIN, DATA_PIN);

  // Setup the TFT sceeen
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);
  tft.setTextWrap(true, false);
  tft.setTextFont(2);
  tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);

  // Setup the WiFi connection
  connectToWifi();

  // Setup the OpenAI client
  if (aiClient.begin(apiKey, DEFAULT_TIMEOUT)) {
    Serial.println("Connected to OpenAI.");
  } else {
    Serial.println("Failed to conect to OpenAI.");
  }
  Serial.println("OpenAI assistant started.");
}

void connectToWifi() {
  // WiFi connection parameters
  WiFi.begin(ssid, password);

  // Wait for Wifi connect to complete
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  return;
}

void loop()
{
  uint32_t scanCode;
  char keyedChar;
  uint8_t keyedCharNo;
  static bool showCursor = true;

  // Read any scancodes in the keyboard queue
  while ((scanCode = kbd.getCode()) != 0) {

    // Map the scancode to an ASCII character
    keyedChar = mapper.translate(scanCode);

    // Set flag to show cursor after ever key is pressed
    showCursor = true;
    if (keyedChar == USB_KBD_BS) {
      // Backspace entered. Remove last entered character.
      prompt.removeLastChar();
      showPrompt(prompt.getText());

    } else if (keyedChar == USB_KBD_CR) {
      // Return entered. Send the entered text to OpenAI
      sendAiRequest(prompt.getText());
      // Clear the entered text
      prompt.reset();
      // Ignore any keys entered after the return key
      kbd.reset();
      // Prevent the cursor from being shown after response from OpenAI is displayed until another key is pressed on the keyboard
      showCursor = false;

    } else if (!isControl(keyedChar)) {
      // If the entered key is for a printable character. Add the character to the text to be sent to OpenAI.
      prompt.addChar(keyedChar);
      showPrompt(prompt.getText());
    }
  }
  if (showCursor) {
    // Blink the cursor if needed.
    blinkCursor();
  }

  // A short delay to make sure everything works as expected.
  delay(32);
}

void showPrompt(char *text) {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.print(text);
  return;
}

// Show and hide an '_' character at the end of the entered text to give the appearance of a blinking cursor.
void blinkCursor() {
  uint32_t ms = millis();
  uint16_t cursorX = tft.getCursorX();
  uint16_t cursorY = tft.getCursorY();

  // Blink roughly every 1/2 second
  if (ms & 0x200) {
    if (!isCursorShowing) {
      // Display a '_' character at the end of the entered prompt
      tft.drawString(CURSOR_STR, cursorX, cursorY, 2);
      isCursorShowing = true;
    }
  } else {
    if (isCursorShowing) {
      // Overwrite the displayed '_' character at the end of the entered prompt with a blank
      tft.drawString(BLANK_CURSOR_STR, cursorX, cursorY, 2);
      isCursorShowing = false;
    }
  }
  return;
}

void sendAiRequest(char *prompt) {
  String response = aiClient.getResponseForRequest(prompt);
  responseHandler.loadResponse(response);
  const char *messageContent = responseHandler.getMessageContent();
  showResponseMessage(messageContent);
  return;
}

void showResponseMessage(const char *message) {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.print(message);
  return;
}

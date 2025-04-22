#ifndef OPENAICLIENT_H
#define OPENAICLIENT_H

#include <Arduino.h>
#include <WiFi.h>              // For ESP32 (Use <ESP8266WiFi.h> for ESP8266)
#include <WiFiClientSecure.h>

#define   DEFAULT_TIMEOUT 30000       // Default timeout for request in ms

class OpenAIClient {
  private:
    const char *_url = "/v1/chat/completions";
    const char *_server = "api.openai.com";
    char *_apiKey;
    uint16_t _timeout;

  public:
    OpenAIClient();

    // Initialise the object with the API key and a timeout value
    bool begin(char *openAIApiKey, uint16_t timeOut);

    // Send a prompt to OpenAI and return the reply as a String
    String getResponseForRequest(char *prompt);
};

#endif /* OPENAICLIENT_H */

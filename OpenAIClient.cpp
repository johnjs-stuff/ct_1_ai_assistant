#include "OpenAIClient.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

OpenAIClient::OpenAIClient () {}

bool OpenAIClient::begin(char *apiKey, uint16_t timeout) {
  _apiKey = apiKey;
  _timeout = timeout;
  return(true);
}

String OpenAIClient::getResponseForRequest(char *prompt) {
  String response = "";

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    // Specify the URL and headers
    http.begin("https://" + String(_server) + String(_url));

    // Set the request headers
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String(_apiKey));

    // Create the JSON payload for the HTTP request
    DynamicJsonDocument doc(2048);
    doc["model"] = "gpt-3.5-turbo";

    // Create the OpenAI request payload
    DynamicJsonDocument messagesDoc(1024);
    messagesDoc["role"] = "user";
    messagesDoc["content"] = prompt;

    // Add the OpenAI request to the HTTP request payload
    JsonArray messagesArray = doc.createNestedArray("messages");
    messagesArray.add(messagesDoc);

    // Serialise and send the payload to OpenAI using HTTP
    String payload;
    serializeJson(doc, payload);
    int httpResponseCode = http.POST(payload);

    // Check the response.
    if (httpResponseCode > 0) {
      // Response OK. Get the response string from HTTP
      response = http.getString();
    } else {
      // Response error. Return the error code.
      response = "HTTP Error: " + String(httpResponseCode);
    }
  } else {
    response = "Not connected to WiFi.";
  }
  return(response);
}

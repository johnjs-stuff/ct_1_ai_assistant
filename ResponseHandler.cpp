#include "ResponseHandler.h"

ResponseHandler::ResponseHandler() { }

void ResponseHandler::loadResponse(String response) {
  _error = deserializeJson(_doc, response.c_str());
  return;
}

const char *ResponseHandler::getMessageContent() {
  if (_error) {
    Serial.print("ResponseHandler error: ");
    Serial.println(_error.c_str());
    return(_error.c_str());
  }

  JsonDocument choicesDoc = _doc["choices"][0];
  if (choicesDoc == NULL) {
    return("No data returned.");
  }

  const char *returnStr = choicesDoc["message"]["content"];
  if (returnStr == NULL) {
    return("No message returned.");
  }
  
  return (returnStr);
}

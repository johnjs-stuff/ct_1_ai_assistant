#ifndef RESPONSEHANDLER_H
#define RESPONSEHANDLER_H

#include <Arduino.h>
#include <ArduinoJson.h>

class ResponseHandler {
  private:
    JsonDocument _doc;
    DeserializationError _error;

  public:
    ResponseHandler();

    // Parse the response into a JsonDocument object
    void loadResponse(String response);

    // Get the contents of the message returned from OpenAI
    const char *getMessageContent();
};

#endif /* RESPONSEHANDLER_H */

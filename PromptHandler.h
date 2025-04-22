#ifndef PROMPTHANDLER_H
#define PROMPTHANDLER_H

#include <Arduino.h>

#define     MAX_PROMPT_SIZE     256

class PromptHandler {
  private:
    char        _text[MAX_PROMPT_SIZE];
    uint16_t    _textCount;

  public:
    PromptHandler();

    // Reset the prompt to be empty
    void        reset();

    // Add the given character to the prompt text
    bool        addChar(char newChar);

    // Remove the last character from the prompt text
    void        removeLastChar();

    // The the prompt text as a character string
    char        *getText();
};

#endif /* PROMPTHANDLER_H */

#include "PromptHandler.h"

PromptHandler::PromptHandler() {
  reset();
}

void PromptHandler::reset() {
  _textCount = 0;
  for (int ix = 0; ix < MAX_PROMPT_SIZE; ix++) {
    _text[ix] = '\0';
  }
}

bool PromptHandler::addChar(char newChar) {
  if (_textCount < MAX_PROMPT_SIZE) {
    _text[_textCount++] = newChar;
    return(true);
  } else {
    return(false);
  }
}

void PromptHandler::removeLastChar() {
  if (_textCount > 0) {
    _text[--_textCount] = '\0';
  }
  return;
}

char *PromptHandler::getText() {
  return(_text);
}

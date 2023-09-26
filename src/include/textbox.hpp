#pragma once

#include <string>

class TextBox {
  public:
    int x, y, width, height;
    std::string text;

    unsigned int cursorPosition;

    std::string fontPath;
    int fontSize;

    TextBox(int x, int y, int width, int height, std::string text = "") {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->text = text;

        this->cursorPosition = 0;

        this->fontPath = "fonts/Ubuntu-Light.ttf";
        this->fontSize = 24;
    }

    void preventCursorOutOfBounds() {
        if (this->cursorPosition < 0)
            this->cursorPosition = 0;
        if (this->cursorPosition > this->text.size())
            this->cursorPosition = this->text.size();
    }
    void moveCursor(int direction) {
        this->cursorPosition += direction;
        this->preventCursorOutOfBounds();
    }
    void deleteCharacter() { this->text.erase(this->cursorPosition, 1); }
    void addCharacter(char character) { this->text.insert(this->cursorPosition, 1, character); }
};
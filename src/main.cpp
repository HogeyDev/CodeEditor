#include "constants.hpp"
#include "screen.hpp"
#include "textbox.hpp"
#include <iostream>

int main() {
    Screen *screen = new Screen();
    TextBox *text = new TextBox(20, 20, 400, 400);
    screen->addTextBox(text);
    while (true) {
        screen->draw();
        screen->processEvents();
        SDL_Delay(1000. / FRAMERATE);
    }
    return 0;
}
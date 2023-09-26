#pragma once

#include "color.hpp"
#include "constants.hpp"
#include "mouse.hpp"
#include "textbox.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <iostream>
#include <vector>

class Screen {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event e;
    std::vector<TextBox *> textBoxes;
    std::vector<int> framebuffer;

  public:
    Screen() {
        TTF_Init();
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &this->window, &this->renderer);
        this->framebuffer.resize(WIDTH * HEIGHT);
    }

    void pixel(int x, int y, int color = 0xffffffff) {
        if (x < WIDTH || x > 0 || y < HEIGHT || y > 0)
            this->framebuffer[y * WIDTH + x] = color;
    }
    void pixel(float x, float y, int color = 0xffffffff) { this->pixel((int)x, (int)y, color); }

    void rect(int x, int y, int width, int height, int color = 0xffffffff) {
        for (int dx = 0; dx < width; dx++) {
            for (int dy = 0; dy < height; dy++) {
                this->pixel(x + dx, y + dy, color);
            }
        }
    }
    void addTextBox(TextBox *textBox) { this->textBoxes.push_back(textBox); }

    Color *getColor(int hexColor) {
        Color *colorObject = new Color();
        colorObject->r = (hexColor >> 24) & 0xff;
        colorObject->g = (hexColor >> 16) & 0xff;
        colorObject->b = (hexColor >> 8) & 0xff;
        colorObject->a = (hexColor >> 0) & 0xff;
        return colorObject;
    }

    void draw() {
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->renderer);

        for (unsigned int i = 0; i < this->framebuffer.size(); i++) {
            Color *pixelColor = getColor(this->framebuffer.at(i));
            int x = i % WIDTH;
            int y = std::floor(i / WIDTH);
            SDL_SetRenderDrawColor(this->renderer, pixelColor->r, pixelColor->g, pixelColor->b, pixelColor->a);
            SDL_RenderDrawPointF(this->renderer, x, y);
        }

        for (auto &textBox : this->textBoxes) {
            SDL_Color color = {255, 255, 255};
            TTF_Font *font = TTF_OpenFont((const char *)(textBox->fontPath.c_str()), textBox->fontSize);
            SDL_Surface *text = TTF_RenderText_Blended(font, textBox->text.c_str(), color);
            if (text) {
                SDL_Texture *textTexture = SDL_CreateTextureFromSurface(this->renderer, text);
                SDL_Rect dest = {textBox->x, textBox->y, text->w, text->h};
                SDL_RenderCopy(this->renderer, textTexture, NULL, &dest);
            }
        }

        SDL_RenderPresent(renderer);
    }

    void processEvents() {
        while (SDL_PollEvent(&this->e)) {
            if (this->e.type == SDL_QUIT) {
                this->quit();
                exit(0);
            }
            if (this->e.type == SDL_KEYDOWN) {
                if (this->e.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
                    this->textBoxes.at(0)->deleteCharacter();
                else
                    this->textBoxes.at(0)->addCharacter(this->e.key.keysym.sym);
            }
        }
    }
    void quit() {
        SDL_Quit();
        TTF_Quit();
    }
};
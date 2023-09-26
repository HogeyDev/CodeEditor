#pragma once

class Color {
  public:
    int r;
    int g;
    int b;
    int a;
    Color() {
        this->r = 0;
        this->g = 0;
        this->b = 0;
        this->a = 0;
    }
    Color(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 0;
    }
    Color(int r, int g, int b, int a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};
#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

struct SelectableBox {
    SDL_Rect rect;
    bool selected;
    std::string text;

    SelectableBox() : rect({0, 0, 0, 0}), selected(false), text("") {}

    SelectableBox(int x, int y, int w, int h, const std::string& text) : rect({x, y, w, h}), selected(false), text(text) {}
};

class startScreen {
public:
    startScreen(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~startScreen();
    
    void render();
    void handleInput(const SDL_Event& event);
    
    bool start(int mouseX, int mouseY);
    
    void moveSelection(int direction);
    void selectBox(int index);
    int getSelected() const;

private:
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    TTF_Font* font;
    SDL_Color textColor;
    
    int screenWidth;
    int screenHeight;
    int selected;

    SelectableBox boxes[4];
};

#endif
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
    
    bool start(int mouseX, int mouseY);
    
    void renderText(const std::string& text, const SDL_Color& color, int x, int y);
    
    void moveSelection(int direction);
    void selectBox(int index);
    
    int getSelected() const { return selected; }
    bool getInstruct() const { return instruct; }
	const SDL_Rect& getClose() const { return close; }
    
    void setSelected(int i);
    void setInstruct(bool i);
    
    const SelectableBox* getBoxes() const;
	
private:
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    TTF_Font* font;
    SDL_Color textColor;
    
    int screenWidth;
    int screenHeight;
    int selected;
    
    bool instruct;
	
    SelectableBox boxes[4];
    SDL_Rect close; // Rectangle for the close button
};
	
#endif
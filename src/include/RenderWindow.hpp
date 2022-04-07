#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils.hpp"

class RenderWindow{
    public:
        RenderWindow(const char* p_title,int p_w,int p_h);
        SDL_Texture* loadTexture(const char* p_filePath);
        void cleanUp();
        void clear();
        int getRefreshRate();
        SDL_Renderer* getRenderer();
        void display();
        void setColor(int r,int g,int b,int a);
        void drawMandelbrot(utils::complex &c,float &rMod,float &gMod,float &bMod,double &iStep,double &rStep,double &viewPosX,double &viewPosY,int steps);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};
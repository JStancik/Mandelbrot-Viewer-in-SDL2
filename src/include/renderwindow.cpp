
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title,int p_w,int p_h):window(NULL), renderer(NULL){
    window=SDL_CreateWindow(p_title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,p_w,p_h,SDL_WINDOW_SHOWN);

    if(window==NULL){
        std::cout << "Window failed to init. Error: " << SDL_GetError << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer,p_filePath);

    if(texture==NULL){
        std::cout<<"Failed to load texture. Error: "<<SDL_GetError()<<std::endl;
    }

    return texture;
}

int RenderWindow::getRefreshRate(){
    int displayIndex = SDL_GetWindowDisplayIndex( window );

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex,0,&mode);

    return mode.refresh_rate;
}

SDL_Renderer* RenderWindow::getRenderer(){
    return renderer;
}

void RenderWindow::clear(){
    SDL_RenderClear(renderer);
}

void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp(){
    SDL_DestroyWindow(window);
}

void RenderWindow::setColor(int r,int g,int b,int a){
    SDL_SetRenderDrawColor(renderer,r,g,b,a);
}

void RenderWindow::drawMandelbrot(utils::complex &c,float &rMod,float &gMod,float &bMod,double &iStep,double &rStep,double &viewPosX,double &viewPosY,int steps){
    utils::complex temp(0,0);
    for(int i=0;i<1080;i++){
        for(int j=0;j<1080;j++){
            utils::complex z(0,0);
            bool bounded = true;
            int k;
            for(k=0;k<steps;k++){
                temp = z*z;
                temp += c;
                z = temp;
                if(z.imaginary>2||z.imaginary<-2||z.real>2||z.real<-2){
                    bounded = false;
                    break;
                }
            }
            if(bounded){
                setColor(0,0,0,255);
                SDL_RenderDrawPoint(renderer,i,j);
            }
            else{
                setColor(255-k*rMod,255-k*gMod,255-k*bMod,255);
                SDL_RenderDrawPoint(renderer,i,j);
            }
            c.imaginary += iStep;
        }
        c.imaginary = viewPosY;
        c.real += rStep;
    }

    c.real = viewPosX;
    c.imaginary = viewPosY;

    std::cout<<"rendered"<<std::endl;
}
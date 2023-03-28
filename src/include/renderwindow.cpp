
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

void RenderWindow::drawMandelbrot(utils::complex &c,int &rMod,int &gMod,int &bMod,double &iStep,double &rStep,double &viewPosX,double &viewPosY,int &steps,bool &isBlack,int &width,int &height){
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            utils::complex z(0,0);
            bool bounded = true;
            int k;
            for(k=0;k<steps;k++){
                z = (z*z)+c;
                if(z.real*z.real+z.imaginary*z.imaginary>=4){
                    bounded = false;
                    break;
                }
            }
            if(bounded){
                if(isBlack)
                    setColor(0,0,0,255);
                else
                    setColor(-abs((k+1)*rMod%510-255)+255,-abs((k+1)*gMod%510-255)+255,-abs((k+1)*bMod%510-255)+255,255);
                SDL_RenderDrawPoint(renderer,i,j);
            }
            else{
                setColor(-abs(k*rMod%510-255)+255,-abs(k*gMod%510-255)+255,-abs(k*bMod%510-255)+255,255);
                SDL_RenderDrawPoint(renderer,i,j);
            }
            c.imaginary += iStep;
        }
        c.imaginary = viewPosY;
        c.real += rStep;
    }

    c.real = viewPosX;
    c.imaginary = viewPosY;

    std::cout<<"-------rendered-------"<<std::endl;
    std::cout<<"position: ("<<viewPosX<<", "<<viewPosY<<")"<<std::endl;
    std::cout<<"iterations: "<<steps<<std::endl;
    std::cout<<"step per pixel (r/i): ("<<rStep<<" / "<<iStep<<")"<<std::endl;
    std::cout<<"zoom: "<<rStep*540<<std::endl;
    std::cout<<"coloring: "<<rMod<<", "<<gMod<<", "<<bMod<<std::endl;
}

void RenderWindow::drawJulia(utils::complex &z,int &rMod,int &gMod,int &bMod,double &iStep,double &rStep,double &viewPosX,double &viewPosY,int &steps,bool &isBlack,int &width,int &height,utils::complex &c){
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            bool bounded = true;
            int k;
            for(k=0;k<steps;k++){
                z = z*z;
                z = z+c;
                if((z.real*z.real+z.imaginary*z.imaginary) > (double)4){
                    bounded = false;
                    break;
                }
            }
            if(bounded){
                if(isBlack)
                    setColor(0,0,0,255);
                else
                    setColor(-abs((k+1)*rMod%510-255)+255,-abs((k+1)*gMod%510-255)+255,-abs((k+1)*bMod%510-255)+255,255);
                SDL_RenderDrawPoint(renderer,i,j);
            }
            else{
                setColor(-abs(k*rMod%510-255)+255,-abs(k*gMod%510-255)+255,-abs(k*bMod%510-255)+255,255);
                SDL_RenderDrawPoint(renderer,i,j);
            }
            z.imaginary = viewPosY+iStep*(j+1);
            z.real = viewPosX+(i+1)*rStep;
        }
        z.imaginary = viewPosY;
        z.real = viewPosX+(i+1)*rStep;
    }

    z.real = viewPosX;
    z.imaginary = viewPosY;

    std::cout<<"-------rendered-------"<<std::endl;
    std::cout<<"position: ("<<viewPosX<<", "<<viewPosY<<")"<<std::endl;
    std::cout<<"iterations: "<<steps<<std::endl;
    std::cout<<"step per pixel (r/i): ("<<rStep<<" / "<<iStep<<")"<<std::endl;
    std::cout<<"zoom: "<<rStep*540<<std::endl;
    std::cout<<"coloring: "<<rMod<<", "<<gMod<<", "<<bMod<<std::endl;
}
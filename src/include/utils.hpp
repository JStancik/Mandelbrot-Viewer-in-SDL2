#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <iostream>

namespace utils{
    //______________________TIME________________________
    inline float getTimeSec(){
        return SDL_GetTicks()*0.001f;
    }
    
    class complex{
        public:
            double real;
            double imaginary;
            complex(double r, double i){
                real = r;
                imaginary = i;
            }
            complex(){}
            complex operator + (const complex& c){
                complex temp;
                temp.real = real+c.real;
                temp.imaginary = imaginary + c.imaginary;
                return temp;
            }

            complex operator * (const complex& c){
                return complex(real*c.real-imaginary*c.imaginary,real*c.imaginary+imaginary*c.real);
            }

            void operator = (const complex& c){
                real = c.real;
                imaginary = c.imaginary;
            }

            void operator+= (const complex& c){
                real += c.real;
                imaginary += c.imaginary;
            }
    };

    void save_image(const std::string filename, SDL_Renderer* renderer,int w,int h) {
        SDL_Surface *sshot = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
        SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
        IMG_SavePNG(sshot, filename.c_str());
        SDL_FreeSurface(sshot);
    }
}
#pragma once

#include <vector>
#include <SDL2/SDL.h>
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
}
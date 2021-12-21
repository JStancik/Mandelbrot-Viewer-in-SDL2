#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "renderwindow.cpp"
#include "utils.hpp"

int main(int argc, char* args[])
{
    //SDL init
    if(SDL_Init(SDL_INIT_VIDEO) > 0){
        std::cout << "SDL_Init FAILED. ERROR: " << SDL_GetError() << std::endl;
    }

    if(!(IMG_Init(IMG_INIT_PNG))){
        std::cout << "IMG_Init FAILED. ERROR: " << SDL_GetError() << std::endl;
    }
    
    const int SCREEN_WIDTH = 1080;

    const int SCREEN_HEIGHT = 1080;

    RenderWindow window("Mandelrot",SCREEN_WIDTH,SCREEN_HEIGHT);
    int windowRefreshRate = 1000/window.getRefreshRate();

    bool running = true;
    const float timestep = 0.01f;
    float accumTime;
    float currentTime = 0.0f;

    utils::complex c(-2,-2);

    double rStep = 4.0/1080;
    double iStep = 4.0/1080;

    int steps = 1;

    bool rStepP = false;
    bool rStepN = false;
    bool iStepP = false;
    bool iStepN = false;

    double viewPosX = -2;
    double viewPosY = -2;

    bool viewPosXP = false;
    bool viewPosXN = false;
    bool viewPosYP = false;
    bool viewPosYN = false;


    float rMod = 0;
    float gMod = 0;
    float bMod = 0;

    bool isRP = false;
    bool isGP = false;
    bool isBP = false;

    bool isRN = false;
    bool isGN = false;
    bool isBN = false;

    bool change = true;

    SDL_Event event;

    while(running){

        int startTicks = SDL_GetTicks();
        float newTime = utils::getTimeSec();
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        accumTime += frameTime;
        
        while(accumTime>=timestep){
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    running = false;    
                }
                else if(event.type == SDL_KEYDOWN){
                    switch(event.key.keysym.sym){
                        case SDLK_q:
                            running = false;
                            break;
                        case SDLK_o:
                            isRP = true;
                            break;
                        case SDLK_l:
                            isRN = true;
                            break;
                        case SDLK_i:
                            isGP = true;
                            break;
                        case SDLK_k:
                            isGN = true;
                            break;
                        case SDLK_u:
                            isBP = true;
                            break;
                        case SDLK_j:
                            isBN = true;
                            break;
                        case SDLK_w:
                            viewPosYN = true;
                            break;
                        case SDLK_a:
                            viewPosXN = true;
                            break;
                        case SDLK_s:
                            viewPosYP = true;
                            break;
                        case SDLK_d:
                            viewPosXP = true;
                            break;
                        case SDLK_UP:
                            iStepP = true;
                            rStepP = true;
                            break;
                        case SDLK_DOWN:
                            iStepN = true;
                            rStepN = true;
                            break;
                        case SDLK_r:
                            rStep = 4.0/1080.0;
                            iStep = 4.0/1080.0;
                            viewPosX = -2;
                            viewPosY = -2;
                            change = true;
                            break;
                        case SDLK_t:
                            change = true;
                            steps++;
                            break;
                        case SDLK_g:
                            if(steps>0){
                            change = true;
                            steps--;
                            }
                            break;
                    }
                }
                else if(event.type == SDL_KEYUP){
                    switch(event.key.keysym.sym){
                        case SDLK_o:
                            isRP = false;
                            break;
                        case SDLK_l:
                            isRN = false;
                            break;
                        case SDLK_i:
                            isGP = false;
                            break;
                        case SDLK_k:
                            isGN = false;
                            break;
                        case SDLK_u:
                            isBP = false;
                            break;
                        case SDLK_j:
                            isBN = false;
                            break;
                        case SDLK_w:
                            viewPosYN = false;
                            break;
                        case SDLK_a:
                            viewPosXN = false;
                            break;
                        case SDLK_s:
                            viewPosYP = false;
                            break;
                        case SDLK_d:
                            viewPosXP = false;
                            break;
                        case SDLK_UP:
                            iStepP = false;
                            rStepP = false;
                            break;
                        case SDLK_DOWN:
                            iStepN = false;
                            rStepN = false;
                            break;
                        
                    }
                }
            }
            accumTime -= timestep;
        }

        if(isRP){
            change = true;
            rMod += 1;
        }
        if(isRN){
            change = true;
            rMod -= 1;
        }
        if(isGP){
            change = true;
            gMod += 1;
        }
        if(isGN){
            change = true;
            gMod -= 1;
        }
        if(isBP){
            change = true;
            bMod += 1;
        }
        if(isBN){
            change = true;
            bMod -= 1;
        }
        if(iStepP){
            change = true;
            iStep += iStep*2;
        }
        if(iStepN){
            change = true;
            iStep -= iStep/2;
        }
        if(rStepP){
            change = true;
            rStep += rStep*2;
        }
        if(rStepN){
            change = true;
            rStep -= rStep/2;
        }
        if(viewPosXP){
            change = true;
            viewPosX += 1080/2*rStep;
        }
        if(viewPosXN){
            change = true;
            viewPosX -= 1080/2*rStep;
        }
        if(viewPosYP){
            change = true;
            viewPosY += 1080/2*iStep;
        }
        if(viewPosYN){
            change = true;
            viewPosY -= 1080/2*iStep;
        }



        if(change){
            window.clear();
            window.drawMandelbrot(c,rMod,gMod,bMod,iStep,rStep,viewPosX,viewPosY,steps);
            window.display();
        }
        change = false;
        
        

        int frameTicks = SDL_GetTicks()-startTicks;
        if(frameTicks<windowRefreshRate){
            SDL_Delay(windowRefreshRate-frameTicks);
        }
    }

    return 0;
}
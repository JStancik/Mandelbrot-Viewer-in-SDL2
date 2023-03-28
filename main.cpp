#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "src/include/renderwindow.cpp"
#include "src/include/utils.hpp"

int main(int argc, char* args[])
{
    std::cout<<"Type M for Mandelbrot or J for Julia set: ";
    std::string type;
    std::cin>>type;
    bool isJulia = type == "J";

    std::string w;
    std::cout<<"Enter width: ";
    std::cin>>w;
    std::string h;
    std::cout<<"Enter height: ";
    std::cin>>h;
    std::cout<<"("+w+", "+h+")"<<std::endl;

    int width = std::stoi(w);
    int height = std::stoi(h);

    std::string x;
    std::cout<<"Enter X step: ";
    std::cin>>x;
    std::string y;
    std::cout<<"Enter Y step: ";
    std::cin>>y;
    std::cout<<"("+x+", "+y+")"<<std::endl;

    int xStep = std::stoi(x);
    int yStep = std::stoi(y);

    std::cout<<"Enter complex X: ";
    std::cin>>x;
    std::cout<<"Enter complex Y: ";
    std::cin>>y;

    double xComplex = std::stod(x);
    double yComplex = std::stod(y);
    utils::complex julia = utils::complex(xComplex,yComplex);
    if(isJulia){

        std::cout<<"Enter complex change X: ";
        std::cin>>x;
        std::cout<<"Enter complex change Y: ";
        std::cin>>y;

        xComplex = std::stod(x);
        yComplex = std::stod(y);
    }
    std::cout<<"would you like to initalize a position?: ";
    std::string initAns;
    std::cin>>initAns;
    double viewPosX;
    double viewPosY;
    double rStep;
    double iStep;      
    int steps;
    if(initAns=="y"){
        std::string input;
        std::cout<<"Enter x Pos: ";
        std::cin>>input;
        viewPosX = std::stod(input);
        std::cout<<"Enter y Pos: ";
        std::cin>>input;
        viewPosY = std::stod(input);
        std::cout<<"Enter zoom : ";
        std::cin>>input;
        rStep = std::stod(input)/540.0;
        iStep = std::stod(input)/540.0;
        std::cout<<"Enter steps: ";
        std::cin>>input;
        steps = std::stoi(input);
    }
    else{
        viewPosX = -2;
        viewPosY = -2;
        rStep = 4.0/1080;
        iStep = 4.0/1080;      
        steps = 1;
    }
    
    //SDL init
    if(SDL_Init(SDL_INIT_VIDEO) > 0){
        std::cout << "SDL_Init FAILED. ERROR: " << SDL_GetError() << std::endl;
    }

    if(!(IMG_Init(IMG_INIT_PNG))){
        std::cout << "IMG_Init FAILED. ERROR: " << SDL_GetError() << std::endl;
    }
    
    

    RenderWindow window("Fractal",width,height);
    int windowRefreshRate = 17;
    std::cout<<"c1";
    bool running = true;
    const float timestep = 0.01f;
    float accumTime;
    float currentTime = 0.0f;

    utils::complex cNum(-2,-2);

    int rMod = 0;
    int gMod = 0;
    int bMod = 0;

    bool isBlack = false;

    bool change = true;

    SDL_Event event;

    while(running){

        int startTicks = SDL_GetTicks();
        float newTime = utils::getTimeSec();
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;   
            }
            else if(event.type == SDL_KEYUP){
                change = true;
                switch(event.key.keysym.sym){
                    case SDLK_o:
                        rMod += 1;
                        break;
                    case SDLK_l:
                        rMod -= 1;
                        break;
                    case SDLK_i:
                        gMod += 1;
                        break;
                    case SDLK_k:
                        gMod -= 1;
                        break;
                    case SDLK_u:
                        bMod += 1;
                        break;
                    case SDLK_j:
                        bMod -= 1;
                        break;
                    case SDLK_w:
                        viewPosY -= yStep*iStep;
                        break;
                    case SDLK_a:
                        viewPosX -= xStep*rStep;
                        break;
                    case SDLK_s:
                        viewPosY += yStep*iStep;
                        break;
                    case SDLK_d:
                        viewPosX += xStep*rStep;
                        break;
                    case SDLK_q:
                        iStep = iStep*2;
                        rStep = rStep*2;
                        viewPosX -= width/4*rStep;
                        viewPosY -= height/4*iStep;
                        break;
                    case SDLK_z:
                        iStep = iStep/2;
                        rStep = rStep/2;
                        viewPosX += width/2*rStep;
                        viewPosY += height/2*iStep;
                        break;
                    case SDLK_r:
                        rStep = 4.0/1080.0;
                        iStep = 4.0/1080.0;
                        viewPosX = -2;
                        viewPosY = -2;
                        break;
                    case SDLK_e:
                        steps++;
                        break;
                    case SDLK_c:
                        if(steps>0)
                            steps--;
                        break;
                    case SDLK_b:
                        isBlack=!isBlack;
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_t:
                        julia.imaginary += yComplex;
                        break;
                    case SDLK_f:
                        julia.real -= xComplex;
                        break;
                    case SDLK_g:
                        julia.imaginary -= yComplex;
                        break;
                    case SDLK_h:
                        julia.real += xComplex;
                        break;
                    case SDLK_x:
                        utils::save_image("img"+std::to_string(cNum.real)+","+std::to_string(cNum.imaginary)+","+std::to_string(rMod)+","+std::to_string(gMod)+","+std::to_string(bMod)+","+std::to_string(iStep)+","+std::to_string(rStep)+","+std::to_string(viewPosX)+","+std::to_string(viewPosY)+","+std::to_string(steps)+","+std::to_string(isBlack)+","+std::to_string(width)+","+std::to_string(height)+","+std::to_string(julia.real)+","+std::to_string(julia.imaginary)+".png",window.getRenderer(),width,height);
                        break;
                }
            }
        }

        if(change){
            window.clear();
            if(isJulia){
                window.drawJulia(cNum,rMod,gMod,bMod,iStep,rStep,viewPosX,viewPosY,steps,isBlack,width,height,julia);
            }
            else{
                window.drawMandelbrot(cNum,rMod,gMod,bMod,iStep,rStep,viewPosX,viewPosY,steps,isBlack,width,height);
            }
            window.display();
        }

        int frameTicks = SDL_GetTicks()-startTicks;
        if(frameTicks<windowRefreshRate){
            SDL_Delay(windowRefreshRate-frameTicks);
        }
    }

    return 0;
}
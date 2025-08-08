#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

Game::Game(){
    isRunning = false;
    std::cout<<"Game Constructor called!"<<std::endl;
}

Game::~Game(){
    std::cout<<"Game Destructor called!"<<std::endl;
}

void Game::Initialize(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr<<"Error Initializing SDL."<<std::endl;
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0,&displayMode);
    // but in last full screen me hi 800 by 600 hi rahega
    windowWidth = 800; //displayMode.w;                // for width
    windowHeight = 600; //displayMode.h;               // for height

    // if all ok then we will create window in operating system
    window = SDL_CreateWindow(NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS
    );

    if(!window){
        std::cerr<<"Error creating SDL window"<<std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window ,-1,0);
    if(!renderer){
        std::cerr<<"Error Creating SDl renderer."<<std::endl;
        return;
    }

    SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
    isRunning = true;
}


void Game::ProcessInput(){
    // pressing the esc key means leaving the window
    SDL_Event sdlEvent;
    // this will include all the addresses of sdlEvent
    while(SDL_PollEvent(&sdlEvent)){
        switch(sdlEvent.type){
            // every time when user try to close window
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if(sdlEvent.key.keysym.sym == SDLK_ESCAPE){
                    isRunning = false;
                }
                break;
        }
    }                
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::setup(){
    // Initialixing game object like position colour ...
    // playerPosition.x = 10.0;
    // playerPosition,y = 20.0;
    playerPosition = glm::vec2(10.0,20.0);
    playerVelocity = glm::vec2(1.0,0.0);
}

void Game::Update(){
    playerPosition.x += playerVelocity.x;
    playerPosition.y += playerVelocity.y;
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer,21,21,21,255);              // background now gray
    SDL_RenderClear(renderer);

    // // drawing a rectangle
    // // from top x and y position it will start with width and height
    // SDL_SetRenderDrawColor(renderer,255,255,255,255);
    // SDL_Rect player = {10,10,20,20};
    // SDL_RenderFillRect(renderer,&player);

    // we need to Load a PNG texture now 
    SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");                        // under this fucntion i have to put file path
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);                                                                       // destroying the surface


    // in rendercopy 3rd variable NULL is because for entire section now renderer
    SDL_Rect dstRect = {
        static_cast<int> (playerPosition.x) , 
        static_cast<int> (playerPosition.y) ,
        32 , 
        32
    };                     // first 2 are positon from where rect is started and other two are width and height
    SDL_RenderCopy(renderer,texture,NULL/*srcRect*/, &dstRect /*dstRect*/);

    SDL_DestroyTexture(texture);
    // we have 2 buffer front buffer and back buffer the front buffer is for showing the object other hand back 
    // buffer is for rendering the object need to showing 
    // to fix this glitch we need to use renderpresent function
    SDL_RenderPresent(renderer);
}

void Game::Run(){
    setup();
    while(isRunning){
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
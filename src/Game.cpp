#include "Game.h"
#include <SDL2/SDL.h>
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
    // if all ok then we will create window in operating system
    window = SDL_CreateWindow(NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
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

void Game::Update(){

}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void Game::Run(){
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
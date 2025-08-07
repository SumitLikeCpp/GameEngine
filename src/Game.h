#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game{
    private:
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;


    public:
        Game();
        ~Game();                                          // its a destructor
        void Initialize();
        void Run();
        void setup();
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();

        int windowWidth;
        int windowHeight;

};

#endif
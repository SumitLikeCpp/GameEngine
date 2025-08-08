#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

// some constant for fps
const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game{
    private:
        bool isRunning;
        int millisecsPreviousFrame = 0;
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
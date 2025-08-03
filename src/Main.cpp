#include "Game.h"

// argument counter and argument array value
int main(int argc,char* argv[]){
    
    // Game loop with Game class
    Game game;

    game.Initialize();
    game.Run();
    game.Destroy();
    
    return 0;
}
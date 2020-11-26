#include <SDL2/SDL.h>

int main(int argc, char *argv[]) 
{
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    int posX = 100, posY = 100, width = 1000, height = 1000;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

     SDL_RenderDrawLine(renderer,0,0,1000,1000);
       
    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            
            if (e.type == SDL_QUIT) {
                break;
            }
        } 
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}

if (a = 0 ?)
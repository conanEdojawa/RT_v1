#include "rtv1.h"

int     file(char *str)
{
    int fd;

    if ((fd = open(str, O_RDONLY)) < 0)
		return (-1);
    return (fd);
}

int main(int argc, char *argv[]) 
{
    if(argc == 2)
	{
        int fd;
        if ((fd = file(argv[1])) == -1)
            {
                ft_putendl("error in file openin");
                return (0);
            }

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
    }
	else
	    ft_putendl("usage: ./rtv1 scene_file");
    return 0;
}
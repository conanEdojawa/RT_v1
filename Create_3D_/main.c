#include <stdio.h>
#include <SDL2/SDL.h>
#include "rt.h"
#include "vector.h"
#include "ray.h"
#include "sphere.h"

void SDL_ExitWithError(char *message);

int intersection(t_ray d, t_sph s, t_vect *p, t_vect *n)
{
    /*a*t^2 + bt + c = 0*/
    double a = 1;
    double b = 2 * vect_scal(d.direction, sub_vect(d.origine, s.origine));
    double c = get_norm_2(sub_vect(d.origine, s.origine)) - (s.rayon * s.rayon);

    double delta = b*b - 4*a*c;
    if(delta < 0)
        return -1;
    double t1 = (-b-sqrt(delta)) / 2*a;
    double t2 = (-b+sqrt(delta)) / 2*a;
    if(t2 < 0) /*pas d'intersection*/
        return -1;
    double t;
    if (t1 > 0)
        t = t1;
    else
        t = t2;
    *p = add_vect(d.origine, vect_mult_val(d.direction, t));
    *n = get_normalized(sub_vect(*p, s.origine));

    return 1;
}

int main(void)
{
    SDL_Window *win = NULL;
    SDL_Renderer *rend = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) != 0) //int SDL_Init(Uint32 flags), see documentation for more informations
		SDL_ExitWithError("initialisation SDL");
    
    win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
    if(win == NULL)
        SDL_ExitWithError("Creation window");
    
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(rend == NULL)
        SDL_ExitWithError("Creation render");
    
    if(SDL_SetRenderDrawColor(rend, 255, 100, 0, 255) != 0)
        SDL_ExitWithError("Get color failed");

    
    int i = 0;
    int j;
    /*rayon de vue*/
    t_ray r;
    t_vect orig_ray;
    t_vect direction;
    /*angle de champs visuel*/
    double helf_fov;
    /*objet sphere*/
    t_sph sphere;
    t_vect orig_sph;
    double rayon_sph;
    t_vect albedo;
    /*point lumineux*/
    t_vect lum_pos;
    double intensite_lum;

    helf_fov = 40 * PI / 180; /*fov : champs visuel horizontal*/
    init_vect(&orig_ray, 0, 0, 0); //camera
    init_vect(&orig_sph, 0, 0, -55);
    rayon_sph = 10;
    init_vect(&albedo, 1, 0, 0);
    init_sph(&sphere, orig_sph, rayon_sph, albedo);
    init_vect(&lum_pos, 35, 0, 30);
    intensite_lum = 1000000;

    t_vect p,n;
    t_vect intensite_pixel;
    while(i < WIN_W)
    {
        j = 0;
        
        while(j < WIN_H)
        {
            init_vect(&direction, i - (WIN_W / 2), j - (WIN_H / 2), -WIN_W / (2 * tan(helf_fov)));
            normalize(&direction);
            init_ray(&r, orig_ray, direction);
            int has_inter = intersection(r, sphere, &p, &n);
            zero_vect(&intensite_pixel);
            if(has_inter == 1)
            {
                intensite_pixel = vect_mult_val(sphere.color, intensite_lum * fmax(0, vect_scal(get_normalized(sub_vect(lum_pos, p)), n)) / get_norm_2(sub_vect(lum_pos, p)));
                if(SDL_SetRenderDrawColor(rend, fmin(255., fmax(0 ,intensite_pixel.x)), fmin(255., fmax(0 ,intensite_pixel.y)), fmin(255., fmax(0 ,intensite_pixel.z)), 255) != 0)
                    SDL_ExitWithError("Get color failed");
            }
            else
            {
                if(SDL_SetRenderDrawColor(rend, intensite_pixel.x, intensite_pixel.y, intensite_pixel.z, 255) != 0)
                    SDL_ExitWithError("Get color failed");
            }
            if(SDL_RenderDrawPoint(rend, i, j) != 0)
                SDL_ExitWithError("Draw point failed");
            j++;
        }
        i++;
    }

    SDL_RenderPresent(rend);

    SDL_bool prog_launched = SDL_TRUE;

    while(prog_launched)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    prog_launched = SDL_FALSE;
                    break;
                default:
                    continue;
            }
        }
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

void SDL_ExitWithError(char *message)
{
	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError()); //void SDL_Log(const char* format);
	SDL_Quit();
	exit(-1);
}
#include "../header/rt.h"


void SDL_ExitWithError(char *message);

int intersection_sphere(t_ray d, t_sph s, t_vect *hitPoint, t_vect *normal)
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
    *hitPoint = add_vect(d.origine, vect_mult_val(d.direction, t));
    *normal = get_normalized(sub_vect(*hitPoint, s.origine));

    return 1;
}

int intersection_plan(t_ray d, t_plane pl , t_vect *hitPoint, t_vect *normal)
{
    /*at + b = 0*/
    /*t = <(pl.ref - d.origine) , pl.direction> / <d.direction , pl.direction>*/
    double denominator = vect_scal(d.direction, pl.direction);
    if(denominator > 0.000001)
    {
        double t = vect_scal(sub_vect(pl.ref, d.origine), pl.direction) / denominator;
        if (t < 0) // plane behind ray's origin
            return (-1);
        *hitPoint = add_vect(d.origine, vect_mult_val(d.direction, t));
        *normal = pl.direction;
        return (1);
    }
    return (-1);
}

    /*
    cy->rayon = rayon;
    cy->lenght = lenght;
    cy->ref = ref;
    cy->axis_o = axis_o;
    cy->axis_dir = axis_dir;
    cy->color = color;
    */

int intersection_cylindre(t_ray d, t_cylindre cy)
{
    /*a*t^2 + bt + c = 0*/
    double a = sub_vect(d.direction, vect_mult_val(cy.axis_dir ,vect_scal(d.direction, cy.axis_dir)));
    double b = vect_scal(sub_vect(d.direction, vect_mult_val(cy.axis_dir, vect_scal(d.direction, cy.axis_dir))), sub_vect(sub_vect(d.origine, cy.axis_o), vect_mult_val(cy.axis_dir, vect_scal(sub_vect(d.origine, cy.axis_o), cy.axis_dir))));
    double c = ;
}

int main(int ac, char **av)
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
    /*objet palne*/
    t_plane pl;
    t_vect ref;
    t_vect dir;
    t_vect col;
    /*point lumineux*/
    t_vect lum_pos;
    double intensite_lum;

    helf_fov = 40 * PI / 180; /*fov : champs visuel horizontal*/
    init_vect(&orig_ray, 0, 0, 0); //camera
    init_vect(&orig_sph, 0, 0, -40);

    init_vect(&ref, 0, 0, -40);
    init_vect(&dir, 0, 1, 0);
    rayon_sph = 10;
    init_vect(&albedo, 0.3, 0.3, 0.3);

    init_vect(&col, 0, 1, 0);

    init_sph(&sphere, orig_sph, rayon_sph, albedo);
    
    init_pln(&pl, ref, dir);
    init_vect(&lum_pos, 40, 0, 30);
    intensite_lum = 1000000;

    t_vect p,n,p1,n1;
    t_vect intensite_pixel;
    while(i < WIN_W)
    {
        j = 0;
        
        while(j < WIN_H)
        {
            init_vect(&direction, i - (WIN_W / 2), j - (WIN_H / 2), -WIN_W / (2 * tan(helf_fov)));
            normalize(&direction);
            init_ray(&r, orig_ray, direction);
            int has_inter = intersection_sphere(r, sphere, &p, &n);
            int inter = intersection_plan(r, pl, &p1, &n1);
            zero_vect(&intensite_pixel);
            if(has_inter == 1)
            {
                intensite_pixel = vect_mult_val(sphere.color, intensite_lum * fmax(0, vect_scal(get_normalized(sub_vect(lum_pos, p)), n)) / get_norm_2(sub_vect(lum_pos, p)));
                if(SDL_SetRenderDrawColor(rend, fmin(255., fmax(0 ,intensite_pixel.x)), fmin(255., fmax(0 ,intensite_pixel.y)), fmin(255., fmax(0 ,intensite_pixel.z)), 255) != 0)
                    SDL_ExitWithError("Get color failed");
            }
            else if(inter == 1)
            {
                intensite_pixel = vect_mult_val(pl.color, intensite_lum * fmax(0, vect_scal(get_normalized(sub_vect(lum_pos, p1)), n1)) / get_norm_2(sub_vect(lum_pos, p1)));
                printf("%f", intensite_pixel.x);
                if(SDL_SetRenderDrawColor(rend, fmin(255., fmax(100 ,intensite_pixel.x)), fmin(255., fmax(100 ,intensite_pixel.y)), fmin(255., fmax(100 ,intensite_pixel.z)), 255) != 0)
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
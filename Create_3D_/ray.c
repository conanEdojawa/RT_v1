#include "ray.h"

void    init_ray(t_ray *r, t_vect origine, t_vect direc)
{
    r->origine = origine;
    r->direction = direc;
}
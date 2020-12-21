#include "../header/rt.h"

void    init_sph(t_sph *sph, t_vect o, double r, t_vect c)
{
    sph->origine = o;
    sph->rayon = r;
    sph->color = c;
}
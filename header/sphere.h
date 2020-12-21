#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"

typedef struct  s_sph
{
    t_vect  origine;
    double  rayon;
    t_vect  color;
}               t_sph;

void    init_sph(t_sph *sph, t_vect o, double r, t_vect c);

#endif
#ifndef RAY_H
#define RAY_H

#include "vector.h"

typedef struct  s_ray
{
    t_vect  origine; /*un point d'origine*/
    t_vect  direction;  /*un vecteur*/
}               t_ray;

void    init_ray(t_ray *r, t_vect origine, t_vect direc);
#endif
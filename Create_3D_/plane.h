#ifndef PLANE_H
#define PLANE_H

#include "vector.h"

typedef struct  s_plane
{
    t_vect     ref; //center plane
    t_vect     direction; //normale
}               t_plane;

void    init_pln(t_plane *pln, t_vect ref, t_vect direction);

#endif
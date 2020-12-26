#ifndef CYLYNDRE_H
#define CYLINDRE_H

#include "vector.h"

typedef struct s_cylindre
{
    double rayon;
    double lenght;
    t_vect axis_o;
    t_vect axis_dir;
    t_vect color;
}               t_cylindre;

void init_cyl(t_cylindre cy, double rayon, double lenght, t_vect axis_o, t_vect axis_dir, t_vect color);


#endif
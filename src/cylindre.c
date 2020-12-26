#include "../header/rt.h"

void init_cyl(t_cylindre *cy, double rayon, double lenght, t_vect axis_o, t_vect axis_dir, t_vect color)
{
    cy->rayon = rayon;
    cy->lenght = lenght;
    cy->axis_o = axis_o;
    cy->axis_dir = axis_dir;
    cy->color = color;
}
#include "plane.h"

void    init_pln(t_plane *pln, t_vect ref, t_vect direction)
{
    pln->ref = ref;
    pln->direction = direction;
}
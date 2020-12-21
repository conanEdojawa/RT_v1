#include "../header/rt.h"

void    init_pln(t_plane *plane, t_vect ref, t_vect direction)
{
	plane->ref = ref;
	plane->direction = direction;
}

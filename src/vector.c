
#include "../header/rt.h"

void zero_vect(t_vect *v)
{
    v->x = 0;
    v->y = 0;
    v->z = 0;
}

void init_vect(t_vect *v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

t_vect  add_vect( t_vect v1, t_vect v2)
{
    t_vect v3;
    
    v3.x = v1.x + v2.x;
    v3.y = v1.y + v2.y;
    v3.z = v1.z + v2.z;
    return v3;
}

t_vect  sub_vect(t_vect v1, t_vect v2)
{
    t_vect v3;
    
    v3.x = v1.x - v2.x;
    v3.y = v1.y - v2.y;
    v3.z = v1.z - v2.z;
    return v3;
}

t_vect  mult_vect(t_vect v1, t_vect v2)
{
    t_vect v3;
    
    v3.x = v1.x * v2.x;
    v3.y = v1.y * v2.y;
    v3.z = v1.z * v2.z;
    return v3;
}

t_vect  vect_mult_val(t_vect v, double a)
{
    t_vect v2;
    
    v2.x = v.x * a;
    v2.y = v.y * a;
    v2.z = v.z * a;
    return v2;
}

t_vect  vect_div_val(t_vect v, double a)
{
    t_vect v2;
    
    v2.x = v.x / a;
    v2.y = v.y / a;
    v2.z = v.z / a;
    return v2;
}

double  vect_scal(t_vect v1, t_vect v2)
{
    double ret;

     ret = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
    return ret;
}

double  get_norm_2(t_vect v)
{
    double ret;

    ret = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
    return ret;
}

void  normalize(t_vect *v)
{
    double norm;

    norm = sqrt(get_norm_2(*v));
    v->x /= norm;
    v->y /= norm;
    v->z /= norm;
}

t_vect    get_normalized(t_vect v)
{
    t_vect v1;

    v1 = v;
    normalize(&v1);
    return v1;
}
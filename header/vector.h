#ifndef VECTOR_H
#define VECTOR_H


typedef struct  s_vect
{
    double x;
    double y;
    double z;
}               t_vect;

void    zero_vect(t_vect *v);
void    init_vect(t_vect* v, double x, double y, double z);
t_vect  add_vect(t_vect v1, t_vect v2);
t_vect  sub_vect(t_vect v1, t_vect v2);
t_vect  mult_vect(t_vect v1, t_vect v2);
t_vect  vect_mult_val(t_vect v, double a);
t_vect  vect_div_val(t_vect v, double a); 
double  vect_scal(t_vect v1, t_vect v2);
double  get_norm_2(t_vect v);
void    normalize(t_vect *v);
t_vect  get_normalized(t_vect v);

#endif
#include "matrix.h"

matrix *m_create(unsigned int dim_x, unsigned int dim_y)
{
    if(!dim_x || !dim_y)
    {
#ifdef ERROR_OUT
        printf("m_create error 0\n");
#endif
        return NULL;
    }

    matrix *new_matrix = (matrix*)malloc(sizeof(matrix));
    if(new_matrix == NULL)
    {
#ifdef ERROR_OUT
        printf("m_create error 1\n");
#endif
        return NULL; //возвращает NULL - указатель, если произошла ошибка.
    }

    new_matrix->dim_x = dim_x;
    new_matrix->dim_y = dim_y;

    new_matrix->arr = (double*)malloc(sizeof(double) * dim_x * dim_y);
    if(new_matrix->arr == NULL)
    {
#ifdef ERROR_OUT
        printf("m_create error 2\n");
#endif
        free(new_matrix); //освобождение уже выделенной памяти.
        return NULL; //возвращает NULL - указатель, если произошла ошибка.
    }
    
    return new_matrix;
}

void m_free(matrix* m)
{
    if(m == NULL) return;
    free(m->arr);
    free(m); 
}

int m_scanf(matrix* m)
{
    if(m == NULL || m->arr == NULL)
    {
        #ifdef ERROR_OUT
        printf("NULL in m_scanf()\n");
        #endif
        return 1;
    }
    for(int t = 0; t < m->dim_x * m->dim_y; ++t) scanf("%lf", m->arr + t);
    return 0;
}

int m_printf(matrix* m)
{
    if(m == NULL || m->arr == NULL)
    {
        #ifdef ERROR_OUT
        printf("NULL in m_printf()\n");
        #endif
        return 1;
    }
    for(unsigned int  x = 0; x < m->dim_x; ++x)
    {
        for(unsigned int  y = 0; y < m->dim_y; ++y)
        {
            printf(KRASOTA, *(m->arr + y + x * m->dim_y)); 
        }
        printf("\n");
    }
    return 0;
}

int m_sum(matrix* a, matrix *b)
{
    if(a == NULL || b == NULL || a->arr == NULL || b->arr == NULL || 
        a->dim_x != b->dim_x || a->dim_y != b->dim_y)
    {
        #ifdef ERROR_OUT
        printf("m_sum error 0\n");
        #endif
        return 1;
    }
    for(int t = 0; t < a->dim_x * a->dim_y; ++t) (a->arr)[t] += (b->arr)[t];
    return 0;
}

int m_minus(matrix* a, matrix *b)
{
    if(a == NULL || b == NULL || a->dim_x != b->dim_x || a->dim_y != b->dim_y)
    {
        #ifdef ERROR_OUT
        printf("m_minus error 0\n");
        #endif
        return 1;
    }
    for(int t = 0; t < a->dim_x * a->dim_y; ++t) (a->arr)[t] -= (b->arr)[t];
    return 0;
}

int m_rand(matrix* m)
{
    if(m == NULL || m->arr == NULL)
    {
        #ifdef ERROR_OUT
        printf("NULL in m_rand()\n");
        #endif
        return 1;
    }
    for(int t = 0; t < m->dim_x * m->dim_y; ++t) m->arr[t] = -10 + rand()%21;
    return 0;
}

//ПЕРЕДЕЛАТЬ!
matrix* m_v_mult(matrix* m, matrix* v)
{
    if(m == NULL || v == NULL)
    {
        #ifdef ERROR_OUT
        printf("NULL in m_v_mult()\n");
        #endif
        return NULL;
    }
    if(m->dim_x != m->dim_y || m->dim_y != v->dim_x || v->dim_y != 1)
    {
        #ifdef ERROR_OUT
        printf("m_v_mult() arguments error\n");
        #endif
        return NULL;
    }
    matrix *t_matrix = m_create(m->dim_x, v->dim_y);
    if(t_matrix == NULL)
    {
        #ifdef ERROR_OUT
        printf("m_v_mult error 1\n");
        #endif
        return NULL;
    }
    for(int t = 0; t < t_matrix->dim_x * t_matrix->dim_y; ++t) t_matrix->arr[t] = 0;

    for(unsigned int x = 0; x < m->dim_x; ++x) 
    {
        for(unsigned int  y = 0; y < m->dim_y; ++y)
        {
            t_matrix->arr[x] += *(m->arr + y + x * m->dim_y) * v->arr[y]; 
        }
    }
    return t_matrix;
}

double norma_v(matrix* v)
{
    if(v == NULL)
    {
        #ifdef ERROR_OUT
        printf("NULL in norma_v()\n");
        #endif
        return -1;
    }
    if(v->dim_y != 1)
    {
        #ifdef ERROR_OUT
        printf("v->dim_y != 0\n");
        #endif
        return -1;
    }
    double num = 0;
    for(int t = 0; t < v->dim_x; ++t) num += v->arr[t] * v->arr[t];
    return sqrt(num);
}

int m_c_mult(matrix* v, double c)
{
    if(v == NULL)
    {
        #ifdef ERROR_OUT
        printf("NULL in norma_v()\n");
        #endif
        return 1;
    }
    for(int t = 0; t < v->dim_x; ++t) v->arr[t] *= c;
    return 0;
}

matrix *m_copy(matrix* m)
{
    if(m == NULL || m->arr == NULL)
    {
        #ifdef ERROR_OUT
        printf("NULL in m_copy()\n");
        #endif
        return NULL;
    }

    matrix *a = m_create(m->dim_x, m->dim_y);
    if(a == NULL)
    {
        #ifdef ERROR_OUT
        printf("m_copy() error 1\n");
        #endif
        return NULL;
    }
    for(int t = 0; t < a->dim_x * a->dim_y; ++t) a->arr[t] = m->arr[t];
    return a;
}

matrix* m_unit_vector(unsigned int size)
{
    matrix *v = m_create(size, 1);
    if(v == NULL) return NULL;
    for(unsigned int t = 0; t < size; ++t)
    {
        v->arr[t] = 1;
    }
    return v;
}

int m_fscanf(matrix* m, char* f_name)
{
    if(m == NULL || m->arr == NULL)
    {
        #ifdef ERROR_OUT
        printf("NULL in m_fscanf()\n");
        #endif
        return 1;
    }
    FILE *fl = fopen(f_name, "r");
    if(fl == NULL) return 2;
    for(int t = 0; t < m->dim_x * m->dim_y; ++t) fscanf(fl, "%lf", m->arr + t);
    fclose(fl);
    return 0;
}
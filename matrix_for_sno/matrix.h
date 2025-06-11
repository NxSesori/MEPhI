#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


#define KRASOTA "%8.8lf" //спецификатор вывода матрицы

//#define ERROR_OUT //режим вывода ошибок

typedef struct
{
    unsigned int dim_x;
    unsigned int dim_y;
    double *arr;
} matrix;

matrix *m_create(unsigned int dim_x, unsigned int dim_y);
//создание матрицы.
//Возвращает NULL при ошибке / невозможности создать матрицу

void m_free(matrix* m);
//деструктор 

matrix *m_copy(matrix* m);
//создает копию матрицы m
//return NULL при неверном аргументе (m == NULL || m->arr == NULL)
//или при ошибке выделения памяти

int m_scanf(matrix* m);
//считывание значений матрицы из std 
//return 1 при неверном аргументе (m == NULL || m->arr == NULL)

int m_fscanf(matrix* m, char* f_name);
//считывание значений матрицы из файла с именем *f_name
//return 1 при неверном аргументе (m == NULL || m->arr == NULL || f_name == NULL)
//return 2, если файла не существует

int m_printf(matrix* m);
//вывод значений матрицы в стандартный поток ввода
//return 1 при неверном аргументе (m == NULL || m->arr == NULL)

int m_sum(matrix* a, matrix *b);
//сложение матриц a+=b
//return 1 при неверном аргументе (m == NULL || m->arr == NULL)

int m_minus(matrix* a, matrix *b);
//разность матриц a-=b
//return 1 при неверном аргументе (m == NULL || m->arr == NULL)
//или при разности размерностей матриц

int m_rand(matrix* m);
//заполение матрицы случайными значениями
//return 1 при неверном аргументе (m == NULL || m->arr == NULL)

matrix* m_v_mult(matrix* m, matrix* v);
//умножение матрицы на вектор
//return NULL при неверном аргументе (m == NULL || m->arr == NULL)

int m_c_mult(matrix* v, double c);
//умножение вектора на константу
//return 1 при неверном аргументе (m == NULL || m->arr == NULL)

double norma_v(matrix* v);
//норма вектора
//return 1 при неверном аргументе

matrix* m_unit_vector(unsigned int size);
//создание вектора из единиц 
//return NULL при ошибке

#endif
#include "own_number.h"

double on_reed_and_seek(char* fin, char* fout, unsigned int size, double torch, char tras, enum own_num_error* err)
{
    if(torch <= 0)
    {
        if(err != NULL) *err = arg_error;
        return 0;
    }

    FILE* fl_out = NULL;
    if(fout != NULL)
    {
        fl_out = fopen(fout, "w"); //если нужно, открываем файл
    }

    matrix *m = m_create(size, size);// создание матрицы 
    if(m == NULL) 
    {
        if(fout != NULL) fclose(fl_out); //если нужно, закрываем файл
        if(err != NULL) *err = alloc_error;
        return 0;
    }
    
    if(fin == NULL)
        m_scanf(m); //считывание матрицы из потока ввода
    else   
        if(m_fscanf(m, fin) == 2)
        {
            if(fout != NULL) fclose(fl_out); //если нужно, закрываем файл
            if(err != NULL) *err = arg_error; //возникает, если файла с именемн е существует
            m_free(m); //удаление уже созданных матриц
            return 0;
        } //считывание из файла

    matrix *v = m_unit_vector(size);; //создание вектора
    if(v == NULL) 
    {
        if(fout != NULL) fclose(fl_out); //если нужно, закрываем файл
        if(err != NULL) *err = alloc_error;
        m_free(m); //удаление уже созданных матриц
        return 0;
    }
    
    matrix *v_t = NULL, *d_t = NULL;
    
    double otw = 0; //собственное число

    int t = 0;
    while(1)
    {
        ++t;
        v_t = m_v_mult(m, v);
        if(v_t == NULL)
        {
            if(fout != NULL) fclose(fl_out); //если нужно, закрываем файл
            m_free(m); //удаление уже созданных матриц
            m_free(v_t);
            m_free(d_t);
            if(err != NULL) *err = alloc_error;
            return 0;
        }
        otw = norma_v(v_t)/norma_v(v);
        if(tras) 
        {
            if(fout == NULL)
            printf("Iter: %d\nNum: %lf\n", t, otw); //трассировка собственного числа
            else fprintf(fl_out, "Iter: %d\nNum: %lf\n", t, otw);
        }
        m_c_mult(v_t, 1.0 / norma_v(v_t));
        d_t = m_copy(v);
        if(d_t == NULL)
        {
            if(fout != NULL) fclose(fl_out); //если нужно, закрываем файл
            m_free(m); //удаление уже созданных матриц
            m_free(v_t);
            m_free(d_t);
            if(err != NULL) *err = alloc_error;
            return 0;
        }
        m_minus(d_t, v_t);
        if(norma_v(d_t) < torch) break;

        m_free(d_t);
        d_t = v;
        v = v_t;
        m_free(d_t);
    }
    m_free(d_t);
    d_t = v;
    v = v_t;
    m_free(d_t);

    //m_printf(v); //вывод вектора

    //scanf("%d", &t);
    m_free(v);
    if(fout != NULL)
    {
        fclose(fl_out); //если нужно, закрываем файл
    }
    if(err != NULL) *err = no_errors;
    return otw;
    
}
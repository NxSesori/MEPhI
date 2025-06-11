//пример программы, которая считает матрицу из потока ввода и выведет результат

#include "matrix.h"
#include "own_number.h"

int main()
{
    double torch = 0.0001; //точность численного метода
    //scanf("%lf", &torch);
    unsigned size = 3;
    double own = on_reed_and_seek(NULL, NULL, size, torch, 1, NULL);

    printf("own num = %lf\n", own);

    return 0;
}

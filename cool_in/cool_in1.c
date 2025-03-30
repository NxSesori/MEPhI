
#define TYPE unsigned int
//наш тип данных

#include <conio.h>

#include <stdio.h>
#include <stdint.h>


TYPE cool_in();
//считывает значение типа TYPE, вводимое в консоль и возвращает его.
//позволяет редактировать число, пока не будет нажат enter.
//! TYPE должен быть целочисленным!
//Особенности ввода:
//0 не может быть отрицательным, число должно иметь значащие символы,
//число должно помещаться в TYPE, число должно быть введено,
//в числе может быть только один значащий 0.

int main()
{
    printf("Enter the number: ");
    TYPE aboba = cool_in();
    printf("You entered the number: %d. Cool!\n", aboba);
    //при смене типа TYPE следует поставить соотвествующий спецификатор.
    getch(); //консоль не закроется, пока не ввести что-то еще.
    return 0;
}

TYPE cool_in()
{
    int sign = 1;
    TYPE n = 0;
    TYPE n_t;
    //n_t не нужно инициализировать, т.к. он не используется до присвоения какого-либо значения
    TYPE size = 0;
    char ch;
    //аналогично n_t
    int stop = 0;

    while(1)
    {
        ch = getch();
        if((ch == '\n' || (int)ch == 13) && size && (sign == 1 || n))
        {
            printf("\n");
            return n;
        }
        if(ch == '\b')
        {
            if(size)
            {
                putch('\b');
                putch(' ');
                putch('\b');
                --size;
                n /= 10;
                if(!size) 
                {
                    sign = 1;
                    stop = 0;
                }
            }
            continue;
        } else
        {
            if(stop) continue;
            //если пользователь ввел в консоль 0, условие не даст ввести иные значения до 
            //enter или backspace
        }

        if(!size && sign == 1)
        {
            if(ch == '-' && ((TYPE)-1 < 0))
            {
                ++size;
                putch('-');
                sign = -1;
                continue;
            }
            if(ch == '0')
            {
                ++size;
                putch('0');
                stop = 1;
                continue;
            }
        }

        if(ch >= '0' && ch <= '9')
        {
            TYPE val = n;
            n_t = 2 * n; 
            if(sign > 0 && n_t < val || sign < 0 && n_t > val) continue;
            val = n_t;
            n_t *= 2;
            if(sign > 0 && n_t < val || sign < 0 && n_t > val) continue;
            val = n_t;
            n_t *= 2;
            if(sign > 0 && n_t < val || sign < 0 && n_t > val) continue;
            val = n_t;
            n_t += 2 * n;
            if(sign > 0 && n_t < val || sign < 0 && n_t > val) continue;
            n_t += sign * ((int)ch - (int)'0');
            //поэтапно увеличиваем число до 10*n + sign*(символ). После каждого этапа проверка на переполнение

            if(sign > 0 && n_t > val || sign < 0 && n_t < val)
            {
                n = n_t;
                ++size;
                putch(ch);
            }
        }
    }
}
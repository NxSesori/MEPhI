//Консольная игра "Висельница" для ОС windows
//Разработчик: @Sesori / @fun_aboba

//Фишки: 
//файлик с кучей слов - реализовано :)
//система рейтинга - не реализовано 
//автоустановка - не реализовано 



#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stddef.h>
#include <wchar.h>
#include <time.h>

#include <io.h> //for _setmode
#include <fcntl.h> //for _O_U16TEXT

#define SIZE_WORD 12 //максимальная длинна слова + 1.
#define INT_COUNT 11 //кол-во разрядов int + 1.

typedef struct
{
    int play_error;
    int win;
    wchar_t chars_arr[34];
    wchar_t p_word[SIZE_WORD];
    int p_word_size;
} play_info;

void locale_setup();
//Начальные действия: настройка языка

void play_info_setup(play_info* aboba, wchar_t *word);
//Начальные действия: конструктор play_info

void read_word(wchar_t* arr, FILE *fl);
//считывание слова из word.txt 

void set_word(wchar_t *word);
//Начальные действия: импорт слова из word.txt

int game_process(wchar_t *word, play_info* aboba);
//игровой процесс. Возвращает 1, если игра должна продолжатся

void gui_pr();
void gui_start();
void gui_hangman(play_info* aboba);

wchar_t hang[8][87] = {
        L"      +---+\n      |   |\n          |\n          |\n          |\n          |\n=========''']\n",
        L"      +---+\n      |   |\n      O   |\n          |\n          |\n          |\n=========''']\n",
        L"      +---+\n      |   |\n      O   |\n      |   |\n          |\n          |\n=========''']\n",
        L"      +---+\n      |   |\n      O   |\n     /|   |\n          |\n          |\n=========''']\n",
        L"      +---+\n      |   |\n      O   |\n     /|\\  |\n          |\n          |\n=========''']\n",
        L"      +---+\n      |   |\n      O   |\n     /|\\  |\n     /    |\n          |\n=========''']\n",
        L"      +---+\n      |   |\n      O   |\n     /|\\  |\n     / \\  |\n          |\n=========''']\n",
    };

int main(int argc, char *argv[])
{
    srand(time(NULL));
    locale_setup();
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);


    wchar_t word[SIZE_WORD];
    do{
        set_word(word);

        play_info aboba;
        play_info_setup(&aboba, word);
        //wprintf(L"%d", (int)L'а');

        gui_start(&aboba);
        
        while(game_process(word, &aboba))
        {
            system("cls");
            gui_pr();
            gui_hangman(&aboba);
            wprintf(L"%ls\n", aboba.p_word);
            wprintf(L"%ls\n", aboba.chars_arr);

        }

        if(aboba.win) 
        {
            wprintf(L"%ls\n", aboba.p_word);
            wprintf(L"\nТы победил!!!\n");
            wprintf(L"\nХочешь продожить? [y/N]\n");
        }
        else
        {
            system("cls");
            gui_pr();
            gui_hangman(&aboba);
            wprintf(L"\nТы проиграл!!!\n");
            wprintf(L"Ответ: %ls\n", word);
            wprintf(L"\nХочешь продожить? [y/N]\n");
        }
        aboba.win = 0;

        wscanf(L"%ls", word);
    }
    while(word[0] == L'y');
    return 0;
}

void locale_setup()
{
    if (setlocale(LC_ALL, "ru_RU.UTF-8") == NULL) //setlocale(LC_CTYPE, "")  ;
    {
        printf("Yazuk slomalsya\n");
        exit(1);
    }
}

void play_info_setup(play_info* aboba, wchar_t *word)
{
    aboba->play_error = 0;
    aboba->win = 0;
    for(int t = 0; t < 34; ++t)
    {
        aboba->chars_arr[t] = L'\0';
    }
    int t = 0;
    for(; word[t] != L'\0'; ++t)
    {
        aboba->p_word[t] = L'_';
    }
    aboba->p_word[t] = L'\0';
}

void read_word(wchar_t* arr, FILE *fl)
{ 
    fwscanf(fl, L"%ls", arr);
    /*
    if(fgetws(arr, SIZE_WORD, fl) == NULL)
    {
        printf("fgets error\n");
        exit(2);
    }
    */
}


void set_word(wchar_t *word)
{
    FILE *fl = fopen("word.txt", "r");
    if(fl == NULL)
    {
        printf("fopen error\n");
        exit(1);
    }

    char arr[INT_COUNT];

    if(fgets(arr, SIZE_WORD, fl) == NULL)
    {
        printf("fgets error\n");
        exit(2);
    }

    int number = (rand() % atoi(arr));
    for(int t = 0; t < number; ++t)
    {
        read_word(word, fl);
    }
    read_word(word, fl);
    fclose(fl);
}

int game_process(wchar_t *word, play_info* aboba)
{
    wchar_t ch;
    int pon;
    while(1)
    {
        wscanf(L"%lc", &ch);
        
        //wprintf(L"%lc", (wchar_t)ch);
        
        if(ch <= 1103 && ch >= 1072) //ch <= (wchar_t)L'я' && ch >= (wchar_t)L'а'
        {
            //wprintf(L"%lc", ch);
            int flug = 1;
            int t = 0;
            for(; aboba->chars_arr[t] != L'\0'; ++t)
            {
                if(ch == aboba->chars_arr[t])
                {
                    flug = 0;
                    break;
                }
            }
            if(flug){
                aboba->chars_arr[t] = ch;
                break;
            } else wprintf(L"Вы уже вводили букву %lc\n", ch);
        }
    }
    int flug = 1;
    for(int t = 0; word[t] != '\0'; ++t)
    {
        if(ch == word[t])
        {
            flug = 0;
            aboba->p_word[t] = word[t];

            int win_flug = 1;
            for(int tt = 0; aboba->p_word[tt] != '\0'; ++tt)
            {
                if(aboba->p_word[tt] != word[tt]) win_flug = 0;
            }
            if(win_flug)
            {
                aboba->win = 1;
                return 0;
            }
        }
    }
    if(flug) aboba->play_error += 1;
    if(aboba->play_error == 6) return 0;

    return 1;
}

void gui_pr()
{
    wprintf(L"//////////////////// Habgman 1.0 ////////////////////\n");
    wprintf(L"Подпишись: t.me/fun_aboba\n");
    wprintf(L"/////////////////////////////////////////////////////\n");
}

void gui_start(play_info* aboba)
{
    system("cls");
    gui_pr();
    wprintf(L"Правила: угадывай слово, пока ты жив!\n Введи русскую букву и нажми enter\n");
    gui_hangman(aboba);
    wprintf(L"Загаданное слово: %ls\n", aboba->p_word);

}

void gui_hangman(play_info* aboba)
{
    wprintf(L"%ls\n", hang[aboba->play_error]);
}
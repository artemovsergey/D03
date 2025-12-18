#include <locale.h>  // Добавьте эту строку
#include <stdbool.h>
#include <stdio.h>

// #include <wchar.h> // так работает с русским текстом

int function(char name[]) {
    char *surname;  // указатель на строку
    scanf("%s", &surname);

    printf("Ввод: %s", &surname);  // & - адрес строки
    // wprintf(L"Ввод: %s", &surname); // Вывод на русском языке
    return 0;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    long a4 = 3L;
    int a = 3;
    short a_1 = 5;
    unsigned int a3 = 7;
    int b = 4;
    int c = a + b;
    // интерполяция строки в C

    // дробные числа
    float f1 = 3.14f;
    double d1 = 2.71828;
    // char
    char ch1 = 'A';
    // boolean - надо подключить библиотеку stdbool.h
    bool flag = 1;
    printf("%d", a_1);
    printf("\n");
    printf("The sum of %d and %d is %d\n", a, b, c);

    function("Hello");

    return 0;
}

// src/1948.c
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Функция для проверки, является ли число простым
// Использует только вычитание и сравнения
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;  // можно избежать этой проверки, но она упрощает логику

    // Проверяем делимость только на нечетные числа
    // Используем вычитание вместо деления для подсчета количества вычитаний
    int divisor = 3;
    while (1) {
        int temp = n;
        // Пока temp >= divisor, вычитаем divisor из temp
        while (temp >= divisor) {
            temp -= divisor;
        }
        // Если temp == 0, значит divisor делит n
        if (temp == 0) {
            return 0;  // нашли делитель, число не простое
        }

        // Увеличиваем divisor для проверки следующего возможного делителя
        // Используем сложение вместо умножения
        divisor += 2;

        // Если divisor * divisor > n, то дальше проверять не нужно
        int square = 0;
        int count = 0;
        while (count < divisor) {
            square += divisor;
            count++;
        }
        if (square > n) {
            break;
        }
    }
    return 1;
}

// Функция для нахождения наибольшего простого делителя
int largest_prime_factor(int a) {
    if (a <= 1) return -1;  // Ошибка

    // Обрабатываем отрицательные числа
    if (a < 0) a = -a;

    int largest = 1;
    int current = 2;

    while (current <= a) {
        // Проверяем, делится ли a на current с помощью вычитания
        int temp = a;
        while (temp >= current) {
            temp -= current;
        }

        // Если temp == 0, значит current делит a
        if (temp == 0) {
            // Проверяем, является ли current простым числом
            if (is_prime(current)) {
                largest = current;
            }

            // Делим a на current (с помощью вычитания)
            // Находим, сколько раз current содержится в a
            int quotient = 0;
            temp = a;
            while (temp >= current) {
                temp -= current;
                quotient++;
            }

            // Продолжаем с тем же current, чтобы проверить его степень
            a = quotient;
        } else {
            // Увеличиваем current
            if (current == 2) {
                current = 3;
            } else {
                current += 2;  // проверяем только нечетные числа после 2
            }
        }
    }

    return largest;
}

int main() {
    int a;

    // Чтение входного числа
    if (scanf("%d", &a) != 1) {
        printf("n/a\n");
        return 1;
    }

    if (a < 0) {
        a = a * (-1);
    }

    // Находим наибольший простой делитель
    int result = largest_prime_factor(a);

    if (result == -1) {
        printf("n/a\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}
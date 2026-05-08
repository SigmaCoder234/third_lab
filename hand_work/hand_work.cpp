#include "hand_work.h"

#include <cstdio>
#include <iostream>

// функция для безопасного ввода int начений
int safe_input() {
    int value;
    int res;
    while (true) {
        res = scanf("%d", &value);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (res == 1) {
            break;
        }

        else {
            printf("Invalid input. Please try again: ");
        }
    }
    return value;
}

// функция для безопасного ввода double начений
double safe_double_input() {
    double value;
    double res;
    while (true) {
        res = scanf("%lf", &value);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (res == 1.0) {
            break;
        }

        else {
            printf("Invalid input. Please try again: ");
        }
    }
    return value;
}

// Функция для безопасного ввода bool значений (y/n или 1/0)
bool safe_bool_input() {
    int value;
    int res;
    while (true) {
        res = scanf("%d", &value);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (res == 1 && (value == 0 || value == 1)) {
            break;
        }

        else {
            printf("Invalid input. Please enter 1 (Yes) or 0 (No): ");
        }
    }
    return value == 1;
}
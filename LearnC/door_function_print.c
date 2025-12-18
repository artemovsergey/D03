#include <math.h>
#include <stdio.h>

#define WIDTH 42
#define HEIGHT 21

double agnesi(double x) { return 1.0 / (x * x + 1.0); }

int bernoulli(double x, double *y) {
    double a = 2.0 * x * x + 1.0;
    double b = x * x * x * x - x * x;
    double d = a * a - 4.0 * b;

    if (d < 0.0) return 0;

    double y2 = (-a + sqrt(d)) / 2.0;
    if (y2 < 0.0) return 0;

    *y = sqrt(y2);
    return 1;
}

int hyperbola(double x, double *y) {
    if (fabs(x) < 1e-12) return 0;
    *y = 1.0 / (x * x);
    return 1;
}

void draw(double values[WIDTH], double ymin, double ymax) {
    char field[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++) field[i][j] = ' ';

    for (int x = 0; x < WIDTH; x++) {
        if (isnan(values[x])) continue;

        int y = (int)((values[x] - ymin) / (ymax - ymin) * (HEIGHT - 1));
        y = HEIGHT - 1 - y;

        if (y >= 0 && y < HEIGHT) field[y][x] = '*';
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) putchar(field[i][j]);
        putchar('\n');
    }
}

int main(void) {
    const double PI = acos(-1.0);
    const double STEP = (2.0 * PI) / (WIDTH - 1);

    double x[WIDTH];
    for (int i = 0; i < WIDTH; i++) x[i] = -PI + STEP * i;

    double y[WIDTH];

    /* Верзьера Аньези */
    for (int i = 0; i < WIDTH; i++) y[i] = agnesi(x[i]);
    draw(y, 0.0, 1.0);

    putchar('\n');

    /* Лемниската Бернулли */
    for (int i = 0; i < WIDTH; i++) {
        if (!bernoulli(x[i], &y[i])) y[i] = NAN;
    }
    draw(y, 0.0, 1.0);

    putchar('\n');

    /* Квадратичная гипербола */
    for (int i = 0; i < WIDTH; i++) {
        if (!hyperbola(x[i], &y[i])) y[i] = NAN;
    }
    draw(y, 0.0, 10.0);

    return 0;
}

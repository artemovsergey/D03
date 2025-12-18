#include <math.h>
#include <stdio.h>

int main(void) {
    const int POINTS = 42;
    const double PI = acos(-1.0);
    const double STEP = (2.0 * PI) / (POINTS - 1);

    for (int i = 0; i < POINTS; i++) {
        double x = -PI + STEP * i;

        /* Абсцисса */
        printf("%.7f | ", x);

        /* Верзьера Аньези */
        double agnesi = 1.0 / (x * x + 1.0);
        printf("%.7f | ", agnesi);

        /* Лемниската Бернулли (Y > 0) */
        double a = 2.0 * x * x + 1.0;
        double b = x * x * x * x - x * x;
        double discriminant = a * a - 4.0 * b;

        if (discriminant < 0.0) {
            printf("- | ");
        } else {
            double y2 = (-a + sqrt(discriminant)) / 2.0;
            if (y2 < 0.0) {
                printf("- | ");
            } else {
                printf("%.7f | ", sqrt(y2));
            }
        }

        /* Квадратичная гипербола */
        if (fabs(x) < 1e-12) {
            printf("-\n");
        } else {
            printf("%.7f\n", 1.0 / (x * x));
        }
    }

    return 0;
}

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Функция кодирования: символ -> двухсимвольная hex-строка (верхний регистр)
void encode_char(char c) { printf("%02X", (unsigned char)c); }

// Функция декодирования: двухсимвольная hex-строка -> символ
// Возвращает 1 при успехе, 0 при ошибке
int decode_pair(const char *pair, char *result) {
    if (strlen(pair) != 2) return 0;
    if (!isxdigit(pair[0]) || !isxdigit(pair[1])) return 0;

    int value;
    if (sscanf(pair, "%2X", &value) != 1) return 0;
    if (value > 255) return 0;  // на всякий случай, хотя %2X ограничивает

    *result = (char)(unsigned char)value;
    return 1;
}

// Режим кодирования (0)
void mode_encode() {
    char ch;
    int first = 1;
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (isspace(ch)) {
            if (!first) putchar(' ');
            encode_char(ch);
            first = 0;
        } else {
            // Встречен не-пробельный символ, не разделённый пробелом правильно
            // Но по условию: только отдельные символы, разделённые пробелами
            // Если идёт строка вроде "WORLD", то это ошибка
            // Мы проверяем: если предыдущий был символ, а сейчас не пробел — ошибка
            // Но проще: если не пробел и не первый — уже был символ без разделителя
            // Лучше собирать по словам
            ungetc(ch, stdin);
            char word[100];
            if (scanf("%99s", word) != 1) {
                printf("n/a");
                return;
            }
            if (strlen(word) != 1) {
                printf("n/a");
                return;
            }
            if (!first) putchar(' ');
            encode_char(word[0]);
            first = 0;
        }
    }
    putchar('\n');
}

// Более правильная реализация кодирования: читать по словам
void mode_encode_fixed() {
    char word[100];
    int first = 1;
    int has_input = 0;

    while (scanf("%99s", word) == 1) {
        has_input = 1;
        if (strlen(word) != 1) {
            printf("n/a\n");
            return;
        }
        if (!first) putchar(' ');
        encode_char(word[0]);
        first = 0;

        // Пропустить остаток строки до пробела или переноса
        int ch;
        while ((ch = getchar()) != EOF && !isspace(ch))
            ;
        if (ch == '\n' || ch == EOF) break;
    }

    if (!has_input) {
        putchar('\n');
        return;
    }
    putchar('\n');
}

// Режим декодирования (1)
void mode_decode() {
    char pair[3] = {0};
    int first = 1;
    int valid = 1;

    while (scanf("%2s", pair) == 1) {
        char result;
        if (!decode_pair(pair, &result)) {
            valid = 0;
            break;
        }
        if (!first) putchar(' ');
        putchar(result);
        first = 0;

        // Пропустить пробелы до следующего токена или конца строки
        int ch;
        while ((ch = getchar()) != EOF && isspace(ch && ch != '\n'))
            ;
        if (ch == '\n' || ch == EOF) break;
        ungetc(ch, stdin);
    }

    if (!valid || !first && getchar() != '\n' && getchar() != EOF) {
        // Если была ошибка или после последнего токена остался мусор
        // Но проще: если не удалось прочитать корректно
        // Лучше очистить буфер и проверить
        // Перезапустим логику
    }

    // Более надёжный способ
}

// Лучшая реализация декодирования
void mode_decode_fixed() {
    char token[100];
    int first = 1;
    int count = 0;

    while (scanf("%99s", token) == 1) {
        count++;
        if (strlen(token) != 2) {
            printf("n/a\n");
            return;
        }
        char result;
        if (!decode_pair(token, &result)) {
            printf("n/a\n");
            return;
        }
        if (!first) putchar(' ');
        putchar(result);
        first = 0;
    }

    // После последнего токена должен быть перевод строки
    int ch = getchar();
    if (ch != '\n' && ch != EOF) {
        printf("n/a\n");
        return;
    }

    if (count == 0) {
        putchar('\n');
        return;
    }

    putchar('\n');
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("n/a\n");
        return 1;
    }

    int mode;
    if (sscanf(argv[1], "%d", &mode) != 1 || (mode != 0 && mode != 1)) {
        printf("n/a\n");
        return 1;
    }

    if (mode == 0) {
        // Кодирование: ожидает отдельные символы, разделённые пробелами
        char token[100];
        int first = 1;
        int has_data = 0;

        while (scanf("%99s", token) == 1) {
            has_data = 1;
            if (strlen(token) != 1) {
                printf("n/a\n");
                return 0;
            }
            if (!first) putchar(' ');
            printf("%02X", (unsigned char)token[0]);
            first = 0;
        }

        // Проверяем, что строка закончилась корректно
        int ch;
        while ((ch = getchar()) != EOF && isspace(ch))
            ;
        if (ch != EOF && ch != '\n') {
            printf("n/a\n");
            return 0;
        }

        if (has_data)
            putchar('\n');
        else
            putchar('\n');
    } else {
        // Декодирование
        char token[100];
        int first = 1;
        int has_data = 0;

        while (scanf("%99s", token) == 1) {
            has_data = 1;
            if (strlen(token) != 2) {
                printf("n/a\n");
                return 0;
            }
            char result;
            if (!decode_pair(token, &result)) {
                printf("n/a\n");
                return 0;
            }
            if (!first) putchar(' ');
            putchar(result);
            first = 0;
        }

        int ch;
        while ((ch = getchar()) != EOF && isspace(ch))
            ;
        if (ch != EOF && ch != '\n') {
            printf("n/a\n");
            return 0;
        }

        if (has_data)
            putchar('\n');
        else
            putchar('\n');
    }

    return 0;
}
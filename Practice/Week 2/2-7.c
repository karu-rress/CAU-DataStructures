#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char strings[100][100] = { 0, };
    int n = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        fgets(strings[i], 100, stdin);
    }

    qsort(strings, 100, sizeof strings[0], strcmp);

    for (int i = 0; i < 100; i++) {
        printf("%s", strings[i]);
    }
}
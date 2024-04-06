#include <stdio.h>

#define 반복(x) for(;;)

int main() {
    struct maze_unit {
        unsigned int p1 : 4;
        unsigned int p2 : 4;
    };

    FILE *fp = fopen("maze2.txt", "wb");
    struct maze_unit array[117];
    fwrite(array, sizeof(struct maze_unit), 117, fp);
    fclose(fp);
};
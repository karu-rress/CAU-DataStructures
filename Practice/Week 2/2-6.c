/*
배열의 합계를 구하는 함수 sum을 이용한 프로그램의 main 함수가 다음과 같다.
프로그램의 용도를 보고 sum 함수가 어떻게 만들어져야 하는지 작성하라.
또 main 함수의 비어있는 부분도 작성하라.
단, sum 함수는 char, short, int형에 대해서만 사용할 수 있다.
빌드시에 경고는 없어야 한다.
*/

#include <stdio.h>

int sum(void *arr, size_t size, size_t len) {
    char *p = (char*)arr;
    int result = 0;
    for (int i = 0; i < len; i++) {
        switch (size)
        {
        case 1:
            result += *(char *)p;
            p += 1;
            break;
        case 2:
            result += *(short *)p;
            p += 2;
            break;
        case 4:
            result += *(int *)p;
            p += 4;
            break;
        }
    }
    return result;
}

int main()
{
    int inum[] = { 1,4,7,9,8,2,5,3,7,6 };
    char cnum[] = { 3,5,8,7,6,1,9 };
    printf("%d\n", sum(inum, sizeof(int), 10));
    printf("%d\n", sum(cnum, sizeof(char), 7));
}

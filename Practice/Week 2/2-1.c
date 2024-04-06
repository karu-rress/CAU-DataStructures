// scanf의 서식을 잘못 사용하여 다음과 같은 결과가 나왔다.
#include <stdio.h>

int main(void)
{
    int i;
    // %d를 써야 할 곳에 %f를 썼다.
    scanf("%f", &i);

    // i 변수의 값을 출력해도 제대로 나오지 않는다.
    // printf("%d %f\n", i, i);
    printf("%d %f\n", i, *(float *)(&i));
}
// printf 문을 수정하거나 문장을 추가하여
// 입력한 1.23 값이 그대로 표시되는 방법을 제시하라.
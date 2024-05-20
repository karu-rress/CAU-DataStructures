/**
 * 2-(3) scanf 만들기
 *
 * 20234748 나선우
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // 가변함수 매크로
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 100

// 입력 큐 정의
typedef struct {
    char *data[MAX_LENGTH];
    int front;
    int rear;
} input_queue;

bool is_empty(input_queue *q);
bool is_full(input_queue *q);
void enqueue(input_queue *q, char *item);
char *dequeue(input_queue *q);
void input_line(input_queue *q);

int my_scanf(const char *format, ...);

int main(void) {
    int num1, num2;
    float f1, f2;
    char buffer[100];

    printf("my_scanf() 테스트\n");
    printf("정수 두 개를 입력하세요: ");
    scanf("%d %d", &num1, &num2);
    printf("%d + %d = %d\n\n", num1, num2, num1 + num2);

    printf("실수 두 개를 입력하세요: ");
    scanf("%f %f", &f1, &f2);
    printf("%f + %f = %f\n\n", f1, f2, f1 + f2);
    
    printf("듣고 싶은 말을 입력하세요: ");
    scanf("%s", buffer);
    printf("\"%s\"\n", buffer);

    return 0;
}

bool is_empty(input_queue *q) {
    return q->front == -1 && q->rear == -1;
}

bool is_full(input_queue *q) {
    return (q->rear + 1) % MAX_LENGTH == q->front;
}

void enqueue(input_queue *q, char *item) {
    if (is_full(q))
        return;

    if (is_empty(q))
        q->front = q->rear = 0;
    else 
        q->rear = (q->rear + 1) % MAX_LENGTH;
    
    q->data[q->rear] = item;
}

char *dequeue(input_queue *q) {
    char *item;
    if (is_empty(q))
        return NULL;

    if (q->front == q->rear) {
        item = q->data[q->front];
        q->front = q->rear = -1;
    }
    else {
        item = q->data[q->front];
        q->front = (q->front + 1) % MAX_LENGTH;
    }
    return item;
}

void input_line(input_queue *q) {
    // 큐가 비어 있지 않다면 지금 입력을 받을 필요가 없음.
    if (!is_empty(q))
        return;
                        
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);

    char *pch = NULL;
    
    pch = strtok(buffer, " ");
    while (pch != NULL) {
        enqueue(q, pch);
        pch = strtok (NULL, " ");
    }
}

int my_scanf(const char *format, ...) {
    // 입력 큐는 프로그램 전반적으로 공유되므로, static으로 선언
    static input_queue q = { .front = -1, .rear = -1};

    int ret = 0; // 입력 받은 개수

    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            ret++;
            switch (*(++format)) {
                case 'c':
                    input_line(&q);

                    char *char_arg = va_arg(args, char *);
                    *char_arg = *dequeue(&q);
                    break;
                case 'd':
                    input_line(&q);

                    int *int_arg = va_arg(args, int *);
                    *int_arg = atoi(dequeue(&q));
                    break;
                case 'f':
                    input_line(&q);

                    float *float_arg = va_arg(args, float *);
                    *float_arg = atof(dequeue(&q));
                    break;
                case 's':
                    input_line(&q);

                    char *str_arg = va_arg(args, char *);
                    strcpy(str_arg, dequeue(&q));
                    break;
            }
        }
        format++;
    }
    va_end(args);

    return ret;
}
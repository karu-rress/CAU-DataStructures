/**
 * 2-(1) 문자열 구현하기
 *
 * 20234748 나선우
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *data;
    size_t length;
} new_string;

new_string create_str(const char *str);
size_t new_strlen(new_string str);
char *new_str(new_string str);
void new_strcpy(new_string *dest, new_string src);
void new_strcat(new_string *dest, new_string src);
void delete_str(new_string *str);


int main(void) {    
    new_string a, b, c, d;
    
    a = create_str("Hello world");
    b = create_str("c program");
    c = create_str("");
    d = create_str("");

    new_strcpy(&c, a); // c <- a (c = "Hello world")
    new_strcpy(&d, a); // d <- a (d = "Hello world")
    new_strcat(&d, b); // b <- d + b (b = Hello worldc program) 

    // OUTPUT: Hello world Hello worldc program 11 20
    printf("%s %s %lld %lld\n", new_str(c), new_str(d), new_strlen(c), new_strlen(d));

    delete_str(&a);
    delete_str(&b);
    delete_str(&c);
    delete_str(&d);
}

// new_string을 만드는 함수
new_string create_str(const char *str) {
    new_string result;
    result.length = strlen(str); // 부득이하게 strlen을 이용할 수밖에 없다.
    result.data = (char *)malloc((result.length + 1) * sizeof(char));
    memcpy(result.data, str, result.length + 1);

    return result;
}

// new_string의 길이를 반환
size_t new_strlen(new_string str) {
    return str.length;
}

// new_string의 raw pointer를 반환
char *new_str(new_string str) {
    return str.data;
}

// new_string용 strcpy
void new_strcpy(new_string *dest, new_string src) {
    dest->data = (char *)realloc(dest->data, (src.length + 1) * sizeof(char));
    memcpy(dest->data, src.data, src.length + 1);
    dest->length = src.length;
}

// new_string용 strcat
void new_strcat(new_string *dest, new_string src) {
    dest->data = (char *)realloc(dest->data, (dest->length + src.length + 1) * sizeof(char));
    memcpy(dest->data + dest->length, src.data, src.length + 1);
    dest->length += src.length;
}

void delete_str(new_string *str) {
    free(str->data);
    str->data = NULL;
    str->length = 0;
}
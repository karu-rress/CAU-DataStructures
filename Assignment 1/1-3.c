/**
 * 과제 1-(3) 다항식의 저장 방식 개선하기
 * 
 * 20234748 나선우
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 50

struct term {
    float coef;
    int exp;
};

typedef struct {
    struct term *terms;
    int len; // terms의 개수
} polynominal;

polynominal create_poly(char *str);
int         cmp_terms(const void *a, const void *b);
void        sort_poly(polynominal *poly);
polynominal add_poly(polynominal polyA, polynominal polyB);
polynominal mul_poly(polynominal polyA, polynominal polyB);
void        print_poly(polynominal poly);
void        delete_poly(polynominal *poly);

int main(void) {
    char buf[BUF_SIZE] = "";
    polynominal polyA, polyB;

    printf("Input polynominal A: ");
    fgets(buf, sizeof buf, stdin);
    polyA = create_poly(buf);

    printf("Input polynominal B: ");
    fgets(buf, sizeof buf, stdin);
    polyB = create_poly(buf);

    polynominal add = add_poly(polyA, polyB);
    polynominal mul = mul_poly(polyA, polyB);

    printf("\nA = ");       print_poly(polyA);
    printf("B = ");         print_poly(polyB);

    printf("\nA + B = ");   print_poly(add);
    printf("A * B = ");     print_poly(mul);

    delete_poly(&polyA);
    delete_poly(&polyB);
    delete_poly(&add);
    delete_poly(&mul);

    return 0;
}

polynominal create_poly(char *str) {
    polynominal poly;
    int i = 0;
    char *token = NULL;

    // 항의 개수 저장
    for (char *p = str; p[i]; p[i] == ' ' ? i++ : *p++);
    i = (i + 1) / 2;

    token = strtok(str, " ");
    poly.terms = (struct term *)calloc(i, sizeof(struct term));
    poly.len = i;

    for (i = 0; token != NULL; i++) {
        poly.terms[i] = (struct term){ 
            .coef = (float)atof(token),
            .exp = atoi(strtok(NULL, " "))
        };

        token = strtok(NULL, " ");
    }

    sort_poly(&poly);
    return poly;
}

int cmp_terms(const void *a, const void *b) {
    const struct term t1 = *(const struct term *)a;
    const struct term t2 = *(const struct term *)b;

    // 지수의 내림차순
    if (t1.exp > t2.exp) return -1;
    if (t1.exp < t2.exp) return 1;
    return 0;
}

void sort_poly(polynominal *poly) {
    qsort(poly->terms, poly->len, sizeof(struct term), cmp_terms);
}

polynominal add_poly(polynominal polyA, polynominal polyB) {
    polynominal result;

    // 실제 길이 계산
    result.len = 0;
    int a = 0, b = 0;

    while (a < polyA.len || b < polyB.len) {
        if (a < polyA.len && (b >= polyB.len || polyA.terms[a].exp > polyB.terms[b].exp)) {
            result.len++; a++;
        }
        else if (b < polyB.len && (a >= polyA.len || polyA.terms[a].exp < polyB.terms[b].exp)) {
            result.len++; b++;
        }
        else {
            result.len++; a++; b++;
        }
    }
    result.terms = (struct term *)calloc(result.len, sizeof(struct term));
    
    a = b = 0;
    for (int i = 0; a < polyA.len || b < polyB.len; i++) {
        // polyA가 현재 가리키는 항이 더 큰가?
        if (a < polyA.len && (b >= polyB.len || polyA.terms[a].exp > polyB.terms[b].exp)) {
            result.terms[i] = polyA.terms[a];
            a++;
        }
        // polyB가 가리키는 게 더 큰가?
        else if (b < polyB.len && (a >= polyA.len || polyA.terms[a].exp < polyB.terms[b].exp)) {
            result.terms[i] = polyB.terms[b];
            b++;
        }
        // 똑같은가?
        else {
            result.terms[i].coef = polyA.terms[a].coef + polyB.terms[b].coef;
            result.terms[i].exp = polyA.terms[a].exp;
            a++; b++;
        }
    }
    return result;
}

polynominal mul_poly(polynominal polyA, polynominal polyB) {
    polynominal result;

    // 우선 최대 길이로 메모리를 할당한다.
    result.len = polyA.len * polyB.len;
    result.terms = (struct term *)calloc(result.len, sizeof(struct term));
    
    // 각각의 항을 곱함
    int i = 0;
    for (int j = 0; j < polyA.len; j++) {
        for (int k = 0; k < polyB.len; k++) {
            result.terms[i] = (struct term){
                .coef = polyA.terms[j].coef * polyB.terms[k].coef,
                .exp = polyA.terms[j].exp + polyB.terms[k].exp
            };
            i++;
        }
    }

    for (int j = 0; j < i; j++) {
        for (int k = j + 1; k < i; k++) {
            // 동류항이라면 합치고, 쉬프트한다.
            if (result.terms[j].exp == result.terms[k].exp) {
                result.terms[j].coef += result.terms[k].coef;
                for (int l = k; l < i - 1; l++)
                    result.terms[l] = result.terms[l + 1];
                i--; k--;
            }
        }
    }

    // 사용하지 않는 공간을 삭제 (실제 사용하는 만큼만 재할당)
    result.terms = (struct term *)realloc(result.terms, i * sizeof(struct term));
    result.len = i;

    sort_poly(&result);
    return result;
}

void print_poly(polynominal poly) {
    float coef;
    if (poly.len == 0) {
        printf("0\n");
        return;
    }

    for (int i = 0; i < poly.len; i++) {
        coef = poly.terms[i].coef;
        if (i != 0)
            coef = coef < 0 ? -coef : coef;

        if (poly.terms[i].exp == 0)
            printf("%.1f", poly.terms[i].coef);
        else if (poly.terms[i].exp == 1)
            printf("%.1fx", poly.terms[i].coef);
        else
            printf("%.1fx^%d", poly.terms[i].coef, poly.terms[i].exp);
    

        if (i < poly.len - 1) {
            if (poly.terms[i + 1].coef > 0)
                printf(" + ");
            else
                printf(" - ");
        }
    }
    putchar('\n');
}

void delete_poly(polynominal *poly) {
    free(poly->terms);
    poly->terms = NULL;
}
/**
 * Cryptography lecture home assignment:
 * A brute force implementation of the integer factoring problem.
 *  @author Matteo Huang
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    unsigned long value;
    struct Node* next;
} NODE;

NODE* init_list(unsigned long val) {
    NODE* first = (NODE*)malloc(sizeof(NODE));

    if (first == NULL) {
        fprintf(stderr, "List initialization failed");
        EXIT_FAILURE;
    }

    first->value = val;
    first->next = NULL;
    return first;
}

// Attention: for simplicity, a O(n) version has been implemented
void tail_insert(NODE* list, unsigned long val) {
    if (list == NULL) {
        fprintf(stderr, "Attention: missing list!");
        EXIT_FAILURE;
    }

    NODE* to_insert = (NODE*)malloc(sizeof(NODE));
    to_insert->value = val;
    to_insert->next = NULL;

    NODE* curr = list;
    int idx = 0;

    while (curr != NULL && curr->next != NULL) {
        curr = curr->next;
        idx++;
    }
    curr->next = to_insert;

    printf("%d inserted at index %d\n", val, idx);
}

void print_list(NODE* list) {
    if (list == NULL) {
        fprintf(stderr, "Attention: missing list!");
        EXIT_FAILURE;
    }

    NODE* curr = list;

    printf("%d ", curr->value);
    curr = curr->next;

    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
}

NODE* factorization_brute_force(unsigned long number_to_factor) {
    //LIST
    NODE* list = init_list(0);

    int cnt = 0;
    unsigned long n = number_to_factor;

    while (n > 1) {
        if (n < 0) {
            printf("Attention: integer too big.\n");
            EXIT_FAILURE;
        }
        else if (n%2 == 0) {
            n /= 2;
            tail_insert(list, 2);
            cnt++;
        }
        else if (n%3 == 0) {
            n /= 3;
            tail_insert(list, 3);
            cnt++;
        }
        else if (n%5 == 0) {
            n /= 5;
            tail_insert(list, 5);
            cnt++;
        } 
        else if (n%7 == 0) {
            n /= 7;
            tail_insert(list, 7);
            cnt++;
        } 
        else {
            tail_insert(list, n);
            cnt++;
            printf("Factorization ended. N's value = %d\nNumber of factors = %d\n", n, cnt);
            break;
        }
    }
    return list;
}

char* simplify(NODE* list) {

    if (list == NULL) {
        fprintf(stderr, "Attention: list empty!");
        EXIT_FAILURE;
    }

    int diff_int_cnt = 1;
    int same_int_cnt = 0;

    // COUNTS THE DIFFERENT INTEGERS INSIDE THE LIST
    NODE* prev = list;
    NODE* curr = list->next;
    while (curr != NULL) {
        if (prev != curr) diff_int_cnt++;
        prev = prev->next;
        curr = curr->next;
    }

    // GETS EACH INTEGERS' OCCURRENCY
    int* integer_occs = (int*)calloc(diff_int_cnt, sizeof(int));
    int occs_idx = 0;
    prev = list;
    curr = list->next;
    while (curr != NULL) {
        if (prev == curr) same_int_cnt++;
        else {
            integer_occs[occs_idx] = same_int_cnt;
            occs_idx++;
            same_int_cnt = 0;
        } 
    }

    // BUILDS THE SIMPLIFIED STRING OF INTEGERS
    prev = list;
    curr = list->next;
    char* str = (char*)calloc((diff_int_cnt*4)+1, sizeof(char));
    occs_idx = 0;
    int str_idx = 0;
    while (curr != NULL) {
        if (prev != curr) {
            str[str_idx] = prev->value;
            str[str_idx+1] = '^';
            str[str_idx+2] =  integer_occs[occs_idx];
            str[str_idx+3] = '+';
            str_idx++;
            occs_idx++;
        } else {
            prev = prev->next;
            curr = curr->next;
        }
    }

    return str;
}

int main(int argc, char** argv) {
    unsigned long arg_integer = strtol(argv[1], NULL, 10);
    NODE* list = factorization_brute_force(arg_integer);
    print_list(list->next);

/*
    char* str = simplify(list->next);
    printf("Simplified expression:\n");
    while (*str != '\n') {
        if (*str != '+') printf("%c");
        else printf(" %c ");
    }
    printf("\n");
*/

    return 0;
}
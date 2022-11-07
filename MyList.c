/**
 * List implementation
*/

#include <stdio.h>
#include <stdlib.h>

#undef DEBUG
#define DEBUG 0

typedef struct Node {
    int value;
    struct Node* next;
} NODE;

NODE* init_list(int val) {
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
void tail_insert(NODE* list, int val) {
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

int main(void) {
    NODE* list = init_list(1);
    tail_insert(list, 100);

#ifdef DEBUG
    printf("DEBUG:\n");
    NODE* curr = list;
    int idx = 0;
    while (curr != NULL) {
        printf("%d) %d\n", idx, curr->value);
        curr = curr->next;
        idx++;
    }
    printf("\n");
    if (curr == NULL) printf("The node at index %d is NULL.\n", idx);
#endif

    tail_insert(list, 1000);
    print_list(list);
    return 0;
}
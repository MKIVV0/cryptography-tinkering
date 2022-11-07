/**
 * Cryptography lecture home assignment:
 * A brute force implementation of the integer factoring problem.
 *  @author Matteo Huang
*/

#include <stdio.h>
#include <stdlib.h>

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

int factorization_brute_force(int number_to_factor) {
    //LIST
    NODE* list = init_list(0);

    int cnt = 0;
    int n = number_to_factor;

    while (1) {
        if (n%2 == 0) {
            n /= 2;
            tail_insert(list, 2);
        }
        else if (n%3 == 0) {
            n /= 3;
            tail_insert(list, 3);
        }
        else if (n%5 == 0) {
            n /= 5;
            tail_insert(list, 5);
        } 
        else if (n%7 == 0) {
            n /= 7;
            tail_insert(list, 7);
        } else {
            printf("Factorization ended. N's value = %d\n", n);
            break;
        }
    }

    NODE* curr = list;

    // ORDER THE LIST
    //TRAVERSE THE LIST L AND GET A COUNTER THAT INDICATES THE LIST'S LENGTH |L|
    int el_cnt = 0;
    while (curr != NULL) {
        curr = list->next;
        el_cnt++;
    }

    // GETS THE NUMBER OF DIFFERENT INTEGERS CONTAINED IN THE LIST
    int diff_nums = 1;
    curr = list;
    while (curr->next != NULL) {
        if (curr != NULL && curr->value == 0 && curr->next != NULL) curr = curr->next;

        if (curr->value != curr->next->value) {
            diff_nums++;
            curr = curr->next;
        }
    }


    return 0;
}

int main(int argc, char** argv) {
    
    return 0;
}
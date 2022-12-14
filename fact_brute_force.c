/**
 * Cryptography lecture home assignment:
 * A brute force implementation of the integer factoring problem.
 *  @author Matteo Huang
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0

typedef struct Node
{
    unsigned long value;
    struct Node *next;
} NODE;

NODE *init_list(unsigned long val)
{
    NODE *first = (NODE *)malloc(sizeof(NODE));

    if (first == NULL)
    {
        fprintf(stderr, "List initialization failed");
        EXIT_FAILURE;
    }

    first->value = val;
    first->next = NULL;
    return first;
}

// Attention: for simplicity, a O(n) version has been implemented
void tail_insert(NODE *list, unsigned long val)
{
    if (list == NULL)
    {
        fprintf(stderr, "Attention: missing list!");
        EXIT_FAILURE;
    }

    NODE *to_insert = (NODE *)malloc(sizeof(NODE));
    to_insert->value = val;
    to_insert->next = NULL;

    NODE *curr = list;
    int idx = 0;

    while (curr != NULL && curr->next != NULL)
    {
        curr = curr->next;
        idx++;
    }
    curr->next = to_insert;

    printf("%d inserted at index %d\n", val, idx);
}

void print_list(NODE *list)
{
    if (list == NULL)
    {
        fprintf(stderr, "Attention: missing list!");
        EXIT_FAILURE;
    }

    NODE *curr = list;

    printf("%d ", curr->value);
    curr = curr->next;

    while (curr != NULL)
    {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
}


// Factorization brute force function
NODE *factorization_brute_force(unsigned long number_to_factor)
{
    // LIST
    NODE *list = init_list(0);

    int cnt = 0;
    unsigned long n = number_to_factor;
    int f = 2;

    while (n > 1)
    {
        if (n < 0)
        {
            printf("Attention: integer too big.\n");
            EXIT_FAILURE;
        }
        else if (n % f == 0)
        {
            n /= f;
            tail_insert(list, f);
            cnt++;
        }
        else
            f++;
    }

    tail_insert(list, n);
    cnt++;
    printf("Factorization ended. N's value = %d\nNumber of steps = %d\n", n, cnt);

    return list;
}

// Factorization reversal function
unsigned long factorization_reversal(NODE* list) {
    unsigned long result = 1;

    NODE* tmp = list->next; // the list has a starting node which element is 0, therefore, a node has to be skipped
    int i = 0;
    while (tmp != NULL && tmp->next != NULL) {
        result = result * tmp->value;
#if DEBUG
        printf("result at step %d: %d\n", result, i++);
#endif
        tmp = tmp->next;
    }

    return result;
}

// Formats the given list into a more readable form. E.g. list = (2,2,2,3,3) --> 2^3 * 3^2 * 1
void simplify(NODE *list)
{
    if (list == NULL)
    {
        fprintf(stderr, "Attention: list empty!");
        EXIT_FAILURE;
    }

    int number_of_factors = 0;
    int occ_cnt = 1;
    NODE *list_p = list;
    NODE *list_p_next = list->next;
    while (list_p_next != NULL && list_p != NULL)
    {
        if (list_p->value != list_p_next->value) ++number_of_factors;
        if (list_p->value == list_p_next->value)
        {
            ++occ_cnt;
            list_p = list_p->next;
            list_p_next = list_p_next->next;

        }
        else if (occ_cnt == 1)
        {
            printf("%d * ", list_p->value);
            list_p = list_p->next;
            list_p_next = list_p_next->next;
        }
        else
        {
            printf("%d^%d * ", list_p->value, occ_cnt);
            occ_cnt = 1;
            list_p = list_p->next;
            list_p_next = list_p_next->next;
        }
    }
    printf("%d\n", list_p->value);
    printf("Number of factors = %d\n", number_of_factors+1);
}
 
int main(int argc, char **argv)
{   
    clock_t t1 = clock();

    unsigned long arg_integer = strtol(argv[1], NULL, 10);
    NODE *list = factorization_brute_force(arg_integer); // list of factors
    // print_list(list->next);

    simplify(list->next);

    t1 = clock() - t1;
    double time_elapsed_1 = (((double)t1)/CLOCKS_PER_SEC)*1000;
    printf("Time elapsed for N's factorization: %f ms\n\n\n", time_elapsed_1);



    clock_t t2 = clock();
    unsigned long rev_fact = factorization_reversal(list); // factorization reversal
    t2 = clock() - t2;
    double time_elapsed_2 = (((double)t2)/CLOCKS_PER_SEC)*1000;
    printf("Result of the factorization reversal: %d\n", rev_fact);
    printf("Time elapsed for the factorization reversal: %f ms\n", time_elapsed_2);

    return 0;
}
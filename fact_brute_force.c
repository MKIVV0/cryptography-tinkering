/**
 * Cryptography lecture home assignment:
 * A brute force implementation of the integer factoring problem.
 *  @author Matteo Huang
 */

#include <stdio.h>
#include <stdlib.h>

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
    printf("Factorization ended. N's value = %d\nNumber of factors = %d\n", n, cnt);

    return list;
}

char *simplify(NODE *list)
{

    if (list == NULL)
    {
        fprintf(stderr, "Attention: list empty!");
        EXIT_FAILURE;
    }

    int list_length = 0;
    NODE *tmp_node = list;

    // Gets the list's length
    while (tmp_node->next != NULL)
    {
        tmp_node = tmp_node->next;
        list_length++;
    }

    /*
        // dinamically allocated result array
        char *tmp = (char *)calloc(list_length * 4 + 1, sizeof(char));

            // occurrencies of a number that gets resetted to 1 each time list_p != list_p_next
            int num_occurrencies = 1;
            // points to the first element of the list
            NODE *list_p = list;
            // points to the element that follows the element pointed by list_p
            NODE *list_p_next = list->next;
            // keeps track of the index of tmp, in order to insert the elements in format (num^occurrencies +)
            int tmp_index = 0;

            while (list_p != NULL && list_p_next != NULL)
            {
                if (list_p->value == list_p_next->value)
                {
                    ++num_occurrencies;
                    list_p = list_p->next;
                    list_p_next = list_p_next->next;
                }
                else
                {
                    tmp[tmp_index++] = list_p->value;
                    tmp[tmp_index++] = '^';
                    tmp[tmp_index++] = num_occurrencies;
                    tmp[tmp_index] = '+';
                    num_occurrencies = 1;
                }
            }

            tmp[--tmp_index] = '\n';
            */

    // return tmp;
}

int main(int argc, char **argv)
{
    unsigned long arg_integer = strtol(argv[1], NULL, 10);
    NODE *list = factorization_brute_force(arg_integer);
    print_list(list->next);
    char *simplified_res = simplify(list->next);

    while (*simplified_res != '\n')
        printf("%c", *simplified_res);
    printf("\n");

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
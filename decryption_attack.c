/*
* Program description:
* TODO
*
* Assumptions:
* 1) The attacker knows that the texts are in english;
* 2) The attacker can perform a chosen-ciphertext attack, hence they can
* access the encyption program and decrypt as many and whatever text files 
* as they want;
* 3) The attacker has a statistic about english alphabet letter occurrencies.
*
* English letter frequencies source: https://en.wikipedia.org/wiki/Letter_frequency
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define FIRST_ASCII_LETTER_CODE 97  // lowercase a
#define LAST_ASCII_LETTER_CODE 122   // lowercase z
#define ENG_ALPHABET_NUMBER (LAST_ASCII_LETTER_CODE - FIRST_ASCII_LETTER_CODE + 1) // 26

struct letterinfo {
    double percentage;
    char ch;
};

typedef struct letterinfo LETTER;


void count_occurrencies(char* file_name, int occurrencies_list[]);
void swap(LETTER* list, int a, int b);
int partition(LETTER* list, int l, int r);
void quicksort(LETTER* list, int l, int r);
void decrypt_file(char* file_name, LETTER eng_letter_occurrencies[], LETTER text_letter_occurrencies[]);


int main(int argc, char **argv) {
    LETTER E; E.ch = 'e'; E.percentage = 13.0;
    LETTER T; T.ch = 't'; T.percentage = 9.1;
    LETTER A; A.ch = 'a'; A.percentage = 8.2;
    LETTER O; O.ch = 'o'; O.percentage = 7.5;
    LETTER I; I.ch = 'i'; I.percentage = 7.0;
    LETTER N; N.ch = 'n'; N.percentage = 6.7;
    LETTER S; S.ch = 's'; S.percentage = 6.3;
    LETTER H; H.ch = 'h'; H.percentage = 6.1;
    LETTER R; R.ch = 'r'; R.percentage = 6.0;
    LETTER D; D.ch = 'd'; D.percentage = 4.3;
    LETTER L; L.ch = 'l'; L.percentage = 4.0;
    LETTER C; C.ch = 'c'; C.percentage = 2.8;
    LETTER U; U.ch = 'u'; U.percentage = 2.8;
    LETTER M; M.ch = 'm'; M.percentage = 2.4;
    LETTER W; W.ch = 'w'; W.percentage = 2.4;
    LETTER F; F.ch = 'f'; F.percentage = 2.2;
    LETTER G; G.ch = 'g'; G.percentage = 2.0;
    LETTER Y; Y.ch = 'y'; Y.percentage = 2.0;
    LETTER P; P.ch = 'p'; P.percentage = 1.9;
    LETTER B; B.ch = 'b'; B.percentage = 1.5;
    LETTER V; V.ch = 'v'; V.percentage = 0.98;
    LETTER K; K.ch = 'k'; K.percentage = 0.77;
    LETTER J; J.ch = 'j'; J.percentage = 0.15;
    LETTER X; X.ch = 'x'; X.percentage = 0.15;
    LETTER Q; Q.ch = 'q'; Q.percentage = 0.095;
    LETTER Z; Z.ch = 'z'; Z.percentage = 0.074;

    LETTER eng_letters_occurrencies[] = {E, T, A, O, I, N, S, H, R, D, L, C, U, M, W, F, G, Y, P, B, V, K, J, X, Q, Z};

    /* 
    * This list's purpouse is to explicit the logic behind the occurrency counting for a given text at code level. 
    * E.g: the counter in position 0 is reserved for the letter 'e' and so on. 
    * */
    int text_occurrencies_list[] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'};
    for (int i = 0; i < ENG_ALPHABET_NUMBER; i++)
        text_occurrencies_list[i] = 0;
    
    char* encrypted_file = "content.txt";
    count_occurrencies(encrypted_file, text_occurrencies_list);

    // prints each letter occurrency in the given text
    for (int i = 0; i < ENG_ALPHABET_NUMBER; i++)
        printf("index %d, letter %c count: %d\n", i, eng_letters_occurrencies[i], text_occurrencies_list[i]);
    
    // Counts the total number of characters of the given file
    int total_ch_num = 0;
    for (int i = 0; i < ENG_ALPHABET_NUMBER; i++)
        total_ch_num += text_occurrencies_list[i];
    printf("TOTAL LETTER NUMBER: %d\n\n", total_ch_num);


    // Converts the given file occurrencies in percentages
    LETTER ch_percentage_list[26];
    for (int i = 0; i < ENG_ALPHABET_NUMBER; i++) {
       ch_percentage_list[i].ch = eng_letters_occurrencies[i].ch;
       ch_percentage_list[i].percentage = (text_occurrencies_list[i]/((double)total_ch_num))*100;
    }

    quicksort(ch_percentage_list, 0, ENG_ALPHABET_NUMBER - 1);

    // Prints the percentages
    for (int i = 0; i < ENG_ALPHABET_NUMBER; i++)
       printf("letter %c percentage: %.2f at index %d\n", ch_percentage_list[i].ch, ch_percentage_list[i].percentage, i);
    printf("\n\n");

    /*Decryption for substitution with the data retrieved*/
    decrypt_file(encrypted_file, eng_letters_occurrencies, ch_percentage_list);


    return 0;
}

/*
* This function counts the letter occurrencies of a given text file.
*/
void count_occurrencies(char* file_name, int occurrencies_list[]) {
    FILE *file_pointer;
    char ch = 0;
    
    // Opens the file in reading mode
    file_pointer = fopen(file_name, "r");

    printf("%s content analysis:\n", file_name);
    if (file_pointer == NULL) {
        fprintf(stderr,"File not available.\n");
        exit(EXIT_FAILURE);
    }

    /* Prints the file content character by character, until 
    * until the end of file character is encountered.
    */
    while (ch != EOF){
        ch = tolower(fgetc(file_pointer));

        switch (ch) {
            case 'e':
                occurrencies_list[0]++;
                break;
            case 't':
                occurrencies_list[1]++;
                break;
            case 'a':
                occurrencies_list[2]++;
                break;
            case 'o':
                occurrencies_list[3]++;
                break;
            case 'i':
                occurrencies_list[4]++;
                break;
            case 'n':
                occurrencies_list[5]++;
                break;
            case 's':
                occurrencies_list[6]++;
                break;
            case 'h':
                occurrencies_list[7]++;
                break;
            case 'r':
                occurrencies_list[8]++;
                break;
            case 'd':
                occurrencies_list[9]++;
                break;
            case 'l':
                occurrencies_list[10]++;
                break;
            case 'c':
                occurrencies_list[11]++;
                break;
            case 'u':
                occurrencies_list[12]++;
                break;
            case 'm':
                occurrencies_list[13]++;
                break;
            case 'w':
                occurrencies_list[14]++;
                break;
            case 'f':
                occurrencies_list[15]++;
                break;
            case 'g':
                occurrencies_list[16]++;
                break;
            case 'y':
                occurrencies_list[17]++;
                break;
            case 'p':
                occurrencies_list[18]++;
                break;
            case 'b':
                occurrencies_list[19]++;
                break;
            case 'v':
                occurrencies_list[20]++;
                break;
            case 'k':
                occurrencies_list[21]++;
                break;
            case 'j':
                occurrencies_list[22]++;
                break;
            case 'x':
                occurrencies_list[23]++;
                break;
            case 'q':
                occurrencies_list[24]++;
                break;
            case 'z':
                occurrencies_list[25]++;
                break;
        }

        //printf("%c", ch);
    }
    printf("\n");
    fclose(file_pointer);
}

void swap(LETTER* list, int a, int b)  {
    LETTER tmp = list[a];
    list[a] = list[b];
    list[b] = tmp;
}

int partition(LETTER* list, int l, int r) {
    LETTER v = list[l];
    int i = l;
    int j = r+1;
    while (1) {
        do { i++; } while (list[i].percentage > v.percentage && i < r);
        do { j--; } while (list[j].percentage < v.percentage && j > l);
        if (i >= j) break;
        swap(list, i, j);
    }
    swap(list, l, j);
    return j;
}

void quicksort(LETTER* list, int l, int r) {
    if (r <= l) return;
    int j = partition(list, l, r);
    quicksort(list, l, j);
    quicksort(list, j+1, r);
}

void decrypt_file(char* file_name, LETTER eng_letter_occurrencies[], LETTER text_letter_occurrencies[]) {
    FILE *file_pointer;
    FILE *dest_file;
    char ch = 0;
    char ch_dest = 0;

    double quotient[26];

    for (int i = 0; i < ENG_ALPHABET_NUMBER; i++) {
        printf("Division between %c and %c percentages\n", text_letter_occurrencies[i].ch, eng_letter_occurrencies[i].ch);
        quotient[i] = text_letter_occurrencies[i].percentage/eng_letter_occurrencies[i].percentage;
        printf("QUOTIENT: %.2f\n\n", quotient[i]);
    }
    
    // Opens the file in reading mode
    file_pointer = fopen(file_name, "r");
    dest_file = fopen("statistical_decryption_attack.txt", "w");

    printf("Deryption attack on file %s\n", file_name);
    if (file_pointer == NULL) {
        fprintf(stderr,"File not available.\n");
        exit(EXIT_FAILURE);
    }

    /* Prints the file content character by character, until 
    * until the end of file character is encountered.
    */
    while (ch != EOF){
        ch = tolower(fgetc(file_pointer));

        if (ch == text_letter_occurrencies[0].ch) {
            if (quotient[0] > 0.5) {
                ch_dest = eng_letter_occurrencies[0].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[1].ch) {
            if (quotient[1] > 0.5) {
                ch_dest = eng_letter_occurrencies[1].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[2].ch) {
            if (quotient[2] > 0.5) {
                ch_dest = eng_letter_occurrencies[2].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[3].ch) {
            if (quotient[3] > 0.5) {
                ch_dest = eng_letter_occurrencies[3].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[4].ch) {
            if (quotient[4] > 0.5) {
                ch_dest = eng_letter_occurrencies[4].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[5].ch) {
            if (quotient[5] > 0.5) {
                ch_dest = eng_letter_occurrencies[5].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[6].ch) {
            if (quotient[6] > 0.5) {
                ch_dest = eng_letter_occurrencies[6].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[7].ch) {
            if (quotient[7] > 0.5) {
                ch_dest = eng_letter_occurrencies[7].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[8].ch) {
            if (quotient[8] > 0.5) {
                ch_dest = eng_letter_occurrencies[8].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[9].ch) {
            if (quotient[9] > 0.5) {
                ch_dest = eng_letter_occurrencies[9].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[10].ch) {
            if (quotient[10] > 0.5) {
                ch_dest = eng_letter_occurrencies[10].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[11].ch) {
            if (quotient[11] > 0.5) {
                ch_dest = eng_letter_occurrencies[11].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[12].ch) {
            if (quotient[12] > 0.5) {
                ch_dest = eng_letter_occurrencies[12].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[13].ch) {
            if (quotient[13] > 0.5) {
                ch_dest = eng_letter_occurrencies[13].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[14].ch) {
            if (quotient[14] > 0.5) {
                ch_dest = eng_letter_occurrencies[14].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[15].ch) {
            if (quotient[15] > 0.5) {
                ch_dest = eng_letter_occurrencies[15].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[16].ch) {
            if (quotient[16] > 0.5) {
                ch_dest = eng_letter_occurrencies[16].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[17].ch) {
            if (quotient[17] > 0.5) {
                ch_dest = eng_letter_occurrencies[17].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[18].ch) {
            if (quotient[18] > 0.5) {
                ch_dest = eng_letter_occurrencies[18].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[19].ch) {
            if (quotient[19] > 0.5) {
                ch_dest = eng_letter_occurrencies[19].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[20].ch) {
            if (quotient[20] > 0.5) {
                ch_dest = eng_letter_occurrencies[20].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[21].ch) {
            if (quotient[21] > 0.5) {
                ch_dest = eng_letter_occurrencies[21].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[22].ch) {
            if (quotient[22] > 0.5) {
                ch_dest = eng_letter_occurrencies[22].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[23].ch) {
            if (quotient[23] > 0.5) {
                ch_dest = eng_letter_occurrencies[23].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[24].ch) {
            if (quotient[24] > 0.5) {
                ch_dest = eng_letter_occurrencies[24].ch;
                fputc(ch_dest, dest_file);
            }
        } else if (ch == text_letter_occurrencies[25].ch) {
            if (quotient[25] > 0.5) {
                ch_dest = eng_letter_occurrencies[25].ch;
                fputc(ch_dest, dest_file);
            }
        }
        else {
            fputc(ch, dest_file);
        }
        
        
        //printf("%c", ch);
    }
    printf("\n");
    fclose(file_pointer);
}
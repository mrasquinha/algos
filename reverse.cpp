#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* It does not work: If i dont make the copy aa of new_ptr
 * there is no infinite loop but the string is not reversed either.
 * Since new_ptr is at the end of the string.. need to move it back
 */
/* Reverse the string */
void reverse(char* str) {
    int len = strlen(str);
    char* ptr = str+len;

    printf("Input string:\t %s\n", str);
    while(ptr>=str) {
        printf("%c", *ptr);
        ptr--;
    }
    printf("\n");
}

/* power set way of finding subsets. This wont work because order matters.
 * For eg. wont work with inputs asd sa; will work with asd as.
 * It will still work if you sort both strings and then try the power set
 */
int is_permuation(char* str1, char* str2) {
    int len = strlen(str1);
    int seed = pow(2,len); 
    char *new_str = (char*)malloc(len*sizeof(char));

    for (int i=1; i<seed; i++) {
        int key = i;
        strcpy(new_str,"");
        char *tmp = new_str;
        while(key) {
            int set_idx = log2(key&(~key+1));   // extract the rightmost set bit

            *tmp = str1[set_idx];
            key=key&(key-1); // flip the rightmost set bit
            //printf("%d %c|%s ", set_idx, str1[set_idx], new_str);
            tmp++;
        }
        *tmp = '\0';

        if (!strcmp(new_str,str2)) {
            printf("seed=%d %s %d\n", i, new_str, strcmp(new_str, str2));
            break;
        }
    }
    return !strcmp(new_str,str2);
}

void replace_spaces(char* str) {
    int length = strlen(str)-1;
    char *tmp = str;
    int space_cnt = 0;

    while(*tmp!='\0') {
        if (*tmp == ' ') space_cnt++;
        tmp++;
    }
    printf ("String: %s num_spaces=%d length=%d\n", str, space_cnt, length);
    char *new_str = (char*)malloc(sizeof(char)*(length+2*space_cnt)+1);
    //new_str = new_str + (length+2*space_cnt);
    //*new_str = '\0'; new_str--;
    char *tmp2 = new_str;

    for (int i=0; i<=length; i++) {
        if(str[i] != ' ') {
            *new_str = str[i]; new_str++;
        }
        else {
            *new_str = '0'; new_str++;
            *new_str = '2'; new_str++;
            *new_str = '%'; new_str++;
        }
    }
    new_str = '\0';
    printf ("New string: %s \n", tmp2);
}

/* replace spaces with %20 without using a new string
 * pointer manipulation from the end of the string
 */
void replace_spaces_ptr(char* str) {
    int length = strlen(str);
    int space_cnt = 0;
    int end_str_len = 0;
    for (int i=0; i<length; i++) {
        if(str[i] == ' ' && str[i+1] == ' ') {
            end_str_len = i; 
            break;
        }
    }

    if(end_str_len == 0) {
        printf("Error in input string \n");
        exit(0);
    }

    printf ("String: %s end_str=%d length=%d\n", str, end_str_len, length);
    char *tmp = str + length-1;
    for (int i=end_str_len-1; i>0; i--) {
        if(str[i] != ' ') {
            *tmp = str[i];
            tmp--;
        }
        else {
            *tmp = '0'; tmp--;
            *tmp = '2'; tmp--;
            *tmp = '%'; tmp--;
        }
    }

    printf ("New string: %s \n", str);
}
// Too slow; needs n+n-1+n-2... comparisons
// as many as n swaps
void selection_sort (char *str) {
    printf ("Input str: %s", str);
    int length = strlen(str);
    for (int i=0; i<length; i++) {
        int min = i;
        for (int j=i+1; j<length; j++) {
            if(str[j]<str[min]) 
                min = j;
        }
        if(i!=min) { //swap
            char tmp = str[i];
            str[i] = str[min];
            str[min] = tmp;
        }
    }
    printf ("\tOutput str: %s\n", str);
    return;
}

void is_substring(char *str) {
    int len = strlen(str);
    printf("str: %s\tlen=%d\t", str, len);

    // swap the 0th elem with n-1
    char tmp;
    tmp = str[0];
    str[0] = str[len-1];
    str[len-1] = tmp;

    for(int i=1; i<len; i++) {
        tmp = str[i];
        str[i] = str[len-1];
        str[len-1] = tmp;
    }
    printf("rotated str: %s \n", str);
}

/*Implement  a  function  for  reversing  the  words  in  a  string. 
 * Your function should use O(1) space 
 */
void reverse_words(char* str)
{
    int length = strlen(str);
    printf("Str is:\t%s length=%d\n", str, length);
    //swap every i with n-i
    for (int i=0; i<length/2; i++) {
        char tmp = str[i];
        str[i] = str[length-i-1];
        str[length-i-1] = tmp;
    }

    //swap every word
    char *end = str;
    char *start = str;
    int k = 0;
    while (k<length) {
        while(*end != ' ' && k<length)  { end++; k++; }
        //new word
        int len = end - start;
        char *wordst = start;
        char *wordend = end-1;

        end++; k++; start = end; //skip space;

        printf("new word:\t len=%d st=%c\tend=%c\t", len, *wordst, *wordend);
        for (int j=0; j<len/2; j++) {
            //printf("swap:\t%c\t%c \n", *wordst, *wordend);
            char tmp = *wordst;
            *wordst = *wordend;
            *wordend = tmp;
            wordst++; wordend--;
        }
        printf("str: %s\tend=%c\n",str,*end);
    }
}
int main (int argc, char** argv) {
    if(argc<2) {
        printf("Input string missing!\n");
        exit(1);
    }
    //1.2 reverse(argv[1]);
    /*1.3 strA is permutation of strB
    if (argc<3) { printf("Invalid input\n"); }
    char *str1, *str2;
    if(strlen(argv[1]) > strlen(argv[2])) {
        str1 = argv[1];
        str2 = argv[2];
    }
    else {
        str1 = argv[2];
        str2 = argv[1];
    }
    selection_sort(str1);
    selection_sort(str2);
    printf("Is permuations? %s \n", is_permuation(str1, str2) ? "Yes" : "No");
    */

    //1.4replace_spaces(argv[1]);
    /*1.4replace spaces where the length is given
    char *str = argv[1];
    int length = strlen(str);
    char *tmp = str;
    int space_cnt = 0;

    while(*tmp!='\0') {
        if (*tmp == ' ') space_cnt++;
        tmp++;
    }

    int new_str_len = length + 2*space_cnt;
    char *new_str = (char*)malloc(sizeof(char)*new_str_len);

    memset(new_str,' ', new_str_len);
    strncpy(new_str, str, length);
    new_str[new_str_len] = '\0';

    replace_spaces_ptr(new_str);
    */

    //1.8 is_substring(argv[1]);
    reverse_words(argv[1]);
}
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>

void swap (int* a, int*b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// small: 0 - (small-1)
// equal: small - (equal-1)
// unsorted: equal to large
// large: large+1 to N
void dutch_flag(int* elements, int pivot, int num_elem) {
    for(int i=0; i<num_elem; i++)
        printf(" %d", elements[i]);
    printf("  sort based on elem %d num_elem=%d\n", pivot, num_elem);
    int small=0, equal=0, large=num_elem-1;
    while(equal <= large) {
        if(elements[equal] < pivot) {
            // printf("*swap %d->%d ", elements[equal], elements[small]);
            swap (&elements[equal++], &elements[small++]);
        }
        else if (elements[equal] > pivot) {
            //printf("swap %d->%d ", elements[equal], elements[large]);
            swap (&elements[equal], &elements[large--]);
        }
        else 
            equal++;
    }

    printf("Output");
    for(int i=0; i<num_elem; i++)
        printf(" %d", elements[i]);
    printf("\n");
}

int main (int argc, char** argv) {
    if (argc < 1) {
        printf ("Invalid input \n");
        exit(0);
    }
    int *elements = (int*)malloc(sizeof(int)*(argc-2));
    for (int i=1; i<argc-1; i++) {
        elements[i-1] = atoi(argv[i]);
    }

    int num_elem = argc - 2;
    int index = atoi(argv[argc-1]);

    int pivot = elements[index];
    dutch_flag(elements, pivot, num_elem);

}
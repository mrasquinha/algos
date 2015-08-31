#include <cstdlib>
#include <stdio.h>

// Solve the 3sum problem: Given an array(S) find all unique pairs 
// such that a+b=c and a,b,c belong to S and a != b != c

//swap two numbers
void swap (int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;

    return;
}

void print_elem (int *elem, int N, const char* str)
{
    printf("%s: ", str);
    for (int i=0; i<N; i++)
        printf("%d ", elem[i]);

    printf("\n");
}

int partition (int *elem, int lo, int hi)
{
  int i=lo, j=hi+1;

  while (1) {
    while (elem[++i] < elem[lo])    //++i to retain i for the swap
      if (i >= hi) break;

    while (elem[--j] > elem[lo])    //--j to retain j for the swap
      if (j <= lo) break; 

    if(i>=j) break;                 // crossed over
    swap (&elem[i], &elem[j]);
  }

  swap(&elem[lo], &elem[j]);

  return j;
}

void quick_sort (int* elem, int lo, int hi) 
{
  if (hi <= lo) return;

  // select a pivot and insert in place
  int j = partition(elem, lo, hi);
  quick_sort(elem, lo, j-1);
  quick_sort(elem, j+1 , hi);

  return;
}

void sort (int* elem, int N)
{
    quick_sort(elem, 0, N-1);
}

bool binary_search (int *elem, int lo, int hi, int search)
{
  while (lo <= hi) {
    int mid = lo + (hi - lo)/2;
    if(elem[mid] == search) return true;
    else if (elem[mid] < search) {
      lo = mid + 1;
      binary_search (elem, lo, hi, search);
    }
    else {
      hi = mid - 1;
      binary_search (elem, lo, hi, search);
    }
  }

  return false;
}

void three_sum (int *elem, int N, bool has_neg) 
{
  int max = elem[N];
  int start = N;
  int is_3sum_cnt = 0;
  int mask0 = 0, mask1 = 0;

  // Given no negative integers the max element will not meet 3sum
  if(!has_neg) start--;

  for (int i=start; i>=0; i--) {
    int prev_elem = -1, prev_found = 0;
    for (int j=0; j<i; j++) {
      bool found = false; //does this pair exist in array
      if (elem[j] == 0) continue;
      if (prev_elem == elem[j] && prev_found) found = true;
      
      if(!found) {
        int search_elem = elem[i] + elem [j];
        if (search_elem > max) break;
        int *sub_array = &elem[i+1];
        int sub_array_elem = N - i;

        //printf("Search %d in array starting at %d with %d elem \n", search_elem, i+1, sub_array_elem );
        found = binary_search(sub_array, 0, sub_array_elem-1, search_elem);
      }

      if (found) {
        is_3sum_cnt++;
        // Do not flip the bit if this elem forms a 3sum twice
        if((mask0 & (1<<i)) == 0) mask0 |= (1<<i);
        if((mask1 & (1<<j)) == 0) mask1 |= (1<<j);
      }

      //update prev data
      prev_elem = elem[j]; prev_found = 1;
    }
  }

  if(mask0) { //mask0 and mask1 are updated together
    printf("\nValues for a:\t");
    for (int i=0; i<N; i++)
      if(mask0 & (1<<i)) printf ("%d ", elem[i]);

    printf("\nValues for b:\t");
    for (int i=0; i<N; i++)
      if(mask1 & (1<<i)) printf ("%d ", elem[i]);
  }
  printf("\nthree_sum count = %d\n", is_3sum_cnt);
}

int main (int argc, char **argv) 
{
  if(argc <= 1) {
    printf ("Usage: ./three_sum <Num_elem>\n");
    exit(1);
  }

  int num_elem = atoi(argv[1]);
  bool has_negative = false;

  printf("Three sum over %d elements\n", num_elem);

  int *elements = (int*)malloc(sizeof(int) * num_elem);
  // Note: Assumptions for data set
  // 1. May contain duplicates
  // 2. May contain zero
  // 3. May be negative

  srand(0xDEADBEEF);
  for (int i=0; i<num_elem; i++) {
    elements[i] = rand()%num_elem;
    if (elements[i] < 0)  has_negative = true;
  }
  print_elem (elements, num_elem, "Init");

  // sort the array using quick sort
  sort (elements, num_elem);
  //print_elem(elements, num_elem, "Sorted");
  three_sum (elements, num_elem-1, has_negative);

  exit(0);
}


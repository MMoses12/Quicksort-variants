/* Onomateponyma: Gavouras Dimitrios  (03145)
 *	              Gerontidis Georgios (03261)
 *	              Moysis Moysis       (03250) */
/* This program only gets input from files. The user can press
 * ctrl + d to put input from terminal. */
 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct {
	int *table;
	int inserted;
} array_t;

typedef struct {
    long int comparisons;
    long int assignments;
} stats_t;

void make_array (array_t *arr) {
	int result, number;

	do {
		result = scanf("%d", &number);
		if (result == EOF) {
			break;
		} 
			
		arr->table[arr->inserted] = number;
		arr->inserted ++;
	} while(1);
}

void swap(int* a, int* b) {
    int temp = *a;
    
    *a = *b;
    *b = temp;
}

void quicksort_2p_r (int* arr, int left, int right, stats_t *find) {    
    int pos1, pos2, leftPivot, rightPivot;
    int i = left + 1, j = right - 1, k = left + 1;
    
	if (right > left) {
    	if (right - left == 1) {
    		if (arr[left] > arr[right]) {
        		swap(&arr[left], &arr[right]);
                find->assignments += 3;
        	}
           
            find->comparisons += 2;
        	return;
       	}
       
       	pos1 = left + rand() % (right-left);
	
		pos2 = left + rand() % (right-left);
		while (pos2 == pos1) {	
			pos2 = left + rand() % (right-left);
		}
		
		swap(&arr[left], &arr[pos1]);
		swap(&arr[right], &arr[pos2]);
        
        find->assignments += 6;
   		
   		if (arr[left] > arr[right])
        	swap(&arr[left], &arr[right]);
        find->comparisons += 1;
        
 		leftPivot = arr[left], 
   	 	rightPivot = arr[right];

		while (k <= j) {
		    // If elements are less than the left pivot
		    if (arr[k] < leftPivot) {
		        swap(&arr[k], &arr[i]);
		        i++;
                
                find->assignments += 3;
            }
		    // If elements are greater than or equal to the right pivot
		    else if (arr[k] >= rightPivot) {
                while (++find->comparisons && arr[j] > rightPivot && k < j)
		            j--;
		        swap(&arr[k], &arr[j]);
		        j--;
		        
		        if (arr[k] < leftPivot) {
		            swap(&arr[k], &arr[i]);
		            i++;
		        }
                
                find->assignments += 6;
		    }
		    k++;
		}
		i--;
		j++;
 
		// Bring pivots to their appropriate positions.
		swap(&arr[left], &arr[i]);
		swap(&arr[right], &arr[j]);
		
        find->assignments += 6;
		
		// Recursive call.
		quicksort_2p_r(arr, left, i-1, find);
		quicksort_2p_r(arr, i + 1, j-1, find);
		quicksort_2p_r(arr, j + 1, right, find);
	}
}
 

int main (int argc, char *argv[]) {
	array_t arr;
	clock_t start, end;
	double quicksortTime = 0.0;
	stats_t stats;


	srand(time(0));
	
	arr.table = (int *) calloc(10000000, sizeof(int));
	if (arr.table == NULL) {
		return -1;
	}
	arr.inserted = 0;
	
	make_array(&arr);
	stats.assignments = 0;
    stats.comparisons = 0;

	start = clock();
	quicksort_2p_r(arr.table, 0, arr.inserted-1, &stats);
	end = clock();
	
	quicksortTime += (double)(end - start) / CLOCKS_PER_SEC;
	
	printf ("Comparisons: %ld, Assignments: %ld\n", stats.comparisons , stats.assignments);
	printf("%f\n", quicksortTime);
	
	free(arr.table);
	
	return 0;
}

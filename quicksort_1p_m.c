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

void sort_medianArr(int arr[]) {
    int i, j, min_idx, temp;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < 2; i++) {
    	// Find the minimum element in unsorted array
    	min_idx = i;
        for (j = i+1; j < 3; j++)
        	if (arr[j] < arr[min_idx]) {
            	min_idx = j;
 			}
 			
        // Swap the found minimum element with the first element
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void quicksort_1p_m (int *arr, int left, int right, stats_t *find) {
	int medArr[3];
	int i = left, j = right + 1;
	int temp, pivot, pos1, pos2, pos3, median;
	
	if (right > left) {	
		pos1 = left + rand() % (right - left);
		pos2 = left + rand() % (right - left);
		pos3 = left + rand() % (right - left);
		
		medArr[0] = arr[pos1];
		medArr[1] = arr[pos2];
		medArr[2] = arr[pos3];
		sort_medianArr(medArr);
		
		find->assignments += 7;
		find->comparisons += 3;
		
		if (medArr[1] == arr[pos1]) {
			median = pos1;
		}
		else if (medArr[1] == arr[pos2]) {
			median = pos2;
		}
		else if (medArr[1] == arr[pos3]) {
			median = pos3;
		}
		
		temp = arr[median];
		arr[median] = arr[left];
		arr[left] = temp;
		
		pivot = arr[left];
		
		while (1) {
			while (++find->comparisons && arr[++i] < pivot) {
				if (i >= right) {
					break;
				}
			}
			
			while (++find->comparisons && arr[--j] > pivot) {
				if (j == left) {
					break;
				}
			}
			
			if (i >= j) {
				break;
			}
			
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		
		temp = arr[j];
		arr[j] = arr[left];
		arr[left] = temp;
		
		find->comparisons += 7;
		find->assignments += 19;
		
		quicksort_1p_m(arr, left, i-1, find);
		
		quicksort_1p_m(arr, i, right, find);
	}
}

int main (int argc, char *argv[]) {
	array_t arr;
	clock_t start, end;
	stats_t stats;
	double quicksortTime = 0.0;
	
	srand(time(0));
	
	arr.table = (int *) calloc(10000000, sizeof(int));
	if (arr.table == NULL) {
		return -1;
	}
	arr.inserted = 0;
	
	stats.comparisons = 0;
	stats.assignments = 0;
	
	make_array(&arr);
	
	start = clock();
	quicksort_1p_m(arr.table, 0, arr.inserted-1, &stats);
	end = clock();
	
	quicksortTime += (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("%f\n", quicksortTime);
	printf("Comparisons = %ld, Assignments = %ld\n", stats.comparisons, stats.assignments);
	
	free(arr.table);
	
	return 0;
}

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
    int comparisons;
    int assignments;
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

void sort_medianArr(int *arr[]) {
    int i, j, min, temp;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < 2; i++) {
    	// Find the minimum element in unsorted array
    	min = i;
        for (j = i+1; j < 3; j++)
        	if (*arr[j] < *arr[min]) {
            	min = j;
 			}
 			
        // Swap the found minimum element with the first element
        temp = *arr[min];
        *arr[min] = *arr[i];
        *arr[i] = temp;
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    
    *a = *b;
    *b = temp;
}

void quicksort_3p_r (int *array, int left, int right, stats_t *find) {
     int a, b, c, d, temp;
     int leftPivot, middlePivot, rightPivot, pos1, pos2, pos3;
     int *medArr[3];

	if (right > left) {
		if (right - left <= 2) {
			if (right - left == 1) {
				if (array[left] > array[right]) {
					temp = array[left];
                    array[left] = array[right];
                    array[right] = temp;
                    
                    find->assignments += 2;
                    find->comparisons += 3;
            	}
            }   
            else if (right - left == 2) {
            	medArr[0] = &array[left];
                medArr[1] = &array[left+1];
                medArr[2] = &array[right];
                sort_medianArr(medArr);
                
                find->assignments += 6;
                find->comparisons += 6;
            }
            
            return;
        }

		a = left + 2;
		b = left + 2;
		c = right - 1;
		d = right - 1;
		
		pos1 = left + rand() % (right-left);
	
		pos2 = left + rand() % (right-left);
		while (pos2 == pos1) {	
			pos2 = left + rand() % (right-left);
		}
		
		pos3 = left + rand() % (right-left);
		while (pos3 == pos1 || pos3 == pos2) {
			pos3 = left + rand() % (right-left);
		}
	
		swap(&array[left], &array[pos1]);
		swap(&array[left+1], &array[pos2]);
		swap(&array[right], &array[pos3]);
        
        find->assignments +=9;

		medArr[0] = &array[left];
		medArr[1] = &array[left+1];
		medArr[2] = &array[right];
		sort_medianArr(medArr);
		
        
		leftPivot = array[left];
		middlePivot = array[left+1];
		rightPivot = array[right];
		
		while (b <= c) {
			while (++find->comparisons && array[b] < middlePivot && b <= c) {
				if (array[b] < leftPivot) {
	                swap(&array[a], &array[b]);
                    find->assignments+=3;
	                a ++;
	            }
	            b ++;
                find->comparisons+=2;
	        }
         
	        while (array[c] > middlePivot && b <= c) {
	            if (array[c] > rightPivot) {
	                swap(&array[c], &array[d]);
                    find->assignments+=3;
	                d --;
	            }
	            c --;
                find->comparisons+=2;
	        }
         
	        if (b <= c) {
	            if (array[b] > rightPivot) {
	                if (array[c] < leftPivot) {
	                     swap (&array[b], &array[a]);
	                     swap (&array[a], &array[c]);
                         
	                     a ++;
	                 }
	                 else {
	                     swap (&array[b], &array[c]);
	                 }
	                 swap (&array[c], &array[d]);
	                 b ++;
	                 c --;
	                 d --;
                     find->comparisons+=2;
                     find->assignments+=6;
	            }
	            else {
	                if (array[c] < leftPivot) {
	                    swap (&array[b], &array[a]);
	                    swap (&array[a], &array[c]);
                        
                        find->comparisons+=1;
                        find->assignments+=6;
	                    a ++;
	                }
	                else {
	                    swap (&array[b], &array[c]);
                        find->assignments+=3;
	                 }
	                 b ++;
	                 c --;
	        	}
	    	}
	    }
	    a --;
	    b --;
	    c ++;
	    d ++;
     
	    swap (&array[left+ 1], &array[a]);
	    swap (&array[a], &array[b]);
	    a --;
	    swap (&array[left], &array[a]);
	    swap (&array[right], &array[d]);
    	
        find->assignments += 12;
        
	    quicksort_3p_r(array, left , a -1, find);
		
	    quicksort_3p_r(array, a + 1,b -1, find);

		quicksort_3p_r(array, b+1, d -1, find);
    
	    quicksort_3p_r(array, d+1, right, find);
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
	
	stats.assignments=0;
    stats.comparisons = 0;
    
	start = clock();
	quicksort_3p_r(arr.table, 0, arr.inserted-1, &stats);
	end = clock();

	quicksortTime += (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("%f\n", quicksortTime);
	printf ("Comparisons: %d, Assignments: %d \n", stats.comparisons, stats.assignments);
	
	free(arr.table);
	
	return 0;
}

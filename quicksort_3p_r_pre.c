/* Onomateponyma: Gavouras Dimitrios  (03145)
 *	              Gerontidis Georgios (03261)
 *	              Moysis Moysis       (03250) */
/* This program only gets input from files. The user can press
 * ctrl + d to put input from terminal. To compile this program
 * use -lm. */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>

typedef struct {
	int *table;
	int inserted;
} array_t;

struct list {
    long unsigned int pos;
    struct list *next;
    struct list *prev;
};
typedef struct list list_t;

typedef struct {
    int inserted;
    list_t *head;
} head_t;

typedef struct {
    int comparisons;
    int assignments;
} find_t;


/*this function frees the allocated memory*/
void free_list (list_t *head) {
    list_t *current, *prev;

    for (current = head; current != NULL;) {
        prev = current;
        current = current->next;
        free (prev);
    }
}

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

void quicksort_3p_r (int *array, int left, int right, head_t *head, find_t *find) {
    int a, b, c, d, temp;
    int p, q, r, pos1 = -1, pos2 = -1, pos3 = -1;
    int *medArr[3];
    list_t *current, *temp1;

	if (right > left) {
		if (right - left <= 2) {
			if (right - left == 1) {
				if (array[left] > array[right]) {
					temp = array[left];
                    array[left] = array[right];
                    array[right] = temp;
                    find->comparisons +=1;
                    find->assignments +=2;
            	}
            }   
            else if (right - left == 2) {
            	medArr[0] = &array[left];
                medArr[1] = &array[left+1];
                medArr[2] = &array[right];
                sort_medianArr(medArr);
                find->assignments += 6;
                find->comparisons +=6;
            }
            
            
            return;
        }

		a = left+2;
		b = left+2;
		c = right-1;
		d = right-1;
		for (current = head->head; current != NULL; ) {
            if (current->pos > left && current->pos < right) {
                if (pos1 == -1) {
                    //afairese stoixeio listas
                    pos1 = current->pos;
                    if (current == head->head) {
                        head->head = head->head->next;
                    }
                    if (current->prev != NULL) {
                        current->prev->next= current->next;
                    }
                    if (current->next != NULL) {
                        current->next->prev = current->prev;
                    }
                    temp1 =current;
                    current = current->next;
                    free(temp1);
                    continue;
                }
                else if (pos2 == -1) {
                    if (current->pos == pos1) {
                        current = current->next;
                        continue;
                    }
                    pos2 = current->pos;
                    //afairese stoixeio
                    if (current == head->head) {
                        head->head = head->head->next;
                    }
                    if (current->prev != NULL) {
                        current->prev->next= current->next;
                    }
                    if (current->next != NULL) {
                        current->next->prev = current->prev;
                    }
                    temp1 =current;
                    current = current->next;
                    free(temp1);
                    continue;
                }  
                else if (pos3 == -1) {
                    if (current->pos == pos1 || current->pos == pos2) {
                        current = current->next;
                        continue;
                    }
                    pos3 = current->pos;
                    if (current == head->head) {
                        head->head = head->head->next;
                    }
                    if (current->prev != NULL) {
                        current->prev->next= current->next;
                    }
                    if (current->next != NULL) {
                        current->next->prev = current->prev;
                    }
                    temp1 =current;
                    current = current->next;
                    free(temp1);
                     
                    break; 
                }
            
            
            }
            current = current->next;
        }
        
        if (pos1 == -1) {
       	    pos1 = left + rand() % (right-left);
        }
        if (pos2 == -1) {
            pos2 = left + rand() % (right-left);
            while (pos2 == pos1) {	
                pos2 = left + rand() % (right-left);
            }
        }
		if (pos3 == -1) {
            pos3 = left + rand() % (right-left);
            while (pos3 == pos1 || pos3 == pos2) {
                pos3 = left + rand() % (right-left);
            }
        }
	
		swap(&array[left], &array[pos1]);
		swap(&array[left+1], &array[pos2]);
		swap(&array[right], &array[pos3]);
        find->assignments+=9;
		medArr[0] = &array[left];
		medArr[1] = &array[left+1];
		medArr[2] = &array[right];
		sort_medianArr(medArr);
		find->comparisons += 6;
		p = array[left];
		q = array[left+1];
		r = array[right];

        find->comparisons += (c- b);
		while (b <= c) {
			while (array[b] < q && b <= c) {
				if (array[b] < p) {
	                swap(&array[a], &array[b]);
	                a = a + 1;
                    find->comparisons += 2;
                    find->assignments += 3;
	            }
	            b = b + 1;
	        }
         
	        while (array[c] > q && b <= c) {
	            if (array[c] > r) {
	                swap(&array[c], &array[d]);
                    find->comparisons += 2;
                    find->assignments += 3;
	                d = d - 1;
	            }
	            c = c - 1;
	        }
         
	        if (b <= c) {
	            if (array[b] > r) {
	                if (array[c] < p) {
	                     swap (&array[b], &array[a]);
	                     swap (&array[a], &array[c]);
                        find->comparisons += 3;
                        find->assignments += 6;
	                     a = a + 1;
	                }
	                else {
	                    swap (&array[b], &array[c]); 
                        find->assignments += 3;
	                }
	                 swap (&array[c], &array[d]);
	                 b = b + 1;
	                 c = c - 1;
	                 d = d - 1;
                     find->assignments += 3;
	            }
	            else {
	                if (array[c] < p) {
	                    swap (&array[b], &array[a]);
	                    swap (&array[a], &array[c]);
	                    a = a + 1;
                        find->assignments += 6;
	                }
	                else {
	                    swap (&array[b], &array[c]);
                        find->assignments += 3;
	                 }
	                 b = b + 1;
	                 c = c - 1;
	             }
	         }
	     }
	    a = a - 1;
	    b = b - 1;
	    c = c + 1;
	    d = d + 1;
     
	    swap (&array[left+ 1], &array[a]);
	    swap (&array[a], &array[b]);
	    a = a -1;
	    swap (&array[left], &array[a]);
	    swap (&array[right], &array[d]);
    	find->assignments += 12;
	    quicksort_3p_r(array, left , a -1, head, find);
		
	    quicksort_3p_r(array, a + 1,b -1, head, find);

		quicksort_3p_r(array, b+1, d -1, head, find);
    
	    quicksort_3p_r(array, d+1, right, head, find);
    }
}


void selection_sort (list_t *head) {
    list_t *current, *temp;
    long unsigned num, count, pos;

    current = head;
    for (current = head; current != NULL; current = current->next) {
        for (temp = current, num = -1, count = 0; temp != NULL; count++, temp = temp->next) {
            if (num == -1) {
                num = temp->pos;
                pos = count;
            }
            if (temp->pos < num) {
                num = temp->pos;
                pos = count;
            }
        }
        for (temp = current, count = 0; count < pos; count++, temp = temp->next);

        num = current->pos;
        current->pos = temp->pos;
        temp->pos = num;
    }
}

int main (int argc, char *argv[]) {
	array_t arr;
	clock_t start, end;
	double quicksortTime = 0.0;
	head_t head;
    list_t *help_ptr, *current;
    find_t find;

	srand(time(0));
	
	arr.table = (int *) calloc(10000000, sizeof(int));
	if (arr.table == NULL) {
		return -1;
	}
	arr.inserted = 0;
	
	make_array(&arr);
	head.head = (list_t*)calloc (1, sizeof(list_t));
    head.inserted = sqrt(arr.inserted);
    head.head->pos = rand() % arr.inserted;
    current= head.head;
    current->next = NULL;
    current->prev = NULL;

    for (int i = 0; i < head.inserted -1; i++) {
        help_ptr = (list_t *) calloc (1,sizeof (list_t));
        if (help_ptr == NULL) {
            exit(-1);
        }
        current->next = help_ptr;
        current->next->prev = current;
        current->next->pos = rand() % arr.inserted;
        current = current->next;
        current->next = NULL;  
    }

    selection_sort(head.head);

    find.assignments=0;
    find.comparisons = 0;

	start = clock();
	quicksort_3p_r(arr.table, 0, arr.inserted-1, &head, &find);
	end = clock();
	
	quicksortTime += (double)(end - start) / CLOCKS_PER_SEC;
	
	printf("%f\n", quicksortTime);
	printf ("Comparisons: %d, Assignments: %d \n", find.comparisons, find.assignments);
	free(arr.table);
	free_list (head.head);
	return 0;
}

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
typedef struct list listNode_t;

typedef struct {
    int inserted;
    listNode_t *head;
} list_t;

typedef struct {
    long int comparisons;
    long int assignments;
} stats_t;

/*this function frees the allocated memory*/
void free_list (listNode_t *head) {
    listNode_t *current, *prev;

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

void swap(int* a, int* b) {
    int temp = *a;
    
    *a = *b;
    *b = temp;
}


void quicksort_2p_r (int* arr, int left, int right, list_t *list, stats_t *find) {    
    int pos1 = -1, pos2 = -1, leftPivot, rightPivot;
    int i = left + 1, j = right - 1, k = left + 1;
    listNode_t *current, *temp;

	if (right > left) {
    	if (right - left == 1) {
    		if (arr[left] > arr[right]) {
        		swap(&arr[left], &arr[right]);
        	}
            find->assignments += 3;
            find->comparisons +=1;
        	return;
       	}

        for (current = list->head; current != NULL; ) {
            if (current->pos > left && current->pos < right) {
                if (pos1 == -1) {
                    //afairese stoixeio listas
                    pos1 = current->pos;
                    if (current == list->head) {
                        list->head = list->head->next;
                    }
                    if (current->prev != NULL) {
                        current->prev->next= current->next;
                    }
                    if (current->next != NULL) {
                        current->next->prev = current->prev;
                    }
                    temp =current;
                    current = current->next;
                    free(temp);
                    continue;
                }
                else if (pos2 == -1) {
                    if (current->pos == pos1) {
                        current = current->next;
                        continue;
                    }
                    pos2 = current->pos;
                    //afairese stoixeio
                    if (current == list->head) {
                        list->head = list->head->next;
                    }
                    if (current->prev != NULL) {
                        current->prev->next= current->next;
                    }
                    if (current->next != NULL) {
                        current->next->prev = current->prev;
                    }
                    temp =current;
                    current = current->next;
                    free(temp);
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
		
		swap(&arr[left], &arr[pos1]);
		swap(&arr[right], &arr[pos2]);
        find->assignments += 6;

   		if (arr[left] > arr[right]) {
        	swap(&arr[left], &arr[right]);
            find->assignments +=6;
        }

 		leftPivot = arr[left], 
   	 	rightPivot = arr[right];

		while (k <= j) {
		    // If elements are less than the left pivot
		    if (arr[k] < leftPivot) {
		        swap(&arr[k], &arr[i]);
                find->assignments +=3;

		        i++;
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
                find->assignments+=6;
                find->comparisons+=2;
		    }
		    k++;
            find->comparisons +=2;
		}
		i--;
		j++;
 
		// Bring pivots to their appropriate positions.
		swap(&arr[left], &arr[i]);
		swap(&arr[right], &arr[j]);
        find->assignments+=6;
		// Recursive call.
		quicksort_2p_r(arr, left, i-1, list, find);
		quicksort_2p_r(arr, i + 1, j-1, list, find);
		quicksort_2p_r(arr, j + 1, right, list, find);
	}
}

void selection_sort (listNode_t *head) {
    listNode_t *current, *temp;
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
	list_t list;
    listNode_t *help_ptr, *current;
    stats_t find;

	srand(time(0));
	
	arr.table = (int *) calloc(10000000, sizeof(int));
	if (arr.table == NULL) {
		return -1;
	}
	arr.inserted = 0;
	
	make_array(&arr);
	
	list.head = (listNode_t*)calloc (1, sizeof(listNode_t));
    list.inserted = sqrt(arr.inserted);
    list.head->pos = rand() % arr.inserted;
    
    current= list.head;
    current->next = NULL;
    current->prev = NULL;

    for (int i = 0; i < list.inserted - 1; i++) {
        help_ptr = (listNode_t *) calloc (1,sizeof (listNode_t));
        if (help_ptr == NULL) {
            exit(-1);
        }
        
        current->next = help_ptr;
        current->next->prev = current;
        current->next->pos = rand() % arr.inserted;
        current = current->next;
        current->next = NULL;  
    }

    selection_sort(list.head);
    
    find.assignments = 0;
    find.comparisons = 0;

	start = clock();
	quicksort_2p_r(arr.table, 0, arr.inserted-1, &list, &find);
	end = clock();
    
	quicksortTime += (double)(end - start) / CLOCKS_PER_SEC;
	printf ("Comparisons: %ld, Assignments: %ld \n", find.assignments , find.comparisons);
	printf("%f\n", quicksortTime);

	free(arr.table);
	free_list (list.head);
	return 0;
}

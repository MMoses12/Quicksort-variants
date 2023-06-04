# Quicksort Variants Performance Comparison
This project aims to implement and compare modern variants of the Quicksort algorithm in terms of their performance in sorting integers stored in main memory. The implemented variants include:

__1.__ Quicksort_1p_l (QS1pL): The classic Quicksort algorithm where the leftmost element of the array is selected as the pivot. <br/>
__2.__ Quicksort_1p_r (QS1pR): The Quicksort algorithm where a random pivot is selected uniformly at random from all elements of the array. <br/>
__3.__ Quicksort_1p_m (QS1pM): The Quicksort algorithm where three candidate pivots are randomly selected, and the median (middle value) of the three is chosen as the final pivot. <br />
__4.__ Quicksort_2p_r (QS2pR): The Quicksort algorithm where two random pivots are selected uniformly at random from all elements of the array. <br />
__5.__ Quicksort_3p_r (QS3pR): This variant uses three pivots p < q < r, and at each iteration, the algorithm divides the array into four subarrays based on the three pivots and recursively sorts them. The pivots are randomly chosen.

__6.__ Based on the previous two variants, two additional variants are generated with the following modifications:
  - Quicksort_2p_r_pre (QS2pRPre): Instead of selecting a pivot from the subarray being sorted, a suitable pivot is chosen from the √n sample elements, and the subarray is partitioned accordingly.
  - Quicksort_3p_r_pre (QS3pRPre): Similar to QS2pRPre, a suitable pivot from the √n sample elements is selected at each recursive call to partition the subarray.
<hr/>

## Experimentation Setup
To compare the competing algorithms on datasets of size n, the following methodology is employed:

__1.__ Generate n integers within the range [0, 2n) pseudorandomly using the random number generator of your computer.
__2.__ Perform the sorting experiment 50 times to calculate the average performance of each competitor for each performance metric. Compute the variance of the performance metric as well.
__3.__ The experimentation is conducted for the following values of n:
  - 10,000
  - 100,000
  - 1,000,000
  - 10,000,000

The following performance metrics are used:

__1.__ Execution Time: Measure the time taken by each algorithm to sort the data. Include hardware specifications used, such as CPU speed, memory size, memory speed, and any other relevant details affecting the performance of the competitors. <br/>
__2.__ Number of Comparisons: Count the number of comparisons made between integers, such as comparisons with the pivot. <br/> 
__3.__ Number of Assignments: Count the number of assignments made, e.g., in a swap(a, b), which involves three assignments using a temporary variable. If any smart assignment techniques are employed to reduce the number of assignments, describe them in the pseudocode of the corresponding algorithm.

//Name: Nathan Deininger
//Class: CSC 362, Fall 2023
//Assignment: Program 3
//Date: 11/8/2023
//Explanation: This program is designed to implment five different functions: main, copy, sort1, sort2, and output. The copy function simply copies the
//			   the contents of one array into another, sort1 implements the selection sort algorithm, sort2 implements the insert sort algorithm, 
//			   and output displays the contents of an array. Furthermore, all of these operations are implmented solely using pointer arthimetic,
//			   instead of the normal index based method of accessing and traversing arrays. 
//	

#include <stdio.h>

//Returns nothing and copies array 1 into array 2 directly
//Accepts (source array pointer, destination array pointer, size of the arrays)
void copy(int* ar1, int* ar2, int size);

//Performs selection sort on an array of integers
//Selection sort repeatedly traverses the array, finds the minimum element, and swaps it to the front of the unsorted portion until entire array is sorted
//Accepts pointer to array and the array's size, and sorts the provided array directly.
void sort1(int* ar, int size);

//Performs an insertion sort on an array of integers
//Insert sort finds the next unsorted element, and searches the sorted section until the unsorted element is larger than the sorted value, and inserts it
//Accepts pointer to array and the array's size, and sorts the provided array directly.
void sort2(int* ar, int size);

//Outputs the contents of an array using pointer arithmetic. 
//Accepts pointer to array and the array's size.
void output(int* ar, int size);


void main() {
	int array1[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int array2[10];
	int size = 10;
	copy(array1, array2, size);
	sort1(array1, size);
	output(array1, size);
	sort2(array2, size);
	output(array2, size);
}

//Implementation of the copy function using pointer arthimetic
//Creates a temp pointer to the destination array and uses a for loop to traverse the source array
//Each loop iteration copies the value in the source array to the corresponding location in the destinationa array
//The temp pointer is then incremented to ensure the source and destination indicies are the same for each iteration
void copy(int* ar1, int* ar2, int size) {
	int* t = ar2; 
	int* p;
	for (p = ar1; p < ar1 + size; p++) {
		*t = *p;
		t++;
	}
}

//Implementation of the selection sort algorithm using pointer arthimetic
//Standard selection sort, see https://www.geeksforgeeks.org/selection-sort/# for more details
void sort1(int* ar, int size) {
	int* ip;
	for (ip = ar; ip < ar + size; ip++) {
		int* minPosition = ip;
		int* jp;
		for (jp = ip + 1; jp < ar + size; jp++) {
			if (*jp < *minPosition) {
				minPosition = jp;
			}
		}
		int temp = *minPosition;
		*minPosition = *ip;
		*ip = temp;
	}
}

//Implementation of the insert sort algorithm using pointer arthimetic
//Standard Insertion sort, see https://www.geeksforgeeks.org/insertion-sort/ for more details
void sort2(int* ar, int size) {
	int* p;
	for (p = ar + 1; p < ar + size; p++) {
		int temp = *p;
		int* loc = p - 1;
		while (loc >= ar && *loc > temp) {
			*(loc + 1) = *loc;
			loc = loc - 1;
		}
		*(loc + 1) = temp;
	}
}

//Implementation of output function
//Simply traverses the array via for loop and prints out each value
void output(int* ar, int size) {
	int* p;
	for (p = ar; p < ar + size; p++) {
		printf("%d ", *p);
	}
	printf("\n");
}


/*
Output 1 with array = { 10, 3, 6, 5, 9, 2, 1, 7, 4, 8 }:
1 2 3 4 5 6 7 8 9 10
1 2 3 4 5 6 7 8 9 10

Output 2 with array = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}:
1 2 3 4 5 6 7 8 9 10
1 2 3 4 5 6 7 8 9 10

*/
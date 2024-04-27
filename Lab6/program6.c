//Name: Nathan Deininger
//Class: CSC 362, Fall 2023
//Assignment: Program 6
//Date: 11/18/2023
//Explanation: This program is designed to traverse an array of size n and find which number occurs the most, 
//			   while also tracking and outputting the number of occurences of that number. Furthermore this
//			   program is intended to be implemented using Intel Assembly language, with the only C code 
//			   being for the initial variable declaration and for outputting the final result. To achieve this,
//			   the program uses a simple, inefficient approach of nested for loops, iterating over each item in
//			   the array via the main loop, and using the nested loop after to count the occurences of that item.
//			   the max number is stored in maxNum, and the number of occurences for that number is kept in maxCount. 

#include <stdio.h>

//Same program implemented in C, not relevant to the assignment submission
//Written in a way that's easy to translate to assembly, not necessarily for efficiency
/*
void programInC() {
	int arr[11] = { 50, 40, 60, 50, 40, 30, 50, 50, 20, 30, 40 };
	int n = 11;
	int num;
	int count;
	int maxNum;
	int maxCount = 0;
	int i;
	int j;

	for (i = 0; i < n; i++) {
		num = arr[i];
		count = 1;
		for (j = i + 1; j < n; j++) {
			if (arr[j] == num) {
				count++;
			}
		}
		if (count > maxCount) {
			maxNum = num;
			maxCount = count;
		}
	}
	printf("%d occurs %d times", maxNum, maxCount);
}
*/

void main() {
	int arr[30] = {25,26,27,28,29,30,25,26,27,29,30,25,28,30,27,30,26,27,28,25,24,26,27,26,27,26,28,26,30,25 }; //array of values to be examined
	int n = 30; //the number of elements in the array
	int nm; //will hold the actual size of the array in memory (bytes)
	int num; //the specific number in the array we are currently examining
	int count; //used to count the number of occurances of a particuliar num
	int maxNum; //holds the current maximum number value
	int maxCount; //holds the number of occurences of the maximum value

	__asm {
				mov maxCount, 0		//initialize maxCount to 0 to ensure proper comparisons
				mov ebx, 0			//initalize ebx to 0, use as main loop counter
				mov eax, 4			//calculate the actual size of the array so we can easily increment the loop and access the array
				mul n				//multiply number of elements in eax by 4 to get the actual size we need
				mov nm, eax			//store the actual size in nm
	topMain:    cmp ebx, nm			//compare main loop counter to nm
				je doneMain			//if loop counter ecx equals nm, exit main loop. otherwise, complete loop iteration
				mov eax, arr[ebx]   //load the next element of the array into eax
				mov num, eax		//move next element into the num variable
				mov count, 1		//initalize count to 1 at the start of the loop
				mov ecx, ebx		//initalize inner loop counter ecx to ebx
	topInner:   add ecx, 4			//increment inner loop counter by 4 to set to right location
				cmp ecx, nm			//compare inner loop counter to nm
				jge doneInner		//if loop counter ecx equals or is greater than nm, exit inner loop. otherwise, repeat inner loop again			
				mov edx, arr[ecx]   //load next element of the array into edx to be compared to current num
				cmp num, edx		//compare edx (current inner loop num) to num in the outer loop
				jne	topInner		//if outer loop num and inner loop number are not equal, jump to top of inner loop. otherwise, continue on to increment counter
				add count, 1		//increment count by 1 
				jmp topInner		//now we can go back to top of inner loop
	doneInner:	nop					//end of inner loop, do nothing here			
				mov edx, maxCount	//load maxCount into edx to be used in comparison
				cmp count, edx		//compare count to maxCount
				jl skipIf			//if count is less than maxCount, skip maxNum and maxCount reassignment. otherwise, assign new values for maxNum and maxCount	
				mov edx, arr[ebx]	//move num into edx so it can be moved to maxNum
				mov maxNum, edx		//assign new number to maxNum
				mov edx, count		//move count into edx so it can be moved into maxCount
				mov maxCount, edx	//assign count to be new maxCount value
	skipIf:     add ebx, 4			//increment the main loop counter by 4, not 1, to ensure proper array access
				jmp topMain			//return back to the begining of the loop
	doneMain:   nop					//main loop finished, do nothing here
	}
	printf("%d occurs %d times", maxNum, maxCount);
}

/* Output of running Array 2:
3 occurs 10 times
*/

/* Output of running Array 3:
26 occurs 7 times
*/
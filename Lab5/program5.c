//Name: Nathan Deininger
//Class: CSC 362, Fall 2023
//Assignment: Program 5
//Date: 11/16/2023
//Explanation: This program is designed to find and output all odd numbers between 3 and 1001 with the property of
//			   their value squared +2 being a prime number, and their value squared - 2 also being a prime number.
//			   Furthermore, this program is intended to be implemented using Intel Assembly language, such that
//			   any needed variables are declared in C, while all of the computation is done using assembly, and 
//			   we only return to C code to output the numbers that meet our criteria.  

#include <stdio.h>

//Same program implemented in C, not relevant to the assignment submission
//Written in a way that's easy to translate to assembly, not necessarily for efficiency
/*
void programInC() {
	int i = 3;
	int n1;
	int n2;
	int isValid;
	int j;

	for (; i <= 1001; i = i + 2) {
		isValid = 1;
		n1 = (i * i) + 2;
		for (j = 2; j < n1; j++) {
			if (n1 % j == 0) {
				isValid = 0;
			}
		}
		n2 = (i * i) - 2;
		for (j = 2; j < n2; j++) {
			if (n2 % j == 0) {
				isValid = 0;
			}
		}
		if (isValid) {
			printf("%d\n", i);
		}
	}
}
*/

void main() {
	int i; //variable to store numbers 3-1001 we will check
	int n1; //variable to store i^2 + 2
	int n2; //variable to store i^2 - 2
	int j; //variable to store inner loop counters

	__asm {
				mov i, 1		//initialize main loop counter to 1 (not three, so incrementation works properly)
				mov n1, 0		//initialize i^2 + 2 variable to 0 
				mov n2, 0		//initialize i^2 - 2 variable to 0
	topMain:	mov eax, i		//load i into eax so we can increment it by 2
				add eax, 2		//add 2 to the eax to increment main counter
				mov i, eax		//move the incremented i counter value back into i
				cmp i, 1001		//top of main loop, check if i > 1001
				jg done			//if i > 1001, done with program, jump to done. else, loop repeats
				mov eax, i		//calculate i^2 + 2, store in n1.
				mul i
				add eax, 2
				mov n1, eax
				mov eax, i		//Calculate i^2 - 2, store in n2
				mul i
				sub eax, 2
				mov n2, eax
				mov j, 2		//initialize first loop counter to j = 2
	topFirst:	mov ecx, n1		//load n1 into ecx so we can compare it to j
				cmp j, ecx		//top of first isPrime loop. Iterate until j = i^2 + 1 (not + 2, don't want to check number itself)
				je doneFirst    //if j = n1, loop is complete, jump out of the loop and start second check on n2
				mov eax, n1		//perform n1 / j operation
				mov edx, 0		//clear edx with 0 to ensure it is 0 if there is no division remainder
				div j
				cmp edx, 0		//check to see if edx has a remainder = 0. 
				je topMain		//if remainder is = 0, we know i^2 + 2 is not prime, therefore jump back to the top of the main loop, no need to do second check
				mov	eax, j		//otherwise, continue first check loop. Load j in eax, so we can increment it
				add eax, 1		//add + 1 to the eax
				mov j, eax		//move the incremeted j value back into j
				jmp topFirst	//jump back to the top of the first check loop
	doneFirst:	mov j, 2		//first loop check passed successfully, need to do the same check on n2. initialize j counter = 2
	topSecond:  mov ecx, n2		//mov n2 into ecx, so we can compare it to j
				cmp j, ecx		//top of second isPrime loop. Interate until j = n2, at which point comparison will be complete
				je doneSecond   //if j = n2, loop is complete, jump out of second loop
				mov eax, n2		//perform n2 / j operation
				mov edx, 0		//clear edx with 0 to ensure it is 0 if there is no division remainder
				div j
				cmp edx, 0		//check to see if edx has a remainder = 0. 
				je topMain      //if remainder = 0, we know i^2 - 2 is not prime, therefore jump back to the top of the main loop, no need to continue
				mov	eax, j		//otherwise, continue second check loop. Load j in eax, so we can increment it
				add eax, 1		//add + 1 to the eax
				mov j, eax		//move the incremeted j value back into j
				jmp topSecond	//jump back to the top of the first check loop
	doneSecond: nop
	}

	printf("%d\n", i);			//i value is valid, print it out

	__asm {
				jmp topMain		//back into assembly. Jump to the top of the main loop
	done:		nop				//done location, do nothing and exit program
	}
}

/* Program Output:
3
9
15
21
33
117
237
273
303
309
387
429
441
447
513
561
573
609
807
897
*/
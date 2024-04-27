//Name: Nathan Deininger
//Class: CSC 362, Fall 2023
//Assignment: Program 1
//Date: 9/6/2023
//Explanation: This program is designed to replicate the cmp Linux program, which takes two files and reports on the first mismatch (if found).
//		       The program will ask the user for two file names as input, and will then ask if the user wants to use case-sensitive comparisons 
//		       and if the user wants to compare non-letter characters. With the file names and criteria provided, the program will open the files,
//             loop through each and compare them character by character, and will 1) detect and output a mismatch with the location it occured,
//             2) will not detect a mismatch but will let the user know one file is longer than the other, or 3) output will indicate that the files 
//             are the same in both content and length. 


#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<ctype.h>

int main() {
	//Step 1: Declare necessary variables
	char fileName1[30];
	char fileName2[30];

	char caseSensitive;
	char nonLetters;
	char fileInput1 = 'a';
	char fileInput2 = 'a';

	FILE *file1;
	FILE *file2;

	int curLocation = 1;
	int errorCode = 0;

	//Step 2: Get user input
	printf("Please provide the name of file 1: ");
	scanf("%s", fileName1);
	printf("Please provide the name of file 2: ");
	scanf("%s", fileName2);

	printf("Case Sensitive? (Y/N): ");
	scanf(" %c", &caseSensitive);
	printf("Match non-letters? (Y/N): ");
	scanf(" %c", &nonLetters);

	//Step 3: Open input files
	file1 = fopen(fileName1, "r");
	file2 = fopen(fileName2, "r");

	//Step 4: Traverse input files, perform comparisons
	while (fileInput1 != EOF && fileInput2 != EOF && errorCode == 0) {
		//Step 4.a: Get next char from each file
		fileInput1 = getc(file1);
		fileInput2 = getc(file2);

		//Step 4.b: Check if file1 is longer than file2 (errorCode = 5), or vice versa (errorCode = 6)
		if (fileInput1 == EOF && fileInput2 != EOF) {
			errorCode = 6;
			printf("Error code 6 - %s is longer than %s - %s is %d bytes long.", fileName2, fileName1, fileName1, curLocation - 1);
			break;
		}
		if (fileInput1 != EOF && fileInput2 == EOF) {
			errorCode = 5;
			printf("Error code 5 - %s is longer than %s - %s is %d bytes long.", fileName1, fileName2, fileName2, curLocation - 1);
			break;
		}

		//Step 4.c: Check for same letter & wrong case (if applicable), errorCode = 1
		if (caseSensitive == 'Y') {
			if (isalpha(fileInput1) && isalpha(fileInput2)) {
				if ((islower(fileInput1) && isupper(fileInput2)) || (islower(fileInput2) && isupper(fileInput1))) {
					errorCode = 1;
					printf("Error code 1 - Same letter and wrong case - At location %d %s has %c and %s has %c", curLocation, fileName1, fileInput1, fileName2, fileInput2);
					break;
				}
			}
		}
		
		//Step 4.d: Check for different letters, errorCode = 2
		if (isalpha(fileInput1) && isalpha(fileInput2)) {
			if (!(islower(fileInput1) && isupper(fileInput2)) && !(islower(fileInput2) && isupper(fileInput1))) {
				if (fileInput1 != fileInput2) {
					errorCode = 2;
					printf("Error code 2 - Different letters - At location %d %s has %c and %s has %c", curLocation, fileName1, fileInput1, fileName2, fileInput2);
					break;
				}
			}	
		}

		//Step 4.e: Check for a letter and a non-letter, errorCode = 3
		if ((isalpha(fileInput1) && !isalpha(fileInput2)) || (isalpha(fileInput2) && !isalpha(fileInput1))) {
			errorCode = 3;
			printf("Error code 3 - Letter and non-letter - At location %d %s has %c and %s has %c", curLocation, fileName1, fileInput1, fileName2, fileInput2);
			break;
		}

		//Step 4.f: Check for two different non-letters (if applicable), errorCode = 4
		if (nonLetters == 'Y') {
			if (!isalpha(fileInput1) && !isalpha(fileInput2)) {
				if (fileInput1 != fileInput2) {
					errorCode = 4;
					printf("Error code 4 - Different non-letters - At location %d %s has %c and %s has %c", curLocation, fileName1, fileInput1, fileName2, fileInput2);
					break;
				}
			}
		}

		//Step 4.g: Increment curLocation
		curLocation++;
	}

	//Step 4.h: Check if files are the same
	if (errorCode == 0) {
		printf("Files are the same with a length of %d", curLocation - 2);
	}

	//Step 5: Close the files
	fclose(file1);
	fclose(file2);

	//Step 6: Return errorCode, exit program
	return errorCode;
}

/* OUTPUT

RUN1
	Please provide the name of file 1: p1in4a.txt
	Please provide the name of file 2: p1in4b.txt
	Case Sensitive? (Y/N): N
	Match non-letters? (Y/N): N
	Files are the same with a length of 117

RUN2
	Please provide the name of file 1: p1in5a.txt
	Please provide the name of file 2: p1in5b.txt
	Case Sensitive? (Y/N): Y
	Match non-letters? (Y/N): N
	Error code 1 - Same letter and wrong case - At location 113 p1in5a.txt has b and p1in5b.txt has B

RUN3
	Please provide the name of file 1: p1in6a.txt
	Please provide the name of file 2: p1in6b.txt
	Case Sensitive? (Y/N): N
	Match non-letters? (Y/N): N
	Error code 5 - p1in6a.txt is longer than p1in6b.txt - p1in6b.txt is 25 bytes long.

RUN4
	Please provide the name of file 1: p1in7a.txt
	Please provide the name of file 2: p1in7b.txt
	Case Sensitive? (Y/N): N
	Match non-letters? (Y/N): N
	Error code 6 - p1in7b.txt is longer than p1in7a.txt - p1in7a.txt is 23 bytes long.

RUN5
	Please provide the name of file 1: p1in8a.txt
	Please provide the name of file 2: p1in8b.txt
	Case Sensitive? (Y/N): N
	Match non-letters? (Y/N): Y
	Error code 4 - Different non-letters - At location 4 p1in8a.txt has - and p1in8b.txt has :
*/
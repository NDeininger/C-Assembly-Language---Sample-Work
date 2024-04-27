//Name: Nathan Deininger
//Class: CSC 362, Fall 2023
//Assignment: Program 2
//Date: 10/5/2023
//Explanation: This program is designed to read several rows of input from a textfile and output predictions about American football game
//			   match-ups using a formula provided by Dr. Fox. To acomplish this, all of the nessecary variables are declared, and a while loop
//			   is set to read through the input. In the while loop, an input function is used to read the input line-by-line and store the results 
//			   in the appropriate variable using pointer variables. Then, several strength calculations and a difference calculation are made with 
//			   computation functions. Next, the predicted winner of a match-up is printed, along with the theoretical score. An update function is 
//			   used during the loop to track stats about the predictions. Finally, when all of the input has been processed, a summary function
//			   is called to print out both the precentage of home team wins, and the average calculated score difference.


#include "header.h"

void main() {
	//Declare variables to store file input
	char homeTeamName[20];
	char visitingTeamName[20];
	int HTO;
	int HTD;
	int HTS;
	int HTH;
	int HTC;
	int VTO;
	int VTD;
	int VTS;
	int VTR;

	//Declare variables to store calculated strengths
	double homeScoreStr;
	double visitScoreStr;
	double specialTeamImpact;
	double homeFieldAdv;
	double vistRoadStr;

	//Declare variable to keep track of the current calculated difference
	int curDifference;

	//Declare variables to keep track of overall prediction stats
	int numPredictions = 0;
	int numHomeWins = 0;
	int totalDifference = 0;

	//Declare file pointer variable and open input file - change file name to run a different file
	FILE* inputFile = fopen("football2.txt", "r");
	
	//Main loop to execute input processing
	while (getInput(inputFile, homeTeamName, visitingTeamName, &HTO, &HTD, &HTS, &HTH, &HTC, &VTO, &VTD, &VTS, &VTR) != EOF) {
		//Calculate the five strength values using input values and passing pointers of strength variables
		firstComputation(HTO, HTD, HTS, HTH, HTC, VTO, VTD, VTS, VTR, &homeScoreStr, &visitScoreStr, &specialTeamImpact, &homeFieldAdv, &vistRoadStr);
		//Calculate the current difference for the match using calculated strengths
		curDifference = secondComputation(homeScoreStr, visitScoreStr, specialTeamImpact, homeFieldAdv, vistRoadStr);
		//Print out winning team and victory amount
		produceOutput(homeTeamName, visitingTeamName, curDifference);
		//Use update function to update the number of total predictions, number of home team wins, and the total difference, using the variables' pointer values
		updateFunc(curDifference, &numPredictions, &numHomeWins, &totalDifference);
	}
	//Call summary function to output home team win % and average calculated difference
	produceSummary(numPredictions, numHomeWins, totalDifference);

	//Close file
	fclose(inputFile);
}

/* Output from running 'football2.txt':

Clemson beats Wake_Forest by 2
Florida_St beats Virginia_Tech by 11
Nebraska beats Illinois by 3
Iowa_St beats TCU by 1
Georgia beats Kentucky by 19
Notre_Dame beats Louisville by 4
Michigan beats Minnesota by 8
LSU beats Missouri by 4
Ohio_State beats Maryland by 21
Oklahoma_St beats Kansas_St by 6
Texas beats Oklahoma by 3
USC beats Arizona by 8
Wisconsin beats Rutgers by 4

Percentage of home team wins is predicted as 69.23%
Average difference in scores is predicted as 4.23

*/
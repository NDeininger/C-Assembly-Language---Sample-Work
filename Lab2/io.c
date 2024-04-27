#include "header.h"

int getInput(FILE* inputFile, char homeTeamName[20], char visitingTeamName[20], int* HTO,
			int* HTD, int* HTS, int* HTH, int* HTC, int* VTO, int* VTD, int* VTS, int* VTR)
{
	//Use fscanf to read from input file line at a time, store data in approperiate variable
	return(fscanf(inputFile, "%s %d %d %d %d %d %s %d %d %d %d", homeTeamName, HTO, HTD, HTS, HTH, HTC, visitingTeamName, VTO, VTD, VTS, VTR));
}

void produceOutput(char homeTeamName[20], char visitingTeamName[20], int curDifference) {
	//output for home team win
	if (curDifference >= 0) {
		//Check if curDifference indicates a tie, default to home team win by 1
		if (curDifference == 0) {
			printf("%s beats %s by %d\n", homeTeamName, visitingTeamName, curDifference + 1);
		}
		//Print out home team win normally
		else {
			printf("%s beats %s by %d\n", homeTeamName, visitingTeamName, curDifference);
		}
	}
	//output for visiting team win
	else {
		printf("%s beats %s by %d\n", visitingTeamName, homeTeamName, abs(curDifference));
	}
}

void produceSummary(int numPredictions, int numHomeWins, int totalDifference) {
	//Calculate and print precentage of home team wins
	printf("\nPercentage of home team wins is predicted as %.2f%%\n", (numHomeWins / (double)numPredictions) * 100);
	//Calculate and print average difference
	printf("Average difference in scores is predicted as %.2f\n", totalDifference / (double)numPredictions);
}
#include "header.h"

void firstComputation(int HTO, int HTD, int HTS, int HTH, int HTC,
					  int VTO, int VTD, int VTS, int VTR, double* homeScoreStr,
					  double* visitScoreStr, double* specialTeamImpact,
					  double* homeFieldAdv, double* vistRoadStr)
{
	//Perform strength calculations using provided formulas, use pass by reference to return values
	*homeScoreStr = HTO * OFFENSIVE_FACTOR - VTD;
	*visitScoreStr = HTD + 2 - VTO * OFFENSIVE_FACTOR;
	*specialTeamImpact = HTS * SPECIAL_TEAMS_FACTOR - VTS;
	*homeFieldAdv = HTH + HTC * HOME_FIELD_ADVANTAGE - VTS;
	*vistRoadStr = HTO * HTD * HTH * OVERALL_FACTOR - VTO * VTD * VTR;
}

int secondComputation(double homeScoreStr, double visitScoreStr,
						 double specialTeamImpact, double homeFieldAdv,
						 double vistRoadStr)
{
	//Calculate current match difference, return ressult
	return (int)(homeScoreStr * OFFENSIVE_WEIGHT + visitScoreStr * DEFENSIVE_WEIGHT + specialTeamImpact * SPECIAL_WEIGHT + homeFieldAdv * HOME_WEIGHT + vistRoadStr * OVERALL_WORTH);
}

void updateFunc(int curDifference, int* numPredictions, int* numHomeWins, int* totalDifference) {
	//Perform simple updates on numPredictions, numHomeWins, totalDifference
	*numPredictions = *numPredictions + 1;
	if (curDifference >= 0) {
		*numHomeWins = *numHomeWins + 1;
	}
	*totalDifference = *totalDifference + curDifference;
}
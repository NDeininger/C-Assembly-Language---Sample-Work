//Name: Nathan Deininger
//Class: CSC 362, Fall 2023
//Assignment: Program 4
//Date: 11/9/2023
//Explanation: This program is designed to implment a version of the classic chutes and ladders board game. In this version, players will randomly role 1-6, and will move according
//			   to that role. If a player lands on a chute character, they will be moved back according to the value of the chute, and similiarly, a ladder will move a player forward.
//			   There are also F and B spots on the board, which move the player forward or backwards, respectively, to the nearest Haven. Once a haven, chute, or ladder has been used,
//			   it is eliminated from the game. Additionally, if players land on each other, the player who landed on the other player must move back one spot. Finally, the player who 
//			   makes it to the end first, or in the event both players make it to the end at the same time, the player that makes it further, wins the game.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//This function writes the current iteration of the game board to a newline in a textfile, reflecting any changes to the board and the players' locations
//Accepts a pointer to the board array, each character's location, and a pointer to the output file.
void output(char* board, char* p1, char* p2, FILE* outputFile);
//Executes the move of one player at a time, and is responsible for outputting what has happened to the terminal. Is responsible for calling the findHaven and chuteLadder functions
//Accepts the player's locations, the pointer to the board array, the number of the player being moved (1 or 2), and the size of the board
char* move(char* p1, char* p2, char* board, int playerNum, int SIZE);
//Calculates the player's new location if a player lands on F or B. Returns the new location of the player. Is called by move, not main.
//Accepts the location of the player that landed on F or B, the pointer to the board, and the size of the board
char* findHaven(char* pLoc, char* board, int SIZE);
//Calculates the player's new location on the board if they land on a chute or ladder and returns the new location. Is called by move, not main
//Accepts just the location of the player who landed on a chute or ladder
char* chuteLadder(char* pLoc);


void main() {
	char board[100] = "  mHk tH l B He Flq p H  hByHlho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB ";
	FILE* outputFile = fopen("Deininger_Program4_Output.txt", "w");
	const int SIZE = 100;
	char* p1 = board;
	char* p2 = board;
	//Seed random number generator for the players' roles
	srand(time(NULL));

	//Main loop that runs the game until one or both of the players reaches the end of the board
	//Handles moving the characters and updating the output file
	while (p1 < board + SIZE && p2 < board + SIZE) {
		p1 = move(p1, p2, board, 1, SIZE);
		printf("\n");
		p2 = move(p1, p2, board, 2, SIZE);
		printf("\n");
		output(board, p1, p2, outputFile);
	}
	//Determine and output the winner of the game
	if (p1 > p2) {
		printf("Player 1 wins!");
	}
	else {
		printf("Player 2 wins!");
	}

	//close output file
	fclose(outputFile);
}

void output(char *board, char* p1, char* p2, FILE* outputFile ) {
	char* current;
	//Loop through board, write chars to text file, replace a char with player's number if they're on that spot
	for (current = board; *current != '\0'; current++) {
		if (current == p1) {;
			putc('1', outputFile);
		}
		else if (current == p2) {
			putc('2', outputFile);
		}
		else {
			putc(*current, outputFile);
		}
	}
	putc('\n', outputFile);
}

char* move(char *p1, char *p2, char* board, int playerNum, int SIZE) {
	//generate a random integer 1-6
	int move = (rand() % 6) + 1;
	//Player 1 is in movement
	if (playerNum == 1) {
		//move player 1 according to their roll
		p1 = p1 + move;
		//Get the numerical location of the player on the board
		int playerIndex = p1 - board;
		printf("Player 1 rolled %d and is moved to %d", move, playerIndex);
		//Check if player 1 is not at the end or further
		if (p1 < board + SIZE) {
			//Check if player landed on B or F
			if (*p1 == 'B' || *p1 == 'F') {
				printf(" and landed on a %c, ", *p1);
				//Call findHaven function
				//Output if player landed on B
				if (*p1 == 'B') {
					p1 = findHaven(p1, board, SIZE);
					playerIndex = p1 - board;
					//Choose correct printf statement - check if player moved back to the start of the board
					if (playerIndex == -1) {
						printf("moved backward to the beginning of the board");
					}
					else {
						printf("moved backward to %d", playerIndex);
					}
				}
				//Call findHaven function
				//Output if player landed on F
				else {
					p1 = findHaven(p1, board, SIZE);
					int temp = playerIndex;
					playerIndex = p1 - board;
					//choose correct printf statement - check if player moved or not
					if (temp == playerIndex) {
						printf("and was unable to move forward");
					}
					else {
						printf("and moved to %d", playerIndex);
					}
				}
			}
			//Check if player landed on chute
			else if (*p1 >= 'a' && *p1 <= 'm') {
				printf(" and landed on a chute and slid down to ");
				//Call chuteLadder function
				p1 = chuteLadder(p1);
				playerIndex = p1 - board;
				printf("%d", playerIndex);
			}
			//Check if player landed on ladder
			else if (*p1 >= 'o' && *p1 <= 'z') {
				printf(" and landed on a ladder and climbed up to ");
				//Call chuteLadder function
				p1 = chuteLadder(p1);
				playerIndex = p1 - board;
				printf("%d", playerIndex);
			}
			//Check if players collided after applying chutes/ladders/B/F
			if (p1 == p2) {
				//Make sure players arent at begining
				if (p1 != board) {
					//This means players have collided, move p1 back 1 spot
					p1 = p1 - 1;
					playerIndex = p1 - board;
					printf(" and landed on the other player and moved back to %d", playerIndex);
				}
			}
			return p1;
		}
		//Player 1 is at the end or further
		else {
			//Must still wait to check if p2 is further than p1 before declaring a winner
			//No need to check for collision here, if p2 beat p1 here, p2 has already won, since round will have been over
			//Simply return p1 location and check for winner only after p2 has moved w/ while loop cond
			return p1;
		}
	}
	//Player 2 is in movement
	else {
		//move player 2 according to their roll
		p2 = p2 + move;
		//Get the numerical location of the player on the board
		int playerIndex = p2 - board;
		printf("Player 2 rolled %d and is moved to %d", move, playerIndex);
		//Check if player 2 is not at the end or further
		if (p2 < board + SIZE) {
			//Check if player landed on B or F
			if (*p2 == 'B' || *p2 == 'F') {
				printf(" and landed on a %c, ", *p2);
				//Call findHaven function
				//Output if player landed on B
				if (*p2 == 'B') {
					p2 = findHaven(p2, board, SIZE);
					playerIndex = p2 - board;
					//Choose correct printf statement - check if player moved back to the start of the board
					if (playerIndex == -1) {
						printf("moved backward to the beginning of the board");
					}
					else {
						printf("moved backward to %d", playerIndex);
					}
				}
				//Call findHaven function
				//Output if player landed on F
				else {
					p2 = findHaven(p2, board, SIZE);
					int temp = playerIndex;
					playerIndex = p2 - board;
					//choose correct printf statement - check if player moved or not
					if (temp == playerIndex) {
						printf("and was unable to move forward");
					}
					else {
						printf("and moved to %d", playerIndex);
					}
				}
			}
			//Check if player landed on chute
			else if (*p2 >= 'a' && *p2 <= 'm') {
				printf(" and landed on a chute and slid down to ");
				//Call chuteLadder function
				p2 = chuteLadder(p2);
				playerIndex = p2 - board;
				printf("%d", playerIndex);

			}
			//Check if player landed on ladder
			else if (*p2 >= 'o' && *p2 <= 'z') {
				printf(" and landed on a ladder and climbed up to ");
				//Call chuteLadder function
				p2 = chuteLadder(p2);
				playerIndex = p2 - board;
				printf("%d", playerIndex);
			}
			//Check if players collided after applying chutes/ladders/B/F
			if (p1 == p2) {
				//Make sure players arent at begining
				if (p2 != board) {
					//This means players have collided, move p2 back 1 spot
					p2 = p2 - 1;
					playerIndex = p2 - board;
					printf(" and landed on the other player and moved back to %d", playerIndex);
				}
			}
			return p2;
		}
		//Player 2 is at the end or further
		else {
			//Since p1 could have reached this area first, must check if p2 collided with p1
			if (p1 == p2) {
				p2 = p2 - 1;
			}
			return p2;
		}
	}
}

char* findHaven(char* pLoc, char* board, int SIZE) {
	//Determine if player landed on B or F
	char BorF = *pLoc;
	char* temp = pLoc;
	//Search backwards for next Haven
	//Search until a Haven is found, or stop at begining or board
	if (BorF == 'B') {
		while (*temp != 'H' && temp >= board) {
			temp = temp - 1;
		}
		//If player landed on Haven, change it to '*' to remove haven from board
		if (*temp == 'H') {
			*temp = '*';
		}
		return temp;
	}
	//Search forward for next H
	//Search until haven is found, or leave player unmoved
	else {
		while (temp < board + SIZE) {
			if (*temp == 'H') {
				//Change Haven to '*' to remove it and return player location
				*temp = '*';
				return temp;
			}
			temp = temp + 1;
		}
		//No haven found, return player's original location
		return pLoc;
	}
}

char* chuteLadder(char* pLoc) {
	//Create temp to store player's old location
	char* temp = pLoc;
	//Calculate player's new location
	pLoc = pLoc + (int)(*pLoc - 'n');
	//Remove chute/ladder from board using temp
	*temp = '-';
	return pLoc;
}

/* SAMPLE RUN
Player 1 rolled 3 and is moved to 3
Player 2 rolled 3 and is moved to 3 and landed on the other player and moved back to 2
Player 1 rolled 2 and is moved to 5
Player 2 rolled 2 and is moved to 4 and landed on a chute and slid down to 1
Player 1 rolled 5 and is moved to 10
Player 2 rolled 2 and is moved to 3
Player 1 rolled 2 and is moved to 12
Player 2 rolled 3 and is moved to 6 and landed on a ladder and climbed up to 12 and landed on the other player and moved back to 11
Player 1 rolled 2 and is moved to 14 and landed on a chute and slid down to 5
Player 2 rolled 1 and is moved to 12
Player 1 rolled 6 and is moved to 11 and landed on a B, moved backward to 7
Player 2 rolled 4 and is moved to 16 and landed on a F, and moved to 22
Player 1 rolled 6 and is moved to 13
Player 2 rolled 1 and is moved to 23
Player 1 rolled 1 and is moved to 14
Player 2 rolled 6 and is moved to 29 and landed on a chute and slid down to 27
Player 1 rolled 6 and is moved to 20 and landed on a ladder and climbed up to 22
Player 2 rolled 1 and is moved to 28
Player 1 rolled 1 and is moved to 23
Player 2 rolled 3 and is moved to 31 and landed on a ladder and climbed up to 32
Player 1 rolled 1 and is moved to 24
Player 2 rolled 3 and is moved to 35 and landed on a B, moved backward to 33
Player 1 rolled 5 and is moved to 29
Player 2 rolled 2 and is moved to 35 and landed on a B, moved backward to 28
Player 1 rolled 3 and is moved to 32
Player 2 rolled 3 and is moved to 31
Player 1 rolled 5 and is moved to 37
Player 2 rolled 3 and is moved to 34
Player 1 rolled 4 and is moved to 41
Player 2 rolled 6 and is moved to 40
Player 1 rolled 1 and is moved to 42 and landed on a F, and moved to 50
Player 2 rolled 5 and is moved to 45 and landed on a chute and slid down to 40
Player 1 rolled 5 and is moved to 55 and landed on a chute and slid down to 52
Player 2 rolled 4 and is moved to 44
Player 1 rolled 1 and is moved to 53 and landed on a F, and moved to 62
Player 2 rolled 6 and is moved to 50
Player 1 rolled 1 and is moved to 63
Player 2 rolled 3 and is moved to 53 and landed on a F, and moved to 69
Player 1 rolled 1 and is moved to 64 and landed on a ladder and climbed up to 66
Player 2 rolled 5 and is moved to 74 and landed on a B, moved backward to 41
Player 1 rolled 3 and is moved to 69
Player 2 rolled 5 and is moved to 46 and landed on a ladder and climbed up to 50
Player 1 rolled 1 and is moved to 70
Player 2 rolled 2 and is moved to 52 and landed on a F, and moved to 79
Player 1 rolled 1 and is moved to 71 and landed on a ladder and climbed up to 81
Player 2 rolled 2 and is moved to 81 and landed on a B, moved backward to 13
Player 1 rolled 1 and is moved to 82 and landed on a chute and slid down to 81
Player 2 rolled 4 and is moved to 17 and landed on a chute and slid down to 15
Player 1 rolled 5 and is moved to 86
Player 2 rolled 1 and is moved to 16 and landed on a F, and moved to 87
Player 1 rolled 4 and is moved to 90 and landed on a F, and moved to 94
Player 2 rolled 1 and is moved to 88 and landed on a chute and slid down to 86
Player 1 rolled 5 and is moved to 99
Player 2 rolled 4 and is moved to 90 and landed on a F, and was unable to move forward
Player 1 rolled 1 and is moved to 100
Player 2 rolled 3 and is moved to 93 and landed on a ladder and climbed up to 94
Player 1 wins!
*/

/* SAMPLE RUN BOARD
  21k tH l B He Flq p H  hByHlho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
 2mH-1tH l B He Flq p H  hByHlho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  m2- tH l1B He Flq p H  hByHlho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -H l 21He Flq p H  hByHlho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH-1-H l B2H- Flq p H  hByHlho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -1 l B H- Flq p 2  hByHlho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B 1- Flq p *2 hByHlho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H1 Flq p *  hB2H-ho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - 1  hBy2-ho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - *1 hByH-h-2H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - * 1hByH-h- 2 B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - *  hBy21h- * B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - *  hBy*-h21* B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - *  hBy*-h- *2B 1jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - *  hBy*-h- * B  jr21FB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - *  hBy*-h- * B  jr2HFB -r j 1 FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - *  hBy*-h- * B  jr HFB2-r j * 1F -u gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - *  hBy*-h- * B  jr HFB -r j 2 FF -u gd  1 pjB mH x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - *  hBy*-h- * B  jr HFB -r j * FF -u gd  *1pjB m2 x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - *  hBy*-h- * B  jr 2FB -r j * FF -u gd  * -j1 m* x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - *  hBy*-h- * B  jr *FB -- j 2 FF -u gd  * -jB m1 x  BF i H Bm oB HlHFBhoH BB
  mH- -* l B H- Flq - *  hBy*-h- * B  jr *FB -- j * FF -u gd  * -jB m*1x  BF i 2 Bm oB HlHFBhoH BB
  mH- -* l B 2- Flq - *  hBy*-h- * B  jr *FB -- j * FF -u gd  * -jB m* -  BF i * 1m oB HlHFBhoH BB
  mH- -* l B *-2F-q - *  hBy*-h- * B  jr *FB -- j * FF -u gd  * -jB m* -  BF i * 1- oB HlHFBhoH BB
  mH- -* l B *- F-q - *  hBy*-h- * B  jr *FB -- j * FF -u gd  * -jB m* -  BF i * B- oB12lHFBhoH BB
  mH- -* l B *- F-q - *  hBy*-h- * B  jr *FB -- j * FF -u gd  * -jB m* -  BF i * B- oB2*-HFBho1 BB
  mH- -* l B *- F-q - *  hBy*-h- * B  jr *FB -- j * FF -u gd  * -jB m* -  BF i * B- oB *-H2Bho* BB
  mH- -* l B *- F-q - *  hBy*-h- * B  jr *FB -- j * FF -u gd  * -jB m* -  BF i * B- oB *-HFBh-2 BB
*/
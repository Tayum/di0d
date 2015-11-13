#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int run(int moves[], int movesLen, int res[], int resLen) {
	enum states { q0=0, q1, q2, q3 };
	int acts[4][206];
	int chngState[4][206];
	int curMove = 0, curState = 0;
	int acting, n = 0, i, j = 0;
	//pop - 100, continue - 200, repeat - 300, break/empty - 400
	//state q0:
	acts[q0][7] = 100;
	chngState[q0][7] = 1;
	acts[q0][15] = 1;
	chngState[q0][15] = 1;
	acts[q0][25] = 400;
	acts[q0][205] = 6;
	chngState[q0][205] = 0;
	//state q1:
	acts[q1][7] = 100;
	chngState[q1][7] = 2;
	acts[q1][15] = 200;
	chngState[q1][15] = 0;
	acts[q1][25] = 2;
	chngState[q1][25] = 2;
	acts[q1][205] = 300;
	chngState[q1][205] = 3;
	//state q2:
	acts[q2][7] = 400;
	acts[q2][15] = 4;
	chngState[q2][15] = 3;
	acts[q2][25] = 400;
	acts[q2][205] = 3;
	chngState[q2][205] = 3;
	//state q3:
	acts[q3][7] = 400;
	acts[q3][15] = 7;
	chngState[q3][15] = 0;
	acts[q3][25] = 5;
	chngState[q3][25] = 2;
	acts[q3][205] = 200;
	chngState[q3][205] = 3;

	for (i = 0; i < movesLen; i++) {
		curMove = moves[i];
		if (curMove != 7 && curMove != 15 && curMove != 25 && curMove != 205) {
			j = 0;
			while (res[j] != 0 && j < resLen) {
				j++;
				n++;
			}
			return n;
		}
		acting = acts[curState][curMove];
		switch (acting) {
		case 200: //continue case
			curState = chngState[curState][curMove];
			break;
		case 300: //repeat case
			curState = chngState[curState][curMove];
			j = j - 1;
			break;
		case 400: //break/empty case
			j = 0;
			while (res[j] != 0 && j < resLen) {
				j++;
				n++;          
			}
			return n;
		case 100: //pop case
			if (j<=0) {
				return 0;
			}
			res[j - 1] = 0;
			j--;
			curState = chngState[curState][curMove];
			
			break;
		default: //push case
			res[j] = acting;
			j++;
			curState = chngState[curState][curMove];
			break;
		}
	}
	j = 0;
	while (res[j] != 0 && j < resLen) {
		j++;
		n++;
	}
	return n;
}
/*
 * Program used in the experimental evaluation of the following papers.
 * 2008ESOP - Chawdhary,Cook,Gulwani,Sagiv,Yang - Ranking Abstractions
 * 2010SAS - Alias,Darte,Feautrier,Gonnord, Multi-dimensional Rankings, Program 
 *           Termination, and Complexity Bounds of Flowchart Programs
 *
 * Date: 2014
 * Author: Caterina Urban
 */

typedef enum {false, true} bool;

extern int __VERIFIER_nondet_int(void);

int x, y, tx;

int main() {
	tx = 0;
	x = 0;
	y = 0;
	while (x >= y && tx >= 0) {
		if (0 != 0) {
			x = x - 1 - tx;
		} else {
			y = y + 1 + tx;
		}
	}
	return 0;
}

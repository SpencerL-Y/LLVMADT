/*
 * Date: 06/07/2015
 * Created by: Ton Chanh Le (chanhle@comp.nus.edu.sg)
 * Adapted from Cairo_true-termination.c
 */

typedef enum {false, true} bool;

extern int __VERIFIER_nondet_int(void);

int x;

int main()
{
    x = 0;
	if (x > 0) {
	    while (x != 0 && x!= -1) {
	    	x = x - 2;
    	}
	}
	return 0;
}

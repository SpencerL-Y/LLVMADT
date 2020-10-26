/*
 * Date: 06/07/2015
 * Created by: Ton Chanh Le (chanhle@comp.nus.edu.sg)
 */

typedef enum {false, true} bool;

extern int __VERIFIER_nondet_int(void);

int x;
int y;
int main()
{
    x = 0;
    y = 0;
	if (y >= 0) {
	    while (x >= 0) {
	    	x = x - y;
    	}
	}
	return 0;
}

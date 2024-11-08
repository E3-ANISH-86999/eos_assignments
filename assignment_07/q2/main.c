/*
Create a multi-ﬁle project (main.c, circle.c/.h, square.c/.h, rectangle.c/.h). Compile the program using "gcc" and execute it. No fork(), exec() expected
here.
*/

#include "circle.h"
#include "rectangle.h"
#include "square.h"
#include <unistd.h>

int main(){
	circle();
	sleep(1);

	rectangle();
	sleep(1);

	square();
	sleep(1);

	return 0;
}

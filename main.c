#include <stdio.h>

#define DEMO1 1
#define DEMO2 2
#define DEMO3 3
#define DEMO4 4
#define DEMO5 5
#define DEMO6 6
#define DEMO7 7

#define RUN_DEMO  DEMO7
/**
 * main.c
 */
int main(void)
{
#if    RUN_DEMO == DEMO1
    demo1();
#elif  RUN_DEMO == DEMO2
    demo2();
#elif  RUN_DEMO == DEMO3
    demo3();
#elif  RUN_DEMO == DEMO4
    demo4();
#elif  RUN_DEMO == DEMO5
    demo5();
#elif  RUN_DEMO == DEMO6
    demo6();
#elif  RUN_DEMO == DEMO7
    demo7();

#endif

	return 0;
}

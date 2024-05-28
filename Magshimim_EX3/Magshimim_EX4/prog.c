/*********************************
* Class: MAGSHIMIM C2			 *
* Week 3           				 *
* HW solution   			 	 *
**********************************/
#include <stdio.h>
#include <string.h>

void printArray(char* p, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%c", p[i]); //the problem is that p is alway smaller than p plus somthing which means the argument will always be true so the loop will run forever
    }
    printf("\n");
}


int main(void)
{
	char* msg = "hi jyegq meet me at 2 :)";
	printArray(msg, strlen(msg));

    getchar();
    getchar();
	return 0;
 }
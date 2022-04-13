/* PROGRAM TO WRITE STRING TO A FILE AND READING THEM AND OUTPUT ON CONSOLE
   REQUIRED FILES TO BE CREATED TO RUN PROGRAM: --test.txt--
*/
#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
//using namespace std;

int main()
{
	FILE *fp;
	int i=5;
	char uname[20],pword[20],filename[20];
	char data[10][20];
	fp = fopen("test.txt","a");
	while(i--)
	{
		printf(">");
		scanf("%s",uname);
		//printf(">");
		//scanf("%s",pword);
		fprintf(fp,"%s\n",uname);
	}
	_fcloseall();
	fp = fopen("test.txt","r");
	i = 0;
	while(i<5)
		fscanf(fp,"%s",data[i++]);
	for(i=0 ; i<10 ; i++)
		printf("%s\n",data[i]);
		
	_fcloseall();	
	
	
	
	return 0;
}





/* PROGRAM TO OPEN A PRE EXISTING FILE WITH STRINGS IN IT
   AND TO DELETE A STRING BASED ON USER INPUT.
   REQUIRED FILES TO BE CREATED TO RUN PROGRAM: --scandelTest.txt--(must have strings in new lines)
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
	FILE *fp,*fq;
	char uname[20],temp[20];
	printf("Account u want to del: ");
	scanf("%s",uname);
	fp = fopen("scandelTest.txt","r");
	fq = fopen("temp.txt","w");
	while(!feof(fp))
	{
		fscanf(fp,"%s\n",temp);
		if(strcmp(uname,temp))
			fprintf(fq,"%s\n",temp);
	}
	_fcloseall();
	remove("scandelTest.txt");
	rename("temp.txt","scandelTest.txt");
	//	printf("%shi",temp);
	
	return 0;
}





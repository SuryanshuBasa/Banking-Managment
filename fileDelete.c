/* PROGRAM TO WRITE 5 STRINGS TO A FILE AND DELETING A STRING 
   BASED ON THE USER CHOICE
   REQUIRED FILES TO BE CREATED TO RUN PROGRAM: --NONE--
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
	int i=5;
	char uname[20],del[20];
	fp = fopen("testdel.txt","w");
	while(i--)
	{
		printf(">");
		scanf("%s",uname);
		fprintf(fp,"%s\n",uname);
		//fputs("\n",fp);
	}
	fclose(fp);
	fp = fopen("testdel.txt","r");
	fq = fopen("temp.txt","w");
	if(fq == NULL)
		return 1;
	printf(">>");
	scanf("%s",del);
	i=5;
	while(!feof(fp))
	{
		fscanf(fp,"%s\n",uname);
		if(strcmp(uname,del))
			fprintf(fq,"%s\n",uname);	
	}
	_fcloseall();
	remove("testdel.txt");
	rename("temp.txt","testdel.txt");
	return 0;
}





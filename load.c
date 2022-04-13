/* ----TEST HEADER FILE----
*/

#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

#define server "masterDataBase.txt"

char temp[20];
struct address{
	char country[20];
	char state[20];
	char city[20];
	int pincode;
};
struct node{
	char user[20];
	char pass[20];
	float balance;
	struct address details;
	struct node* right;
	struct node* left;
};
struct user user,userA;
struct node* head = NULL;
struct node* tail = NULL;

void load()
{
	FILE *fp, *fq;
	fp = fopen(server,"r");
	while(!feof(fp))
	{
		fscanf(fp,"%s\n",temp);
		fq = fopen(strcat(temp,".txt"),"r");
		fread(&user,sizeof(user),1,fq);
		append(userA);
		fclose(fp);
	}
}
void append(struct user temp)
{
	struct node* node;
	node = (struct node*)malloc(sizeof(struct node));
	strcpy(node->user,temp.user);
	strcpy(node->pass,temp.pass);
	node->balance = temp.balance;
	strcpy(node->details.country,temp.address.country);
	strcpy(node->details.state,temp.address.state);
	strcpy(node->details.city,temp.address.city);
	node->details.pincode = temp.address.pincode;
	node->right = NULL;
	node->left = NULL;
	if(head == NULL)
		head = tail = node;
	else
	{
		tail->right = node;
		node->left = tail;
		tail = node;
	}		
}
void display()
{
	struct node* p;
		p = head;
		while(p != NULL)
		{
			printf("|%s|--",p->user);
			p = p->right;
		}
		printf("\n");
}







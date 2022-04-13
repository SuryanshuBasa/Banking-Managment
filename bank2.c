/* BASIC MENU DRIVEN BANK MANAGMENT SYSTEM WITH USE OF FILES TO STORE AND RETIREVE DATA
   AND PERFORM DEPOSIT WITHDRAW SEND MONEY OPERATIONS.
   LOAD ALL THE PRE REGISTERED USER TO LINKED LIST DYNAMICALLY TO UPADTE
   INFO AT RUN TIME AND WRITE IT BACK TO THE FILE TO STORE PERMANANT.
   REQUIRED FILES TO BE CREATED TO RUN PROGRAM: --masterDataBase.txt--
*/
#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>


#define server "masterDataBase.txt"

bool first = true;
char username[20],pass[20],temp[20];
char usernameA[20],passA[20];
char filename[20];
char updatestr[20];
int pinupdate;
float amount,deposit,sendmoney;

struct address{
	char country[20];
	char state[20];
	char city[20];
	int pincode;
};

struct user{
	char user[20];
	char pass[20];
	float balance;
	struct address address;
};
struct user user,userA;

struct node{
	char user[20];
	char pass[20];
	float balance;
	struct address details;
	struct node* right;
	struct node* left;
};

struct node* head = NULL;
struct node* tail = NULL;

void updateserver(char NEW[],char OLD[])
{
	FILE *a , *b;
	char tempb[20];
	a = fopen(server,"r");
	b = fopen("temp.txt","w");
	while(!feof(a))
	{
		fscanf(a,"%s\n",tempb);
		if(strcmp(tempb,OLD))
			fprintf(b,"%s\n",tempb);
	}
	fprintf(b,"%s\n",NEW);
	_fcloseall();
	remove(server);
	rename("temp.txt","masterDataBase.txt");
	return;
}
void load()
{
	FILE *fp, *fq;
	fp = fopen(server,"r");
	while(!feof(fp))
	{
		fscanf(fp,"%s\n",temp);
		fq = fopen(strcat(temp,".txt"),"r");
		fread(&user,sizeof(struct user),1,fq);
		append(user);
		fclose(fq);
	}
	fclose(fp);
	fclose(fq);
	return;
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
	system("cls");
	struct node* p;
		p = head;
		if(p == NULL) return;
		
		while(p != NULL)
		{
			printf("|%s|--",p->user);
			p = p->right;
		}
		printf("\n");
		getch();
		return;
}

void registeracc()
{
	FILE *fp;
	printf("-----Create Account-----\n");
	system("cls");
	printf("Enter User name: ");
	scanf("%s",user.user);
	printf("Enter New Password: ");
	scanf("%s",user.pass);
	user.balance = 0;
	printf("\nAddress Details: ");
	printf("Country: ");
	scanf("%s",user.address.country);
	printf("State: ");
	scanf("%s",user.address.state);
	printf("City: ");
	scanf("%s",user.address.city);
	printf("Pincode: ");
	scanf("%d",&user.address.pincode);
	strcpy(filename,user.user);
	fp = fopen(strcat(filename,".txt"),"w");
	if(fp == NULL)
	{
		printf("Error Occured Try again :(");
		getch();
		_fcloseall();
		return;
	}
	else
	{
		FILE *fq;
		fq = fopen(server,"a");
		fprintf(fq,"%s\n",user.user);
		fwrite(&user,sizeof(struct user),1,fp);
		append(user);
		printf("Account Created Welcome!!");
		getch();
		_fcloseall();
		return;
	}	
}
void login()
{
	FILE *fp;
	system("cls");
	printf("Welcome Back-----\n");
	printf("Username: ");
	scanf("%s",username);
	printf("Password: ");
	scanf("%s",pass);
	strcpy(filename,username);
	fp = fopen(strcat(filename,".txt"),"r+");
	fread(&user,sizeof(struct user),1,fp);
	if(fp == NULL)
	{
		printf("User name incorrect try again");
		getch();
		_fcloseall();
		return;
	}
	else
	{
		int choice;
		if(!strcmp(pass,user.pass))
		{
				printf("Welcome Back %s!!",user.user);
				getch();	
			while(1)
			{
				system("cls");
				printf("1.Check Balance\n");
				printf("2.Address Details\n");
				printf("3.Withdraw\n");
				printf("4.Deposit\n");
				printf("5.Send Money\n");
				printf("6.Update info\n");
				printf("7. Change Username or Password\n");
				printf("8.Go back\n");
				printf("Choice-> ");
				scanf("%d",&choice);
				switch(choice)
				{
					case 1:{
						printf("Available Balance: %.2f\n",user.balance);
						printf("Press Enter to go back..\n");
						getch();
						break;
					}
					case 2:{
						printf("Country: %s\n",user.address.country);
						printf("State: %s\n",user.address.state);
						printf("City: %s\n",user.address.city);
						printf("Pincode: %d\n",user.address.pincode);
						printf("Press Enter to go back..\n");
						getch();
						break;
					}
					case 3:{
						printf("Enter amount to Withdraw: ");
						scanf("%f",&amount);
						if(user.balance - amount < 0)
						{
							printf("Insuffciant Funds..");
							printf("Press Enter to go back..\n");
							getch();
							return;
						}
						else
							user.balance -= amount;
						printf("Money Withdraw successful\n");
						rewind(fp);
						fwrite(&user,sizeof(user),1,fp);	
						printf("Press Enter to go back..\n");
						getch();	
						break;
					}
					case 4:{
						printf("Amount to Deposit: ");
						scanf("%f",&deposit);
						user.balance += deposit;
						rewind(fp);
						fwrite(&user,sizeof(user),1,fp);
						printf("Money Depoit successful\n");
						getch();
						break;
					}
					case 5:{
						FILE *fq;
						printf("Enter account name: ");
						scanf("%s",usernameA);
						strcpy(filename,usernameA);
						fq = fopen(strcat(filename,".txt"),"r+");
						if(fq == NULL)
						{
							printf("Account not found\n");
							printf("Press Enter to go back..\n");
							getch();	
							break;
						}
						else
						{
							fread(&userA,sizeof(struct user),1,fq);
							printf("Amount to be sent: ");
							scanf("%f",&sendmoney);
							if(user.balance - sendmoney < 0)
							{
								printf("Invalid Funds\n");
								printf("Press Enter to go back..\n");
								getch();	
								break;	
							}
							else
							{
								user.balance -= sendmoney;
								userA.balance += sendmoney;
								rewind(fp);
								fwrite(&user,sizeof(user),1,fp);
								rewind(fq);
								fwrite(&userA,sizeof(user),1,fq);
								printf("Money Sent!\n");
								printf("Press Enter to go back..\n");
								getch();	
								break;	
							}
						}
					}
					case 6:{
						int choice;
						struct node* temp;
						temp = head;
						while(strcmp(user.user,temp->user))
							temp = temp->right;
						while(1)
						{
							system("cls");
							printf("Details you want to change:\n");
							printf("1.Country\n");
							printf("2.State\n");
							printf("3.City\n");
							printf("4.Pincode\n");
							printf("5.Go back\n");
							printf("Choice-> ");
							scanf("%d",&choice);
							switch(choice)
							{
								case 1:{
									printf("Enter new Country: ");
									scanf("%s",updatestr);
									strcpy(user.address.country,updatestr);
									strcpy(temp->details.country,user.address.country);
									rewind(fp);
									fwrite(&user,sizeof(struct user),1,fp);
									printf("Info Updated\n");
									printf("Press Enter to go back..\n");
									getch();
									break;
								}
								case 2:{
									printf("Enter new State: ");
									scanf("%s",updatestr);
									strcpy(user.address.state,updatestr);
									strcpy(temp->details.state,user.address.state);
									rewind(fp);
									fwrite(&user,sizeof(struct user),1,fp);
									printf("Info Updated\n");
									printf("Press Enter to go back..\n");
									getch();
									break;
								}
								case 3:{
									printf("Enter new City: ");
									scanf("%s",updatestr);
									strcpy(user.address.city,updatestr);
									strcpy(temp->details.city,user.address.city);
									rewind(fp);
									fwrite(&user,sizeof(struct user),1,fp);
									printf("Info Updated\n");
									printf("Press Enter to go back..\n");
									getch();
									break;
								}
								case 4:{
									printf("Enter new Pincode: ");
									scanf("%d",&pinupdate);
									user.address.pincode = temp->details.pincode = pinupdate;
									rewind(fp);
									fwrite(&user,sizeof(struct user),1,fp);
									printf("Info Updated\n");
									printf("Press Enter to go back..\n");
									getch();
									break;
								}
								case 5:{
									_fcloseall();
									return;
									break;
								}
							}
						}	
						
						break;
					}
					case 7:{
						int x;
						struct node* temp;
						temp = head;
						while(strcmp(user.user,temp->user))
							temp = temp->right;
							
						printf("Press 1 to change password and 2 for username: ");
						scanf("%d",&x);
						if(x == 1)
						{
							printf("Enter new password: ");
							scanf("%s",pass);
							strcpy(user.pass,pass);
							strcpy(temp->pass,user.pass);
							rewind(fp);
							fwrite(&user,sizeof(struct user),1,fp);
							printf("Info Updated\n");
							printf("Press Enter to go back..\n");
							getch();
							_fcloseall();
							return;
						}
						else if(x == 2)
						{
							char tempa[20];
							char tempb[20],tempc[20];
							strcpy(tempa,user.user);
							strcpy(tempc,tempa);
							printf("Enter new username: ");
							scanf("%s",username);
							strcpy(user.user,username);
							strcpy(temp->user,user.user);
							strcpy(tempb,user.user);
							rewind(fp);
							fwrite(&user,sizeof(struct user),1,fp);
							_fcloseall();
							strcat(tempa,".txt");
							strcat(tempb,".txt");
							rename(tempa,tempb);
							updateserver(user.user,tempc);
							printf("Info Updated\n");
							printf("Press Enter to go back..\n");
							getch();
							return;	
						}
						return;
						break;
					}
					case 8:{
						_fcloseall();
						return;
						break;
					}
				}	
				
			}			
		}
		else
		{
			printf("Wrong Password :(\n");
			printf("Press Enter to go back..\n");
			getch();	
			return;
		}
		
	}
		_fcloseall();
		getch();
		return;	
}
int main()
{
	if(first)
	{
		load();
		first = false;
	}
	
	int choice;
	while(1)
	{
		system("cls");
		choice = 0;
		printf("-----Welcome to Basa Bank-----\n");
		printf("1. Register Account\n");
		printf("2. Login to Account\n");
		printf("3. Display\n");
		printf("4. Exit Bank\n");
		printf("Choice-> ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:{
				registeracc();
				break;
			}
			case 2:{
				login();
				break;
			}
			case 3:{
				display();
				break;
			}
			case 4:{
				_fcloseall();
				exit(0);
				break;
			}
			
		}
	}	
	return 0;
}





/* BASIC MENU DRIVEN BANK MANAGMENT SYSTEM WITH USE OF FILES TO STORE AND RETIREVE DATA
   AND PERFORM DEPOSIT WITHDRAW SEND MONEY OPERATIONS
   REQUIRED FILES TO BE CREATED TO RUN PROGRAM: --masterDataBase.txt--
*/
#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

//#include"load.c"
#define server "masterDataBase.txt"

char username[20],pass[20];
char usernameA[20],passA[20];
char filename[20];
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
	fp = fopen(strcat(filename,".txt"),"r");
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
				printf("6.Go back\n");
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
	//load();
	int choice;
	while(1)
	{
		system("cls");
		printf("-----Welcome to Basa Bank-----\n");
		printf("1. Register Account\n");
		printf("2. Login to Account\n");
		printf("3. Exit Bank\n");
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
				_fcloseall();
				exit(0);
				break;
			}
		}
	}
	
	return 0;
}





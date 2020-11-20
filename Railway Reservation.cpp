#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
const int noofSeats=10;
const int noofUsers=10;
struct
{
	int seatNo;
	int status;
	int userId;
	char travelerName[10];
	int travelerAge;
}seatDictionary[10];

struct
{
	int userId;
	int passCode;
	char name[10];
	int age;
	int allocSeats[6];
}userDictionary[10];


int getArraySize(int a[],int size)
{
	int i=0;
	 for(i=0;i<size;i++)
		if(a[i]=='\0')
			return i;
	return -1;
}
void createSeats()
{
	int i=0;
	for(i=0;i<noofSeats;i++)
	{
		seatDictionary[i].seatNo=i+1;
		seatDictionary[i].status=0;
	}
}

int getSeatStatus(int seatNo)
{
	int i=0;
	for(i=0;i<noofSeats;i++)
		if(seatDictionary[i].seatNo==seatNo)
			return seatDictionary[i].status;
	return -1;
}



int switchSeatStatus(int seatNo,int id,char travelerName[10],int travelerAge)
{
	int i;
	for(i=0;i<sizeof(seatDictionary);i++)
		if(seatDictionary[i].seatNo==seatNo)
		{
			seatDictionary[i].status=seatDictionary[i].status>0?0:1;
			seatDictionary[i].userId=id;
			seatDictionary[i].travelerAge=travelerAge;
			strcpy(seatDictionary[i].travelerName,travelerName);
		}
	return -1;
}

void printAvailableSeats(char o)
{
	int i,noSeatsFlg=1;
	if(o!='c')
	{
		for(i=0;i<noofSeats;i++)
		if(seatDictionary[i].status==0)
		{
			printf("%d\t",seatDictionary[i].seatNo);
			noSeatsFlg=0;
		}
		if(noSeatsFlg==1)
			printf("\nSorry!No seats are available");
	}
	else
	{
		for(i=0;i<noofSeats;i++)
		if(seatDictionary[i].status!=0)
		{
			if(noSeatsFlg==1)
				printf("\tName\t\tAge\tSeatNo\n\n----------------------------------------------------\n\n");
			printf("\t");
			printf("%s",seatDictionary[i].travelerName);
			printf("\t\t%d",seatDictionary[i].travelerAge);
			printf("\t%d\n",seatDictionary[i].seatNo);
			noSeatsFlg=0;
		}
		printf("\n");
		if(noSeatsFlg==1)
			printf("\nNo bookings done so far.\n");
	}
}

int bookSeats(int id)
{
	int seatNo,travelerage;
	char travelerName[10];
	int userPos=findUserPosById(id);
	int bookedseatscount=getArraySize(userDictionary[userPos].allocSeats,sizeof(userDictionary[userPos].allocSeats));
	printf("\nEnter the name of the traveler (within 10 char without space) :");
	scanf("%s",&travelerName);
	printf("\nEnter the age of the traveler :");
	scanf("%d",&travelerage);
	printf("\nChoose any of the below seats :\n");
	printAvailableSeats('s');
	printf("\n");
	scanf("%d",&seatNo);
	if(getSeatStatus(seatNo)!=0)
	{
		printf(getSeatStatus(seatNo)==1?"\nSeat already booked\n":"\nInvalid seat no\n");
		return 0;
	}
	if(bookedseatscount>5)
	{
		printf("\nBooking failed!Max seats reached!\n");
		return 0;
	}
	userDictionary[userPos].allocSeats[bookedseatscount]=seatNo;
	switchSeatStatus(seatNo,id,travelerName,travelerage);
	return 1;
}

int cancelSeats(int id)
{
	int seatNo;
	int userPos=findUserPosById(id);
	int usrSeatPos=-1,i;
	char travelerName[10];
	int seatPos;
	if(getArraySize(userDictionary[userPos].allocSeats,sizeof(userDictionary[userPos].allocSeats))==0)
	{
		printf("\nNo seats were booked!\n");
		return 0;
	}
	printf("\nChoose any one seat to cancel\n");
	for(i=0;i<getArraySize(userDictionary[userPos].allocSeats,sizeof(userDictionary[userPos].allocSeats));i++)
	{
		seatPos=findSeatPosBySeatNo(userDictionary[userPos].allocSeats[i]);
		if(i==0)
			printf("*****************************************\n\tName\t\tAge\tSeat No\n-------------------------------------\n");

		printf("\t");
		printf("%s",seatDictionary[seatPos].travelerName);
		printf("\t\t%d",seatDictionary[seatPos].travelerAge);
		printf("\t%d\n",seatDictionary[seatPos].seatNo);
	}
	printf("\n*****************************************\n");
	scanf("%d",&seatNo);
	for(i=0;i<getArraySize(userDictionary[userPos].allocSeats,sizeof(userDictionary[userPos].allocSeats));i++)
		if(userDictionary[userPos].allocSeats[i]==seatNo)
			usrSeatPos=i;
	if(usrSeatPos==-1)
	{
		printf("\nThe selected seat was not booked by you!\n");
		return 0;
	}
	for(i=usrSeatPos;i<sizeof(userDictionary[userPos].allocSeats)+1;i++)
		userDictionary[userPos].allocSeats[i]=userDictionary[userPos].allocSeats[i+1];
	switchSeatStatus(seatNo,0,travelerName,0);
	return 1;
}

int findUserPosById(int id)
{
	int i;
	for(i=0;i<noofUsers;i++)
		if(userDictionary[i].userId==id)
			return i;
	return -1;
}

int findSeatPosBySeatNo(int seatNo)
{
	int i;
	for(i=0;i<noofUsers;i++)
		if(seatDictionary[i].seatNo==seatNo)
			return i;
	return -1;
}
int login(int id,int passCode)
{
	int userPos=findUserPosById(id);
	if(userPos==-1)
	{
		printf("\nInvalid UserId\n");
		return 0;
	}
	if(userDictionary[userPos].passCode!=passCode)
	{
		printf("\nWrong passcode\n");
		return 0;
	}
	return 1;
}
int findLastUserPosition()
{
	int i=0;
	for(i=0;i<noofUsers;i++)
		if(userDictionary[i].userId==0)
			return i;
	return -1;
}
int signUp(char name[10],int id,int passCode,int age)
{
	int userPos=findLastUserPosition();
	if(userPos>9)
	{
		printf("\nMax users reached!\n");
		return 0;
	}
	if(findUserPosById(id)!=-1)
	{
		printf("\nUserID already exists!\n");
		return 0;
	}
	userDictionary[userPos].userId=id;
	userDictionary[userPos].passCode=passCode;
	strcpy(userDictionary[userPos].name,name);
	userDictionary[userPos].age=age;
	return 1;
}
void printName(int userId)
{
	printf("%s",userDictionary[findUserPosById(userId)].name);
}

void main()
{
	int option,userId,passCode,sessionUserId=-1,age;
	char name[10];
	createSeats();
	home:
	clrscr();
	if(sessionUserId==-1)
	{
		printf("\n********Welcome to railways********\n1.Login\n2.SingUp\n3.Exit\n");
		scanf("%d",&option);
		switch(option)
		{
			case 1:
				printf("\nUser Id :");
				scanf("%d",&userId);
				printf("\nPassCode :");
				scanf("%d",&passCode);
				if(login(userId,passCode)==1)
				{
					sessionUserId=userId;
					printf("\nSuccessfully logged in.Welcome ");
					printName(userId);
					getch();
					goto home;
				}
				else
				{
					printf("Login failed!");
					getch();
					goto home;
				}
			case 2:
				printf("\nName (within 10 char without space):");
				scanf("%s",name);
				printf("\nAge :");
				scanf("%d",&age);
				printf("\nUser Id (Numeric) :");
				scanf("%d",&userId);
				printf("\nPassCode (Numeric) :");
				scanf("%d",&passCode);
				if(signUp(name,userId,passCode,age)==1)
				{
					printf("\nUser Id creation succeeded!\n");
					getch();
					//clrscr();
					goto home;
				}
				else
				{
					printf("\nSign Up failed!\n");
					getch();
					goto home;
				}
			case 3:
				exit(0);
		}
	}
	else
	{
		printf("\nHi ");
		printName(sessionUserId);
		printf("!\nChoose any of the below option\n1.Book a ticket\n2.Cancel ticket\n3.Availability check\n4.View chart\n5.Logout\n");
		scanf("%d",&option);
		switch(option)
		{
			case 1:
				if(bookSeats(sessionUserId)==0)
					printf("\nBooking failed!\n");
				else
					printf("\nBooked successfully\n");
				getch();
				goto home;
			case 2:
				if(cancelSeats(sessionUserId)==0)
					printf("\nCancelation failed!\n");
				else
					printf("\nTicket canceled successfully\n");
				getch();
				goto home;
			case 3:
				printf("\nThe below seats are available for booking\n");
				printAvailableSeats('s');
				getch();
				goto home;
			case 4:
				printf("\n\n**********************RailWay Chart**********************\n\n");
				printAvailableSeats('c');
				printf("\n\n**********************The End**********************\n\n");
				getch();
				goto home;
			case 5:
				sessionUserId=-1;
				goto home;
			default:
				printf("\nInvalid option\n");
				getch();
				goto home;
		}
	}
	
}




















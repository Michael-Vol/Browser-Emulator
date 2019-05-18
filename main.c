/*************************************************
Implementation File	: main.c
Author				: M.Volakis 28/04/2019
Content				: Implementation of Browser Simulation with ATD Session

Μιχάλης Βολάκης Α.Μ:1115201800022
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Session.h"

void print_options(void); //Function to print User Options
char * get_address(void); //Function to get adress
int main(int argc, char *argv[]) {
	InfoSessionPtr MySessions[2];
	MySessions[0] = NULL;
	MySessions[1] = NULL;
	char *address;
	int option,currSession = 0,err; 
	char x;
	do{
		//Print  options
		print_options();
		//Read user input
		if(scanf("%d",&option) == 0) { // if users enters unexpected input
			while ( (x = getchar()) != EOF && x != '\n' );//read and discard the invalid data from stdin
			continue;
		}
		switch(option){ 
			case 1:  
				printf("\nInsert new Opening Address: ");
				address = get_address(); 
				MySessions[currSession] = SessionNew(address);
				if(MySessions[currSession] == NULL) printf("Couldn't create Session");
				else printf("\nNew Session has been created!\n"); 
				break; 
			case 2:
				if((err = SessionNewTab(MySessions[currSession])) == 1) printf("New Tab has been created");
				else if(err == 0) printf("\nCouldn't create new Tab\n"); 
				else printf("\nNo Session exists.\n"); 
				break;
			case 3:
				printf("Address of Current Tab: ");
				if(SessionTabShow(MySessions[currSession]) == -1) printf("\nNo Session exists.\n"); 
				break;
			case 4:
				if(SessionTabNext(MySessions[currSession]) == -1) printf("\nNo Session exists.\n"); 
				break;
			case 5:
				if(SessionTabPrev(MySessions[currSession]) == -1) printf("\nNo Session exists.\n"); 
				break;
			case 6:	
				if((err = SessionTabMoveLeft(MySessions[currSession]) == -1)) printf("\nNo Session exists.\n"); 
				else if(err) printf("\nThe Tab has been moved to the left\n");
				break;	
			case 7:
				if((err = SessionTabMoveRight(MySessions[currSession]) == -1)) printf("\nNo Session exists.\n"); 
				else if(err) printf("\nThe Tab has been moved to the right\n");
				break;
			case 8: 
				printf("\nPrint new Opening Address: ");
				if(SessionNewOpeningAddress(MySessions[currSession],get_address()) == -1) printf("\nNo Session exists.\n"); 
				break;
			case 9:
				if(SessionShowOpeningAddress(MySessions[currSession]) == -1) printf("\nNo Session exists.\n"); 
				break;
			case 10:
				if(SessionSiteNext(MySessions[currSession]) == -1) printf("\nNo Session exists.\n"); 
				break;
			case 11:
				if(SessionSitePrev(MySessions[currSession]) == -1) printf("\nNo Session exists.\n"); 
				break;
			case 12:
				printf("Address of current Site: ");
				if(SessionSiteShow(MySessions[currSession]) == -1) printf("\nNo Session exists.\n"); 
				break;
			case 13:
				if((err = SessionTabClose(MySessions[currSession])) == 0) printf("Last Tab and Session have been deleted");
				else if(err == 1) printf("The current Tab has been deleted.");
				else if(err == -1) printf("\nNo Session exists.\n");
				else if(err == 2) printf("The Tab is linked to another Tab.Delete this Tab first.");
				break;
			case 14: 
				if(SessionClose(MySessions[currSession]) == -1) printf("\nNo Session exists.");
				else printf("\nThe Session has been closed\n");
				break;    
			case 15:
				printf("\nInsert new Address: ");
				address = get_address();
				if((err = SessionNewAddress(MySessions[currSession],address)) == 1) printf("\nNew Site has been created");
				else if(err == 0) printf("Couldn't create new Site\n");
				else printf("\nNo Session exists.\n");
				break;
			case 16: 
				if(currSession == 0){
					currSession = 1;
					printf("Current Session : Session 2"); 
				}
				else{
					currSession = 0;
					printf("Current Session : Session 1");
				}
			case 17:
				if((err = SessionOpenNewTab(MySessions[currSession])) == -1) printf("\nNo Session exists.");
				else if(err == 0) printf("\nCouldn't create new Tab\n"); 
				else if(err == 1) printf("New Tab has been created\n");
		}
	}while(option); 
	free(address);
	return 0;
}	


void print_options(void){
	printf("\n\
1)Create New Session\n\
2)Create New  Tab\n\
3)Show data of current Tab\n\
4)Go to next Tab\n\
5)Go to previous Tab\n\
6)Move Tab to the left\n\
7)Move Tab to the right\n\
8)Change Opening Address\n\
9)Show Opening Address\n\
10)Go to next Site\n\
11)Go to previous Site\n\
12)Show data of current Site\n\
13)Close Tab\n\
14)Close Session\n\
15)Create new Site(New Address)\n\
16)Switch Session(Default Session is Session 1)\n\
17)Create new Tab with the Address of Current Site\n\n\n\
Insert your option(1-16, 0 for exit):");
}
char * get_address(){
		char *address = malloc(sizeof(char) * 100);
		scanf("%s",address);
		return address;
}

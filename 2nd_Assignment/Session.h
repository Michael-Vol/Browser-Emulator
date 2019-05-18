/*************************************************
Implementation File : Session.h
Author  			: M.Volakis 28/04/2019
Content 			: ATD Session Interface


Μιχάλης Βολάκης Α.Μ:1115201800022
**************************************************/
#ifndef __SESSION__
#define __SESSION__

typedef struct InfoSession *InfoSessionPtr;

InfoSessionPtr SessionNew(char *); //Creates new Session
int SessionNewTab(InfoSessionPtr); //Creates new Tab
int SessionTabShow(InfoSessionPtr); //Shows Opening Address of current Tab
int SessionTabNext(InfoSessionPtr); //Moves current Tab to the next Tab
int SessionTabPrev(InfoSessionPtr); //Moves current Tab to the previous Tab
int SessionTabMoveLeft(InfoSessionPtr); //Moves Tab to the left
int SessionTabMoveRight(InfoSessionPtr); //Moves Tab to the right
int SessionNewOpeningAddress(InfoSessionPtr,char *); //Changes the Opening Address
int SessionShowOpeningAddress(InfoSessionPtr); //Prints Current Opening Address
int SessionSiteNext(InfoSessionPtr); //Moves current Site to Next Site
int SessionSitePrev(InfoSessionPtr); //Moves current Site to Previous Site
int SessionSiteShow(InfoSessionPtr); //Shows address of current Site
int SessionTabClose(InfoSessionPtr);  //Deletes Current Tab
int SessionClose(InfoSessionPtr); //Deletes the whole Session
int SessionNewAddress(InfoSessionPtr, char *); //Creates new Site
int SessionOpenNewTab(InfoSessionPtr);

#endif

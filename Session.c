/*************************************************
Implementation File	: Session.c
Author				: M.Volakis 28/04/2019
Content				: ATD Session Implementation

Μιχάλης Βολάκης Α.Μ:1115201800022
**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "Session.h"
typedef struct InfoSession *InfoSessionPtr;
typedef struct TabNode *TabNodePtr;
typedef struct SiteNode *SiteNodePtr;
//Additional Functions
void print_tab_sequence(InfoSessionPtr); //Prints current Tab sequence
void print_site_sequence(TabNodePtr); //Prints current Site sequence

typedef struct InfoSession {
	TabNodePtr FirstTab;
	TabNodePtr LastTab;
	TabNodePtr CurrTab;
	TabNodePtr AuxTab;
	char* 	  OpeningAddress;
} InfoSession;

typedef struct TabNode {	
	TabNodePtr PrevTab, NextTab;
	SiteNodePtr FirstSite;
	SiteNodePtr CurrSite;
} Tab;

typedef struct SiteNode{  
	SiteNodePtr PrevSite, NextSite;
	TabNodePtr UpTab;
	char *Address; 
} Site;


InfoSessionPtr SessionNew(char *OpeningAddress){
	InfoSessionPtr Isession = (InfoSessionPtr)malloc(sizeof(InfoSession)); //Creation of first InfoSession node
	TabNodePtr new_Tab = (TabNodePtr)malloc(sizeof(Tab));	//Creation of first Tab Node   
	SiteNodePtr new_Site = (SiteNodePtr)malloc(sizeof(Site));  //Creation of first Site Node
	if(!(Isession && new_Tab && new_Site)) return NULL; // returns NULL in case malloc fails

	/* Initialization of InfoSession Members*/  
	Isession->FirstTab = new_Tab;  	 
	Isession->LastTab = new_Tab;
	Isession->CurrTab = new_Tab;      
	Isession->AuxTab = NULL;
	Isession->OpeningAddress = OpeningAddress;

	/*Initialization of Tab Members*/
	new_Tab->PrevTab = new_Tab; 
	new_Tab->NextTab = new_Tab;
	new_Tab->FirstSite = new_Site;
	new_Tab->CurrSite = new_Site;

	/*Initialization of Site Members*/
	new_Site->PrevSite = NULL; 
	new_Site->NextSite = NULL;
	new_Site->UpTab = new_Tab;
	new_Site->Address = Isession->OpeningAddress; 

	/*Print Current Tab and Site Sequences*/
	print_tab_sequence(Isession);     
	print_site_sequence(Isession->CurrTab);
	return Isession;
	
}	

int SessionNewTab(InfoSessionPtr Session){
	/*Insertion of New Tab at the end of the Tab List*/
	if(Session == NULL) return -1; //if there no Session has been created return -1
	Session->LastTab->NextTab = malloc(sizeof(Tab)); 
	if(!(Session->LastTab->NextTab)) return 0; // return 0 in case malloc fails 
	Session->LastTab->NextTab->PrevTab = Session->LastTab;
	Session->LastTab = Session->LastTab->NextTab;
	Session->CurrTab = Session->LastTab;    
	Session->LastTab->NextTab = Session->FirstTab;
	Session->FirstTab->PrevTab = Session->LastTab;
	/*Insertion of New Site below the last Tab*/

	Session->LastTab->FirstSite = malloc(sizeof(Site));
	if(!(Session->LastTab->FirstSite)) return 0; // returns 0 in case malloc fails
	Session->LastTab->CurrSite = Session->LastTab->FirstSite;
	Session->LastTab->FirstSite->Address = malloc(sizeof(char) * 100);
	Session->LastTab->FirstSite->Address = Session->OpeningAddress;
	Session->LastTab->FirstSite->PrevSite = NULL;
	Session->LastTab->FirstSite->NextSite = NULL;
	Session->LastTab->FirstSite->UpTab = Session->LastTab; 
	/*Print Current Tab and Site Sequences*/  
	if(Session->AuxTab == NULL){
		print_tab_sequence(Session);
		print_site_sequence(Session->CurrTab);
	}
	return 1; // return 1 for successful creation of new Tab
}
 
int SessionTabShow(InfoSessionPtr Session){ 
	if(Session == NULL) return -1; //return -1 in case there is no Session
	else printf("%s\n",Session->CurrTab->CurrSite->Address); 
	return 1;
}	
int SessionTabNext(InfoSessionPtr Session){
	if(Session == NULL) return -1; //return -1 in case there is no Session
	else Session->CurrTab = Session->CurrTab->NextTab;
	print_tab_sequence(Session);
	print_site_sequence(Session->CurrTab);
	return 1;
}
int SessionTabPrev(InfoSessionPtr Session){
	if(Session == NULL) return -1; //return -1 in case there is no Session
	else Session->CurrTab = Session->CurrTab->PrevTab;
	print_tab_sequence(Session);
	print_site_sequence(Session->CurrTab);
	return 1;
}
int SessionTabMoveLeft(InfoSessionPtr Session){
	if(Session == NULL) return -1; //return -1 in case there is no Session
	if(Session->CurrTab != Session->FirstTab){  
		if(Session->CurrTab->PrevTab == Session->FirstTab) Session->FirstTab = Session->CurrTab; //Adjustment of FirstTab pointer
		if(Session->CurrTab == Session->LastTab) Session->LastTab = Session->CurrTab->PrevTab; //Adjustment of LastTab pointer

		TabNodePtr old_prev = Session->CurrTab->PrevTab->PrevTab; //temporary Tab pointer

		Session->CurrTab->PrevTab->PrevTab = Session->CurrTab;//Change prev and next pointers
		Session->CurrTab->PrevTab->NextTab = Session->CurrTab->NextTab;
		Session->CurrTab->NextTab->PrevTab = Session->CurrTab->PrevTab;
		Session->CurrTab->NextTab->NextTab = Session->CurrTab;	 
		Session->CurrTab->NextTab = Session->CurrTab->PrevTab;
		Session->CurrTab->PrevTab = old_prev;
		/*Print Current Tab and Site Sequences*/  
		print_tab_sequence(Session);
		print_site_sequence(Session->CurrTab);
	}
	else{
		printf("The current Tab is the first Tab"); //Current Tab is the first Tab, can't be moved to the left
		return 0;
	}	
	return 1;
}
int SessionTabMoveRight(InfoSessionPtr Session){
	if(Session == NULL) return -1; //return -1 in case there is no Session
	if(Session->CurrTab != Session->LastTab){ 
	  if(Session->CurrTab == Session->FirstTab) Session->FirstTab = Session->CurrTab->NextTab; //Adjustment of FirstTab pointer
	  if(Session->CurrTab->NextTab == Session->LastTab) Session->LastTab = Session->CurrTab; //Adjustment of LastTab pointer

	  TabNodePtr old_next = Session->CurrTab->NextTab->NextTab; //temporary Tab pointer
	
	  Session->CurrTab->PrevTab->PrevTab = Session->CurrTab;		//Change prev and next pointers
	  Session->CurrTab->PrevTab->NextTab = Session->CurrTab->NextTab;
	  Session->CurrTab->NextTab->PrevTab = Session->CurrTab->PrevTab; 	  
	  Session->CurrTab->NextTab->NextTab = Session->CurrTab;
	  Session->CurrTab->PrevTab = Session->CurrTab->NextTab;
	  Session->CurrTab->NextTab = old_next;
	  	/*Print Current Tab and Site Sequences*/ 
		print_tab_sequence(Session);
		print_site_sequence(Session->CurrTab); 
	}
	else{
		printf("The Current Tab is the last Tab"); // Current Tab is the last Tab, can't be moved to the right
		return 0;
	}	
	return 1;
}
int SessionNewOpeningAddress(InfoSessionPtr Session,char *newAddress){
	if(Session == NULL) return -1; //return -1 in case there is no Session
	else Session->OpeningAddress = newAddress; 
	return 1;
}
int SessionShowOpeningAddress(InfoSessionPtr Session){
	if(Session == NULL) return -1; //return -1 in case there is no Session
	else printf("Opening Address: %s\n",Session->OpeningAddress);
	return 1;
}
int SessionSiteNext(InfoSessionPtr Session){
	if(Session == NULL) return -1; //return -1 in case there is no Session
	if(Session->CurrTab->CurrSite->NextSite){
		Session->CurrTab->CurrSite = Session->CurrTab->CurrSite->NextSite;
	}
	return 1;
}
int SessionSitePrev(InfoSessionPtr Session){
	if(Session == NULL) return -1; //return -1 in case there is no Session
	if(Session->CurrTab->CurrSite->PrevSite){
		Session->CurrTab->CurrSite = Session->CurrTab->CurrSite->PrevSite;
	} 
	return 1;
}
int SessionSiteShow(InfoSessionPtr Session){
	if(Session == NULL) return -1; //return -1 in case there is no Session
	else printf("%s\n",Session->CurrTab->CurrSite->Address);
	return 1;
}

int SessionTabClose(InfoSessionPtr Session){
	if(Session == NULL) return -1; //return -1 in case there is no Session
	if(Session->CurrTab == Session->AuxTab) return 2;//return 2 - linked to new Tab
	SiteNodePtr site_to_del = Session->CurrTab->FirstSite; //creation of temporaty pointer, site to be deleted
	SiteNodePtr next_site; //creation of temporary pointer of next site
	//Deletion of all sites
	while(site_to_del->NextSite){ 
		next_site = site_to_del->NextSite;
		free(site_to_del); 
		site_to_del = next_site;
	}
	free(site_to_del); 
 
	TabNodePtr tab_to_del; //creation of pointer to the tab to be deleted
	tab_to_del = Session->CurrTab;
	if(Session->CurrTab == Session->FirstTab && Session->CurrTab == Session->LastTab){ //Current Tab is the only tab in the Session
		free(Session->CurrTab); //Deletion of Current Tab and Session
		free(Session);
		return 0; // return 0 - complete Session has been deleted
	}
	else{ 
		//delete the current tab
		if(Session->CurrTab == Session->FirstTab) Session->FirstTab = Session->CurrTab->NextTab; 
		if(Session->CurrTab == Session->LastTab)  Session->LastTab = Session->CurrTab->PrevTab;
		Session->CurrTab->PrevTab->NextTab = Session->CurrTab->NextTab;
		Session->CurrTab->NextTab->PrevTab = Session->CurrTab->PrevTab;
		if(Session->AuxTab != NULL){
			Session->CurrTab = Session->AuxTab; //return to site 
			Session->AuxTab = NULL;
		}	else	Session->CurrTab = Session->CurrTab->NextTab; //make current site the next site 
		
		free(tab_to_del);

		/*Print Current Tab and Site Sequences*/  
		print_tab_sequence(Session);
		print_site_sequence(Session->CurrTab);
		printf("\n");
		return 1; // return 1 - only the current tab has been deleted
	}	
}
int SessionClose(InfoSessionPtr Session){
		if(Session == NULL) return -1; //return -1 in case there is no Session
		Session->CurrTab = Session->FirstTab; //begin deletion from first tab
		while(SessionTabClose(Session)); // SessionTabClose function deletes every tab and the whole Session
		return 1;
}

int SessionNewAddress(InfoSessionPtr Session, char *newAddress){
	if(Session == NULL) return -1; //return -1 in case there is no Session  
	SiteNodePtr new_site = malloc(sizeof(Site));  
	if(new_site == NULL) return 0; //returns 0 in case malloc fails
	new_site->Address = newAddress;
	if(Session->CurrTab->CurrSite->NextSite){ //if Current Site is not the last Site
			//Deletion of every Site ahead of current Site
		SiteNodePtr next_site;
		SiteNodePtr curr_site = Session->CurrTab->CurrSite->NextSite;
		while(curr_site){
			next_site = curr_site->NextSite;
			free(curr_site);
			curr_site = next_site;
		}
	}
	//Initialization of new Site members
	Session->CurrTab->CurrSite->NextSite = new_site;
	Session->CurrTab->CurrSite->NextSite->PrevSite = Session->CurrTab->CurrSite;
	Session->CurrTab->CurrSite = Session->CurrTab->CurrSite->NextSite;
	Session->CurrTab->CurrSite->UpTab = Session->CurrTab;
	Session->CurrTab->CurrSite->NextSite = NULL;

	/*Print Current Tab and Site Sequences*/  
	print_tab_sequence(Session);
	print_site_sequence(Session->CurrTab);
	return 1; //returns 1 - successful creation of new Site
	} 
int SessionOpenNewTab(InfoSessionPtr Session){
		if(Session->AuxTab == NULL){ //if there is no previous AuxTab stored
			Session->AuxTab = Session->CurrTab; //store current Tab
			int return_res = SessionNewTab(Session); //call SessionNewTab to create new Tab
			if(return_res == -1 ) return -1; //No Session, return -1 
			else if(return_res == 0) return 0; //malloc failed, return 0
			else{	//successful creation of new Tab
				Session->CurrTab->CurrSite->Address = Session->AuxTab->CurrSite->Address; //rename CurrSite Address to the address of site that opened the new Tab
				print_tab_sequence(Session);
				print_site_sequence(Session->CurrTab);
			}
		} 
		else{  //There is  a previous AuxTab already stored
			printf("A new Tab using this option has been already created.Delete this Tab to proceed.\n");
			return 2;
		}
	return 1;
}


//Additional Functions
void print_tab_sequence(InfoSessionPtr Session){
	printf("Tab Sequence of Current Session: ");
	TabNodePtr current_tab = Session->FirstTab; //Sequence begins from first Tab
	int tab_count = 1; //Initialization of tab counter
	while(current_tab != Session->LastTab){ //Loop all tabs except the last
		printf("Tab %d-->",tab_count); 
		current_tab = current_tab->NextTab;
		tab_count++;
	} 
	printf("Tab %d\n",tab_count);
}

void print_site_sequence(TabNodePtr Tab){
	SiteNodePtr current_site = Tab->FirstSite;
	int site_count = 1; //Initialization of site counter
	printf("Site Sequence of Current Tab: ");
	while(current_site){ //Loop all current Sites
		printf("Site %d (%s) ",site_count,current_site->Address);
		current_site = current_site->NextSite;
		site_count++;
	}
	printf("\n");
} 


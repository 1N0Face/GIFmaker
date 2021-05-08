#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "view.h"
#include "saveLoad.h"
#define UNDEFINED -1
#define CREATE 0
#define LOAD 1
void startMenu(FrameNode* head);
void menu();
void manager(FrameNode* head, int count);
enum Options{EXIT, ADD, REMOVE, CHANGE_IND, CHANGE_DUR, CHANGE_ALL_DUR, LIST, PLAY, SAVE};

int main(void)
{
	FrameNode* head = NULL;
	startMenu(head);
	freeList(head);
	getchar();
	return 0;
}
/**
	This function is the start menu, it sends you to create or load a project
	input:head(list)
	output: none
**/
void startMenu(FrameNode* head)
{
	int option = UNDEFINED, count = 0;
	printf(" Welcome to Gif-Maker\n");
	while (CREATE != option && LOAD != option)
	{
		printf(" [0] Create a new project\n");
		printf(" [1] Load existing project\n");
		(scanf("%d", &option) != 1) ? getchar() : 1;//if the input is char make another getchar()
		getchar();
		if (CREATE == option)
		{
			manager(head, count);
		}
		else if (LOAD == option)
		{
			count = loadAProject(&head);
			if(UNDEFINED != count) // if the file was opened
			{
				manager(head, count);
			}
		}
		else
		{
			printf("Input-Error\n");
		}
	}
}
/**
	This function prints the menu each time
	input: none
	output: none
**/
void menu()
{
	printf("What would you like to do?\n");
	printf(" [0] Exit\n");
	printf(" [1] Add new Frame\n");
	printf(" [2] Remove a Frame\n");
	printf(" [3] Change frame index\n");
	printf(" [4] Change frame duration\n");
	printf(" [5] Change duration of all frames\n");
	printf(" [6] List frames\n");
	printf(" [7] Play movie!\n");
	printf(" [8] Save project\n");
	printf(" Enter: ");
}
/**
	This function is the manager, it sends to the chosen function according to the input
	input: head(list), the number of frames (count)
	output: none
**/
void manager(FrameNode* head, int count)
{
	FrameNode* frame = NULL;
	char name[NAME_LEN] = { 0 };
	int option = UNDEFINED, saver = 0;
	while (option != EXIT)
	{
		menu(); // prints the menu each time
		(scanf("%d", &option) != 1) ? getchar() : 1; //if the option is char do: getchar again
		getchar();
		if (EXIT == option)
		{
			printf("Goodbye!");
		}
		else if (ADD == option)
		{
			frame = getDetails();
			!takenOrNot(&head, frame->frame->name) ? addNode(&head, frame), count++ : printf("Name is taken\n");
			//if the name is not taken, add it to list, make the number of frames + 1
		}
		else if (REMOVE == option)
		{
			printf("Enter name to remove:\n");
			myFgets(name, NAME_LEN);
			removePerson(&head, name) ? printf("Removed from line\n"), count-- : printf("Not in line\n");
			//removes the person from the list and make the number of frames -1
		}
		else if (CHANGE_IND == option)
		{
			printf("Enter name to change index:\n");
			myFgets(name, NAME_LEN);
			if (takenOrNot(&head, name)) // checks if the name is in the list
			{
				printf("Enter the new index: ");
				(scanf("%d", &saver) != 1) ? getchar() : 1; // get user`s answer to choose new index
				getchar();
				(saver > 0 && saver < count + 1) ? changeIndex(&head, saver, name) : printf("Index-Error!\n");
				//if the index is between 1 and number of frames + 1, change the index
			}
			else {
				printf("Not found!\n");
			}
		}
		else if (CHANGE_DUR == option)
		{
			printf("Enter the name of the frame:\n");
			myFgets(name, NAME_LEN);
			Change1Dur(&head, name);
		}
		else if (CHANGE_ALL_DUR == option)
		{
			printf("Enter the new duration: ");
			(scanf("%d", &saver) != 1) ? getchar() : 1;
			getchar();
			ChangeAllDur(&head, saver);
		}
		else if (PLAY == option)
		{
			play(head);
		}
		else if (LIST == option)
		{
			printList(&head);
		}
		else if (SAVE == option)
		{
			saveProject(&head);
		}
		else
		{
			printf("Input-Error\n");
		}
	}
}
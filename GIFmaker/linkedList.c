/*********************************
* Class: MAGSHIMIM Final Project *
* Play function				 	 *
**********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

/*
	This fucntion is collecting the data for the frame
	input: none
	output: New frame node
*/
FrameNode* getDetails()
{
	char name[NAME_LEN] = { 0 };
	char path[PATH_LEN] = { 0 };
	int duration = 0;
	printf("*** Crafting new frame ***\n");
	printf("Please insert frame path:\n");
	myFgets(path, PATH_LEN);
	printf("Please insert duration(in miliseconds):\n");
	(scanf("%d", &duration) != 1) ? getchar() : 1;
	getchar(); // clean buffer
	printf("Please choose a name for that frame:\n");
	myFgets(name, NAME_LEN);
	return initFrame(name, path, duration);
}
/*
	This fucntion is initiating the data from the last function, into the node
	input: name, path , duration
	output: New frame node
*/
FrameNode* initFrame(char* name, char* path, int duration)
{
	Frame* newFrame = (Frame*)malloc(sizeof(Frame) + 1); // setting up memory for the Frame struct pointer
	FrameNode* frameInNode = (FrameNode*)malloc(sizeof(FrameNode) + 1);// setting up memory for the FrameNode struct pointer
	newFrame->name = (char*)malloc(sizeof(char) * NAME_LEN + 1); // setting up memory for the name of the Frame struct
	newFrame->path = (char*)malloc(sizeof(char) * PATH_LEN + 1);// setting up memory for the path of the Frame struct
	strncpy(newFrame->name, name, NAME_LEN); // puts the name in the frame name
	newFrame->duration = duration;// puts the duration in the frame duration
	strncpy(newFrame->path, path, PATH_LEN); // puts the path in the frame path
	frameInNode->frame = newFrame; // making the frameInNode to contain the frame
	frameInNode->next = NULL; // the frame doesn`t has a next for now :(
	return frameInNode;
}
/*
	This fucntion is adding the node into the list(head)
	input: head, the frame to add
	output: none
*/
void addNode(FrameNode** head, FrameNode* frame)
{
	FrameNode* curr = *head;
	int added = FALSE;
	if (curr == NULL) // list is empty
	{
		(*head) = frame; // make the frame to be at the first of the list
	}
	else
	{
		while (curr->next) // until the next is set to NULL
		{
			curr = curr->next; // move to the next each time
		}
		curr->next = frame; // the last frame will contain in his next the new frame
		frame->next = NULL; // the new frame will be the last in the list
	}
}
/*
	This fucntion is checking if a frame is in the list, by the name
	input: head, the frame name
	output: found or not (TRUE, FALSE)
*/
int takenOrNot(FrameNode** head, char* frameName)
{
	int found = FALSE;
	FrameNode* curr = *head;
	if (curr) // line isn't empty
	{
		while (curr && !found)
		{
			if (0 == strcmp(curr->frame->name, frameName)) // if the name was found
			{
				found = TRUE;
			}
			curr = curr->next; // move to the next node
		}
	}
	return found;
}
/*
	This fucntion is removing a chosen node by the name
	input: head, the frame name
	output: removed or not (TRUE, FALSE)
*/
int removePerson(FrameNode** head, char* name)
{
	FrameNode* temp = NULL;
	FrameNode* curr = *head;
	int removed = FALSE;
	if (*head) // list isn't empty
	{
		if (*head && 0 == strcmp((*head)->frame->name, name)) // if first is the one to remove
		{
			temp = (*head)->next; // points to the next of the first node
			free(*head); // removes the first node
			*head = temp; // the first is now the second...
			removed = TRUE;
		}
		else
		{
			// the next one isn't the one, and we are not on the last person
			while (!removed && curr->next && 0 != strcmp((curr->next)->frame->name, name))
			{
				curr = curr->next;
			}
			if (curr->next && 0 == strcmp(curr->next->frame->name, name)) // we got our person to remove!
			{
				temp = curr->next;
				curr->next = temp->next; // the curr now points to the next of the removed frame
				free(temp); // removes the first node
				removed = TRUE;
			}
		}
	}
	return removed;
}
/*
	This fucntion is changing the index of a selected frame (index starts from 1)
	input: head, the index to move, the frame name
	output: none
	****IT`S VERY HARD TO EXPLAIN IT BECUASE ALL OF THESE SITUATIONS WERE CALCULATED****
*/
void changeIndex(FrameNode** head, int index, char* name)
{
	int i = 1, j = 0, flag = NO_FLAG, done = FALSE, found = FALSE;
	FrameNode* first = *head;
	FrameNode* curr = *head;
	FrameNode* saver = NULL;
	FrameNode* temp = NULL;
	if (0 == strcmp(name, curr->frame->name)) // if the first node is the one to move
	{
		saver = curr;
		temp = curr->next; // saves the next of the node
	}
	else
	{
		while (curr && !found)
		{
			first = curr;
			curr = curr->next;
			if (0 == strcmp(name, curr->frame->name))
			{
				temp = first; // save the previous node, before the founded node
				saver = curr; // save the found node
				found = TRUE;
			}
			j++;
		}
	}
	//We have 3 situations that frame can be moved, to left, to right or to index 1
	if (index == 1) // the frame wants to move to index 1
	{
		flag = 0;
	}
	else if (j < index) // the frame wants to move to right
	{
		flag = RIGHT;
	}
	else if (j >= index) // the frame wants to move to left
	{
		flag = LEFT;
	}
	if (saver && index != j+1 && index > 0)
	{
		curr = *head; // make the curr point to the first node
		while (curr && !done)
		{
			first = curr;
			curr = curr->next;
			if (i == index - 1 || flag == 0)
			{
				if (RIGHT == flag)
				{
					saver->next = curr->next;
					curr->next = saver;
					if (j == 0) // if we move first node, the start of the node should change...
					{
						*head = temp;
					}
					else // if we move not the first node, 
					{
						if (strcmp(saver->frame->name, first->frame->name) == 0) // checks if the name and the frame now are the same node
						{
							temp->next = curr;
						}
						else
						{
							temp->next = first;
						}
					}
				}
				else if (0 == flag)
				{
					if (0 == strcmp(saver->frame->name, curr->frame->name)) // checks if the name and the next are the same node
					{
						first->next = saver->next;
						saver->next = first;// made to avoid an infinite loop
					}
					else
					{
						if (saver->next == NULL)
						{
							temp->next = NULL;
						}
						else
						{
							curr->next = saver->next;
						}
						saver->next = first;
					}
					*head = saver;
				}
				else if (LEFT == flag)
				{
					first->next = saver;
					temp->next = saver->next;
					saver->next = curr;
				}
				done = TRUE;
			}
			i++;
		}
	}
	else
	{
		printf("Error!\n");
	}
}
/*
	This fucntion is changing the duration of a selected frame, by name
	input: head, the name of the frame
	output: none
*/
void Change1Dur(FrameNode** head, char* name)
{
	int newDur = 0;
	int found = FALSE;
	FrameNode* curr = *head;
	if (curr) // line isn't empty
	{
		while (curr && !found)
		{
			if (0 == strcmp(curr->frame->name, name)) // if the name was found in the list
			{
				found = TRUE;
				printf("Enter new duration:\n");
				(scanf("%d", &newDur) != 1) ? getchar() : 1;
				getchar();
				curr->frame->duration = newDur; // initates the new duration to the frame
			}
			curr = curr->next;
		}
	}
	if (!found)
	{
		printf("The frame with this name does not exist\n");
	}
}
/*
	This fucntion is changing the duration of all the frames in the list
	input: head, the new duration to change
	output: none
*/
void ChangeAllDur(FrameNode** head, int duration)
{
	FrameNode* curr = *head;
	if (curr) // line isn't empty
	{
		while (curr)
		{
			curr->frame->duration = duration; // initates the new duration to the frame
			curr = curr->next;
		}
	}
}
/*
	This fucntion prints all the frames in the list
	input: head(the list)
	output: none
*/
void printList(FrameNode** head)
{
	FrameNode* curr = *head;
	printf("Name                          Duration                       Path\n"); // the print struct
	if (curr)
	{
		while (curr)
		{
			printf("%s", curr->frame->name); //prints the name of the frame
			printf("                          %d", curr->frame->duration); //prints the duration of the frame
			printf("                            %s\n", curr->frame->path);//prints the path of the frame
			curr = curr->next;
		}
	}
	printf("\n");
}
/*
	This fucntion let all the allocated memory (each frame) be free :)
	input: head(the list)
	output: none
*/
void freeList(FrameNode* head)
{
	FrameNode* temp = head;
	while (head)
	{
		temp = head->next; // points to the next node each time
		free(head); // free the node
		head = temp; // set to be the next node
	}
}
/*
	This fucntion is an improve to the fgets function
	input: string, size
	output: none
*/
void myFgets(char str[], int n)
{
	fgets(str, n, stdin);
	str[strcspn(str, "\n")] = 0;// sets the '0' at the end
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saveLoad.h"

/*
	This fucntion is saving the project
	input: head(the list)
	output: none
*/
void saveProject(FrameNode** head)
{
	FrameNode* curr = *head;
	char path[TOTAL_LEN] = { 0 };
	FILE * fp;
	if (curr) // if the list is not empty
	{
		printf("Where to save the project? enter a full path and file name, exmp: C:/<name>\n");
		myFgets(path, TOTAL_LEN);
		strcat(path, ".txt"); // adds a txt to the end
		fp = fopen(path, "w+"); // opens the file to writing
		while (curr)
		{
			fprintf(fp, "%s %d %s\n", curr->frame->name, curr->frame->duration, curr->frame->path);// saves the data of each frame
			curr = curr->next;// move to the next node
		}
		fclose(fp); //close the file for writing
	}
}
/*
	This fucntion loads a saved project
	input: head(the list)
	output: the number of frames(count)
*/
int loadAProject(FrameNode** head)
{
	int c = 0, i = 0, j = 0, duration = 0, count = 0;
	char buffer[BUFFER_SIZE] = { 0 };
	char txtPath[TOTAL_LEN] = { 0 };
	char name[NAME_LEN] = { 0 };
	char path[PATH_LEN] = { 0 };
	printf("Enter the path and file name, exmp: C:/<name>\n");
	myFgets(txtPath, TOTAL_LEN);
	strcat(txtPath, ".txt"); // adds the format of the saved file to the path
	FILE* fp = fopen(txtPath, "r"); //opens the file for reading
	if (fp) 
	{
		while ((c = fgetc(fp)) != EOF)// while the end of file is not reached
		{
			if (c != (int)(' ') && NEW_LINE != c)
			{
				buffer[i] = c;
				i++;
			}
			else if (c == (int)(' ') || NEW_LINE == c)
			{
				if (NAME_INDEX == j)//if the first space was detected
				{
					strcpy(name, buffer); // save the chars before the space to the name
				}
				else if (DUR_INDEX == j)//if the second space was detected
				{
					duration = atoi(buffer);//makes the number in the string be int
				}
				else if (PATH_INDEX == j)
				{
					strcpy(path, buffer);// save the chars before the space to the path
				}
				memset(buffer, 0, strlen(buffer)); // clean the buffer
				i = 0; //make the index back to 0
				j++;
			}
			if (NEW_LINE == c)
			{
				addNode(head, initFrame(name, path, duration));
				memset(path, 0, strlen(path));//clean the path
				memset(name, 0, strlen(name));//clean the name
				count++; //counts how many frames in the file
				j = 0;
			}
		}
		fclose(fp); // closes the file for reading
	}
	else
	{
		printf("File Not found\n");
		count = ERROR;
	}
	return count;
}
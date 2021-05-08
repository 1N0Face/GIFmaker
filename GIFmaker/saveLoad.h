#ifndef SAVELOADH
#define SAVELOADH
#define TOTAL_LEN 80
#define BUFFER_SIZE 100
#define NEW_LINE 10
#define NAME_INDEX 0
#define DUR_INDEX 1
#define PATH_INDEX 2
#define ERROR -1
#include "LinkedList.h"
void saveProject(FrameNode** head);
int loadAProject(FrameNode** head);
#endif

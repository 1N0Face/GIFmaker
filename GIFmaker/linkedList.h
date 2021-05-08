#ifndef LINKEDLISTH
#define LINKEDLISTH
#define FALSE 0
#define TRUE !FALSE
#define NAME_LEN 15
#define PATH_LEN 40
#define LEFT -1
#define RIGHT 1
#define NO_FLAG 2
// Frame struct
typedef struct Frame
{
	char* name;
	unsigned int duration;
	char* path;
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

FrameNode* getDetails();
FrameNode* initFrame(char* name, char* path, int duration);
void addNode(FrameNode** head, FrameNode* frame);
int takenOrNot(FrameNode** head, char* frameName);
int removePerson(FrameNode** head, char* name);
void changeIndex(FrameNode** head, int index, char* name);
void Change1Dur(FrameNode** head, char* name);
void ChangeAllDur(FrameNode** head, int duration);
void printList(FrameNode** head);
void freeList(FrameNode* head);
void myFgets(char str[], int n);
#endif

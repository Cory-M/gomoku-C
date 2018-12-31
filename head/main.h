#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAXIUM 15

#ifdef WIN32
#include <conio.h>
#include <io.h>
#include <direct.h>
#define mkdirs(path) _mkdir(path)
#define _printspace printf("                            ");
#define sleep(sleeptime) _sleep(sleeptime);
#define cls system("cls");

#else
#include <unistd.h>
#include <getopt.h>
#include <sys/select.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define mkdirs(path) mkdir(path, 0777)
#define _printspace printf("             ");
#define cls system("clear");

int getch(void);
int kbhit(void);
#endif

FILE *file;				   
int board[MAXIUM][MAXIUM]; 
int Round;				   
int model[4];			   
int sleeptime;			   
char filename[50];		   
char nowtime[50];		   
int readmodel;			   
int run_mode;		   

struct cursor
{ 
	int x, y;
};
struct cursor cursor; 

typedef struct record
{						
	struct cursor cursor;
	struct record *next; 
	struct record *back; 
} Record;

struct record *head;   
struct record *renow;  
struct record *reback; 

#define pause            
	printf("WaitKey\n"); 
	getch();
#define _printn printf("\n"); 
#define _turns              
	if (Round % 2)          
		printf("black turn"); 
	else                    
		printf("white turn"); 
#define getdate                          
	memset(time, 0, sizeof(nowtime)); 
	get_time();                        
	printf("%s", nowtime) 


void backrecord();
void printboard();
void read_record(void);
char *getStyle(int i, int j);
int iswin();
void win();
void initial(void);
void move();
void hand_swap(void);
void begin_a(int a);
void begin_b(int a);
void begin(void);
void get_time();
int turn(int r);
int get_score(int i, int j, int k);
void clearrecord(struct record *head);
void Addrecord(int i, int j);
struct record *newrecord();
void modelchoose(void);
char *iitoa(int num, char *str, int radix);
void dofile();
void getfilename();
char charrecord();
void del();
void mainAlgorithm(void);
int gain(int n, int m);
int cost(int n, int m);
void replay();
void replay_();
int replay_control();
void tips();
void forbidden();
int get_jin(int i, int j, int k);
void check_jin(int n, int m);


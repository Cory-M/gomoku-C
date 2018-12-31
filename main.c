#include "head/main.h"


int main(void)
{
	initial(); 
	while (1)
	{
		move();
	}
	return 0;
}

void initial(void) 
{
#ifndef WIN32
	printf("\033[0m\033[37;1m"); 
#else
	system("chcp 65001");
	system("title gomuku");				 
	system("mode con cols=63 lines=34"); 
	system("color E0");					 
#endif
	cls;
	run_mode = 0;
	if (access("record", 0) == -1)
	{
		mkdirs("record");
	}
	head = newrecord();
	renow = newrecord();
	reback = newrecord();
	head->next = renow;
	renow->back = head;
	reback = renow->back;
	Round = 1;	 
	modelchoose(); 

	cls;
	if (model[0] == 1) 
	{
		getfilename(); 
		if (model[1] == 2 && model[2] == 2)
		{
			Addrecord(7, 7);
			Round++;
			printboard();
		} 
		else
			begin(); 
	}
	else if (model[0] == 2) 
		read_record();
	if (model[1] != 3)
		run_mode = 1;
	printf("开始游戏");
}

#ifndef WIN32
int kbhit(void) 
{
	struct termios oldt, newt;
	int ch;
	int oldf;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if (ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
}

int getch(void)
{ 
	struct termios tm, tm_old;
	int fd = STDIN_FILENO, c;
	if (tcgetattr(fd, &tm) < 0)
		return -1;
	tm_old = tm;
	cfmakeraw(&tm);
	if (tcsetattr(fd, TCSANOW, &tm) < 0)
		return -1;
	c = fgetc(stdin);
	if (kbhit())
	{
		c += getch();
	}
	if (tcsetattr(fd, TCSANOW, &tm_old) < 0)
		return -1;
	return c;
}
#endif
#include "head/main.h"


void getfilename() 
{
	get_time(); 
	strcat(filename, "record/qipu ");
	strcat(filename, nowtime);
	strcat(filename, ".txt"); 
}

void dofile() 
{
	file = fopen(filename, "at+"); 
	if (file != NULL)			   
	{
		char a[50] = "\n"; 
		char r[3];
		char x[3], y[3];
		strcat(a, iitoa(Round, r, 10)); 
		strcat(a, "\t");
		strcat(a, iitoa(renow->cursor.x + 1, x, 10)); 
		strcat(a, " ");
		strcat(a, iitoa(renow->cursor.y + 1, y, 10)); 
		strcat(a, " ");
		strcat(a, " ");
		strcat(a, "\t");
		strcat(a, nowtime);			  
		fwrite(a, strlen(a), 1, file);
		fclose(file);				  
	}
}

void del() 
{
	FILE *fin, *fout; 
	int c;
	int count = 0;
	int ncount = 0;

	fin = fopen(filename, "r"); 
	while (1)
	{
		c = fgetc(fin);
		if (EOF == c)
			break;
		if ('\n' == c)
			count++;
	}

	fclose(fin); 

	fin = fopen(filename, "r"); 
	fout = fopen("t.tmp", "w"); 
	while (1)
	{
		c = fgetc(fin);
		if (c == '\n')
		{
			ncount++;
			if (ncount == count)
				break;
		}
		fputc(c, fout);
	}
	fclose(fin); 
	fclose(fout);
	remove(filename);		  
	rename("t.tmp", filename);
}

void read_record() 
{
	readmodel = 1; 
	char c;
	int count = 0;
	int ncount = 0;
	char x[2], y[2];
	int i = 0, j = 0;
	file = fopen(filename, "r");
	
	while ((c = fgetc(file)) != EOF)
	{
		if (c == '	')
		{
			c = fgetc(file);
			count++;
			i = j = ncount = 0;
		}
		if (count % 2)
		{
			if (c == ' ')
			{
				c = fgetc(file);
				ncount++;
			}
			if (ncount == 0)
				x[i++] = c;
			else if (ncount == 1)
				y[j++] = c;
			else if (ncount == 2)
			{
				if (i == 1)
					i = x[0] - '0'; 
				else
					i = 10 + (int)x[1] - 48;
				if (j == 1)
					j = y[0] - '0';
				else
					j = 10 + (int)y[1] - 48;
				Addrecord(i - 1, j - 1); 
				Round++;				 
			}
		}
	}
	
	fclose(file);  
	readmodel = 0; 
	printboard();
	replay(); 
}

void replay() 
{
	char tempname[50]; 
	strcpy(tempname, filename);
	strcat(filename, "tmp");
	
	while (1)
	{
		
		printboard();
#ifdef WIN32
		printf("\n          方向键控制回放,ESC退出回放并从当前开始游戏");
#else
		printf("\n方向键控制回放,ESC退出回放并从当前开始游戏");
#endif
		if (replay_control()) 
			break;
	}
	printboard();
	reback = renow->back;
	reback->next = newrecord();
	renow = reback->next;
	renow->back = reback;
	renow = head->next;
	Round = 1;
	while (renow->next != NULL)
	{
		dofile();
		renow = renow->next;
		Round++;
	}

	remove(tempname);					  
	rename(filename, tempname);			  
	memset(filename, 0, sizeof(filename));
	strcpy(filename, tempname);			  
}

int replay_control() 
{
	int key1;
	while (1)
	{
		if (kbhit())
		{
		A:
			switch (key1 = getch())
			{

			case 27: 
				return 1;
#ifndef WIN32
			case 183: 
			case 186: 
				if (renow->back->back != NULL)
				{
					renow = renow->back; 
					board[renow->cursor.x][renow->cursor.y] = 0;
					Round--;
				}
				else
					goto A;
				break;
			case 184: 
			case 185: 
				if (renow->next != NULL)
				{

					board[renow->cursor.x][renow->cursor.y] = turn(Round);
					renow = renow->next; 
					Round++;
				}
#else
			case 72: 
			case 75: 
				if (renow->back->back != NULL)
				{
					renow = renow->back;
					board[renow->cursor.x][renow->cursor.y] = 0;
					Round--;
				}
				else
					goto A;
				break;
			case 80: 
			case 77: 
				if (renow->next != NULL)
				{

					board[renow->cursor.x][renow->cursor.y] = turn(Round);
					renow = renow->next;
					Round++;
				}
#endif
				else
					goto A;
				break;
			default:
				break;
			}
			return 0;
		}
	}
}


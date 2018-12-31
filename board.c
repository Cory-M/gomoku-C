#include "head/wzq.h"


char *getStyle(int i, int j) 
{
#ifndef WIN32
	if (!readmodel)
	{
		if (i == reback->cursor.x && j == reback->cursor.y)
		{
			if (board[i][j] == 1) 
			{
				if (i == 14)
					return "\033[30m★\033[37;1m";
				else 
				{
					switch (j)
					{
					case 0:;
					case 14:
						return "\033[30m★\033[37;1m━";
						break;
					default:
						return "\033[30m★\033[37;1m─";
						break;
					}
				}
			}
			else 
			{
				if (i == 14)
					return "★";
				else 
				{
					switch (j)
					{
					case 0:;
					case 14:
						return "★━";
						break;
					default:
						return "★─";
						break;
					}
				}
			}
		}
	}
	if (board[i][j] == 1) 
	{
		if (i == 14)
			return "\033[30m●\033[37;1m"; 
		else							  
		{
			switch (j)
			{
			case 0:;
			case 14:
				return "\033[30m●\033[37;1m━";
				break;
			default:
				return "\033[30m●\033[37;1m─";
				break;
			}
		}
	}
	else if (board[i][j] == 2) 
	{
		if (i == 14)
			return "●";
		else
		{
			switch (j)
			{
			case 0:;
			case 14:
				return "●━";
				break;
			default:
				return "●─";
				break;
			}
		}
	}
	else if (board[i][j] == 3)
	{
		if (i == 14)
			return "╳";
		else //边缘位置
		{
			switch (j)
			{
			case 0:;
			case 14:
				return "╳━";
				break;
			default:
				return "╳─";
				break;
			}
		}
	}
#else
	if (!readmodel)
	{
		if (i == reback->cursor.x && j == reback->cursor.y)
		{
			if (board[i][j] == 1) 
			{
				if (i == 14)
					return "★";
				else 
				{
					switch (j)
					{
					case 0:;
					case 14:
						return "★━";
						break;
					default:
						return "★─";
						break;
					}
				}
			}
			else if (board[i][j] == 2) 
			{
				if (i == 14)
					return "☆";
				else 
				{
					switch (j)
					{
					case 0:;
					case 14:
						return "☆━";
						break;
					default:
						return "☆─";
						break;
					}
				}
			}
		}
	}
	if (board[i][j] == 1) 
	{
		if (i == 14)
			return "●";
		else
		{
			switch (j)
			{
			case 0:;
			case 14:
				return "●━";
				break;
			default:
				return "●─";
				break;
			}
		}
	}
	else if (board[i][j] == 2) 
	{
		if (i == 14)
			return "○";
		else 
		{
			switch (j)
			{
			case 0:;
			case 14:
				return "○━";
				break;
			default:
				return "○─";
				break;
			}
		}
	}
	else if (board[i][j] == 3)
	{
		if (i == 14)
			return "╳";
		else 
		{
			switch (j)
			{
			case 0:;
			case 14:
				return "╳━";
				break;
			default:
				return "╳─";
				break;
			}
		}
	}

#endif
	else if (board[i][j] == 0)
	{
		
		if (i == 0 && j == 0)
			return "┗━";
		else if (i == MAXIUM - 1 && j == 0)
			return "┛";
		else if (i == MAXIUM - 1 && j == MAXIUM - 1)
			return "┓";
		else if (i == 0 && j == MAXIUM - 1)
			return "┏━";
		else if (i == 0)
			return "┠─";
		else if (i == MAXIUM - 1)
			return "┨";
		else if (j == 0)
			return "┷━";
		else if (j == MAXIUM - 1)
			return "┯━";

		return "┼─"; 
	}
	return NULL;
}

void printboard()
{
	cls;
	int i, j;
#ifndef WIN32
	_printn					   
		printf("%2d", MAXIUM); 
	for (i = 0; i < MAXIUM; i++)
	{
		printf(getStyle(i, 14));
	}
	_printn for (j = 13; j > 0; j--) 
	{
		printf("%2d", j + 1);
		for (i = 0; i < MAXIUM; i++)
		{
			printf(getStyle(i, j));
		}
		_printn
	}

	printf("%2d", 1);
	for (i = 0; i < MAXIUM; i++)
	{
		printf(getStyle(i, 0));
	}

	_printn printf(" ");
	for (i = 0; i < MAXIUM; i++)
	{
		printf("%2c", i + 'a');
	}

	_printn 
		_turns printf("        ");
	getdate;
	_printn if (run_mode) tips();
	_printspace
#else
	printf("%2d", MAXIUM); 
	for (i = 0; i < MAXIUM; i++)
	{
		printf(getStyle(i, 14));
	}
	printf("\n  ┃");
	for (i = 0; i < MAXIUM - 2; i++)
	{
		printf("  │");
	}
	printf("  ┃\n");		
	for (j = 13; j > 0; j--)
	{
		printf("%2d", j + 1);
		for (i = 0; i < MAXIUM; i++)
		{
			printf(getStyle(i, j));
		}
		printf("\n  ┃");
		for (i = 0; i < MAXIUM - 2; i++)
		{
			printf("  │");
		}
		printf("  ┃\n"); 
	}
	printf("%2d", 1); 
	for (i = 0; i < MAXIUM; i++)
	{
		printf(getStyle(i, 0));
	}
	_printn for (i = 0; i < MAXIUM; i++) { printf("%4c", i + 'a'); } 
	_printn printf("               ");
	_turns printf("           ");
	getdate;
	_printn 
		if (run_mode) tips();
	_printspace

#endif
}

void get_time() 
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	char year[5], mon[3], day[3], hour[3], min[3], sec[3];
	

	if ((p->tm_hour + 8) >= 24) 
	{
		p->tm_hour -= 24;
		p->tm_mday++;
	}

	strcat(nowtime, iitoa(1900 + p->tm_year, year, 10)); 
	strcat(nowtime, "-");								 
	strcat(nowtime, iitoa(1 + p->tm_mon, mon, 10));
	strcat(nowtime, "-");
	strcat(nowtime, iitoa(p->tm_mday, day, 10));
	strcat(nowtime, " ");
	strcat(nowtime, iitoa(p->tm_hour + 8, hour, 10));
	strcat(nowtime, "-");
	strcat(nowtime, iitoa(p->tm_min, min, 10));
	strcat(nowtime, "-");
	strcat(nowtime, iitoa(p->tm_sec, sec, 10)); 
}

char *iitoa(int num, char *str, int radix) 
{
	char string[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char *ptr = str;
	int denom = 0; 
	int count = -1;
	int i;
	int j;

	while (num >= radix)
	{
		denom = num % radix;
		num /= radix;
		*ptr++ = string[denom];
		count++;
	}

	if (num >= 0)
	{
		*ptr++ = string[num];
		count++;
	}

	*ptr = '\0';
	j = count;

	for (i = 0; i < (count + 1) / 2; i++)
	{
		int temp = str[i];
		str[i] = str[j];
		str[j--] = temp;
	}

	return str;
}

void tips()
{
#ifndef WIN32
	printf("  输入坐标后回车以落子  按z悔棋\n");
#else
	printf("                  输入坐标后回车以落子  按z悔棋\n");
#endif
}


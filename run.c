#include "head/main.h"

int turn(int r) 
{
	if (r % 2)
		return 1; 
	else
		return 2; 
}

void move()
{
	int c;
	if (model[1] == 3) 
	{
		mainAlgorithm();		
		win(cursor.x, cursor.y);
		printboard();
#ifndef WIN32
		printf("\n按回车键暂停\n按ESC退出");
#else
		printf("\n按回车键暂停\n按ESC退出");
#endif
		if (kbhit())
		{
#ifndef WIN32
			if ((c = getch()) == '\n')
#else
			if ((c = getch()) == '\r')
#endif
			{
#ifndef WIN32
				printf("\n按任意键回到游戏\n");
#else
				cls;
				printboard();
				printf("\n按任意键回到游戏\n");
#endif
				while (1)
				{
					if (getch() != 0)
						break;
				}
			} 
			else if (c == 27)
				return replay(); 
		}

		sleep(sleeptime); 
	}
	else
	{

		int key1, key2, key3;
		int num;
		if (kbhit()) 
		{
			printboard();
			printf(" ");
			key1 = getch();
			if (key1 == 27)
				replay();
			else if (key1 == 'z')
			{
				if (reback->back != NULL) 
				{
					backrecord();	  
					if (model[1] == 2)
						backrecord(); 
					printboard();
				}
			}
			else if (key1 <= 'o' && key1 >= 'a') 
			{
				printf("%1c", key1);
			A:
				key2 = getch();
				if ((key2 >= '1' && key2 <= '9') || (key2 >= 'a' && key2 <= 'f'))
				{
					printf("%c", key2);
#ifndef WIN32
					if ((key3 = getch()) != '\r') 
#else
					if ((key3 = getch()) != '\n') 
#endif
					{
						if (key2 == '1') 
						{
							printf("%c", key3);
#ifndef WIN32
							while (getch() == '\r')
#else
							while (getch() == '\n')
#endif
								break;
						}
					}

					if (key2 <= 'f' && key2 >= 'a') 
						num = key2 - 'a' + 10;
					else if (key3 >= '0' && key3 <= '5' && key2 == '1') 5
						num = 10 * (key2 - '0') + (key3 - '0');
					else 
						num = key2 - '0';

					if (!board[key1 - 'a'][num - 1]) 
					{
						Addrecord(key1 - 'a', num - 1);
						if (model[3] == 1)
							forbidden();			 
						win(cursor.x, cursor.y); 
						if (model[1] == 2)		 
						{
							mainAlgorithm();	
							win(cursor.x, cursor.y); 
							printboard();
						}
						else 
							printboard();
					}
				}
				else
					goto A; 
			}
		}
	}
}

void modelchoose(void) 
{
W:
	printf("按1开始新游戏\n按2加载棋谱\n按3查看帮助\n按ESC退出程序\n");
	while (model[0] != 1 && model[0] != 2 && model[0] != 3 && model[0] != -21)
	{
		model[0] = getch() - '0';
	}
	if (model[0] != -21)
		printf("%d\n", model[0]);
	else
		replay();

	if (model[0] == 3)
	{
		FILE *help;
		char line[100];
		help = fopen("src/README.txt", "r");

		if (help != NULL)
		{
			cls;
			int i = 0;
			while (fgets(line, 100, help))
			{
				printf("%s", line);
				i++;
				if (i > 15)
				{
					if (getch() != 0)
					{
						i = 0;
					}
				}
			}
			while (1)
			{
				if (getch() != 0)
				{
					cls;
					break;
				}
			}
		}
		model[0] = 0;
		fclose(help);
		goto W;
	}
	if (model[0] == 2)
	{
	A:
		printf("输入文件名(例: qipu 2015-1-1 1-1-1.txt)\n");
		char tmpname[50];
		scanf("%[^\n]", tmpname);
		strcat(filename, "record/");
		strcat(filename, tmpname);
		if (strstr(tmpname, ".txt") == NULL)
		{
			strcat(filename, ".txt");
		}
		file = fopen(filename, "r");
		if (file == NULL)
		{
			getchar();
			memset(filename, 0, sizeof(filename));
			int t = 0;
			printf("文件不存在\n按1重新输入文件名\n按2开始新游戏\n");
			while (t != 1 && t != 2)
			{
				t = getch() - '0';
			}
			printf("%d\n", t);
			if (t == 1)
				goto A;
			else
			{
				model[0] = 1;
				goto B;
			}
		}
		else
			fclose(file);
		printf("按1开始人人对战\n按2开始人机对战\n按ESC回到上一层\n");
		while (model[1] != 1 && model[1] != 2 && model[1] != 27 - '0')
		{
			model[1] = getch() - '0';
		}
		if (model[1] != -21)
			printf("%d\n", model[1]);
		else
		{
			model[0] = 0;
			model[1] = 0;
			printf("\n");
			goto W;
		}
	}

	if (model[0] == 1)
	{
	B:
		printf("按1开始人人对战\n按2开始人机对战\n按3开始机机对战(测试模式)\n按ESC回到上一层\n");
		while (model[1] != 1 && model[1] != 2 && model[1] != 3 && model[1] != 27 - '0')
		{
			model[1] = getch() - '0';
		}
		if (model[1] != -21)
			printf("%d\n", model[1]);
		else
		{
			model[0] = 0;
			model[1] = 0;
			printf("\n");
			goto W;
		}
		if (model[1] == 2)
		{
			printf("按1选择黑方\n按2选择白方\n按ESC回到上一层\n");
			while (model[2] != 1 && model[2] != 2 && model[2] != 27 - '0')
			{
				model[2] = getch() - '0';
			}
			if (model[2] != -21)
				printf("%d\n", model[2]);
			else
			{
				model[1] = 0;
				model[2] = 0;
				printf("\n");
				goto B;
			}
		}
		else if (model[1] == 3)
		{
#ifndef WIN32
			printf("希望电脑多久下一步棋(s)\n");
			scanf("%d", &sleeptime);
#else
			printf("希望电脑多久下一步棋(ms)\n");
			scanf("%d", &sleeptime);
#endif
		}
	}
	printf("按1选择黑方禁手\n按2不禁手\n");
	while (model[3] != 1 && model[3] != 2)
	{
		model[3] = getch() - '0';
	}
	printf("%d\n", model[3]);
}

void win(int a, int b) 
{
	if (iswin(a, b)) 
	{
		if (turn(Round) == 1) 
		{
			printboard();
			printf("black win!");
		}
		else
		{
			printboard();
			printf("white win!");
		}
		replay(); 
	}
	Round++; 
}

int iswin(int a, int b) 
{
	int w = 1, x = 1, y = 1, z = 1;
	int i;
	int k = turn(Round);
	for (i = 1; i < 5; i++)
		if (b + i < MAXIUM && board[a][b + i] == k)
			w++;
		else
			break; 
	for (i = 1; i < 5; i++)
		if (b - i >= 0 && board[a][b - i] == k)
			w++;
		else
			break;
	if (w >= 5)
		return 1;

	for (i = 1; i < 5; i++)
		if (a + i < MAXIUM && board[a + i][b] == k)
			x++;
		else
			break; 
	for (i = 1; i < 5; i++)
		if (a - i >= 0 && board[a - i][b] == k)
			x++;
		else
			break; 
	if (x >= 5)
		return 1;

	for (i = 1; i < 5; i++)
		if (a + i < MAXIUM && b + i < MAXIUM && board[a + i][b + i] == k)
			y++;
		else
			break; 
	for (i = 1; i < 5; i++)
		if (a - i >= 0 && b - i >= 0 && board[a - i][b - i] == k)
			y++;
		else
			break; 
	if (y >= 5)
		return 1;

	for (i = 1; i < 5; i++)
		if (a + i < MAXIUM && b - i >= 0 && board[a + i][b - i] == k)
			z++;
		else
			break; 
	for (i = 1; i < 5; i++)
		if (a - i >= 0 && b + i < MAXIUM && board[a - i][b + i] == k)
			z++;
		else
			break; 
	if (z >= 5)
		return 1;

	return 0; 
}

void replay() 
{
	int i;
	printf("\n按1重新开始游戏      按2退出\n");
	int t = 0;
	while (t != 1 && t != 2)
	{
		t = getch() - '0';
	}
	printf("%d\n", t);
	if (t == 1) 
	{
		memset(model, 0, sizeof(model));
		memset(nowtime, 0, sizeof(nowtime));
		memset(filename, 0, sizeof(filename));
		for (i = 0; i < MAXIUM; i++)
			memset(board[i], 0, sizeof(board[i])); 
		initial();								   
	}
	else
	{ 
		pause;
#ifndef WIN32
		printf("\033[0m");
#else
		system("color 7");
		cls
#endif
		exit(0);
	}
}

void backrecord() 
{

	board[reback->cursor.x][reback->cursor.y] = 0;
	reback = reback->back;						  
	renow->back = reback;						 
	reback->next = renow;						 
	Round--;									  
	del();										  
}


char *join(char *s1, char *s2)
{
	char *result = malloc(strlen(s1) + strlen(s2) + 1);
	
	if (result == NULL)
		exit(1);

	strcpy(result, s1);
	strcat(result, s2);

	return result;
}
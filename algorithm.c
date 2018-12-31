#include "head/main.h"

//Algorithm
int san, si;

void mainAlgorithm(void)
{
	if (Round == 1)
		Addrecord(7, 7);
	else if (Round == 2)
	{
		if (board[7][7] == 0) 
			Addrecord(7, 7);
		else 
			Addrecord(8, 8);
	}
	else
	{
		srand((unsigned int)time(NULL)); 
		int i, j;
		int s, t;
		int q = 0, w = 0;							 
		int now[3] = {0, 0, 0};						 
		int best[3] = {-1000000, -1000000, -1000000};
		int fbest = 100000000;						 
		int Best[255][2];							 
		int candidates[255];							  
		int bestnum;
		int k = turn(Round); 

		for (i = 0; i < MAXIUM; i++) //取遍棋盘
			for (j = 0; j < MAXIUM; j++)
			{
				if (board[i][j] == 0 || (board[i][j] == 3 && k == 2)) 
				{
					now[0] = get_score(i, j, k);
					if (best[0] < now[0])		
					{
						best[0] = now[0];
						Best[0][0] = i;
						Best[0][1] = j;
						w = 1; 
					}
					else if (best[0] == now[0]) 
					{
						Best[w][0] = i;
						Best[w][1] = j;
						w++; 
					}
				}
			}
		if (w == 0)
		{
			printf("dogfall\n");
			return replay();
		}
		for (q = 0; q < w; q++) 
		{
			board[Best[q][0]][Best[q][1]] = k; 
			for (s = 0; s < MAXIUM; s++)	   
				for (t = 0; t < MAXIUM; t++)
				{
					if (board[s][t] == 0 || (board[s][t] == 3 && k == 2)) 
					{
						now[1] = get_score(s, t, 3 - k); 
						if (best[1] <= now[1])
						{
							board[s][t] = 3 - k;
							for (i = 0; i < MAXIUM; i++)
								for (j = 0; j < MAXIUM; j++)
								{
									if (board[s][t] == 0 || (board[s][t] == 3 && k == 2))
									{
										now[2] = get_score(s, t, k);
										if (best[2] < now[2])
											best[2] = now[2];
									}
								}
							board[s][t] = 0;
							now[1] -= best[2];
							if (best[1] < now[1])
								best[1] = now[1];
						}
					}
				}

			if (fbest > best[1]) 
			{
				fbest = best[1];
				candidates[0] = q；
				i = 1;			
			}
			else if (fbest == best[1]) 
				candidates[i++] = q;	

			board[Best[q][0]][Best[q][1]] = 0; 
		}
		if (i) 
			bestnum = (int)(rand() % i);
		else 
			bestnum = 0;

		Addrecord(Best[candidates[bestnum]][0], Best[candidates[bestnum]][1]); //添加行棋记录
		if (model[3] == 1)
			forbidden(); 
	}
}

int get_score(int i, int j, int k) 
{
	int n = 0;		
	int count = 0;  
	int ncount = 0; 
	int t, p;
	for (p = 0; p < 5; p++) 
	{
		if (j - p < 0) 
			break;
		else if (j - p + 4 >= MAXIUM) 
			continue;
		else
		{
			for (t = 0; t < 5; t++) 
			{
				if (board[i][j - p + t] == k)
					count++; 
				else if (board[i][j - p + t] == 3 - k || board[i][j - p + t] == 3)
					ncount++; 
			}
			n += gain(count, ncount);
			n += cost(count, ncount); 
			count = ncount = 0;		
		}
	}

	for (p = 0; p < 5; p++) 
	{
		if (i - p < 0)
			break;
		else if (i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)
			{
				if (board[i - p + t][j] == k)
					count++;
				else if (board[i - p + t][j] == 3 - k || board[i][j - p + t] == 3)
					ncount++;
			}
			n += gain(count, ncount);
			n += cost(count, ncount);
			count = ncount = 0;
		}
	}

	for (p = 0; p < 5; p++) 
	{
		if (j - p < 0 || i - p < 0)
			break;
		else if (j - p + 4 >= MAXIUM || i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)
			{
				if (board[i - p + t][j - p + t] == k)
					count++;
				else if (board[i - p + t][j - p + t] == 3 - k || board[i][j - p + t] == 3)
					ncount++;
			}
			n += gain(count, ncount);
			n += cost(count, ncount);
			count = ncount = 0;
		}
	}

	for (p = 0; p < 5; p++) 
		if (j + p >= MAXIUM || i - p < 0)
			break;
		else if (j + p - 4 < 0 || i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++) 
			{
				if (board[i - p + t][j + p - t] == k)
					count++;
				if (board[i - p + t][j + p - t] == 3 - k || board[i][j - p + t] == 3)
					ncount++;
			}

			n += gain(count, ncount);
			n += cost(count, ncount);
			count = ncount = 0;
		}
	}
	if (n < 5000) 
	{
		if (i <= 7)
			n += i + 1;
		else
			n += MAXIUM - i;
		if (j <= 7)
			n += j + 1;
		else
			n += MAXIUM - j;
	}
	return n; 
}

int gain(int n, int m) 
{
	int p = 0;			
	if (m == 0 && n != 0) 
	{
		switch (n)
		{ 
		case 4:
			p = 9999999;
			break;
		case 3:
			p = 99999;
			break;
		case 2:
			p = 999;
			break;
		case 1:
			p = 99;
			break;
		default:
			p = 0;
			break;
		}
	}
	return p;
}

int cost(int n, int m) 
{
	int p = 0;
	if (n == 0 && m != 0)
						 
						 
	{
		switch (m)
		{
		case 4:
			p = 8888888;
			break;
		case 3:
			p = 88888;
			break;
		case 2:
			p = 888;
			break;
		case 1:
			p = 8;
			break;
		default:
			p = 0;
			break;
		}
	}
	return p; 
}

void forbidden()
{
	int i, j;
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
		{
			if (Round % 2)
			{
				if (board[i][j] == 3)
					board[i][j] = 0;
			}
			else
			{
				if (board[i][j] == 0)
					board[i][j] = get_jin(i, j, 1);
			}
		}
}

void check_jin(int n, int m)
{
	if (m == 0 && n != 0)
	{
		switch (n)
		{
		case 3:
			si++;
			break;
		case 2:
			san++;
			break;
		default:
			break;
		}
	}
}

int get_jin(int i, int j, int k)
{
	int huosan = 0;
	int huosi = 0;
	int count = 0;  
	int ncount = 0; 
	int t, p;
	san = 0;
	si = 0;
	for (p = 0; p < 5; p++) 
	{
		if (j - p < 0) 
			break;
		else if (j - p + 4 >= MAXIUM) 
			continue;
		else 
		{
			for (t = 0; t < 5; t++) 
			{
				if (board[i][j - p + t] == k)
					count++; 
				else if (board[i][j - p + t] == 3 - k)
					ncount++; 
			check_jin(count, ncount);
			count = 0;
			ncount = 0;
		}
	}
	if (san > 1)
		huosan++;
	if (si > 0)
		huosi++;
	san = 0;
	si = 0;
	for (p = 0; p < 5; p++) 
	{
		if (i - p < 0)
			break;
		else if (i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)
			{
				if (board[i - p + t][j] == k)
					count++;
				else if (board[i - p + t][j] == 3 - k)
					ncount++;
			}
			check_jin(count, ncount);
			count = 0;
			ncount = 0;
		}
	}
	if (san > 1)
		huosan++;
	if (si > 0)
		huosi++;
	san = 0;
	si = 0;
	for (p = 0; p < 5; p++) 
	{
		if (j - p < 0 || i - p < 0)
			break;
		else if (j - p + 4 >= MAXIUM || i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)
			{
				if (board[i - p + t][j - p + t] == k)
					count++;
				else if (board[i - p + t][j - p + t] == 3 - k)
					ncount++;
			}
			check_jin(count, ncount);
			count = 0;
			ncount = 0;
		}
	}
	if (san > 1)
		huosan++;
	if (si > 0)
		huosi++;
	san = 0;
	si = 0;
	for (p = 0; p < 5; p++) 
	{
		if (j + p >= MAXIUM || i - p < 0)
			break;
		else if (j + p - 4 < 0 || i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++) 
			{
				if (board[i - p + t][j + p - t] == k)
					count++;
				if (board[i - p + t][j + p - t] == 3 - k)
					ncount++;
			}
			check_jin(count, ncount);
			count = 0;
			ncount = 0;
		}
	}
	if (san > 1)
		huosan++;
	if (si > 0)
		huosi++;
	san = 0;
	si = 0;
	if (huosan > 1 || huosi > 1)
		return 3;
	else
		return 0;
}

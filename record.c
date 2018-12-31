#include "head/main.h"


struct record *newrecord() 
{
	struct record *r = (struct record *)malloc(sizeof(struct record)); 
	r->next = NULL;													   
	r->back = NULL;
	return r; 
}

void Addrecord(int i, int j) 
{
	renow->cursor.x = i; 
	renow->cursor.y = j;

	if (!readmodel) 
		dofile();
	board[i][j] = turn(Round); 
	cursor.x = i;
	cursor.y = j;

	renow->next = newrecord(); 

	reback = renow; 
	renow = renow->next;
	renow->back = reback;
}


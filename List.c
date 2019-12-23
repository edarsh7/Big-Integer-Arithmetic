/*------------------------------

Edmond Arshakyan
earshaky
pa3

-------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"


typedef struct NodeObj
{
    long data;
    struct NodeObj *next;
    struct NodeObj *prev;
} NodeObj;

typedef struct NodeObj* Node;

typedef struct ListObj
{
    int curIndex;
    int listLength;
    Node front;
    Node back;
    Node cursor;
} ListObj;


//-------------------------------------------


Node newNode(long data)
{
    Node x = malloc(sizeof(NodeObj));
    x->data = data;
    x->next = NULL;
    x->prev = NULL;
    return(x);
}


void freeNode(Node *nP)
{
    if(nP != NULL && *nP != NULL)
    {
        free(*nP);
        *nP = NULL;
    }
}


List newList(void)
{
    List L;
    L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->curIndex = -1;
    L->listLength = 0;
	return L;
}



void freeList(List* pL)
{
	if (pL != NULL && *pL != NULL)
	{
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

//-----------------------------------------------------------------------
//access funcs----------------



int length(List L)
{
	if (L == NULL)
	{
		printf("Error: In List.c function length(L) was sent a NULL list");
		printf("\n");

		return 0;
	}
	else
	{
		return(L->listLength);

	}
}


int index(List L)
{
	if (L == NULL)
	{
		printf("Error: In List.c function Index(L) was sent a NULL list");
		printf("\n");

		return 0;
	}
    else
    {
        return L->curIndex;
    }

}

// Returns front element of L. Pre: length()>0

long front(List L)
{
	if (L == NULL)
	{
		printf("Error: In List.c function front(L) was sent a NULL list");
		printf("\n");

		return 0;
	}
    else if(length(L) <= 0)
    {
        printf("Error in List.c / int front(List L) / Length of list is not > 0");
		printf("\n");

        return -1;
    }
	else if(length(L) > 0)
	{
		return(L->front->data);
	}
}

// Returns back element of L. Pre: length()>0
long back(List L)
{
	if (L == NULL)
	{
		printf("Error: In List.c function back(L) was sent a NULL list");
		printf("\n");
	}
	if (length(L) <= 0)
	{
		printf("Error in List.c / int back(List L) / Length of list is not > 0");
		printf("\n");

		return -1;
	}
	else if (length(L) > 0)
	{
		return(L->back->data);
	}
}

 // Returns cursor element of L. Pre: length()>0, index()>=0
long get(List L)
{
	if (length(L) > 0 && index(L) >= 0)
	{
		return(L->cursor->data);
	}
	else
	{
		printf("Error in List.c / int get(List L) / Length of list is not > 0 or index(L) is not > 0\n");
		if(length(L) < 1)
		{
			printf("Length < 1 \n");
		}

		if(index(L) < 0)
		{
			printf(" index < 0\n");
		}
		return -1;
	}
}




//Manipulation procedures----------------------------------------




void clear(List L)
{
	if (L == NULL)
	{
		printf("function clear in List.c was sent a NULL list");
		printf("\n");
	}
	else
	{
		while (length(L) > 0)
		{
			deleteFront(L);
		}
		L->back = NULL;
		L->curIndex = -1;
		L->cursor = NULL;
		L->front = NULL;
		L->listLength = 0;
	}
	
}

void moveFront(List L)
{
	if (length(L) > 0)
	{
		L->cursor = L->front;
		L->curIndex = 0;
	}
}

void moveBack(List L)
{
    if(length(L) > 0)
    {
        L->cursor = L->back;
		L->curIndex = (L->listLength)-1;
    }
}

void movePrev(List L)
{
    if(L->cursor != NULL && L->cursor != L->front)
    {
        L->cursor = L->cursor->prev;
		L->curIndex--;
    }
	else if (L->cursor == L->front)
	{
		L->cursor = NULL;
		L->curIndex = -1;
	}
}

void moveNext(List L)
{
    if(L->cursor != NULL && L->cursor != L->back)
    {
        L->cursor = L->cursor->next;
		L->curIndex++;
    }
	else if (L->cursor == L->back)
	{
		L->cursor = NULL;
		L->curIndex = -1;
	}
}

void prepend(List L, long data)
{
	Node x = newNode(data);
	if (length(L) > 0)
	{
		x->next = L->front;
		L->front->prev = x;
		L->front = x;
		L->listLength++;
		if(index(L) != -1)
		{
			L->curIndex++;
		}
	}
	else
	{
		L->front = x;
		L->back = x;
		L->listLength++;
	}
}

void append(List L, long data)
{
	Node x = newNode(data);
	if (length(L) > 0)
	{
		x->prev = L->back;
		L->back->next = x;
		L->back = x;
		L->listLength++;
	}
	else
	{
		L->front = x;
		L->back = x;
		L->listLength++;
	}
}

// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, long data)
{
	if (length(L) > 0 && index(L) >= 0)
	{
		Node x = newNode(data);
		if(index(L) == 0)
		{
			prepend(L, data);
		}
		else
		{
			x->next = L->cursor;
			x->prev = L->cursor->prev;
			L->cursor->prev->next = x;
			L->cursor->prev = x;
			L->listLength++;
			L->curIndex++;
		}	
			x = NULL;
	freeNode(&x);

	}
	else
	{
		printf("Error in List.c Function insertBefore(L, data) length is 0 or index() is undefined");
		printf("\n");

	}
}

// Insert new element after cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, long data)
{
	if (length(L) > 0 && index(L) >= 0)
	{
		Node x = newNode(data);
		if(L->cursor == L->back)
		{
			append(L, data);
		}
		else
		{
			x->next = L->cursor->next;
			x->prev = L->cursor;
			L->cursor->next->prev = x;
			L->cursor->next = x;
			L->listLength++;
		}
			x = NULL;
	freeNode(&x);

	}
	else
	{
		printf("Error in List.c Function insertAfter(L, data) length is 0 or index() is undefined");
		printf("\n");
	}

}

// Delete the front element. Pre: length()>0
void deleteFront(List L)
{
	if (length(L) > 0)
	{
		Node temp = L->front;

		if(L->cursor == L->front)
		{
			L->cursor = NULL;
			L->curIndex = -1;
		}
		else if(L->curIndex > -1)
		{
			L->curIndex--;
		}
		
		L->front = L->front->next;
		freeNode(&temp);
		L->listLength--;
	}
	else
	{
		printf("Error in List.c Function deleteFront(L) length is 0");
		printf("\n");

	}
}
// Delete the back element. Pre: length()>0
void deleteBack(List L)
{
	if (length(L) > 0)
	{
		Node temp = L->back;

		if(L->cursor == L->back)
		{
			L->cursor = NULL;
			L->curIndex = -1;
		}

		L->back = L->back->prev;
		freeNode(&temp);
		L->listLength--;
	}
	else
	{
		printf("Error in List.c Function deleteBack(L) length is 0");
		printf("\n");

	}
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0

void delete(List L)
{
	if (length(L) > 0 && index(L) >= 0)
	{
		if (L->cursor == L->front)
		{
			deleteFront(L);
		}
		else if (L->cursor == L->back)
		{
			deleteBack(L);
		}
		else 
		{
			Node temp = L->cursor;
			L->curIndex = -1;
			L->cursor->prev->next = L->cursor->next;
			L->cursor->next->prev = L->cursor->prev;\
			L->cursor = NULL;
			freeNode(&temp);
			L->listLength--;

		}
	}
	else
	{
		printf("Error in List.c Function delete(L) length is 0 or index() is undefined");
		printf("\n");
	}
}

void set(List L, long x)
{
	if(length(L) > 0 && index(L) >= 0)
	{
		L->cursor->data = x;
	}
	else
	{
		if(length(L) < 1)
		{
			printf("Error in List.c: function set was sent a list with length < 1\n");
		}
		if(index(L) < 0)
		{
			printf("Error in List.c: function set was sent a list with index < 0\n");
		}
	}
	
}

//OTHER OPERATIONS --------------------------------------------------------------

List copyList(List L)
{
	List X = newList();
	moveFront(L);
	while (index(L) != -1)
	{
		append(X, get(L));
		moveNext(L);
	}

	return X;
}

void printList(FILE* out, List L)
{
	Node x = L->back;
	while (x)
	{
		printf("%ld", x->data);
			x = x->prev;
	}
}



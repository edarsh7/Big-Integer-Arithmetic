/*------------------------------

Edmond Arshakyan
earshaky
pa3

-------------------------------*/


#include "BigInteger.h"
#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Structs---------------------------------------------------------------------

typedef struct BigIntegerObj{
    int sign;
    List integer;
}BigIntegerObj;


// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger()
{
    BigInteger B = malloc(sizeof(BigIntegerObj));
    B->sign = 0;
    B->integer = newList();
    return B;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN)
{
    if(pN != NULL && *pN != NULL)
    {
        freeList(&((*pN)->integer));
        free(*pN);
        *pN = NULL;
    }
}

long power(long x, int y)
{
    long accum = 1;
    for(;y>0;y--)
    {
        accum = accum * x;
    }
    return accum;
}


List vectorSum(List A, List B)
{
    long carry = 0;
    long temp = 0;
    List C = newList();
    moveFront(A);
    moveFront(B);
    while(index(A) != -1  && index(B) != -1)
    {
        temp = (get(A) + get(B));
        temp = temp + carry;
        if(temp >= 1000000000)
        {

            temp = temp - 1000000000;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        append(C, temp);
        moveNext(A);
        moveNext(B);
    }

    temp = 0;

    while(index(B) != -1)
    {
        temp = get(B);
        if(carry > 0)
        {
            temp = temp +carry;
            if(temp >= 1000000000)
            {
                temp = temp - 1000000000;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
        }
        append(C, temp);
        moveNext(B);
    }
    while(index(A) != -1)
    {
        temp = get(A);
        if(carry > 0)
        {
            temp = temp +carry;
            if(temp >= 1000000000)
            {
                temp = temp - 1000000000;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
        }
        append(C, temp);
        moveNext(A);
    }  
    if(carry == 1)
    {
        append(C, 1);
    }
    return C;
}

List vectorDiff(List A, List B)
{
    long carry = 0;
    long temp = 0;
    List C = newList();
    moveFront(A);
    moveFront(B);
    while(index(A) != -1  && index(B) != -1)
    {
        temp = (get(A) - get(B));
        temp = temp - carry;
        if(temp < 0)
        {

            temp = temp + 1000000000;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        if(index(B) == -1 || temp != 0)
        {
            append(C, temp);
        }
        moveNext(A);
        moveNext(B);
    }


    while(index(B) != -1)
    {
        temp = get(B);
        if(carry > 1)
        {
            temp = temp - carry;
            if(temp < 0)
            {

                temp = temp + 1000000000;
                carry++;
            }
            else
            {
                carry = 0;
            }
        }
        if(index(B) == -1 || temp != 0)
        {
            append(C, temp);
        }
        moveNext(B);
    }

    while(index(A) != -1)
    {
        temp = get(A);
        if(carry > 1)
        {
            temp = temp - carry;
            if(temp < 0)
            {

                temp = temp + 1000000000;
                carry++;
            }
            else
            {
                carry = 0;
            }
        }
        if(index(A) == -1 || temp != 0)
        {
            append(C, temp);
        }
        moveNext(A);
    }
    
    return C;
}

void normalize(List A)
{
    long carry = 0;
    long temp;

    moveFront(A);
    while(index(A) != -1)
    {
        temp = get(A);
        if(temp >= 1000000000)
        {
            carry = get(A) / 1000000000;
            set(A, get(A)-carry * 1000000000);
            moveNext(A);
            if(index(A) != -1)
            {
                set(A, (get(A))+carry);
                carry = 0;
            }
        }
        else 
        {
            moveNext(A);
        }
    }
    if(carry > 0 )
    {
        append(A, carry);
    }

}

void fakeVS(List A, List B)
{
    long temp;

    moveFront(A);
    moveFront(B);

    while(index(A) != -1  && index(B) != -1)
    {
        temp = (get(A) + get(B));
        set(A, temp);
        moveNext(A);
        moveNext(B);
    }

    while(index(B) != -1)
    {
        temp = get(B);
        append(A, temp);
        moveNext(B);
    }
    normalize(A);
    clear(B);
}

BigInteger listProd(List A, List B)
{
    BigInteger C = newBigInteger();
    BigInteger D = newBigInteger();

    C->sign =  1; 
    D->sign = 1;

    long temp;
    int fake, counter = 0, coin = 0;
    moveFront(B);
    while(index(B) != -1)
    {
        moveFront(A);
        while(index(A) != -1)
        {
            temp = (get(A) * get(B));
            if(coin == 0)
            {
                append(C->integer, temp);
            }
            if(coin == 1)
            {
                append(D->integer, temp);
            }
            moveNext(A);
        }
        coin = 1;
        fake = counter;
        for(;fake > 0; fake--)
        {
            prepend(D->integer, 0);
        }
        counter++;
        fakeVS(C->integer, D->integer);
        moveNext(B);
    }

    freeBigInteger(&D);
    return C;
}


int listCheck(List A, List B)
{
    if(length(A) < length(B)) return -1;
    if(length(A) > length(B)) return  1;
    moveBack(A);
    moveBack(B);
    while(index(A)!=-1)
    {
        if(get(A) > get(B)) return 1;
        if(get(A) < get(B)) return -1;
        if(get(A) == get(B))
        {
            movePrev(A);
            movePrev(B);
        }
    }
    return 0;
}

// Access functions -----------------------------------------------------------



// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N)
{
    return N->sign;
}





// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B)
{
    if(equals(A,B) == 1)
    {
        return 0;
    }
    else
    {
        if(sign(A) == 1 && sign(B) == 1)
        {
            if(length(A->integer) < length(B->integer)) return -1;
            if(length(A->integer) > length(B->integer)) return  1;
            moveBack(A->integer);
            moveBack(B->integer);
            while(index(A->integer)!=-1)
            {
                if(get(A->integer) > get(B->integer)) return 1;
                if(get(A->integer) < get(B->integer)) return -1;
                if(get(A->integer) == get(B->integer))
                {
                    movePrev(A->integer);
                    movePrev(B->integer);
                }
            }
        }
        if(sign(A) == -1 && sign(B) == -1)
        {
            if(length(A->integer) < length(B->integer)) return  1;
            if(length(A->integer) > length(B->integer)) return -1;
            moveBack(A->integer);
            moveBack(B->integer);
            while(index(A->integer)!=-1)
            {
                if(get(A->integer) > get(B->integer)) return -1;
                if(get(A->integer) < get(B->integer)) return 1;
                if(get(A->integer) == get(B->integer))
                {
                    movePrev(A->integer);
                    movePrev(B->integer);
                }
            }
        }
        if(sign(A) ==  1 && (sign(B) == 0 || sign(B) == -1)) return  1;
        if(sign(A) == -1 && (sign(B) == 0 || sign(B) ==  1)) return -1;
        if(sign(A) ==  0 && sign(B) ==  1) return -1;
        if(sign(A) ==  0 && sign(B) ==  0) return  0;
        if(sign(A) ==  0 && sign(B) == -1) return  1;
    }
}







// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B)
{
    if(sign(A) == 0 && sign(B) == 0)
    {
        return 1;
    }
    else if( (sign(A) != sign(B)) || (length(A->integer) != length(B->integer)) )
    {
        return 0;
    }
    else
    {
        moveFront(A->integer);
        moveFront(B->integer);
        while(index(A->integer) != -1)
        {
            if(get(A->integer) != get(B->integer))
            {
                return 0;
            }
            
            moveNext(A->integer);
            moveNext(B->integer);
        }
        return 1;
    }
}




// Manipulation procedures ----------------------------------------------------




// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N)
{
    if(N != NULL)
    {
        N->sign = 0;
        if(N->integer != NULL)
        {
            clear(N->integer);
        }
    }
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N)
{
    if(N->sign == -1)
    {
        N->sign = 1;
    }
    else if(N->sign == 1)
    {
        N->sign = -1;
    }
    
}





// BigInteger Arithmetic operations -----------------------------------------------








// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s)
{
    BigInteger X= newBigInteger();
    int signHold = 0;
    int numCheck = 0;
    char* realStr;
    char* strStart;

    if(s == NULL)
    {
        printf("Error in BigInteger.c, stringToBigInteger(): parameter string is empty");
        exit(EXIT_FAILURE);
    }

    if(*(s+0) == 43 || *(s+0) == 45)
    {
        if(*(s+0) == 43) signHold = 1;
        if(*(s+0) == 45) signHold = -1;
        realStr = s + 1;
    }
    else
    {
        signHold = 1;
        realStr = s;
    }
    
    for(int i=0; i < strlen(realStr) ; i++)
    {
        if(!isdigit( *(realStr+i) ))
        {
            printf("Error in BigInteger.c, stringToBigInteger(): parameter string had non-digits");
            exit(EXIT_FAILURE); 
        }
        if(*(realStr+i) != '0')
        {
            numCheck = 1;
            strStart = realStr + i ;
            break;
        }
    }

    if(numCheck == 0)
    {
        X->sign = 0; 
        return X;
    }

    if( signHold == -1)
    {
        X->sign = -1;
    }
    else
    {
        X->sign = 1;
    }
 
    long var = 0;
    int y = 1 ;
    int z = 0;
    long j = strlen(strStart);
    long count = 0;
    while(j > 0)
    {
        if(*(strStart+j-1) == '0')
        {
            var = 0;
        }
        else
        {
            var = *(strStart+j-1) - '0';
            count = count + (var*power(10,z));
        }


        z++;
        j--;
        if(y==9)
        {
            append(X->integer, count);
            y=0;
            count = 0;
            z=0;
        }
        y++;
    }

    if(count > 0)
    {
        append(X->integer, count);
    }

    return X;
}




// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N)
{
    BigInteger X= newBigInteger();
    X->integer = copyList(N->integer);
    X->sign = N->sign;
    return X;
}


// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
    BigInteger C = newBigInteger();
    BigInteger D = newBigInteger();
    BigInteger E = newBigInteger();
    C= copy(A);
    D= copy(B);
    E = sum(C,D);
    makeZero(S);
    S->integer = copyList(E->integer);
    S->sign = E->sign;
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B)
{
    BigInteger C= newBigInteger();

    if(sign(A) == 0 && sign(B) == 0) return C;
    if(A == B)
    {
        BigInteger D = newBigInteger();
        D = copy(A);
        C->integer = vectorSum(A->integer,D->integer);
        C->sign = sign(A);
        freeBigInteger(&D);
        return C;
    }
    if(equals(A,B))
    {
        C->integer = vectorSum(A->integer,B->integer);
        C->sign = sign(A);
        return C;
    }
    if(sign(A) == 0 && (sign(B) == 1 || sign(B) ==-1))
    {
        C=copy(B);
        return C;
    }
    if(sign(B) == 0 && (sign(A) == 1 || sign(A) ==-1))
    {
        C=copy(A);
        return C;
    }

    int check = listCheck(A->integer, B->integer);

    if(sign(A) == 1 && sign(B) == -1)
    {
        if(check == 1)
        {
            C->integer = vectorDiff(A->integer, B->integer);
            C->sign = 1;
            return C;
        }else if(check == -1)
        {
            C->integer = vectorDiff(B->integer, A->integer);
            C->sign = -1;
            return C;
        }
        else if(check == 0)
        {
            return C;
        }
    }
    if(sign(A) == -1 && sign(B) == 1)
    {
        if(check == 1)
        {
            C->integer = vectorDiff(A->integer, B->integer);
            C->sign = -1;
            return C;
        }else if(check == -1)
        {
            C->integer = vectorDiff(B->integer, A->integer);
            C->sign = 1;
            return C;
        }
        else if(check == 0)
        {
            return C;
        }
    }

    if(sign(A) == 1 && sign(B) == 1)
    {
        C->integer = vectorSum(A->integer, B->integer);
        C->sign = 1;
        return C;
    }

    if(sign(A) == -1 && sign(B) == -1)
    {
        C->integer = vectorSum(A->integer, B->integer);
        C->sign = -1;
        return C;
    }
    return C;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
    BigInteger C = newBigInteger();
    BigInteger F = newBigInteger();
    BigInteger E = newBigInteger();
    C= copy(A);
    F= copy(B);
    E = diff(C,F);
    makeZero(D);
    D->integer = copyList(E->integer);
    D->sign = E->sign;
    freeBigInteger(&C);
    freeBigInteger(&F);
    freeBigInteger(&E);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{
    BigInteger C= newBigInteger();

    if(sign(A) == 0 && sign(B) == 0) return C;
    if(A == B) return C;
    if(equals(A,B)) return C;
    if(sign(A) == 0 && (sign(B) == 1 || sign(B) ==-1))
    {
        C=copy(B);
        if(sign(B) == 1)
        {
            C->sign = -1;
        }
        else if(sign(B) == -1)
        {
            C->sign = 1;
        }
        return C;
    }
    if(sign(B) == 0 && (sign(A) == 1 || sign(A) ==-1))
    {
        C=copy(A);
        return C;
    }

    int check = listCheck(A->integer, B->integer);

    if(sign(A) == 1 && sign(B) == 1)
    {
        if(check == 1)
        {
            C->integer = vectorDiff(A->integer, B->integer);
            C->sign = 1;
            return C;
        }else if(check == -1)
        {
            C->integer = vectorDiff(B->integer, A->integer);
            C->sign = -1;
            return C;
        }
        else if(check == 0)
        {
            return C;
        }
    }
    if(sign(A) == -1 && sign(B) == -1)
    {
        if(check == 1)
        {
            C->integer = vectorDiff(A->integer, B->integer);
            C->sign = -1;
            return C;
        }else if(check == -1)
        {
            C->integer = vectorDiff(B->integer, A->integer);
            C->sign = 1;
            return C;
        }
        else if(check == 0)
        {
            return C;
        }
    }

    if(sign(A) == 1 && sign(B) == -1)
    {
        C->integer = vectorSum(A->integer, B->integer);
        C->sign = 1;
        return C;
    }

    if(sign(A) == -1 && sign(B) == 1)
    {
        C->integer = vectorSum(A->integer, B->integer);
        C->sign = -1;
        return C;
    }
    return C;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B)
{
    if(sign(A) == 0|| sign(B) == 0)
    {
        makeZero(P);
    }
    else
    {
        BigInteger C = newBigInteger();
        BigInteger D = newBigInteger();
        BigInteger E = newBigInteger();
        C= copy(A);
        D= copy(B);
        E = prod(C,D);
        makeZero(P);
        P->integer = copyList(E->integer);
        P->sign = E->sign;
        freeBigInteger(&C);
        freeBigInteger(&D);
        freeBigInteger(&E);
    }
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B)
{
    BigInteger C = newBigInteger();
    if(sign(A) == 0 || sign(B) == 0) return C;

    int x = listCheck(A->integer, B->integer);
    if(x == 1 || x == 0)
    {
        C = listProd(A->integer, B->integer);
    }
    if(x == -1)
    {
        C = listProd(B->integer, A->integer);
    }

    if(sign(A) == -1 || sign(B) == -1)
    {
        if(sign(A) == -1 && sign(B) == -1)
        {
            C->sign = 1;
        }
        else
        {
            C->sign = -1;
        }
    }
    else
    {
        C->sign = 1;
    }
    
    return C;
}



// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N)
{
    if(sign(N) == 0)
    {
        fprintf(out, "0");
    }
    else
    {
        if(N->sign == -1)
        {
            fprintf(out, "%c", 45);
        }

        int counter = 0;
        long x;
        long y;
        moveBack(N->integer);
        fprintf(out, "%ld", get(N->integer));
        movePrev(N->integer);
        while(index(N->integer) != -1)
        {
            x= get(N->integer);
            y = x;
            while( y != 0)
            {
                y = y/10;
                counter++;
            }
            y = 9 - counter;
            for(; y > 0; y--)
            {
                fprintf(out, "0");
            }
            counter = 0;

            fprintf(out, "%ld", x);
            fflush(out);
            movePrev(N->integer);
        }
    }
}
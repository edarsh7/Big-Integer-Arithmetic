/*------------------------------

Edmond Arshakyan
earshaky
pa3

-------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include "BigInteger.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stdout, "Error: invalid number of command line arguments.");
        exit(EXIT_FAILURE);
    }

    FILE* in, *out;
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if(in == NULL)
    {
        fprintf(stdout, "Error: Cannot open file.");
        exit(EXIT_FAILURE);
    }
    else
    {
        int s1;
        fscanf(in, "%d", &s1);
        char str1[s1+2];
        fscanf(in, "%s" , &str1);

        int s2;
        fscanf(in, "%d", &s2);
        char str2[s2+2];
        fscanf(in, "%s" , &str2);

        BigInteger A = newBigInteger();
        BigInteger B = newBigInteger();
        BigInteger C = newBigInteger();

        A = stringToBigInteger(str1);
        B = stringToBigInteger(str2);

        printBigInteger(out, A);
        fprintf(out, "\n\n");
        printBigInteger(out, B);
        fprintf(out, "\n\n");

        C = sum(A, B);
        printBigInteger(out, C);
        fprintf(out, "\n\n");

        makeZero(C);

        subtract(A, A, B);
        printBigInteger(out, A);
        fprintf(out, "\n\n");
        
        makeZero(A);
        A = stringToBigInteger(str1);

        makeZero(C);

        C= diff(A, A);
        printBigInteger(out, C);
        fprintf(out, "\n\n");

        makeZero(C);

        BigInteger D = newBigInteger();
        BigInteger E = newBigInteger();
        BigInteger F = newBigInteger();
        BigInteger G = newBigInteger();
        BigInteger H = newBigInteger();
        BigInteger I = newBigInteger();
        BigInteger J = newBigInteger();
        BigInteger K = newBigInteger();

        char * x1 = "2";
        char * x2 = "3";
        char * x3 = "9";
        char * x4 = "16";

        D = stringToBigInteger(x1);
        E = stringToBigInteger(x2);
        F = stringToBigInteger(x3);
        G = stringToBigInteger(x4);

        I = prod(A, E);
        J = prod(B, D);
        C = diff(I, J);
        printBigInteger(out, C);
        fprintf(out, "\n\n");

        makeZero(A);
        makeZero(B);
        makeZero(C);

        A = stringToBigInteger(str1);
        B = stringToBigInteger(str2);
        C = prod(A, B);
        printBigInteger(out, C);
        fprintf(out, "\n\n");
        makeZero(C);

        multiply(A, A, A);
        printBigInteger(out, A);
        fprintf(out, "\n\n");

        H = copy(B);

        multiply(B, B, B);
        printBigInteger(out, B);
        fprintf(out, "\n\n");

        multiply(A, A, A);
        multiply(B, B, B);

        C = prod(B, H);
        multiply(A, A, F);
        multiply(C, C, G);

        
        K = sum(A, C);
        printBigInteger(out, K);
        fprintf(out, "\n\n");
        
        freeBigInteger(&A);
        freeBigInteger(&B);
        freeBigInteger(&C);
        freeBigInteger(&D);
        freeBigInteger(&E);
        freeBigInteger(&F);
        freeBigInteger(&G);
        freeBigInteger(&H);
        freeBigInteger(&I);
        freeBigInteger(&J);
        freeBigInteger(&K);

    }
    fflush(out);
    fclose(out);
    fclose(in);

}
#include <stdio.h>
#include <stdlib.h>
#include "bino.h"
#include "hex.h"

// buggy :(

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("usage: ./path/conv <start-base> <dest-base> <num>");
        printf("\nbases: 2 (binary), 10 (decimal), 16 (hexadecial)\n");
        return 1;
    }

    int startbase = atoi(argv[1]);
    int destbase = atoi(argv[2]);
    const char *num = argv[3];
    long long decNum;

    if (startbase == 2)
    {
        decNum = bintodec(num);
    } else if (startbase == 16)
    {
        decNum = hextodec(num);
    } else if (startbase == 10)
    {
        decNum = atoll(argv[3]);
    } 
    
    char *result;

    if (destbase == 2)
    {
        result = dectobin(decNum);
    } else if (destbase == 16)
    {
        result = dectohex(decNum);
    } else if (destbase == 10)
    {
        sprintf(result, "%s", decNum);
    }
    printf("| start base: %d | target base: %d | input: %s | output: %s |\n", startbase, destbase, num, result);
    //printf("| output: %s |", result);
    return 0;
}

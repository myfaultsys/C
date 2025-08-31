#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *dectobin(long long n)
{
    static const char digits[] = "01";
    static char bin[66];
    char *ptr = &bin[0];
    if (n == 0)
    {
        *(ptr++) = '0';
        *ptr = '\0';
        return bin;
    }
    while (n > 0)
    {
        int remainder = n % 2;
        *(ptr++) = digits[remainder];
        n /= 2;
    }
    long long length = ptr - bin;
    for (long long i = 0; i < length / 2; i++)
    {
        char tmp = bin[i];
        bin[i] = bin[length - i - 1];
        bin[length - i - 1] = tmp;
    }
    *ptr = '\0';
    return bin;
}

long long bintodec(const char *bin)
{
    long long base = 1;
    long long result = 0;
    long long length = strlen(bin);
    for (long long i = length - 1; i >= 0; i--)
    {
        char character = bin[i];
        if (character == '1')
        {
            result += base;
        }
        base *= 2;
    }
    return result;
}

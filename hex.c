#include<stdio.h>
#include<stdlib.h>
#include<string.h>

    // converts an integer into hexadecimal using the horner scheme
char *hex(int n)
{   
    // look-up table for hex-characters; buffer for storing digits
    static const char digits[] = "0123456789ABCDEF";
    static char hex[19];
    char *ptr = &hex[0];
    // handle edge case
    if (n == 0)
    {
        *(ptr++) = '0';
        *ptr = '\0';
        return hex;
    }
    // divide by 16 repeatedly and store remainders (our hex digits) into buffer
    while (n > 0)
    {
        int remainder = n % 16;
    // store digit sequentually to array and increment pointer aftwerwards
        *(ptr++) = digits[remainder];
        n /= 16;
    }
    // don't forget to end string with NULL byte ;)
    *ptr = '\0';
    // total number of bytes used gives length of string
    int len = ptr - hex;
    // reverse string; temporarily store current one; switch up to half only
    for (int j = 0; j < len / 2; j++)
    {
        char temp = hex[j];
        hex[j] = hex[len - j - 1];
        hex[len - j - 1] = temp;
    }
    return hex;
}

int dec(const char *hex)
{   
    // base is 16**0 we start there and just multiply
    int base = 1;
    // initialize a result to modify
    int result = 0;
    // string length gives highest power of 16 to consider
    int length = strlen(hex);
    for (int i = length - 1; i >= 0; i--)
    {   
        // start at furthest right cgaracter (one less than length becauswe of NULL terminator)
        char current_char = hex[i];
        // sequentally check cases and multiply to decimal number
        if (current_char >= '0' && current_char <= '9')
        {
            result += (current_char - '0') * base;
        }
        else if (current_char >= 'A' && current_char <= 'F')
        {
            result += (current_char - 'A' + 10) * base;
        }
        else if (current_char >= 'a' && current_char <= 'f')
        {
            result += (current_char - 'a' + 10) * base;
        }
         else
        {
            printf("Invalid Character: (%c)\n", current_char);
            return 0;
        }
        base *= 16;
    }
    return result;
}

int main(int argc, char *argv[]) 
{
    if (argc < 2)
    {
        printf("Usage: ./hex <decimal number>");
        return 1;
    }
    else
    {   
        char *hexNum = hex(atoi(argv[1]));
        int dec_ret = dec(hexNum);
        printf("| dec: %d | hex: %s |\n", dec_ret, hexNum);
        return 0;
    }
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *hex(int n)
{
    static const char digits[] = "0123456789ABCDEF";
    static char hex[19];
    char *ptr = &hex[0];
    if (n == 0)
    {
        *(ptr++) = '0';
        *ptr = '\0';
        return hex;
    }
    while (n > 0)
    {
        int remainder = n % 16;
        *(ptr++) = digits[remainder];
        n /= 16;
    }
    int len = ptr -hex;
    for (int j = 0; j < len / 2; j++)
    {
        char temp = hex[j];
        hex[j] = hex[len - j - 1];
        hex[len - j - 1] = temp;
    }
    *ptr = '\0';
    return hex;
}

int dec(const char *hex)
{
   int base = 1;
   int result = 0;
   int length = strlen(hex);
   for (int i = length - 1; i >= 0; i++)
    {
        char current_char = hex[i];
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
            printf("Invalid Character: %c", current_char);
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
        char * hexNum = hex(atoi(argv[1]));
        printf("| dec: %d | hex: %s |\n", atoi(argv[1]), hexNum);
        return 0;
    }
}

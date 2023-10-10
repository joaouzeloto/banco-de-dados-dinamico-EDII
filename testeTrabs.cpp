#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio2.h>

float stringToFloat(const char *str) {
    float result = 0.0;
    int decimalFound = 0;
    int sign = 1; 
    if (*str == '-') {
        sign = -1;
        str++; 
    }

    while (*str) {
        if (*str >= '0' && *str <= '9') {
            result = result * 10.0 + (*str - '0');
            if (decimalFound) {
                decimalFound *= 10;
            }
        } else if (*str == '.') {
            decimalFound = 1;
        } else {
            return 0.0;
        }
        str++; 
    }

    result /= decimalFound;
    result *= sign;

    return result;
}

int main() {
    
	gotoxy(10,10);
	printf("pos[10][10]");
    return 0;
}

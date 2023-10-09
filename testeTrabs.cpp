#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

float stringToFloat(const char *str) {
    float result = 0.0;
    int decimalFound = 0;
    int sign = 1; // Para lidar com números negativos

    // Verificar se o número é negativo
    if (*str == '-') {
        sign = -1;
        str++; // Avançar para o próximo caractere
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
            // Caractere inválido
            printf("Erro: Caractere inválido '%c' encontrado na string.\n", *str);
            return 0.0;
        }
        str++; // Avançar para o próximo caractere
    }

    result /= decimalFound;
    result *= sign;

    return result;
}

int main() {
    const char str[] = "474.70"; // Sua string com o valor float
    float valor = stringToFloat(str);

    printf("O valor em float : %.2f\n", valor);

    return 0;
}

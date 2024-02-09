#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <operand1> <operand2>\n", argv[0]);
        return 1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    printf("Addition: %d\n", add(a, b));
    printf("Subtraction: %d\n", sub(a, b));
    printf("Multiplication: %d\n", mul(a, b));
    printf("Division: %d\n", divide(a, b));

    return 0;
}

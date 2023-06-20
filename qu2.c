#include <stdio.h>

int findMaxUsingIfElse(int num1, int num2) {
    if (num1 > num2)
        return num1;
    else
        return num2;
}

int findMaxUsingTernaryOperator(int num1, int num2) {
    return (num1 > num2) ? num1 : num2;
}

int main() {
    int num1, num2;
    
    printf("Enter the first number: ");
    scanf("%d", &num1);
    
    printf("Enter the second number: ");
    scanf("%d", &num2);
    
    int maxUsingIfElse = findMaxUsingIfElse(num1, num2);
    int maxUsingTernaryOperator = findMaxUsingTernaryOperator(num1, num2);
    
    printf("Using if-else, the maximum number is: %d\n", maxUsingIfElse);
    printf("Using ternary operator, the maximum number is: %d\n", maxUsingTernaryOperator);
    
    return 0;
}


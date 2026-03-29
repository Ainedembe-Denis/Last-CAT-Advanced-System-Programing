#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arrayof5;
    int i, sum = 0;

    // Dynamically allocate memory for 5 integers
    arrayof5 = (int *)malloc(5 * sizeof(int));

    // Check if memory allocation is successful
    if (arrayof5 == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter 5 integers:\n");
    // Input values
    const char *ordinals[] = {"1st", "2nd", "3rd", "4th", "5th"};
    for (i = 0; i < 5; i++) {
        printf("%s: ", ordinals[i]);
        scanf("%d", &arrayof5[i]);
    }

    // Calculate sum
    for (i = 0; i < 5; i++) {
        sum += arrayof5[i];
    }

    // Print sum
    printf("Sum = %d\n", sum);

    // Free allocated memory
    free(arrayof5);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main() {
    int* array = (int*)malloc(5 * sizeof(int));  // Pocz¹tkowy rozmiar tablicy: 5
    int size = 5;
    int count = 0;

    if (array == NULL) {
        printf("Blad przy alokacji pamiêci.");
        return 1;
    }

    int number;
    do {
        printf("Podaj liczbe (0 - zakoncz): ");
        scanf("%d", &number);

        if (count == size) {
            size += 5;
            int* temp = (int*)realloc(array, size * sizeof(int));
            if (temp == NULL) {
                printf("Blad przy realokacji pamieci.");
                free(array);
                return 1;
            }
            array = temp;
        }

        array[count] = number;
        count++;
    } while (number != 0);

    printf("Zawartosc tablicy:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", array[i]);
    }

    free(array);
    return 0;
}

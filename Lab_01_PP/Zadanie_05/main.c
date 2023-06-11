#include <stdio.h>
#include <stdlib.h>

void printElement(float* element) {
    printf("%.2f ", *element);
}

void saveElementToFile(float* element, FILE* file) {
    fprintf(file, "%.2f ", *element);
}

void processArray(float* array, int size, void (*processElement)(float*, void*), void* additionalData) {
    for (int i = 0; i < size; i++) {
        processElement(&array[i], additionalData);
    }
}

int main() {
    float* array = (float*)malloc(20 * sizeof(float));
    if (array == NULL) {
        printf("B��d przy alokacji pami�ci.");
        return 1;
    }

    printf("Wybierz opcj�:\n");
    printf("1. Wy�wietlaj warto�ci na ekranie\n");
    printf("2. Zapisuj warto�ci do pliku\n");
    int option;
    scanf("%d", &option);

    void (*processElement)(float*, void*);
    void* additionalData = NULL;

    if (option == 1) {
        processElement = printElement;
    } else if (option == 2) {
        processElement = saveElementToFile;
        FILE* file = fopen("output.txt", "w");
        if (file == NULL) {
            printf("B��d przy otwieraniu pliku.");
            free(array);
            return 1;
        }
        additionalData = file;
    } else {
        printf("Nieprawid�owa opcja.");
        free(array);
        return 1;
    }

    printf("Wprowad� warto�ci:\n");
    for (int i = 0; i < 20; i++) {
        scanf("%f", &array[i]);
    }

    processArray(array, 20, processElement, additionalData);

    if (option == 2) {
        FILE* file = additionalData;
        fclose(file);
    }

    free(array);
    return 0;
}

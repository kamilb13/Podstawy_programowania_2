#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void uzupelnijRandom(int **macierz, int n);
void sumaMacierz(int **macierz, int n);

int main() {
    int n;
    printf("podaj rozmiar macierzy: ");
    scanf("%d", &n);
    int **macierz = (int **)malloc(n*sizeof(int));
    for(int i=0; i<n; i++)
        macierz[i] = (int *)malloc(n*sizeof(int));

    uzupelnijRandom(macierz, n);
    sumaMacierz(macierz, n);

    free(macierz);
    return 0;
}

void uzupelnijRandom(int **macierz, int n){
    srand(time(NULL));
    for(int i=0; i<n; i++){
        for (int j=0; j<n; j++)
            macierz[i][j] = -10+rand()%21;
    }
}

void sumaMacierz(int **macierz, int n){
        int suma = 0;
    printf("macierz: ");
    puts(" ");
    for(int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%d ", macierz[i][j]);
            if (i == j)
                suma += macierz[i][j];
        }
        puts("");
    }
    printf("suma przekatnej: %d\n", suma);
}

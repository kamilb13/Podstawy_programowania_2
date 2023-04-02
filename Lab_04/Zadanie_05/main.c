#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROZMIAR_STOSU 11

typedef struct {
    int stos[ROZMIAR_STOSU];
    int wierzcholek;
} Stos;

void inicjuj_stos(Stos *s) {
    s->wierzcholek = -1;
}

int czy_pusty(Stos *s) {
    return s->wierzcholek == -1;
}

int czy_pelny(Stos *s) {
    return s->wierzcholek == ROZMIAR_STOSU - 1;
}

int push(Stos *s, int liczba) {
    if (czy_pelny(s)) {
        printf("Stos jest pelny\n");
        return 0;
    }
    s->wierzcholek++;
    s->stos[s->wierzcholek] = liczba;
    return 1;
}

int pop(Stos *s) {
    if (czy_pusty(s)) {
        printf("Stos jest pusty\n");
        return -1;
    }
    int wynik = s->stos[s->wierzcholek];
    s->wierzcholek--;
    return wynik;
}

int main() {
    srand(time(NULL));

    Stos parzyste, nieparzyste;
    inicjuj_stos(&parzyste);
    inicjuj_stos(&nieparzyste);

    for (int i = 0; i < 10; i++) {
        int liczba = rand() % 11;
        if (liczba % 2 == 0) {
            push(&parzyste, liczba);
        } else {
            push(&nieparzyste, liczba);
        }
    }

    printf("Liczby parzyste:\n");
    while (!czy_pusty(&parzyste)) {
        printf("%d\n", pop(&parzyste));
    }

    printf("\nLiczby nieparzyste:\n");
    while (!czy_pusty(&nieparzyste)) {
        printf("%d\n", pop(&nieparzyste));
    }

    return 0;
}

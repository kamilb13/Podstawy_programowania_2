#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROZMIAR 100

typedef struct {
    char stos[MAX_ROZMIAR];
    int wierzcholek;
} Stos;

void inicjalizuj(Stos *s) {
    s->wierzcholek = -1;
}

int czy_pusty(Stos *s) {
    return s->wierzcholek == -1;
}

int czy_pelny(Stos *s) {
    return s->wierzcholek == MAX_ROZMIAR - 1;
}

void push(Stos *s, char znak) {
    if (czy_pelny(s)) {
        printf("Stos jest pelny\n");
        return;
    }
    s->wierzcholek++;
    s->stos[s->wierzcholek] = znak;
}

char pop(Stos *s) {
    if (czy_pusty(s)) {
        printf("Stos jest pusty\n");
        return '\0';
    }
    char znak = s->stos[s->wierzcholek];
    s->wierzcholek--;
    return znak;
}

int main() {
    Stos s;
    inicjalizuj(&s);

    char wyrazenie[MAX_ROZMIAR];
    printf("Podaj wyrazenie: ");
    fgets(wyrazenie, MAX_ROZMIAR, stdin);
    wyrazenie[strcspn(wyrazenie, "\n")] = '\0'; // usuwa znak nowej linii z fgets

    int dlugosc = strlen(wyrazenie);
    int i;
    for (i = 0; i < dlugosc; i++) {
        if (wyrazenie[i] == '(') {
            push(&s, wyrazenie[i]);
        } else if (wyrazenie[i] == ')') {
            char znak = pop(&s);
            if (znak != '(') {
                printf("Blad parowania nawiasow\n");
                return 1;
            }
        }
    }

    if (!czy_pusty(&s)) {
        printf("Blad parowania nawiasow\n");
        return 1;
    }

    printf("Poprawne parowanie nawiasow\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX_ROZMIAR 10

typedef struct {
    int stos[MAX_ROZMIAR];
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

void push(Stos *s, int wartosc) {
    if (czy_pelny(s)) {
        printf("Stos jest pelny\n");
        return;
    }
    s->wierzcholek++;
    s->stos[s->wierzcholek] = wartosc;
}

int pop(Stos *s) {
    if (czy_pusty(s)) {
        printf("Stos jest pusty\n");
        return -1;
    }
    int wartosc = s->stos[s->wierzcholek];
    s->wierzcholek--;
    return wartosc;
}

int main() {
    Stos s;
    inicjalizuj(&s);

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    printf("Pobrana wartosc: %d\n", pop(&s));
    printf("Pobrana wartosc: %d\n", pop(&s));
    printf("Pobrana wartosc: %d\n", pop(&s));
    printf("Pobrana wartosc: %d\n", pop(&s));

    return 0;
}

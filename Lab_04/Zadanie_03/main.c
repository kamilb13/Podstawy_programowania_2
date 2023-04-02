#include <stdbool.h>  // Dodajemy bibliotek� bool

bool push(Stos *s, char znak) {  // Zmieniamy typ z void na bool
    if (czy_pelny(s)) {
        printf("Stos jest pelny\n");
        return false;  // Zwracamy warto�� false, gdy stos jest pe�ny
    }
    s->wierzcholek++;
    s->stos[s->wierzcholek] = znak;
    return true;  // Zwracamy warto�� true, gdy element zosta� dodany do stosu
}

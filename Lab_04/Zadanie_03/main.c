#include <stdbool.h>  // Dodajemy bibliotekê bool

bool push(Stos *s, char znak) {  // Zmieniamy typ z void na bool
    if (czy_pelny(s)) {
        printf("Stos jest pelny\n");
        return false;  // Zwracamy wartoœæ false, gdy stos jest pe³ny
    }
    s->wierzcholek++;
    s->stos[s->wierzcholek] = znak;
    return true;  // Zwracamy wartoœæ true, gdy element zosta³ dodany do stosu
}

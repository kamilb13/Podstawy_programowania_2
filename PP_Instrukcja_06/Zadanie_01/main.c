#include <stdio.h>
#include <stdlib.h>

struct Wezel{
    int klucz;          // klucz - WARTOŒÆ
    struct Wezel* lewy;
    struct Wezel* prawy;
};

struct Wezel* stworzWezel(int klucz){
    struct Wezel* nowyWezel = (struct Wezel*)malloc(sizeof(struct Wezel));
    nowyWezel->klucz = klucz;
    nowyWezel->lewy = NULL;
    nowyWezel->prawy = NULL;
    return nowyWezel;
}
/*
struct Wezel* dodajRek(struct Wezel* korzen, int klucz){
    if(korzen == NULL)
        return stworzWezel(klucz);


    if(klucz < korzen->klucz){
        korzen->lewy = dodajRek(korzen->lewy, klucz);
    }
    else if(klucz > korzen->klucz){
        korzen->prawy = dodajRek(korzen->prawy, klucz);
    }

    return korzen;
}
*/
struct Wezel* dodaj(struct Wezel* korzen, int klucz){
    if(korzen == NULL){
        return stworzWezel(klucz);
    }

    struct Wezel* aktualny = korzen;
    struct Wezel* poprzedni = NULL;

    while(aktualny != NULL){
        poprzedni = aktualny;

        if(klucz < aktualny->klucz){
            aktualny = aktualny->lewy;
        }else if(klucz > aktualny->klucz){
            aktualny = aktualny->prawy;
        }else{
            return korzen;
        }
    }

    if(klucz < poprzedni->klucz){
        poprzedni->lewy = stworzWezel(klucz);
    }
    else{
        poprzedni->prawy = stworzWezel(klucz);
    }

    return korzen;
}

void szukaj(struct Wezel* korzen, int klucz){
    if(korzen == NULL){
        printf("Nie znaleziono klucza %d w drzewie\n", klucz);
    }else if(korzen->klucz == klucz){
        printf("Znaleziono klucza %d w drzewie\n", klucz);
    }else if(klucz < korzen->klucz){
        szukaj(korzen->lewy, klucz);
    }else{
        szukaj(korzen->prawy, klucz);
    }
}

void preOrder(struct Wezel* korzen){
    if(korzen){
        printf("%d ", korzen->klucz);
        preOrder(korzen->lewy);
        preOrder(korzen->prawy);
    }
}

void inOrder(struct Wezel* korzen) {
    if(korzen){
        inOrder(korzen->lewy);
        printf("%d ", korzen->klucz);
        inOrder(korzen->prawy);
    }
}

void postOrder(struct Wezel* korzen){
    if(korzen){
        postOrder(korzen->lewy);
        postOrder(korzen->prawy);
        printf("%d ", korzen->klucz);
    }
}

void inOrderOdwrotnie(struct Wezel* korzen){
    if(korzen) {
        inOrderOdwrotnie(korzen->prawy);
        printf("%d ", korzen->klucz);
        inOrderOdwrotnie(korzen->lewy);
    }
}

void levelOrder(struct Wezel* korzen){
    if(korzen == NULL){
        return;
    }

    struct Wezel* kolejka[100];
    int front = 0;
    int wolne = 0;

    kolejka[wolne++] = korzen;

    while(front < wolne){
        struct Wezel* aktualny = kolejka[front++];
        printf("%d ", aktualny->klucz);

        if (aktualny->lewy != NULL){
            kolejka[wolne++] = aktualny->lewy;
        }

        if (aktualny->prawy != NULL){
            kolejka[wolne++] = aktualny->prawy;
        }
    }
}

int wysokoscDrzewa(struct Wezel* korzen){
    if (korzen == NULL) {
        return 0;
    }else {
        int lewaWysokosc = wysokoscDrzewa(korzen->lewy);
        int prawaWysokosc = wysokoscDrzewa(korzen->prawy);
        if (lewaWysokosc > prawaWysokosc){
            return lewaWysokosc + 1;
        }else {
            return prawaWysokosc + 1;
        }
    }
}

void wyswietlDrzewo(struct Wezel* korzen, int poziom){
    if (korzen == NULL) {
        return;
    }

    wyswietlDrzewo(korzen->prawy, poziom + 1);

    for (int i = 0; i < poziom; i++){
        printf("    ");
    }

    printf("%d\n", korzen->klucz);

    wyswietlDrzewo(korzen->lewy, poziom + 1);
}

int main(){
    struct Wezel* korzen = NULL;

    korzen = dodaj(korzen, 50);
    korzen = dodaj(korzen, 30);
    korzen = dodaj(korzen, 70);
    korzen = dodaj(korzen, 20);
    korzen = dodaj(korzen, 40);
    korzen = dodaj(korzen, 60);
    korzen = dodaj(korzen, 80);

    szukaj(korzen, 40);
    szukaj(korzen, 90);
    printf("\n");

    printf("PreOrder: ");
    preOrder(korzen);
    printf("\n");

    printf("InOrder: ");
    inOrder(korzen);
    printf("\n");

    printf("PostOrder: ");
    postOrder(korzen);
    printf("\n");

    printf("InOrder odwrotnie: ");
    inOrderOdwrotnie(korzen);
    printf("\n");

    printf("LevelOrder: ");
    levelOrder(korzen);
    printf("\n");

    printf("Wysokosc drzewa: %d\n", wysokoscDrzewa(korzen));

    printf("Drzewo w postaci semi-graficznej:\n");
    wyswietlDrzewo(korzen, 0);

    return 0;
}

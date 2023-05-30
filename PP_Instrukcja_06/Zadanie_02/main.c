#include <stdio.h>
#include <stdlib.h>

struct Wezel{
    int klucz;
    struct Wezel* lewy;
    struct Wezel* prawy;
};

struct Wezel* rotacjaWLewo(struct Wezel* korzen){
    if(korzen == NULL || korzen->prawy == NULL){
        return korzen;
    }

    struct Wezel* nowyKorzen = korzen->prawy;
    korzen->prawy = nowyKorzen->lewy;
    nowyKorzen->lewy = korzen;

    return nowyKorzen;
}

struct Wezel* rotacjaWPrawo(struct Wezel* korzen){
    if(korzen == NULL || korzen->lewy == NULL){
        return korzen;
    }

    struct Wezel* nowyKorzen = korzen->lewy;
    korzen->lewy = nowyKorzen->prawy;
    nowyKorzen->prawy = korzen;

    return nowyKorzen;
}

struct Wezel* wstaw(struct Wezel* korzen, int klucz){
    if(korzen == NULL) {
        struct Wezel* nowyWezel = (struct Wezel*)malloc(sizeof(struct Wezel));
        nowyWezel->klucz = klucz;
        nowyWezel->lewy = NULL;
        nowyWezel->prawy = NULL;
        return nowyWezel;
    }

    if(klucz < korzen->klucz){
        korzen->lewy = wstaw(korzen->lewy, klucz);
    }else if (klucz > korzen->klucz){
        korzen->prawy = wstaw(korzen->prawy, klucz);
    }

    return korzen;
}

void inOrder(struct Wezel* korzen){
    if(korzen){
        inOrder(korzen->lewy);
        printf("%d ", korzen->klucz);
        inOrder(korzen->prawy);
    }
}

int main(){
    struct Wezel* korzen = NULL;

    korzen = wstaw(korzen, 50);
    korzen = wstaw(korzen, 30);
    korzen = wstaw(korzen, 70);
    korzen = wstaw(korzen, 20);
    korzen = wstaw(korzen, 40);
    korzen = wstaw(korzen, 60);
    korzen = wstaw(korzen, 80);

    printf("Przed rotacja:\n");
    inOrder(korzen);
    printf("\n");

    korzen = rotacjaWLewo(korzen);

    printf("Po rotacji w lewo:\n");
    inOrder(korzen);
    printf("\n");

    korzen = rotacjaWPrawo(korzen);

    printf("Po rotacji w prawo:\n");
    inOrder(korzen);
    printf("\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool allocate_array(float **tablica, int rozmiar_tab);

int main(){
    int rozmiar_tab = 8;
    float* tablica;
    if(allocate_array(&tablica, rozmiar_tab)){
        printf("przydzielono pamiec");
        puts(" ");
        for(int i=0; i<rozmiar_tab; i++) {
            tablica[i] = i+1;
            puts(" ");
            printf("%.2f ", tablica[i]);
        }
        puts(" ");
        free(tablica);
    }else
        printf("blad przydzielania pamieci");
    return 0;
}

bool allocate_array(float **tablica, int rozmiar_tab) {
    *tablica = (float*)malloc(rozmiar_tab*sizeof(float));
    if(*tablica) {
        return true;
    }else{
        return false;
    }
}

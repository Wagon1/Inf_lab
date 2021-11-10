#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int wypisz_wielomian(int wspolczynniki[], int stopien){
    for(int i = 0; i < stopien; i++){
        if(wspolczynniki[i] != 1){
            printf("%dx^%d + ", wspolczynniki[i], stopien-i);
        }else{
            printf("x^%d + ", stopien-i);
        }
    }
    printf("%d", wspolczynniki[stopien]);

}

int max(int a, int b){
    if(a > b){
        return a;
    }else{
        return b;
    }
}

int dodaj_wielomiany(int wspolczynniki1[], int stopien1, int wspolczynniki2[], int stopien2, int wspolczynniki_wyniku[]){
    int stopien_wyniku = max(stopien1, stopien2);
    int rozmiar = 0;
    int mniejszy = 0;
    if(stopien2 < stopien1){
        mniejszy = 2;
        rozmiar = stopien2;
    }else{
        mniejszy = 1;
        rozmiar = stopien1;
    }
    for(int i = 0; i <= stopien_wyniku; i++){
        if(i >= stopien_wyniku - rozmiar){
            wspolczynniki_wyniku[i] = wspolczynniki1[i] + wspolczynniki2[i];
        }else{
            if(mniejszy == 1){
                wspolczynniki_wyniku[i] = wspolczynniki2[i];
            }else{
                wspolczynniki_wyniku[i] = wspolczynniki1[i];
            }
        }
    }
}

int przemnoz_wielomiany(int wspolczynniki1[], int stopien1, int wspolczynniki2[], int stopien2, int wspolczynniki_wyniku[]){
    int stopien_wyniku = stopien1 * stopien2;
    for(int i = 0; i <= stopien_wyniku; i++){
        if(i >= stopien_wyniku - rozmiar){
            wspolczynniki_wyniku[i] = wspolczynniki1[i] + wspolczynniki2[i];
        }else{
            if(mniejszy == 1){
                wspolczynniki_wyniku[i] = wspolczynniki2[i];
            }else{
                wspolczynniki_wyniku[i] = wspolczynniki1[i];
            }
        }
    }
}
int main()
{
    int wielomian1[] = {1,2,1,2,4,5};
    int wielomian2[] = {3,4,5,6,4,2};
    int wielomian_ze_stopniem[10];
    dodaj_wielomiany(wielomian1, 5, wielomian2, 5, wielomian_ze_stopniem);
    wypisz_wielomian(wielomian_ze_stopniem, 5);
    return 0;
}
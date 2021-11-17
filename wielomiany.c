#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int wypisz_wielomian(int wspolczynniki[], int stopien){
    int pierwszy = 0;
    for(int i = 0; i < stopien; i++){
        if(wspolczynniki[i] != 0){
            if(pierwszy){
                printf(" + ");
            }
            pierwszy = 1;
            if(wspolczynniki[i] != 1){
                if((stopien - i) != 1){
                    printf("%dx^%d", wspolczynniki[i], stopien-i);
                }else{
                    printf("%dx", wspolczynniki[i]);
                }
            }else{
                if((stopien - i) != 1){
                    printf("x^%d", stopien-i);
                }else{
                    printf("x");
                }
            }
        }
    }
    if(wspolczynniki[stopien]){
        printf(" + %d", wspolczynniki[stopien]);
    }

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

/*
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
*/

int wczytaj_wielomian(int wielomian[], int stopien){
    int stan = 1;
    int znak;
    int wspolczynnik = 0;
    int plus_minus = 1;
    int wykladnik = 0;
    int wczytalem = 0;
    while((znak = getchar()) != '\n'){
        switch(stan){
            case 1:
                wczytalem = 0;
                if(znak == 'x'){
                    if(wspolczynnik == 0){
                        wspolczynnik = 1;
                    }
                    stan++;
                }
                if(znak == '-'){
                    plus_minus = -1;
                }
                if('0' <= znak && znak <= '9'){        
                    wspolczynnik = wspolczynnik * 10+plus_minus * (znak - '0');
                }
                break;
            case 2:
                if(znak == '+' || znak == '-'){
                    wielomian[stopien - wykladnik - 1] = wspolczynnik;
                    wczytalem = 1;
                    wykladnik = 0;
                    wspolczynnik = 0;
                    stan--;
                }
                if('0' <= znak && znak <= '9'){
                    wykladnik = wykladnik * 10+plus_minus * (znak - '0');
                }
                break;
        }
    }
    if(!wczytalem){
        wielomian[stopien - wykladnik - 1] = wspolczynnik;
    };
    wypisz_wielomian(wielomian, stopien);
    printf("\n");
}


int main()
{
    int wielomian1[] = {1,2,1,2,4,5};
    int wielomian2[] = {3,4,5,6,4,2};
    int wielomian_ze_stopniem[10] = {0,0,0,0,0,0,0,0,0,0};
    wczytaj_wielomian(wielomian_ze_stopniem, 9);
    // dodaj_wielomiany(wielomian1, 5, wielomian2, 5, wielomian_ze_stopniem);
    // wypisz_wielomian(wielomian_ze_stopniem, 5);
    return 0;
}
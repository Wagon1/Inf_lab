#include <stdio.h>

//Define stałych WIERSZE, KOLUMNY, POLA i WYBOR.
#ifndef WIERSZE
    #define WIERSZE 26
#endif

#ifndef POLA
    #define POLA 5
#endif

#ifndef KOLUMNY
    #define KOLUMNY 26
#endif

#ifndef WYBOR
    #define WYBOR 1000
#endif

void zeruj_plansze(int p[][KOLUMNY]){
    //Wyzeruj wartosci tablicy.
    for(int i = 0; i < KOLUMNY; i++){
        for(int j = 0; j < WIERSZE; j++){
            p[j][i] = 0;
        }
    }
}
int x_ruchu(char r[]){
    if(r[0] >= 'a'){
        return r[0] - 'a';
    }else{
        return r[1] - 'a';
    }
}
int y_ruchu(char r[]){
    if(r[0] < 'a' && r[0] >= 'A'){
        return r[0] - 'A';
    }else{
        return r[1] - 'A';
    }
}
int poza_plansza(char r[]){
    if(x_ruchu(r) < 0 || x_ruchu(r) >= WIERSZE){
        return 1;
    }
    if(y_ruchu(r) < 0 || y_ruchu(r) >= KOLUMNY){
        return 1;
    }
    return 0;
}
void narysuj_plansze(int p[][KOLUMNY]){
    //Funkcja pomocnicza do rysowania planszy.
    char znak;
    printf("  ");
    for(int i = 0; i < KOLUMNY; i++){
        znak = (char) ('A' + i);
        printf("%c ", znak);
    }
    printf("\n");
    for(int i = 0; i < WIERSZE; i++){
        znak = (char) ('a' + i);
        printf("%c ", znak);
        for(int j = 0; j < KOLUMNY; j++){
            if(p[i][j] == 0){
                printf(". ");
            }else{
                printf("# ");
            }
        }
        printf("\n");
    }
}
int czy_mozna_wykonac_prawy(char r[], int p[][KOLUMNY]){
    char pole[2];
    pole[0] = (char) (x_ruchu(r) + 'a');
    for(int i = 0; i < POLA; i++){
        pole[1] = (char) (y_ruchu(r) + i + 'A');
        if(poza_plansza(pole)){
            return 0;
        }
        if(p[x_ruchu(pole)][y_ruchu(pole)] == 1){
            return 0;
        }
    }
    return 1;
}
int czy_mozna_wykonac_lewy(char r[], int p[][KOLUMNY]){
    char pole[2];
    pole[1] = (char) (y_ruchu(r)+'A');
    for(int i = 0; i < POLA; i++){
        pole[0] = (char) (x_ruchu(r) + i + 'a');
        if(poza_plansza(pole)){
            return 0;
        }
        if(p[x_ruchu(pole)][y_ruchu(pole)] == 1){
            return 0;
        }
    }
    return 1;
}
void zapisz_ruch_lewego(char r[], int p[][KOLUMNY]){
    //Zapisz na planszy ruch lewego.
    char pole[2];
    pole[0] = r[0];
    if(czy_mozna_wykonac_lewy(r, p)){
        for(int i = 0; i < POLA; i++){
            pole[1] = (char) (r[1] + i);
            p[x_ruchu(pole)][y_ruchu(pole)] = 1;
        }
    }
}
void zapisz_ruch_prawego(char r[], int p[][KOLUMNY]){
    //Zapisz na planszy ruch prawego
    char pole[2];
    pole[1] = r[1];
    if(czy_mozna_wykonac_prawy(r, p)){
        for(int i = 0; i < POLA; i++){
            pole[0] = (char) (r[0] + i);
            p[x_ruchu(pole)][y_ruchu(pole)] = 1;
        }
    }
}
void copy_plansza(int p[][KOLUMNY], int c[][KOLUMNY]){
    for(int i = 0; i < KOLUMNY; i++){
        for(int j = 0; j < WIERSZE; j++){
            c[j][i] = p[j][i];
        }
    }
}
int ile_ruchow_prawego(int p[][KOLUMNY]){
    //Wylicz ile mozliwych ruchow ma prawy.
    int counter = 0;
    int copy_p[WIERSZE][KOLUMNY];
    char pole[2] = "aA";
    copy_plansza(p, copy_p);
    for(int i = 0; i < KOLUMNY; i++){
        for(int j = 0; j < WIERSZE; j++){
            pole[0] = (char) ('A'+i);
            pole[1] = (char) ('a'+j);
            if(czy_mozna_wykonac_prawy(pole, copy_p)){
                zapisz_ruch_prawego(pole, copy_p);
                counter++;
            }
        }
    }
    return counter;
}
int ile_ruchow_lewego(int p[][KOLUMNY]){
    //Wylicz ile mozliwych ruchow ma lewy.
    int counter = 0;
    int copy_p[WIERSZE][KOLUMNY];
    char pole[2] = "Aa";
    copy_plansza(p, copy_p);
    for(int i = 0; i < KOLUMNY; i++){
        for(int j = 0; j < WIERSZE; j++){
            pole[0] = (char) ('A'+i);
            pole[1] = (char) ('a'+j);
            if(czy_mozna_wykonac_lewy(pole, copy_p)){
                zapisz_ruch_lewego(pole, copy_p);
                counter++;
            }
        }
    }
    return counter;
}
int ocena_planszy(int p[][KOLUMNY]){
    return ile_ruchow_prawego(p) - ile_ruchow_lewego(p);
}
int find_max(int ile, int oceny[]){
    int max = -2137;
    for(int i = 0; i < ile; i++){
        if(max < oceny[i]){
            max = oceny[i];
        }
    }
    return max;
}
int find_n(int n, int m, int a[]){
    //Znajdz nty element o wartosci m.
    int counter = 0;
    int i = 0;
    while(counter < n){
        if(a[i] == m){
            counter++;
        }
        if(counter == n)return i;
        i++;
    }
    return i;
}
int ile_n(int n, int l, int a[]){
    //Ile elementow o wartosci n w tablicy a dlugosci l.
    int counter = 0;
    for(int i = 0; i < l; i++){
        if(a[i] == n)counter++;
    }
    return counter;
}
int ile_wszystkich_ruchow_prawego(int p[][KOLUMNY]){
    int counter = 0;
    char pole[2] = "Aa";
    for(int i = 0; i < KOLUMNY; i++){
        for(int j = 0; j < WIERSZE; j++){
            pole[0] = (char) ('A'+i);
            pole[1] = (char) ('a'+j);
            if(czy_mozna_wykonac_prawy(pole, p)){
                counter++;
            }
        }
    }
    return counter;
}
int ile_wszystkich_ruchow_lewego(int p[][KOLUMNY]){
    int counter = 0;
    char pole[2] = "Aa";
    for(int i = 0; i < KOLUMNY; i++){
        for(int j = 0; j < WIERSZE; j++){
            pole[0] = (char) ('A'+i);
            pole[1] = (char) ('a'+j);
            if(czy_mozna_wykonac_lewy(pole, p)){
                counter++;
            }
        }
    }
    return counter;
}
void generuj_ruchy(int oceny[], char ruchy[][2], int p[][KOLUMNY]){
    int counter = 0;
    int copy_p[WIERSZE][KOLUMNY];
    char pole[2] = "Aa";
    for(int i = 0; i < WIERSZE; i++){
        for(int j = 0; j < KOLUMNY; j++){
            pole[0] = (char) ('A' + j);
            pole[1] = (char) ('a' + i);
            copy_plansza(p, copy_p);
            if(czy_mozna_wykonac_prawy(pole, copy_p)){
                zapisz_ruch_prawego(pole, copy_p);
                oceny[counter] = ocena_planszy(copy_p);
                ruchy[counter][0] = pole[0];
                ruchy[counter][1] = pole[1];
                counter++;
            }
        }
    }
}
void najlepszy_ruch(char r[], int p[][KOLUMNY]){
    int ile = ile_wszystkich_ruchow_prawego(p) + 1;
    int oceny_kandydatow[676];
    for(int i = 0; i < ile;i++)oceny_kandydatow[i] = -2137;
    char kandydaci[676][2];
    generuj_ruchy(oceny_kandydatow, kandydaci, p);
    int max = find_max(ile, oceny_kandydatow);
    r[0] = kandydaci[find_n(WYBOR % ile_n(max, ile, oceny_kandydatow) + 1, max, oceny_kandydatow)][0];
    r[1] = kandydaci[find_n(WYBOR % ile_n(max, ile, oceny_kandydatow) + 1, max, oceny_kandydatow)][1];
    zapisz_ruch_prawego(r, p);
}
void odczytaj_ruch(char r[]){
    //Wczytaj ze stdin ruch lewego.
    int znak;
    znak = getchar();
    if(znak == '.'){
        r[0] = '.';
        r[1] = ' ';
        znak = getchar();
    }else if(znak == '-'){
        r[0] = '-';
        r[1] = ' ';
        znak = getchar();
    }else{
        r[0] = (char) znak;
        znak = getchar();
        r[1] = (char) znak;
        znak = getchar();
    }
}
int czy_poprawny(char r[]){
    if(r[0] == '.'){
        return 2;
    }else if(r[0] == '-'){
        return 1;
    }else{
        return 0;
    }
}
int ruch_lewego(char r[], int p[][KOLUMNY], int *stan){
    odczytaj_ruch(r);
    if(!czy_poprawny(r)){
        zapisz_ruch_lewego(r, p);
    }else{
        if(czy_poprawny(r) == 2){
            //Lewy sie poddal, stan gry 0 oznacza gre zakonczona
            *stan = 0;
            return 0;
        }
    }
    return 1;
}
void wykonaj_ruch(char r[], int p[][KOLUMNY], int *stan){
    //Umieszcza na planszy ruch lewego i wykonuje ruch prawego.
    if(ruch_lewego(r, p, stan)){
        //Znajdujemy ruch ktory ma najlepsza ocene pozycji
        if(ile_ruchow_prawego(p) == 0){
            printf(".\n");
            *stan = 0;
        }else{
            char ruch_p[2]; 
            najlepszy_ruch(ruch_p, p);
            printf("%c%c\n", ruch_p[1], ruch_p[0]);
        }
    }
}

//Tablica reprezentujaca plansze.
int plansza[WIERSZE][KOLUMNY];
//0 oznacza gre zakonczona, 1 oznacza trwajaca gre.
int gra_trwa = 1;

int main(){
    char ruch_l[2];
    zeruj_plansze(plansza);
    while(gra_trwa){
        wykonaj_ruch(ruch_l, plansza, &gra_trwa);
    }
    return 0;
}
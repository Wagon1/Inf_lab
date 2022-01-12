#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "napiernaf.h"


void iton(int x, int **a, int *n){
    if(x == INT_MAX){
        int *pom;
        pom = malloc((size_t) 2 * sizeof(int));
        pom[0] = -1;
        pom[1] = 31;
        *a = pom;
        *n = 2;
    }else if(x == INT_MIN){
        int pom[1] = {-32};
        *a = pom;
        *n = 1;
    }else{
        int np;
        int nm;
        int xh = x >> 1;
        int x3 = x + xh;
        int c = xh ^ x3;
        np = x3 & c;
        nm = xh & c;
        int len = __builtin_popcount((unsigned int) np) + __builtin_popcount((unsigned int) nm);
        int *naf; 
        naf = malloc((size_t) len * sizeof(int));
        int i = 0;
        int pot = 1;
        int wyk = 0;
        while(i < len){
            if((np & pot) >= 1){
                naf[i] = wyk;
                i++;
            }
            if((nm & pot) >= 1){
                naf[i] = -wyk-1;
                i++;
            }
            pot = pot * 2;
            wyk++;
        }
        *a = naf;
        *n = len;
    }
}

int ntoi(int *a, int n){
    int wsk = n - 1;
    int suma = 0;
    if(n == 0){
        return 0;
    }
    if(a[wsk] > 31 || a[wsk] < -32){
        return 0;
    }else{
        if(a[wsk] == 31){
            for(int i = wsk-1; i >= 0; i--){
                if(a[i] >= 0){
                    suma = suma + (1 << a[i]);
                }else{
                    suma = suma - (1 << -1*(a[i]+1));
                }
            }
            if(suma >= 0){
                return 0;
            }else{
                return INT_MAX + (int) suma + 1;
            }
        }else if(a[wsk] == -32){
            for(int i = wsk-1; i >= 0; i--){
                if(a[i] >= 0){
                    suma = suma + (1 << a[i]);
                }else{
                    suma = suma - (1 << -1*(a[i]+1));
                }
            }
            if(suma >= 0){
                return INT_MIN + (int) suma;
            }else{
                return 0;
            }
        }else{
            for(int i = wsk; i >= 0; i--){
                if(a[i] >= 0){
                    suma = suma + (1 << a[i]);
                }else{
                    suma = suma - (1 << -1*(a[i]+1));
                }
            }
        }
    }
    return (int) suma;
}

void usunzera(int **a, int *n){
    int counter = 0;
    for(int i = 0; i < *n; i++){
        if((*a)[i] != 0){
            counter++;
        }
    } 
    int *new;
    new = malloc((size_t) counter * sizeof(int));
    counter = 0;
    for(int i = 0; i < *n; i++){
        if((*a)[i] != 0){
            new[counter] = (*a)[i];
            counter++;
        }
    }
    free(*a);
    *a = new;
    *n = counter;
}

void skroctablice(int **a, int *n){
    int counter = 0;
    for(int i = 0; i < *n; i++){
        if((*a)[i] != 0){
            counter++;
        }
    } 
    int *new;
    new = malloc((size_t) counter * sizeof(int));
    counter = 0;
    for(int i = 0; i < *n; i++){
        if((*a)[i] != 0){
            if((*a)[i] < 0){
                new[counter] = (*a)[i];
            }else{
                new[counter] = (*a)[i] - 1;
            }
            counter++;
        }
    }
    free(*a);
    *a = new;
    *n = counter;
}

void mergetablice(int *a, int an, int *b, int bn, int **c, int *cn){
    int len = an + bn;
    int *new;
    new = malloc((size_t) len * sizeof(int));
    int acounter = 0;
    int bcounter = 0;
    for(int i = 0; i < len; i++){
        if(acounter < an){
            //mamy cos w a
            if(bcounter < bn){
                //mamy cos w a i b
                if(a[acounter] >= 0){
                    if(b[bcounter] >= 0){
                        //oba z +
                        if(a[acounter] == b[bcounter]){
                            new[i] = 0;
                            new[i+1] = a[acounter] + 2;
                            acounter++;
                            bcounter++;
                            i++;
                        }else if(a[acounter] > b[bcounter]){
                            new[i] = b[bcounter] + 1;
                            bcounter++;
                        }else{
                            new[i] = a[acounter] + 1;
                            acounter++;
                        }
                    }else{
                        //a + b -
                        if(a[acounter] + 1 ==    b[bcounter] * -1){
                            new[i] = 0;
                            new[i+1] = 0;
                            acounter++;
                            bcounter++;
                            i++;
                        }else if(a[acounter] + 1 > b[bcounter] * -1){
                            new[i] = b[bcounter];
                            bcounter++;
                        }else{
                            new[i] = a[acounter] + 1;
                            acounter++;
                        }
                    }
                }else{
                    if(b[bcounter] >= 0){
                        //a- b+
                        if(b[bcounter] + 1 == a[acounter] * -1){
                            new[i] = 0;
                            new[i+1] = 0;
                            acounter++;
                            bcounter++;
                            i++;
                        }else if(b[bcounter] + 1 > a[acounter] * -1){
                            new[i] = a[acounter];
                            acounter++;
                        }else{
                            new[i] = b[bcounter] + 1;
                            bcounter++;
                        }
                    }else{
                        //a- b-
                        if(a[acounter] == b[bcounter]){
                            new[i] = 0;
                            new[i+1] = a[acounter] - 1;
                            acounter++;
                            bcounter++;
                            i++;
                        }else if(a[acounter] > b[bcounter]){
                            new[i] = a[acounter];
                            acounter++;
                        }else{
                            new[i] = b[bcounter];
                            bcounter++;
                        }
                    }
                }
            }else{
                //nie ma nic w b bierzemy z a
                if(a[acounter] >= 0){
                    new[i] = a[acounter] + 1;
                }else{
                    new[i] = a[acounter];
                }
                acounter++;
            }
        }else{
            //nie ma nic w a bierzemy z b
            if(b[bcounter] >= 0){
                new[i] = b[bcounter] + 1;
            }else{
                new[i] = b[bcounter];
            }
            bcounter++;
        }
    }
    usunzera(&new, &len);
    *c = new;
    *cn = len;
}

void nadd(int *a, int an, int *b, int bn, int **c, int *cn){
    int *new;
    int len;
    mergetablice(a, an, b, bn, &new, &len);
    int counter = 0;
    while(counter < len - 1){
        if(abs(new[counter]) == abs(new[counter+1])){
            if(new[counter] < 0 && new[counter+1] < 0){
                new[counter] = 0;
                new[counter+1] = new[counter+1] - 1;
            }else if(new[counter] > 0 && new[counter + 1] > 0){
                new[counter] = 0;
                new[counter+1] = new[counter+1] + 1;
            }else{
                new[counter] = 0;
                new[counter+1] = 0;
            }
        }else if(abs(new[counter]) == abs(new[counter+1]) - 1){
            if(new[counter] < 0){
                if(new[counter+1] < 0){
                    new[counter] = new[counter] * -1;
                    new[counter + 1] = new[counter + 1] - 1;
                }else{
                    new[counter] = new[counter] * -1;
                    new[counter + 1] = 0;
                }
            }else{
                if(new[counter+1] < 0){
                    new[counter] = new[counter] * -1;
                    new[counter + 1] = 0;
                }else{
                    new[counter] = new[counter] * -1;
                    new[counter + 1] = new[counter + 1] + 1;
                }
            }
        }       
        counter++;

    }
    skroctablice(&new, &len);
    *c = new;
    *cn = len;
}

void nsub(int *a, int an, int *b, int bn, int **c, int *cn){
    int *new;
    new = malloc((size_t) bn * sizeof(int));
    for(int i = 0; i < bn; i++){
        new[i] = (b[i] + 1) * -1;
    }
    nadd(a, an, new, bn, c, cn);
    free(new);
}

void podzielprzezdwa(int **a, int *n){
    int *new;
    if((*a)[0] == 0){
        new = malloc((size_t) (*n - 1) * sizeof(int));
        for(int i = 0; i < *n - 1; i++){
            if((*a)[i+1] < 0){
                new[i] = (*a)[i+1] + 1;
            }else{
                new[i] = (*a)[i+1] - 1;
            }
        }
        free(*a);
        *a = new;
        *n = *n-1;
    }else if((*a)[0] == -1){
        new = malloc((size_t) (*n - 1) * sizeof(int));
        for(int i = 0; i < *n - 1; i++){
            if((*a)[i+1] < 0){
                new[i] = (*a)[i+1] + 1;
            }else{
                new[i] = (*a)[i+1] - 1;
            }
        }
        int *temp;
        int t;
        int one[] = {0};
        nsub(new, *n-1, one, 1, &temp, &t);
        free(*a);
        free(new);
        *a = temp;
        *n = t;
    }else{
        new = malloc((size_t) (*n) * sizeof(int));
        for(int i = 0; i < *n; i++){
            if((*a)[i] < 0){
                new[i] = (*a)[i] + 1;
            }else{
                new[i] = (*a)[i] - 1;
            }
        }
        free(*a);
        *a = new;
    }
    
}

void pomnozprzezdwa(int **a, int *n){
    int *new;
    new = malloc((size_t) (*n) * sizeof(int));
    for(int i = 0; i < *n; i++){
        if((*a)[i] < 0){
            new[i] = (*a)[i] - 1;
        }else{
            new[i] = (*a)[i] + 1;
        }
    }
    free(*a);
    *a = new;
    *n = *n;
}

void copya2b(int *a, int an, int **b, int *bn){
    int *new;
    new = malloc((size_t) an * sizeof(int));
    for(int i = 0; i < an; i++){
        new[i] = a[i];
    }
    free(*b);
    *b = new;
    *bn = an;
}

void nmul(int *a, int an, int *b, int bn, int **c, int *cn){
    if(an == 0 || bn == 0){
        *cn = 0;
    }else{
        int *copya = malloc((size_t) sizeof(int));
        int x;
        int *copyb = malloc((size_t) sizeof(int));
        int y;
        int *wynik = malloc((size_t) sizeof(int));;
        int w = 0;
        int *temp;
        int t;
        copya2b(a, an, &copya, &x);
        copya2b(b, bn, &copyb, &y);
        int znak;
        if(a[an-1] < 0){
            if(b[bn-1] < 0){
                znak = 1;
                for(int i = 0; i < bn; i++){
                    copyb[i] = (b[i] + 1) * -1;
                }
                for(int i = 0; i < an; i++){
                    copya[i] = (a[i] + 1) * -1;
                }
            }else{
                znak = -1;
                for(int i = 0; i < an; i++){
                    copya[i] = (a[i] + 1) * -1;
                }
            }
        }else{
            if(b[bn-1] < 0){
                znak = -1;
                for(int i = 0; i < bn; i++){
                    copyb[i] = (b[i] + 1) * -1;
                }
            }else{
                znak = 1;
            }
        }
        while(y != 0){
            if(copyb[0] == 0 || copyb[0] == -1){
                nadd(copya, x, wynik, w, &temp, &t);
                copya2b(temp, t, &wynik, &w);                
                free(temp);
            }
            pomnozprzezdwa(&copya, &x);
            podzielprzezdwa(&copyb, &y);
        }
        free(copya);
        free(copyb);
        if(znak == -1){
            for(int i = 0; i < w; i++){
                    wynik[i] = (wynik[i] + 1) * -1;
                }
        }
        *c = wynik;
        *cn = w;
    }
}

void nexp(int *a, int an, int *b, int bn, int **c, int *cn){
    int *copya = malloc((size_t) sizeof(int));
    int x;
    int *copyb = malloc((size_t) sizeof(int));
    int y;
    int *wynik;
    int w = 0;
    int *temp;
    int t;
    copya2b(a, an, &copya, &x);
    copya2b(b, bn, &copyb, &y);
    iton(1, &wynik, &w);
    while(y > 0){
        if(copyb[0] == 0 || copyb[0] == -1){
            nmul(wynik, w, copya, x, &temp, &t);
            copya2b(temp, t, &wynik, &w);                
            free(temp);
        }
        nmul(copya, x, copya, x, &temp, &t);
        copya2b(temp, t, &copya, &x);                
        free(temp);
        podzielprzezdwa(&copyb, &y);
    }
    free(copya);
    free(copyb);
    *c = wynik;
    *cn = w;
}

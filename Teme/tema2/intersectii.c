#include "intersectii.h"
// pentru qsort
#include <stdlib.h>

// functie ajutatoare
void afiseaza_lista_intervale(ListaIntervale2D *lista) {
    int i;
    for(i = 0; i < lista->dimensiune; i++) {
        Interval2D *interv = lista->intervale[i];
        printf("{punct stanga x: %d, punct stanga y: %d, punct dreapta x: %d, punct dreapta y: %d}\n",
                    interv->punct_stanga->x, interv->punct_stanga->y,
                    interv->punct_dreapta->x, interv->punct_dreapta->y);
    }
}


ListaIntervale2D* citeste_intrare(char *nume_fisier_intrare) {
    ListaIntervale2D *lista = malloc(sizeof(ListaIntervale2D));
    if (!lista)
        exit(1);

    FILE *file = fopen(nume_fisier_intrare, "rt");
    if (!file)
        exit(1);

    fscanf(file, "%d", &lista->dimensiune);
    lista->intervale = malloc(sizeof(Interval2D*) * lista->dimensiune);
    if (!lista->intervale)
        exit(1);

    int i;
    // pointer auxiliar pentru a nu ingramadi liniile
    Interval2D **l = lista->intervale;
    for(i = 0; i < lista->dimensiune; i++){
        l[i] = (Interval2D*)malloc(sizeof(Interval2D));
        l[i]->punct_dreapta = (Punct2D*)malloc(sizeof(Punct2D));
        l[i]->punct_stanga = (Punct2D*)malloc(sizeof(Punct2D));

        fscanf(file, "%d %d", &l[i]->punct_stanga->x, &l[i]->punct_stanga->y);
        fscanf(file, " %d %d", &l[i]->punct_dreapta->x, &l[i]->punct_dreapta->y);
    }

    return lista;
}

// ! Functie pentru actualizarea in arbore
// ! O veti da ca parametru cand initializati arborele
void actualizare_cu_delta(Nod *nod, int v2) {
    nod->info += v2;
}

// ! Functie pentru combinarea raspunsurilor in arbore
// ! O veti da ca parametru cand initializati arborele
int suma_raspunsurilor(int r1, int r2) {
    return r1 + r2;
}

// functie care verifica daca un interval e orizontal
int is_horizontal(Interval2D* interval) {
    return interval->punct_stanga->y == interval->punct_dreapta->y;
}

// index-ul reprezinta index-ul intervalului din care face parte, indexarea
// incepe de la 0
// type este 0 daca e capat stanga si 1 daca e capat dreapta
typedef struct punct2D {
    int x;
    int y;
    int index;
    int type;
} Punct;

// functie de compare pentru qsort, verifica ordinea dintre structuri de tip
// Punct in functie de coordonata x
int comparepoints(const void *a, const void *b) {
    int xpoint_a = ((Punct *)a)->x; 
    int xpoint_b = ((Punct *)b)->x; 
    return (xpoint_a - xpoint_b);
}

int calculeaza_numar_intersectii(ListaIntervale2D *lista) {
    int y_max = 0, i, intersection_num = 0, dim = lista->dimensiune;
    Interval2D** l = lista->intervale;
    for(i = 0; i < dim; i++) {
        if (l[i]->punct_dreapta->y > y_max) {
            y_max = l[i]->punct_dreapta->y;
        }
    }

    ArboreDeIntervale *arbore = construieste_arbore(0, y_max, 0, 
                                    actualizare_cu_delta, suma_raspunsurilor);

    // 2 puncte per interval => 2 * interval puncte
    // cum stiu exact numarul de elemente si nu o sa adaug sau o sa scot
    // elemente din vector este in beneficiul meu sa aloc static
    Punct puncte[dim * 2];

    // adaug punctele in vectorul de structuri
    for(i = 0; i < dim; i++) {
        puncte[2 * i].x = l[i]->punct_stanga->x;
        puncte[2 * i].y = l[i]->punct_stanga->y;
        puncte[2 * i + 1].x = l[i]->punct_dreapta->x;
        puncte[2 * i + 1].y = l[i]->punct_dreapta->y;

        puncte[2 * i].index = i;
        puncte[2 * i].type = 0;
        puncte[2 * i + 1].index = i;
        puncte[2 * i + 1].type = 1;
    }

    // sortez un vector alocat static cu qsort si functia compare de mai sus
    qsort (puncte, dim * 2, sizeof(Punct), comparepoints);

    for(i = 0; i < dim * 2; i++) {
        Interval* interval = (Interval*)malloc(sizeof(Interval));
        if (!interval)
            exit(1);
        
        interval->capat_stanga = puncte[i].y;

        // daca e orizontal fac actualizare cu 1 pt capat stanga si cu -1 pt
        // capat dreapta
        // daca e vertical atunci capatul dreapta al intervalului va fi
        // cel al urmatorului punct crescator(puncte din acelasi interval
        // vertical sunt consecutive)
        if (is_horizontal(l[puncte[i].index])) {
            interval->capat_dreapta = puncte[i].y;

            if (puncte[i].type == 0) {
                actualizare_interval_in_arbore(arbore, interval, 1);
            } else {
                actualizare_interval_in_arbore(arbore, interval, -1);
            }
        } else {
            // iau celalalt capat al intervalului vertical
            interval->capat_dreapta = puncte[i + 1].y;

            int num = interogare_interval_in_arbore(arbore, interval);
            intersection_num += num;

            // sar peste celalalt capat al intervalului vertical
            i++;
        }

        free(interval);
    }

    return intersection_num;
}

// strcmp, dar pentru caractere
int ccmp(char a, char b) {
    return (int)a - (int)b;
}

// functie care verifica apartenenta unui numar la un interval inchis la capete
int contain(int x, int a, int b) {
    if(a <= x && x <= b)
        return 1;

    return 0;
}

// verifica daca o coordonata a unui punct se afla intre 2 coordonate de punct
// in functie de axa precizata in parametru
int it_contains(Interval2D **l, int i, int j, char axis) {
    if (!ccmp(axis, 'y')) {
        return contain(l[i]->punct_dreapta->y, l[j]->punct_stanga->y, 
                                                        l[j]->punct_dreapta->y);

    } else {
        return contain(l[i]->punct_dreapta->x, l[j]->punct_stanga->x, 
                                                        l[j]->punct_dreapta->x);

    }
}

// verific intersectia dintre 2 intervale fara repetari
int calculeaza_numar_intersectii_trivial(ListaIntervale2D *lista) {
    int i, j, intersection_num = 0;
    Interval2D **l = lista->intervale;

    for(i = 0; i < lista->dimensiune; i++) {
        int is_i_horizontal = is_horizontal(l[i]);

        for(j = i + 1; j < lista->dimensiune; j++) {
            int is_j_horizontal = is_horizontal(l[j]);

            if(is_i_horizontal && !is_j_horizontal) {
                // verific daca au un punct comun
                if (it_contains(l, i, j, 'y') && it_contains(l, j, i, 'x')) {
                    intersection_num++;
                }

            } else if (!is_i_horizontal && is_j_horizontal) {
                if (it_contains(l, j, i, 'y') && it_contains(l, i, j, 'x')) {
                    intersection_num++;
                }

            }
        }
    }

    return intersection_num;
}

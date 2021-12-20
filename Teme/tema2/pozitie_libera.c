#include "pozitie_libera.h"
// pentru INT_MAX
#include<limits.h> 


DateIntrare* citeste_fisier_in(char *nume_fisier_intrare) {
    DateIntrare* date = (DateIntrare*)malloc(sizeof(DateIntrare));
    if (!date)
    	exit(1);

    FILE* file = fopen(nume_fisier_intrare, "rt");
    if (!file)
    	exit(1);

    fscanf(file, "%d", &date->numarul_maxim_din_intrari);
    fscanf(file, " %d", &date->numar_intrari);

    date->intrari = (int*)malloc(sizeof(int) * date->numar_intrari);
    if (!date->intrari)
    	exit(1);

    int i;
    for(i = 0; i < date->numar_intrari; i++) {
    	fscanf(file, "%d", &date->intrari[i]);
    }

    return date;
}

// o sa fie cazuri in care a sau b este negativ, caz in care o sa prefer
// valoarea negativa in detrimentul lui 0 care este starea default
int min(int a, int b) {
	if (a == 0)
		return b;

	if (b == 0)
		return a;

	if (a < b)
		return a;

	return b;
}

int este_frunza(Nod* nod) {
	if (nod->interval->capat_stanga == nod->interval->capat_dreapta)
		return 1;

	return 0;
}

void actualizare_copii(Nod* nod) {
	nod->copil_stanga->info = nod->info;
	nod->copil_dreapta->info = nod->info;
}

void actualizare_poz(Nod* nod, int poz_act) {
	// primul IF folosit pentru poz_act > 1
	if (poz_act > 1 && !este_frunza(nod)) {
		int nod_length;
		nod_length = nod->interval->capat_dreapta - nod->interval->capat_stanga;

		// nod_length este o limita superioara pentru stramosii care au voie
		// sa-si modifice copiii
		if (nod_length <= 3 * (poz_act - 1)) {
			actualizare_copii(nod);
		}

		return;
	} else if (poz_act > 1) {
		return;
	}

	// al doilea IF folosit pentru poz_act = +/- 1
	if (nod->info != 0) {
		// actualizare nod deja initializat in functie de poz_act
		nod->info += poz_act;

		// pentru a nu confunda cu default(0), ce a devenit 0 dupa adaugare
		// de poz_act devine -1(in general pentru poz_act = -1)
		if (nod->info == 0) {
			nod->info = -1;
		}
	} else {
		// initializare nod
		nod->info = nod->interval->capat_dreapta;
	}
}

int* calculeaza_vector_raspuns(DateIntrare *date_intrare) {
	int nr_max = date_intrare->numarul_maxim_din_intrari;
	int* list = calloc(sizeof(int), nr_max + 1);
    if (!list)
    	exit(1);

    ArboreDeIntervale *arbore;
    arbore = construieste_arbore(1, nr_max, 0, actualizare_poz, min);

    int i;
    for(i = 0; i < date_intrare->numar_intrari; i++) {
    	Interval* interval = (Interval*)malloc(sizeof(Interval));
        if (!interval)
            exit(1);

        interval->capat_stanga = date_intrare->intrari[i];
        interval->capat_dreapta = date_intrare->intrari[i];

    	actualizare_interval_in_arbore(arbore, interval, -1);

    	int num = interogare_interval_in_arbore(arbore, interval);

    	// daca trebuie introdus pe pozitia 0 va avea o valoare negativa
    	if (num < 0)
    		num = 0;

    	// daca locul gasit in urma interogarii nu e ocupat il adaug
    	// altfel o sa tot fac interogari pana gasesc un loc liber
    	if (list[num] == 0) {
    		list[num] = date_intrare->intrari[i];
    	} else {
    		// inlocuiesc valoarea frunzelor cu cele ale stramosilor de la
    		// cel mai apropiat la cel mai indepartat pana gasesc un loc liber
    		// sau frunza are pozitia 1
    		int j = 2;
    		while (list[num] != 0 && num > 1) {
    			actualizare_interval_in_arbore(arbore, interval, j);
    			num = interogare_interval_in_arbore(arbore, interval);

    			j++;
    		}

    		// daca s-a gasit un loc liber se va ocupa altfel se readuce
    		// arborele la forma initiala
    		if (list[num] == 0) {
    			list[num] = date_intrare->intrari[i];
    		} else if (list[0] == 0) {
    			list[0] = date_intrare->intrari[i];
    		} else {
    			actualizare_interval_in_arbore(arbore, interval, +1);
    		}
    	}

    	free(interval);
    }

    return list;
}

int* calculeaza_vector_raspuns_trivial(DateIntrare *date_intrare) {
	int nr_max = date_intrare->numarul_maxim_din_intrari;
    int* list = calloc(sizeof(int), nr_max + 1);
    if (!list)
    	exit(1);

    int i, j;
    for(i = 0; i < date_intrare->numar_intrari; i++) {
    	if (list[date_intrare->intrari[i]] == 0) {
    		list[date_intrare->intrari[i]] = date_intrare->intrari[i];
    	} else {
    		for(j = date_intrare->intrari[i] - 1; j >= 0; j--) {
    			if (list[j] == 0) {
    				list[j] = date_intrare->intrari[i];
    				break;
    			}
    		}
    	}
    }

    return list;
}
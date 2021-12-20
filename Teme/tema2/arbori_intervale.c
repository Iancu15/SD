#include "arbori_intervale.h"

// functie auxiliara pentru crearea arborelui din construieste_arbore
Nod *create_tree(int left, int right, int *dimension) {
	Nod *nod = (Nod*)malloc(sizeof(Nod));
	if (!nod) 
		exit(1);

	nod->interval = (Interval*)malloc(sizeof(Interval));
	if (!nod->interval)
		exit(1);

	nod->info = 0;
	nod->interval->capat_stanga = left;
	nod->interval->capat_dreapta = right;

	*dimension = *dimension + 1;
	if (left < right) {
		int mid = (left + right) / 2;

		nod->copil_stanga = create_tree(left, mid, dimension);
		nod->copil_dreapta = create_tree(mid + 1, right, dimension);
	}

	return nod;
}

// pentru debug
void afisare_arbore(Nod* nod){
	if(nod == NULL)
		return;

	afisare_arbore(nod->copil_stanga);

	printf("%d %d %d\n", nod->interval->capat_stanga, 
									nod->interval->capat_dreapta, nod->info);

	afisare_arbore(nod->copil_dreapta);
}

ArboreDeIntervale *construieste_arbore(int capat_stanga, int capat_dreapta,
        int valoare_predifinita_raspuns_copil,
        void (*f_actualizare)(Nod *nod, int v_actualizare),
        int (*f_combinare_raspunsuri_copii)(int raspuns_stanga, int raspuns_dreapta)) {
    
    ArboreDeIntervale *arbore = malloc(sizeof(ArboreDeIntervale));
    if (!arbore)
    	exit(1);
    
    arbore->f_actualizare = f_actualizare;
    arbore->f_combinare_raspunsuri_copii = f_combinare_raspunsuri_copii;
    arbore->valoare_predifinita_raspuns_copil = 0;

    // initializez dimensiunea arborelui cu 0 si returnez dimensiunea prin
    // parametru, incrementand ajutandu-ma de adresa
    arbore->dimensiune = 0;
    int *p_dim = &arbore->dimensiune;
    arbore->radacina = create_tree(capat_stanga, capat_dreapta, p_dim);

    return arbore;
}

// actualizez nod-ul la fiecare apel recursiv si cand s-a gasit un nod
// cu intervalul ce respecta limitele impuse de parametru se iese
// daca nodul e NULL se iese
void actualizare_interval_pentru_nod(ArboreDeIntervale *arbore, Nod *nod,
                                        Interval *interval, int v_actualizare) {
	if(nod == NULL)
		return;

	arbore->f_actualizare(nod, v_actualizare);

	// variabile auxiliare pentru a nu ingramadi conditiile
	int interval_left = interval->capat_stanga;
	int nod_left = nod->interval->capat_stanga;
	int nod_right = nod->interval->capat_dreapta;
	int interval_right = interval->capat_dreapta;

	if (interval_left <= nod_left && nod_right <= interval_right)
		return;
		
	int mid = (nod->interval->capat_stanga + nod->interval->capat_dreapta) / 2;

	if (interval_left <= mid) {
		Nod *left = nod->copil_stanga;
		actualizare_interval_pentru_nod(arbore, left, interval, v_actualizare);
	}

	if (interval_right > mid) {
		Nod *right = nod->copil_dreapta;
        actualizare_interval_pentru_nod(arbore, right, interval, v_actualizare);
	}

}


// Functia este deja implementata, se cheama functia de mai sus cu radacina arborelui
void actualizare_interval_in_arbore(ArboreDeIntervale *arbore, 
                                        Interval *interval, int v_actualizare) {
    actualizare_interval_pentru_nod(arbore, arbore->radacina, interval, v_actualizare);
}


int interogare_interval_pentru_nod(ArboreDeIntervale *arbore, Nod *nod, Interval *interval) {
	if (nod == NULL)
		return 0;

    if (interval->capat_stanga <= nod->interval->capat_stanga && 
					nod->interval->capat_dreapta <= interval->capat_dreapta){
		return nod->info;
	}

	int mid = (nod->interval->capat_stanga + nod->interval->capat_dreapta) / 2;
	int left_v = 0, right_v = 0;

	if (interval->capat_stanga <= mid) {
		Nod *left = nod->copil_stanga;
		left_v = interogare_interval_pentru_nod(arbore, left, interval);
	}

	if (interval->capat_dreapta > mid){
		Nod *right = nod->copil_dreapta;
        right_v = interogare_interval_pentru_nod(arbore, right, interval);
	}

	return arbore->f_combinare_raspunsuri_copii(left_v, right_v);
}


// Functia este deja implementata, se cheama functia de mai sus cu radacina arborelui
int interogare_interval_in_arbore(ArboreDeIntervale *arbore, Interval *interval) {
    return interogare_interval_pentru_nod(arbore, arbore->radacina, interval);
}


// ----- DOAR pentru bonus si DOAR daca considerati ca e necesara ----- //
// am construit eu propria mea functie in pozitie_libera.c
void seteaza_info_in_nod_la_valoare_capat_dreapta(Nod* nod) {
    // TODO cred ca e destul de clar ce vrea sa faca functia asta
}


void seteaza_info_in_arbore_la_valoare_capat_dreapta(ArboreDeIntervale* arbore) {
    seteaza_info_in_nod_la_valoare_capat_dreapta(arbore->radacina);
}
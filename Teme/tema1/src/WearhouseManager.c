#include <stdio.h>
#include "WearhouseManager.h"


Package *create_package(long priority, const char* destination) {
    Package* pack = (Package*)malloc(sizeof(Package));

    if (!pack)
        exit(1);
    pack->priority = priority;

    if (destination == NULL){
        pack->destination = NULL;
    }
    else{
        // nu pot face sizeof(destination) pentru ca malloc are
        // nevoie de sizeof(char), nu de sizeof(char*)
        pack->destination = (char*)calloc(1, strlen(destination)+1);
        if (!pack->destination)
            exit(1);
        strcpy(pack->destination, destination);
    }

    return pack;
}

void destroy_package(Package* package) {
    free(package->destination);
    free(package);
}

Manifest* create_manifest_node(void) {
    Manifest* manifest = (Manifest*)malloc(sizeof(Manifest));
    if (!manifest)
        exit(1);

    manifest->package = NULL;
    manifest->next = NULL;
    manifest->prev = NULL;
    return manifest;
}

void destroy_manifest_node(Manifest* manifest_node) {
    if (manifest_node->package != NULL)
        destroy_package(manifest_node->package);

    free(manifest_node);
}

Wearhouse* create_wearhouse(long capacity) {
    Wearhouse* wearhouse;
    if (capacity == 0){
        wearhouse = NULL;
        return wearhouse;
    }

    wearhouse = (Wearhouse*)malloc(sizeof(Wearhouse));
    if (!wearhouse)
        exit(1);

    wearhouse->packages = malloc(sizeof(Package*) * capacity);
    if (!wearhouse->packages)
        exit(1);
    
    wearhouse->capacity = capacity;
    wearhouse->size = 0;
    return wearhouse;
}

Wearhouse *open_wearhouse(const char* file_path) {
    ssize_t read_size;
    char* line = NULL;
    size_t len = 0;
    char* token = NULL;
    Wearhouse *w = NULL;


    FILE *fp = fopen(file_path, "r");
    if(fp == NULL)
        goto file_open_exception;

    if((read_size = getline(&line, &len, fp)) != -1){
        token = strtok(line, ",\n ");
        w = create_wearhouse(atol(token));

        free(line);
        line = NULL;
        len = 0;
    }

    while((read_size = getline(&line, &len, fp)) != -1){
        token = strtok(line, ",\n ");
        long priority = atol(token);
        token = strtok(NULL, ",\n ");
        Package *p = create_package(priority, token);
        w->packages[w->size++] = p;

        free(line);
        line = NULL;
        len = 0;
    }

    free(line);


    fclose(fp);
    return w;

    file_open_exception:
    return NULL;
}

long wearhouse_is_empty(Wearhouse *w) {
    if (w->size == 0)
        return 1;
    return 0;
}

long wearhouse_is_full(Wearhouse *w) {
    if (w->size == w->capacity)
        return 1;
    return 0;
}

long wearhouse_max_package_priority(Wearhouse *w) {
    if (w->size == 0)
        return 0;

    int i, max = w->packages[0]->priority;
    for(i = 1; i < w->size; i++){
        if (w->packages[i]->priority > max){
            max = w->packages[i]->priority;
        }
    }

    return max;
}

long wearhouse_min_package_priority(Wearhouse *w) {
    if(w->size == 0)
        return 0;

    int i,min = w->packages[0]->priority;
    for(i=1; i<w->size; i++){
        if(w->packages[i]->priority < min){
            min = w->packages[i]->priority;
        }
    }

    return min;
}


void wearhouse_print_packages_info(Wearhouse *w) {
    for(long i = 0; i < w->size; i++){
        printf("P: %ld %s\n",
                w->packages[i]->priority,
                w->packages[i]->destination);
    }
    printf("\n");
}

void destroy_wearhouse(Wearhouse* wearhouse) {
    int i;
    for(i = 0; i < wearhouse->size; i++){
        destroy_package(wearhouse->packages[i]);
    }

    free(wearhouse->packages);
    free(wearhouse);
}


Robot* create_robot(long capacity) {
    Robot* robot;
    robot = (Robot*)malloc(sizeof(Robot));
    if (!robot)
        exit(1);
    robot->manifest = NULL;
    robot->next = NULL;
    robot->capacity = capacity;
    robot->size = 0;
    return robot;
}

int robot_is_full(Robot* robot) {
    if (robot->size==robot->capacity)
        return 1;
    return 0;
}

int robot_is_empty(Robot* robot) {
    if (robot->size==0)
        return 1;
    return 0;
}

Package* robot_get_wearhouse_priority_package(Wearhouse *w, long priority) {
    int i;
    for(i=0; i<w->size; i++){
        if(w->packages[i]->priority==priority){
            return w->packages[i];
        }
    }

    return NULL;
}

void robot_remove_wearhouse_package(Wearhouse *w, Package* package) {
    if(w->size == 0)
        return;

    int i,j;
    for(i = 0; i < w->size; i++){
        if(w->packages[i] == package){

            // mut mai la stanga toti vectorii dupa pachetul eliminat
            // pentru a umple golul lasat de acesta
            for(j = i; j < w->size-1; j++){
                w->packages[j] = w->packages[j+1];
            }

            // ies din instructiunea repetitiva sa nu se atinga de pachete
            // duplicat
            break;
        }
    }

    w->size--;
}

void robot_load_one_package(Robot* robot, Package* package) {
    if (robot->size==robot->capacity)
        return;

    int boolean, statement;
    Manifest* newpackage = create_manifest_node();
    newpackage->package = package;
    if (robot->size == 0){
        robot->manifest = newpackage;
        robot->size++;
        return;
    }
    Manifest* p = robot->manifest;

    // cat timp nu s-a gasit un pachet cu prioritatea cel mult egala
    // se parcurge manifestul
    while(p->next != NULL && p->package->priority > package->priority){
        p = p->next;
    }

    // dupa in cazul in care s-a oprit while-ul precedent pentru ca pachetul
    // gasit avea prioritatea egala, atunci cat timp nu s-a gasit un pachet
    // cu destinatia 'alfabetic mai mare sau egala' se parcurge manifestul
    boolean = strcmp(p->package->destination, package->destination);
    if (p->package->priority == package->priority && p->next != NULL){
        while(p->next != NULL && (boolean < 0)){
            p = p->next;
            boolean=strcmp(p->package->destination, package->destination);
        }
    }

    // cele 4 cazuri dupa care ma orientez daca pun pachetul intainte sau dupa
    // cel curent(p)
    if (p->package->priority == package->priority){
        if (boolean < 0){
            statement = 1;
        } else {
            statement = 2;
        }
    } else {
        if (p->package->priority > package->priority){
            statement = 0;
        } else{
            statement = -1;
        }
    }

    // cazurile sunt cele uzuale pentru liste, dar conditiile modificate sa
    // satisfaca situatia curenta
    // in if verific daca elementul trebuie pus inaintea primului element
    // in else if verific daca elementul trebuie pus dupa ulimul element
    // alegerile facute avand ca referinta faptul ca prioritatea e descrescatoare
    // si destinatia este lexicografic   crescatoare
    // la else sunt toate celelalte cazuri care sunt la mijloc si se vor pune
    // mereu inaintea lui p(stanga) datorita condiitilor atent alese in while-uri
    if (p->prev == NULL && (statement == 2 || statement == -1)){
        p->prev = newpackage;
        newpackage->next = p;
        newpackage->prev = NULL;
        robot->manifest = newpackage;
    } else if (p->next == NULL && (statement == 1 || statement == 0)){
        p->next = newpackage;
        newpackage->prev = p;
        newpackage->next = NULL;
    } else {
        newpackage->next = p;
        newpackage->prev = p->prev;
        p->prev->next = newpackage;
        p->prev = newpackage;
    }

    robot->size++;
}

long robot_load_packages(Wearhouse* wearhouse, Robot* robot) {
    long top_p;
    Package* package_to_load;
    int loaded_packages = 0;

    while(robot->size != robot->capacity && wearhouse->size != 0){
        top_p = wearhouse_max_package_priority(wearhouse);
        package_to_load = robot_get_wearhouse_priority_package(wearhouse, top_p);

        robot_load_one_package(robot, package_to_load);
        robot_remove_wearhouse_package(wearhouse, package_to_load);

        loaded_packages++;
    }

    return loaded_packages++;
}

Package* robot_get_destination_highest_priority_package(Robot* robot, const char* destination){
    if(robot->size == 0)
        return NULL;

    Manifest* p = robot->manifest;
    // cum prioritatea este descrescator ordonata in robot, atunci automat
    // primul element cu destinatia egala cu cea din parametru va fi cel
    // cu prioritatea cea mai mare aferent destinatiei
    while(p->next!=NULL){
        if (!strcmp(p->package->destination, destination))
            return p->package;
        p = p->next;
    }

    // iese din while la ultimul element, testez si ultimul element
    if (!strcmp(p->package->destination, destination))
        return p->package;

    return NULL;
}

void destroy_robot(Robot* robot){
    if(robot==NULL)
        return;

    robot->next=NULL;

    if(robot->size == 0 || robot->manifest == NULL){
        free(robot);
        return;
    }

    // distrug toate nodurile in ordine
    Manifest* mpack = robot->manifest;
    Manifest* m_temp;
    while(mpack != NULL){
        m_temp = mpack;
        mpack = mpack->next;
        destroy_manifest_node(m_temp);
    }
    robot->manifest=NULL;

    free(robot);
}

void robot_unload_packages(Truck* truck, Robot* robot) {
    if(truck->capacity == 0 || truck == NULL)
        return;
    if(robot->manifest == NULL || robot == NULL)
        return;

    Manifest* mpack=robot->manifest;
    Manifest* cpypack;

    while(mpack != NULL && truck->size < truck->capacity && robot->size > 0){
        // o sa modific mpack->next asa ca am nevoie de un pointer la urmatorul
        // element din manifest
        cpypack = mpack->next;

        if (!strcmp(mpack->package->destination, truck->destination)){

            // nu e nevoie de mpack->next!=NULL la conditia while-ului de mai sus
            // pentru ca verific intai pt cazuri de mpack->prev si p->next NULL
            // astfel mpack->prev->next si mpack->next->prev sigur nu va
            // da segfault

            // doar tai legaturile, nu-mi pasa de altceva ca am salvat nodul
            // de manifest in mpack
            if (mpack->prev == NULL){
                robot->manifest = robot->manifest->next;
                // in cazul in care mai e doar un singur element in manifest
                // cum robot->manifest->next va fi NULL in acea situatie
                // atunci robot->manifest va deveni NULL => robot->manifest->prev
                // va da segfault, acopar acest caz mai jos
                if (robot->manifest != NULL){
                    robot->manifest->prev = NULL;
                }
            } else if (mpack->next==NULL){
                mpack->prev->next=NULL;
            } else {
                mpack->prev->next = mpack->next;
                mpack->next->prev = mpack->prev;
            }

            // adaug elementul in truck drept head daca n-am elemente sau
            // in locul headului daca am elemente
            if (truck->manifest == NULL && truck->size == 0){
                truck->manifest = mpack;
                truck->manifest->next = NULL;
            } else{
                truck->manifest->prev = mpack;
                mpack->next = truck->manifest;
                truck->manifest = mpack;
                mpack->prev = NULL;
            }

            truck->size++;
            robot->size--;
        }

        // folosesc pointer-ul salvat la mpack->next sa parcurg while-ului
        mpack = cpypack;
    }
}



// Attach to specific truck
int robot_attach_find_truck(Robot* robot, Parkinglot *parkinglot){
    int found_truck = 0;
    long size = 0;
    Truck *arrived_iterator = parkinglot->arrived_trucks->next;
    Manifest* m_iterator = robot->manifest;


    while(m_iterator != NULL){
        while(arrived_iterator != parkinglot->arrived_trucks){
            size  = truck_destination_robots_unloading_size(arrived_iterator);
            if(strncmp(m_iterator->package->destination, arrived_iterator->destination, MAX_DESTINATION_NAME_LEN) == 0 &&
                    size < (arrived_iterator->capacity-arrived_iterator->size)){
                found_truck = 1;
                break;
            }

            arrived_iterator = arrived_iterator->next;
        }

        if(found_truck)
            break;
        m_iterator = m_iterator->next;
    }

    if(found_truck == 0)
        return 0;


    Robot* prevr_iterator = NULL;
    Robot* r_iterator = arrived_iterator->unloading_robots;
    while(r_iterator != NULL){
        Package *pkg = robot_get_destination_highest_priority_package(r_iterator, m_iterator->package->destination);
        if(m_iterator->package->priority >= pkg->priority)
            break;
        prevr_iterator = r_iterator;
        r_iterator = r_iterator->next;
    }

    robot->next = r_iterator;
    if(prevr_iterator == NULL)
        arrived_iterator->unloading_robots = robot;
    else
        prevr_iterator->next = robot;

    return 1;
}

void robot_print_manifest_info(Robot* robot){
    Manifest *iterator = robot->manifest;
    while(iterator != NULL){
        printf(" R->P: %s %ld\n", iterator->package->destination, iterator->package->priority);
        iterator = iterator->next;
    }

    printf("\n");
}



Truck* create_truck(const char* destination, long capacity, long transit_time, long departure_time) {
    Truck* truck=(Truck*)malloc(sizeof(Truck));
    if(!truck)
        exit(1);

    truck->next = NULL;
    truck->manifest = NULL;
    truck->unloading_robots = NULL;

    if (destination == NULL){
        truck->destination=NULL;
    }else {
        truck->destination = (char*)malloc(strlen(destination)+1);
        if (!truck->destination)
            exit(1);

        strcpy(truck->destination, destination);
    }

    truck->transit_end_time = transit_time;
    truck->in_transit_time = 0;
    truck->departure_time = departure_time;
    truck->capacity = capacity;
    truck->size = 0;

    return truck;
}

int truck_is_full(Truck *truck) {
    if(truck->capacity == truck->size)
        return 1;

    return 0;
}

int truck_is_empty(Truck *truck){
    if(truck->size == 0)
        return 1;

    return 0;
}

long truck_destination_robots_unloading_size(Truck* truck) {
    if (truck->unloading_robots == NULL)
        return 0;
    if (truck->unloading_robots->manifest == NULL)
        return 0;

    Robot* p = truck->unloading_robots;
    Manifest* mpack;
    long nr_to_unload=0;

    // nu e problematica abordarea p!=NULL pt ca nu folosesc p->next in while
    // pentru altceva inafara de rolul sau ca instrument de iteratie
    while(p != NULL){
        if(p->manifest != NULL){
            mpack = p->manifest;

            while(mpack != NULL){
                if(strcmp(mpack->package->destination, truck->destination) == 0){
                    nr_to_unload += p->size;
                }

                mpack = mpack->next;
            }
        }

        p = p->next;
    }

    return nr_to_unload;
}

void truck_print_info(Truck* truck){
    printf("T: %s %ld %ld %ld %ld %ld\n", truck->destination, truck->size, truck->capacity,
            truck->in_transit_time, truck->transit_end_time, truck->departure_time);

    Manifest* m_iterator = truck->manifest;
    while(m_iterator != NULL){
        printf(" T->P: %s %ld\n", m_iterator->package->destination, m_iterator->package->priority);
        m_iterator = m_iterator->next;
    }

    Robot* r_iterator = truck->unloading_robots;
    while(r_iterator != NULL){
        printf(" T->R: %ld %ld\n", r_iterator->size, r_iterator->capacity);
        robot_print_manifest_info(r_iterator);
        r_iterator = r_iterator->next;
    }
}


void destroy_truck(Truck* truck) {
    if (truck->destination != NULL)
        free(truck->destination);
    truck->next = NULL;

    // ambele while-uri facute pe acelasi principiu ca distrugerea de noduri
    // de tip manifest de la destroy_robot()
    // doar n-am mai verificat ca manifestul si robotii sunt nuli la inceput
    // ca ar fi necesitat mai mult scris si mai multe cazuri
    Manifest* mpack = truck->manifest;
    Manifest* m_temp;

    while(mpack != NULL){
        m_temp = mpack;
        mpack = mpack->next;
        destroy_manifest_node(m_temp);
    }
    truck->manifest = NULL;

    Robot* p = truck->unloading_robots;
    Robot* temp;

    while(p != NULL){
        temp = p;
        p = p->next;
        destroy_robot(temp);
    }
    truck->unloading_robots = NULL;

    free(truck);
}

Parkinglot* create_parkinglot(void) {
    Parkinglot* parkinglot = (Parkinglot*)malloc(sizeof(Parkinglot));
    if(!parkinglot)
        exit(1);

    parkinglot->arrived_trucks = (Truck*)malloc(sizeof(Truck));
    if (!parkinglot->arrived_trucks)
        exit(1);
    parkinglot->arrived_trucks->next = parkinglot->arrived_trucks;

    parkinglot->departed_trucks = (Truck*)malloc(sizeof(Truck));
    if (!parkinglot->departed_trucks)
        exit(1);
    parkinglot->departed_trucks->next = parkinglot->departed_trucks;

    parkinglot->pending_robots = (Robot*)malloc(sizeof(Robot));
    if (!parkinglot->pending_robots)
        exit(1);
    parkinglot->pending_robots->next = parkinglot->pending_robots;

    parkinglot->standby_robots = (Robot*)malloc(sizeof(Robot));
    if(!parkinglot->standby_robots)
        exit(1);
    parkinglot->standby_robots->next = parkinglot->standby_robots;

    return parkinglot;
}

Parkinglot* open_parckinglot(const char* file_path){
    ssize_t read_size;
    char* line = NULL;
    size_t len = 0;
    char* token = NULL;
    Parkinglot *parkinglot = create_parkinglot();

    FILE *fp = fopen(file_path, "r");
    if(fp == NULL)
        goto file_open_exception;
    int i=0;
    while((read_size = getline(&line, &len, fp)) != -1){
        token = strtok(line, ",\n ");
        // destination, capacitym transit_time, departure_time, arrived
        if(token[0] == 'T'){
            token = strtok(NULL, ",\n ");
            char *destination = token;

            token = strtok(NULL, ",\n ");
            long capacity = atol(token);

            token = strtok(NULL, ",\n ");
            long transit_time = atol(token);

            token = strtok(NULL, ",\n ");
            long departure_time = atol(token);

            token = strtok(NULL, ",\n ");
            int arrived = atoi(token);

            Truck *truck = create_truck(destination, capacity, transit_time, departure_time);

            if(arrived)
                truck_arrived(parkinglot, truck);
            else
                truck_departed(parkinglot, truck);

        }else if(token[0] == 'R'){
            token = strtok(NULL, ",\n ");
            long capacity = atol(token);

            Robot *robot = create_robot(capacity);
            parkinglot_add_robot(parkinglot, robot);

        }

        free(line);
        line = NULL;
        len = 0;
        i++;
    }
    free(line);

    fclose(fp);
    return parkinglot;

    file_open_exception:
    return NULL;
}

void parkinglot_add_robot(Parkinglot* parkinglot, Robot *robot){
    if(robot == NULL || parkinglot == NULL)
        return;
    Robot* p;

    if (robot->size == 0){
        if (parkinglot->standby_robots->next == parkinglot->standby_robots){
            robot->next = parkinglot->standby_robots;
            parkinglot->standby_robots->next = robot;
            return;
        }

        // avansez prin robotii standby pana ce urmatorul robot are capacitatea
        // mai mica decat cel ce trebuie inserat, il pun inaintea acestuia
        p=parkinglot->standby_robots;
        while(p->next != parkinglot->standby_robots){
            if(p->next->capacity <= robot->capacity){
                robot->next = p->next;
                p->next = robot;
                return;
            }

            p = p->next;
        }

        // daca iese din while inseamna a ajuns la final si nu a gasit un
        // robot cu capacitatea mai mica, inseamna ca el ar avea cea mai mica
        // capacitate si ar trebui pus la finalul listei circulare
        robot->next = p->next;
        p->next = robot;
    } else{
        if (parkinglot->pending_robots->next == parkinglot->pending_robots){
            robot->next = parkinglot->pending_robots;
            parkinglot->pending_robots->next = robot;
            return;
        }

        // analog standby_robots
        p = parkinglot->pending_robots;
        while(p->next != parkinglot->pending_robots){
            if(p->next->size <= robot->size){
                robot->next = p->next;
                p->next = robot;
                return;
            }

            p = p->next;
        }

        robot->next = p->next;
        p->next = robot;
    }
}

void parkinglot_remove_robot(Parkinglot *parkinglot, Robot* robot) {
    if (robot == NULL || parkinglot == NULL)return;
    Robot* p;

    if (robot->size == 0){
        if (parkinglot->standby_robots->next == parkinglot->standby_robots)
            return;

        // daca urmatorul robot e cel ce trebuie eliminat sar peste el in lista
        p = parkinglot->standby_robots;
        while(p->next != parkinglot->standby_robots){
            if (p->next == robot){
                p->next = p->next->next;
                robot->next = NULL;
                return;
            }

            p = p->next;
        }
        // verific la penultimul element daca ultimul element este robot asa
        // ca nu e nevoie sa mai fac nimic cand ies din while
    } else{
        if(parkinglot->pending_robots->next == parkinglot->pending_robots)
            return;

        p = parkinglot->pending_robots;
        while(p->next != parkinglot->pending_robots){
            if(p->next == robot){
                p->next = p->next->next;
                robot->next = NULL;
                return;
            }

            p = p->next;
        }
    }
}

int parckinglot_are_robots_peding(Parkinglot* parkinglot){
    if(parkinglot->pending_robots!=parkinglot->pending_robots->next)
        return 1;

    return 0;
}

int parkinglot_are_arrived_trucks_empty(Parkinglot* parkinglot){
    if(parkinglot->arrived_trucks != parkinglot->arrived_trucks->next){
        Truck* p = parkinglot->arrived_trucks->next;

        while(p != parkinglot->arrived_trucks){
            if(p->size != 0){
                return 0;
            }

            p=p->next;
        }
    }

    return 1;
}


int parkinglot_are_trucks_in_transit(Parkinglot* parkinglot){
    // daca e cel putin un element diferit de santinela in departed_trucks
    // atunci sigur e un tir in tranzit in parcare
    if(parkinglot->departed_trucks != parkinglot->departed_trucks->next){
        return 1;
    }

    return 0;
}


void destroy_parkinglot(Parkinglot* parkinglot){
    Robot* temp;
    Truck* t_temp;

    // cat timp lista nu e goala sterg elementul de dupa santinela
    while(parkinglot->pending_robots->next != parkinglot->pending_robots){
        temp = parkinglot->pending_robots->next->next;
        destroy_robot(parkinglot->pending_robots->next);
        parkinglot->pending_robots->next = temp;
    }

    // dau free la santinela
    free(parkinglot->pending_robots);

    // restul pe acelasi principiu
    while(parkinglot->standby_robots->next != parkinglot->standby_robots){
        temp = parkinglot->standby_robots->next->next;
        destroy_robot(parkinglot->standby_robots->next);
        parkinglot->standby_robots->next = temp;
    }

    free(parkinglot->standby_robots);

    while(parkinglot->arrived_trucks->next != parkinglot->arrived_trucks){
        t_temp = parkinglot->arrived_trucks->next->next;
        destroy_truck(parkinglot->arrived_trucks->next);
        parkinglot->arrived_trucks->next = t_temp;
    }

    free(parkinglot->arrived_trucks);

    while(parkinglot->departed_trucks->next != parkinglot->departed_trucks){
        t_temp = parkinglot->departed_trucks->next->next;
        destroy_truck(parkinglot->departed_trucks->next);
        parkinglot->departed_trucks->next = t_temp;
    }

    free(parkinglot->departed_trucks);

    free(parkinglot);
}

void parkinglot_print_arrived_trucks(Parkinglot* parkinglot){
    Truck *iterator = parkinglot->arrived_trucks->next;
    while(iterator != parkinglot->arrived_trucks){

        truck_print_info(iterator);
        iterator = iterator->next;
    }

    printf("\n");

}

void parkinglot_print_departed_trucks(Parkinglot* parkinglot){
    Truck *iterator = parkinglot->departed_trucks->next;
    while(iterator != parkinglot->departed_trucks){
        truck_print_info(iterator);
        iterator = iterator->next;
    }
    printf("\n");

}

void parkinglot_print_pending_robots(Parkinglot* parkinglot){
    Robot *iterator = parkinglot->pending_robots->next;
    while(iterator != parkinglot->pending_robots){
        printf("R: %ld %ld\n", iterator->size, iterator->capacity);
        robot_print_manifest_info(iterator);
        iterator = iterator->next;
    }
    printf("\n");

}

void parkinglot_print_standby_robots(Parkinglot* parkinglot){
    Robot *iterator = parkinglot->standby_robots->next;
    while(iterator != parkinglot->standby_robots){
        printf("R: %ld %ld\n", iterator->size, iterator->capacity);
        robot_print_manifest_info(iterator);
        iterator = iterator->next;
    }
    printf("\n");

}

void truck_departed(Parkinglot *parkinglot, Truck* truck) {
    if(truck == NULL || parkinglot == NULL)
        return;
    Truck* p = parkinglot->arrived_trucks;

    // daca e cel putin un element in arrived_trucks verific de fiecare data
    // daca urmatorul element dupa contor este truck-ul, daca este sar peste
    // el in lista mutand next-ul contorului la elementul de dupa truck
    while(p->next != parkinglot->arrived_trucks){

        if (p->next == truck){
            p->next = p->next->next;
            break;
        }

        p = p->next;
    }

    // parcurg lista pana la santinela, daca cumva gasesc ca urmatorul element
    // de dupa contor are departure_time mai mare sau egal termin while-ul 
    // mai devreme
    p = parkinglot->departed_trucks;
    while(p->next != parkinglot->departed_trucks){
        if (p->next->departure_time >= truck->departure_time){
            break;
        }

        p = p->next;
    }

    // am parcurs in while sa ajung la elementul dupa care trebuie sa pun
    // truck-ul
    // apropo folosind break n-am nevoie sa pun cele doua linii de mai jos si
    // in if si inafara if-ului, e destul sa le am inafara if-ului
    truck->next = p->next;
    p->next = truck;
}


void truck_arrived(Parkinglot *parkinglot, Truck* truck) {
    if(truck == NULL || parkinglot == NULL)
        return;

    // daca nu e gol tirul, dezaloc toata memoria din manifest si il setez
    // NULL
    if(truck->size != 0 || truck->manifest != NULL){

        Manifest* mpack = truck->manifest;
        Manifest* m_temp;
        while(mpack != NULL){
            m_temp = mpack;
            mpack = mpack->next;
            destroy_manifest_node(m_temp);
        }

        truck->manifest = NULL;
        truck->size = 0;
    }

    // la fel ca la departed_trucks cand scoteam din arrived_trucks
    Truck* p = parkinglot->departed_trucks;
    while(p->next != parkinglot->departed_trucks){

        if(p->next == truck){
            p->next = p->next->next;
            break;
        }

        p = p->next;
    }

    // boolean-ul va tine cont de sortarea lexicografica
    // -1 e o valoare arbitrara
    int boolean = -1;
    p = parkinglot->arrived_trucks;

    // incep de la santinela, cat timp urmatorul element e diferit de santinela
    // atunci verific daca destinatia lui este mai mare sau egala cu cea
    // a tirului ce trebuie bagat si ies din break pentru ca am facut
    // rost de pointer catre elementul din fata tirului ce vreau sa-l bag
    while(p->next != parkinglot->arrived_trucks){
        boolean = strcmp(p->next->destination, truck->destination);
        if(boolean >= 0){
            break;
        }

        p = p->next;
    }

    // in caz ca a iesit din while pentru ca boolean-ul a dat 0, atunci
    // pe acelasi principiu parcurg lista si ma opresc cand dau de un element
    // cu departure_time-ul mai mare sau egal decat tirul ce trebuie inserat
    while(p->next != parkinglot->arrived_trucks && boolean == 0){
        if(p->next->departure_time >= truck->departure_time){
            break;
        }

        p = p->next;

        // daca ultimul tir din lista are aceeasi destinatie si departure_time-ul
        // mai mic decat tirul ce trebuie inserat, atunci mai sus in p=p->next
        // p-ul va ajunge sa pointeze catre ultimul element, astfel in strcmp-ul
        // de mai jos p->next->destination va fi santinela->destination
        // dar n-am setat nicio destinatie santinelei asa ca va da segfault
        // astfel testez sa fiu sigur ca nu se va intampla acest lucru
        if(p->next != parkinglot->arrived_trucks){
            boolean = strcmp(p->next->destination, truck->destination);
        }
    }

    // inserez tirul in spatele tirului urmator crescator in lista conform
    // conditiilor concepute
    truck->next = p->next;
    p->next = truck;
}

void truck_transfer_unloading_robots(Parkinglot* parkinglot, Truck* truck) {
    if(truck == NULL || parkinglot == NULL)
        return;

    Robot* p = truck->unloading_robots;
    Robot* temp;

    // daca cumva truck->unloading_robots e NULL sare peste while si nu face
    // nimic
    while(p != NULL){
        temp = p;
        p = p->next;
        parkinglot_add_robot(parkinglot, temp);
    }

    truck->unloading_robots = NULL;
}

// Depends on parking_turck_departed
void truck_update_depatures(Parkinglot* parkinglot, long day_hour) {
    Truck* p = parkinglot->arrived_trucks->next;
    // parcurg un while care se opreste cand gaseste primul tir al carui
    // departure_time este egal cu day_hour
    // daca nu-l gaseste se va opri la santinela si functia nu va schimba nimic
    while(p != parkinglot->arrived_trucks && p->departure_time < day_hour){
        p = p->next;
    }

    // pt fiecare tir care are departure_time egal cu day_hour i se vor transfera
    // unloading_robots catre parkinglot, iar tirul in sine va trece la
    // departed_trucks
    Truck* temp;
    while(p != parkinglot->arrived_trucks && p->departure_time == day_hour){
        temp = p;
        p = p->next;
        truck_transfer_unloading_robots(parkinglot, temp);
        truck_departed(parkinglot, temp);
    }
    // folosind 2 while-uri in acest fel nu mai e nevoie sa verific tirurile care
    // au departure_time mai mare decat day_hour
}

void truck_update_transit_times(Parkinglot* parkinglot) {
    if(parkinglot == NULL)
        return;
    Truck* p = parkinglot->departed_trucks->next;

    // parcurg lista de departed_trucks si le cresc in_transit_time, daca
    // cumva dupa ce le cresc in_transit_time acesta devine egal cu cel final
    // atunci le setez drept truck sosit si le setez timpul in tranzit 0
    while(p != parkinglot->departed_trucks){
        p->in_transit_time++;

        if (p->in_transit_time == p->transit_end_time){
            Truck* t_temp = p;
            p = p->next;

            truck_arrived(parkinglot, t_temp);
            t_temp->in_transit_time = 0;
        }

        p = p->next;
    }
}

void robot_swarm_collect(Wearhouse *wearhouse, Parkinglot *parkinglot){
    Robot *head_robot = parkinglot->standby_robots;
    Robot *current_robot = parkinglot->standby_robots->next;
    while(current_robot != parkinglot->standby_robots){

        // Load packages from wearhouse if possible
        if(!robot_load_packages(wearhouse, current_robot)){
            break;
        }

        // Remove robot from standby list
        Robot *aux = current_robot;
        head_robot->next = current_robot->next;
        current_robot = current_robot->next;

        // Add robot to the
        parkinglot_add_robot(parkinglot, aux);
    }
}

void robot_swarm_assign_to_trucks(Parkinglot *parkinglot){

    Robot *current_robot = parkinglot->pending_robots->next;

    while(current_robot != parkinglot->pending_robots){
        Robot* aux = current_robot;
        current_robot = current_robot->next;
        parkinglot_remove_robot(parkinglot, aux);
        int attach_succeded = robot_attach_find_truck(aux, parkinglot);
        if(!attach_succeded)
            parkinglot_add_robot(parkinglot, aux);
    }
}

void robot_swarm_deposit(Parkinglot* parkinglot){
    Truck *arrived_iterator = parkinglot->arrived_trucks->next;
    while(arrived_iterator != parkinglot->arrived_trucks){
        Robot *current_robot = arrived_iterator->unloading_robots;
        while(current_robot != NULL){
            robot_unload_packages(arrived_iterator, current_robot);
            Robot *aux = current_robot;
            current_robot = current_robot->next;
            arrived_iterator->unloading_robots = current_robot;
            parkinglot_add_robot(parkinglot, aux);
        }
        arrived_iterator = arrived_iterator->next;
    }
}


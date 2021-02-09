//Maksimalan broj osoba u toaletu
#define MAX_PERSON 3

//enum vrijednosti za pol
enum gender
     { g_male,
       g_female
     };

// inicijalna vrijednost brojaca muskaraca i zana koji zahtijevaju pristup toaletu
int m_count = 0;
int f_count = 0;

// definicija semafora 
sem_t empty, maleSwitch, femaleSwitch, maleMultiplex, femaleMultiplex, turnstile;

// funkcija koja vraca string 'muskog pola' ili 'zenskog pola' u zavisnosti od enum vrijednosti koju predamo kao parametar
char *genderName(int enum_gender){
    if(enum_gender == 0)
       return "muskog pola";
    else
       return "zenskog pola";
}

// funkcija koja signalizira ulazak osobe u toalet, izlazak osobe iz toaleta, kao i vrijeme zadrzavanja u toalatu
void bathroom_enter(int g, int id){
    printf("Osoba %s ID %d je usla u toaleta.\n", genderName(g), id);
    int duration = rand() % 6 + 5;
    sleep(duration); // random broj od 5 do 10
    printf("Osoba %s ID %d je izasla iz toaleta posle %ds.\n", genderName(g), id, duration);
}

// funkcija koja simulira kasnjenje u kreiranu niti 
void thread_delay(){
   int duration = rand() % 5;
   sleep(duration);
}

// funkcija koja signalizira zahtjev korisnika za koriscenje toaleta
void bathroom_access(int g, int id) {
    printf("Osoba %s ID %d zeli da udje u toalet.\n", genderName(g), id);
}

// funkcija koja na slucajan nacin vraca pol osobe
enum gender getGender() {
	return (enum gender) (rand() % 2);
}

// funkcija koja se koristi prilikom izvrsavanja niti a vezana je za osobe muskog pola da pristupi toaletu
void *male(void *arg){
    bathroom_access(0, *((int *) arg));
    sem_wait(&turnstile);
    
    sem_wait(&maleSwitch);
    m_count = m_count + 1;
    if (m_count==1) sem_wait(&empty); 
    sem_post(&maleSwitch);
    
    sem_post(&turnstile);
    
    sem_wait(&maleMultiplex);
    bathroom_enter(0, *((int *) arg));
    sem_post(&maleMultiplex);
    
    sem_wait(&maleSwitch);
    m_count = m_count - 1;
    if (m_count==0) sem_post(&empty); 
    sem_post(&maleSwitch);
}

// funkcija koja se koristi prilikom izvrsavanja niti a vezana je za osobe muskog pola da pristupi toaletu
void *female(void *arg){
    bathroom_access(1, *((int *) arg));
    sem_wait(&turnstile);

    sem_wait(&femaleSwitch);
    f_count = f_count + 1;
    if (f_count==1) sem_wait(&empty); 
    sem_post(&femaleSwitch);

    sem_post(&turnstile);
    
    sem_wait(&femaleMultiplex);
    bathroom_enter(1, *((int *) arg));
    sem_post(&femaleMultiplex);
    
    sem_wait(&femaleSwitch);
    f_count = f_count - 1;
    if (f_count==0) sem_post(&empty); 
    sem_post(&femaleSwitch);
} 



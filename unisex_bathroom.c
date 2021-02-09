/* 
Seminarski rad AROS
Matija Colakovic 0132/2019
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "function_prototype.h" // fajl sa prototipovima korisnickih funkcija
#include "user_function.h" // fajl sa definicijom korisnickih funkcija

#define MAX_THREAD 20

int main(void){
    srand(time(NULL)); // inicijalizacija random generatora 	
    printf("Unisex Bathroom problem - PROJEKTNI RAD\n");
   
    printf("Ukupno %d zaposlenih\n", MAX_THREAD);
       
    /*
    postavljamo semafore na default vrednosti
    sem_init(adresa semafora, 0 ukoliko zelimo da semafor bude deljen izmedju niti, inicijalna vrednost semafora)
    */
    sem_init(&empty, 0, 1);  
    sem_init(&maleSwitch, 0, 1);
    sem_init(&femaleSwitch, 0, 1);
    sem_init(&maleMultiplex, 0, MAX_PERSON);
    sem_init(&femaleMultiplex, 0, MAX_PERSON);
    sem_init(&turnstile, 0, 1);

    pthread_t person[MAX_THREAD];

    for(int i = 0; i < MAX_THREAD; i++){
         int *arg = malloc(sizeof(int));
         *arg = i+1;

        if(getGender() == g_female)
             pthread_create(&person[i], NULL, female, arg);
        else
             pthread_create(&person[i], NULL, male, arg);

        thread_delay();
    }
    
    // join-ujemo sve stvorene niti u glavnu nit
    for(int i = 0; i < MAX_THREAD; i++){     
       pthread_join(person[i], NULL);
    }

    sem_destroy(&empty);  
    sem_destroy(&maleSwitch);
    sem_destroy(&femaleSwitch);
    sem_destroy(&maleMultiplex);
    sem_destroy(&femaleMultiplex);
    sem_destroy(&turnstile);

    return 0;
}



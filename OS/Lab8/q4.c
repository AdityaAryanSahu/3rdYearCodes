#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 3

sem_t customers;
sem_t barber;
sem_t accessSeats;

int freeSeats = CHAIRS;

void *barberFunc(void *arg) {
    while (1) {
        sem_wait(&customers);
        sem_wait(&accessSeats);
        freeSeats++;
        sem_post(&barber);
        sem_post(&accessSeats);

        printf("Barber is cutting hair...\n");
        sleep(2);
        printf("Barber finished cutting hair.\n");
    }
}

void *customerFunc(void *arg) {
    int id = *(int *)arg;
    sem_wait(&accessSeats);
    if (freeSeats > 0) {
        freeSeats--;
        printf("Customer %d is waiting. Free chairs: %d\n", id, freeSeats);
        sem_post(&customers);
        sem_post(&accessSeats);
        sem_wait(&barber);
        printf("Customer %d is getting a haircut.\n", id);
    } else {
        sem_post(&accessSeats);
        printf("Customer %d left (no chairs available).\n", id);
    }
    return NULL;
}

int main() {
    pthread_t btid, ctid[10];
    int ids[10];

    sem_init(&customers, 0, 0);
    sem_init(&barber, 0, 0);
    sem_init(&accessSeats, 0, 1);

    pthread_create(&btid, NULL, barberFunc, NULL);

    for (int i = 0; i < 10; i++) {
        ids[i] = i + 1;
        pthread_create(&ctid[i], NULL, customerFunc, &ids[i]);
        sleep(rand() % 3);
    }

    for (int i = 0; i < 10; i++)
        pthread_join(ctid[i], NULL);

    pthread_cancel(btid);
    sem_destroy(&customers);
    sem_destroy(&barber);
    sem_destroy(&accessSeats);

    return 0;
}

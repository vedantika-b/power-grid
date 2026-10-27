// power_grid.c : Producer-Consumer (Bounded Buffer) - Power Grid
// Compile: gcc power_grid.c -o power_grid -pthread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CAPACITY 10   // grid capacity in units, 1 unit = 10 MW
#define PRODUCERS 3
#define CONSUMERS 3
#define ROUNDS 8

int grid = 0;                 // shared buffer
sem_t empty_slots, full_slots;
pthread_mutex_t mutex;
const char *plant[PRODUCERS] = {"Power Plant 1", "Power Plant 2", "Power Plant 3"};
const char *cons[CONSUMERS]  = {"Households", "Factories", "Offices"};

void *producer(void *arg) {
    int id = (int)(long)arg;
    for (int i = 0; i < ROUNDS; i++) {
        usleep((rand() % 400 + 100) * 1000);
        sem_wait(&empty_slots);
        pthread_mutex_lock(&mutex);
        grid++;
        printf("[PRODUCER] %-13s produced 10 MW | Grid: %3d MW | Utilization: %3d%%\n", plant[id], grid * 10, grid * 100 / CAPACITY);
        pthread_mutex_unlock(&mutex);
        sem_post(&full_slots);
    }
    return NULL;
}

void *consumer(void *arg) {
    int id = (int)(long)arg;
    for (int i = 0; i < ROUNDS; i++) {
        usleep((rand() % 400 + 100) * 1000);
        sem_wait(&full_slots);
        pthread_mutex_lock(&mutex);
        grid--;
        printf("[CONSUMER] %-13s consumed 10 MW | Grid: %3d MW | Utilization: %3d%%\n", cons[id], grid * 10, grid * 100 / CAPACITY);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty_slots);
    }
    return NULL;
}

int main(void) {
    pthread_t p[PRODUCERS], c[CONSUMERS];
    sem_init(&empty_slots, 0, CAPACITY);
    sem_init(&full_slots, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    for (long i = 0; i < PRODUCERS; i++) pthread_create(&p[i], NULL, producer, (void *)i);
    for (long i = 0; i < CONSUMERS; i++) pthread_create(&c[i], NULL, consumer, (void *)i);
    for (int i = 0; i < PRODUCERS; i++) pthread_join(p[i], NULL);
    for (int i = 0; i < CONSUMERS; i++) pthread_join(c[i], NULL);
    printf("Final grid load = %d MW\n", grid * 10);
    return 0;
}

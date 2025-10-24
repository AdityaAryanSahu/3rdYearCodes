#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define P 5
#define R 3

int total[R] = {10, 5, 7};
int max[P][R], allocation[P][R], need[P][R], available[R];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

bool isSafe(int work[R], bool finish[P]) {
    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool can = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        can = false;
                        break;
                    }
                }
                if (can) {
                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

bool request_resources(int p, int req[R]) {
    pthread_mutex_lock(&mutex);

    for (int j = 0; j < R; j++) {
        if (req[j] > need[p][j] || req[j] > available[j]) {
            pthread_mutex_unlock(&mutex);
            return false;
        }
    }

    for (int j = 0; j < R; j++) {
        available[j] -= req[j];
        allocation[p][j] += req[j];
        need[p][j] -= req[j];
    }

    int work[R];
    bool finish[P] = {0};
    for (int j = 0; j < R; j++)
        work[j] = available[j];

    bool safe = isSafe(work, finish);

    if (!safe) {
        for (int j = 0; j < R; j++) {
            available[j] += req[j];
            allocation[p][j] -= req[j];
            need[p][j] += req[j];
        }
    }

    pthread_mutex_unlock(&mutex);
    return safe;
}

void release_resources(int p, int rel[R]) {
    pthread_mutex_lock(&mutex);
    for (int j = 0; j < R; j++) {
        allocation[p][j] -= rel[j];
        need[p][j] += rel[j];
        available[j] += rel[j];
    }
    pthread_mutex_unlock(&mutex);
}

void* process(void* arg) {
    int p = *(int*)arg;
    free(arg);

    int attempts = 0;
    while (attempts < 200) {  
        int req[R] = {0};

        pthread_mutex_lock(&mutex);
        bool done = true;
        for (int j = 0; j < R; j++) {
            if (need[p][j] > 0)
                done = false;
        }
        pthread_mutex_unlock(&mutex);
        if (done)
            break;

        pthread_mutex_lock(&mutex);
        for (int j = 0; j < R; j++) {
            if (need[p][j] > 0 && available[j] > 0) {
                int limit = (need[p][j] < available[j]) ? need[p][j] : available[j];
                req[j] = (limit > 0) ? (rand() % limit + 1) : 0;
            } else {
                req[j] = 0;
            }
        }
        pthread_mutex_unlock(&mutex);

        if (request_resources(p, req)) {
            usleep(1000);
            release_resources(p, req);
            usleep(1000);
        } else {
            usleep(500);
        }

        attempts++;
    }

    printf("Process %d finished execution.\n", p);
    return NULL;
}

int main() {
    srand(time(NULL));

    for (int j = 0; j < R; j++) {
        available[j] = total[j];
    }

    printf("Enter Max matrix (5x3):\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
            allocation[i][j] = 0;
            need[i][j] = max[i][j];
        }
    }

    pthread_t threads[P];

    for (int i = 0; i < P; i++) {
        int* arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&threads[i], NULL, process, arg);
    }

    for (int i = 0; i < P; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nAll processes finished safely.\n");
    return 0;
}

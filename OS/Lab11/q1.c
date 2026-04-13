#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

int total[R] = {10, 5, 7};

bool isSafe(int avail[R], int alloc[P][R], int need[P][R], int safeSeq[P]) {
    bool finish[P] = {false};
    int work[R];
    for(int i=0; i<R; i++) work[i] = avail[i];
    int count = 0;

    while(count < P) {
        bool found = false;
        for(int i=0; i<P; i++) {
            if(!finish[i]) {
                bool canAlloc = true;
                for(int j=0; j<R; j++)
                    if(need[i][j] > work[j]) {
                        canAlloc = false;
                        break;
                    }
                if(canAlloc) {
                    for(int j=0; j<R; j++)
                        work[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if(!found) return false;
    }
    return true;
}

void calculateNeed(int need[P][R], int max[P][R], int alloc[P][R]) {
    for(int i=0; i<P; i++)
        for(int j=0; j<R; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

bool requestGrant(int p, int req[R], int avail[R], int alloc[P][R], int need[P][R]) {
    for(int i=0; i<R; i++)
        if(req[i] > need[p][i] || req[i] > avail[i])
            return false;

    for(int i=0; i<R; i++) {
        avail[i] -= req[i];
        alloc[p][i] += req[i];
        need[p][i] -= req[i];
    }

    int safeSeq[P];
    if(isSafe(avail, alloc, need, safeSeq))
        return true;

    for(int i=0; i<R; i++) {
        avail[i] += req[i];
        alloc[p][i] -= req[i];
        need[p][i] += req[i];
    }
    return false;
}

int main() {
    int max[P][R], alloc[P][R], need[P][R], avail[R];
    int sumAlloc[R] = {0};
    int safeSeq[P];

    printf("Enter Max matrix (5x3):\n");
    for(int i=0; i<P; i++)
        for(int j=0; j<R; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Allocation matrix (5x3):\n");
    for(int i=0; i<P; i++)
        for(int j=0; j<R; j++) {
            scanf("%d", &alloc[i][j]);
            sumAlloc[j] += alloc[i][j];
        }

    for(int i=0; i<R; i++)
        avail[i] = total[i] - sumAlloc[i];

    calculateNeed(need, max, alloc);

    printf("\nNeed Matrix:\n");
    for(int i=0; i<P; i++) {
        for(int j=0; j<R; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    if(isSafe(avail, alloc, need, safeSeq)) {
        printf("System is in a SAFE state.\nSafe sequence: ");
        for(int i=0; i<P; i++)
            printf("P%d%s", safeSeq[i], (i==P-1) ? "\n" : " -> ");
    } else
        printf("System is NOT in a safe state.\n");

    int requests[][R] = {
        {1, 0, 2},
        {3, 3, 0},
        {0, 2, 0}
    };
    int processes[] = {1, 4, 0};

    for(int k=0; k<3; k++) {
        int p = processes[k];
        printf("\nRequest from P%d: (", p);
        for(int i=0; i<R; i++) {
            printf("%d", requests[k][i]);
            if(i<R-1) printf(", ");
        }
        printf(")\n");

        if(requestGrant(p, requests[k], avail, alloc, need)) {
            printf("Request can be granted.\n");
            printf("Updated Allocation:\n");
            for(int i=0; i<P; i++) {
                for(int j=0; j<R; j++)
                    printf("%d ", alloc[i][j]);
                printf("\n");
            }
            printf("Updated Need:\n");
            for(int i=0; i<P; i++) {
                for(int j=0; j<R; j++)
                    printf("%d ", need[i][j]);
                printf("\n");
            }
            printf("Updated Available:\n");
            for(int i=0; i<R; i++)
                printf("%d ", avail[i]);
            printf("\n");

        } else {
            printf("Request cannot be granted immediately.\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct DSA {
    int request_id;
    int arrival_time_stamp;
    int cylinder;
    int address;
    int process_id;
};

void fcfs(struct DSA requests[], int n, int head) {
    printf("\n--- FCFS Scheduling ---\n");
    int total_movement = 0;
    printf("Order of service: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i].request_id);
        total_movement += abs(requests[i].cylinder - head);
        head = requests[i].cylinder;
    }
    printf("\nTotal Head Movement: %d\n", total_movement);
}

void sstf(struct DSA requests[], int n, int head) {
    printf("\n--- SSTF Scheduling ---\n");
    bool serviced[n];
    for (int i = 0; i < n; i++) serviced[i] = false;
    int total_movement = 0, completed = 0;

    printf("Order of service: ");
    while (completed < n) {
        int idx = -1, min_dist = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!serviced[i] && abs(requests[i].cylinder - head) < min_dist) {
                min_dist = abs(requests[i].cylinder - head);
                idx = i;
            }
        }
        serviced[idx] = true;
        total_movement += abs(requests[idx].cylinder - head);
        head = requests[idx].cylinder;
        printf("%d ", requests[idx].request_id);
        completed++;
    }
    printf("\nTotal Head Movement: %d\n", total_movement);
}

int main() {
    int n, head;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    struct DSA requests[n];

    printf("Enter head start position: ");
    scanf("%d", &head);

    printf("Enter request details:\n");
    printf("(request_id arrival_time cylinder address process_id)\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d %d",
              &requests[i].request_id,
              &requests[i].arrival_time_stamp,
              &requests[i].cylinder,
              &requests[i].address,
              &requests[i].process_id);
    }

    fcfs(requests, n, head);
    sstf(requests, n, head);

    return 0;
}

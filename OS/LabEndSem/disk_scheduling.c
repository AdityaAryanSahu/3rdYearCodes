#include <stdio.h>
#include <stdlib.h>
#include<math.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

void scan(int requests[], int n, int head, int disk_size, int direction) {
    int total = 0;
    int i, j;
    int index;

    int temp[n + 1];
    for (i = 0; i < n; i++) temp[i] = requests[i];
    temp[n] = head;
    sort(temp, n + 1);

    for (i = 0; i < n + 1; i++) {
        if (temp[i] == head) {
            index = i;
            break;
        }
    }
    int prev=temp[index];
    int sum=0; // sum is cylinder movement
    printf("\nSCAN Disk Scheduling Order:\n");
    if (direction == 1) { // right
        for (i = index; i < n + 1; i++){ 
        printf("%d ", temp[i]);
        sum+=abs(temp[i]-prev);
        prev=temp[i];
        }
        
        printf("%d ", disk_size - 1);
        sum += abs((disk_size - 1) - prev);
        prev = disk_size - 1;

        for (i = index - 1; i >= 0; i--){ 
        printf("%d ", temp[i]);
        sum+=abs(temp[i]-prev);
        prev=temp[i];
        }
        total = (disk_size - 1 - head) + (disk_size - 1 - temp[0]);
    } else {
        for (i = index; i >= 0; i--) printf("%d ", temp[i]);
        if (temp[index] != 0)
            printf("0 ");
        for (i = index + 1; i < n + 1; i++) printf("%d ", temp[i]);
        total = head + temp[n] - 0;
    }
    printf("\nTotal head movement = %d\n", sum);
}

void cscan(int requests[], int n, int head, int disk_size, int direction) {
    int total = 0, i, index;

    int temp[n + 1];
    for (i = 0; i < n; i++) temp[i] = requests[i];
    temp[n] = head;
    sort(temp, n + 1);

    for (i = 0; i < n + 1; i++) {
        if (temp[i] == head) {
            index = i;
            break;
        }
    }

    printf("\nC-SCAN Disk Scheduling Order:\n");
    if (direction == 1) { // right
        for (i = index; i < n + 1; i++) printf("%d ", temp[i]);
        printf("%d ", disk_size - 1);
        printf("0 ");
        for (i = 0; i < index; i++) printf("%d ", temp[i]);
        total = (disk_size - 1 - head) + (disk_size - 1 - 0) + temp[index - 1];
    } else {
        for (i = index; i >= 0; i--) printf("%d ", temp[i]);
        printf("0 ");
        printf("%d ", disk_size - 1);
        for (i = n; i > index; i--) printf("%d ", temp[i]);
        total = head + (disk_size - 1) + (disk_size - 1 - temp[index + 1]);
    }
    printf("\nTotal head movement = %d\n", total);
}

void look(int requests[], int n, int head, int direction) {
    int total = 0, i, index;
    int temp[n + 1];
    for (i = 0; i < n; i++) temp[i] = requests[i];
    temp[n] = head;
    sort(temp, n + 1);

    for (i = 0; i < n + 1; i++) {
        if (temp[i] == head) {
            index = i;
            break;
        }
    }

    printf("\nLOOK Disk Scheduling Order:\n");
    if (direction == 1) {
        for (i = index; i < n + 1; i++) printf("%d ", temp[i]);
        for (i = index - 1; i >= 0; i--) printf("%d ", temp[i]);
        total = (temp[n] - head) + (temp[n] - temp[0]);
    } else {
        for (i = index; i >= 0; i--) printf("%d ", temp[i]);
        for (i = index + 1; i < n + 1; i++) printf("%d ", temp[i]);
        total = (head - temp[0]) + (temp[n] - temp[0]);
    }
    printf("\nTotal head movement = %d\n", total);
}

void clook(int requests[], int n, int head, int direction) {
    int total = 0, i, index;
    int temp[n + 1];
    for (i = 0; i < n; i++) temp[i] = requests[i];
    temp[n] = head;
    sort(temp, n + 1);

    for (i = 0; i < n + 1; i++) {
        if (temp[i] == head) {
            index = i;
            break;
        }
    }

    printf("\nC-LOOK Disk Scheduling Order:\n");
    if (direction == 1) {
        for (i = index; i < n + 1; i++) printf("%d ", temp[i]);
        for (i = 0; i < index; i++) printf("%d ", temp[i]);
        total = (temp[n] - head) + (temp[n] - temp[0]);
    } else {
        for (i = index; i >= 0; i--) printf("%d ", temp[i]);
        for (i = n; i > index; i--) printf("%d ", temp[i]);
        total = (head - temp[0]) + (temp[n] - temp[0]);
    }
    printf("\nTotal head movement = %d\n", total);
}

int main() {
    int n, head, disk_size, direction;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter total disk size: ");
    scanf("%d", &disk_size);
    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    scan(requests, n, head, disk_size, direction);
    cscan(requests, n, head, disk_size, direction);
    look(requests, n, head, direction);
    clook(requests, n, head, direction);

    return 0;
}

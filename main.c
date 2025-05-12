#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>  // for usleep

#define MAXN 100
#define DELAY 200000  // microseconds

int arr[MAXN];
int n;
int mode = 0; // 0 = list, 1 = bars

// ANSI escape codes
#define CLEAR_SCREEN "\033[2J"
#define MOVE_CURSOR_HOME "\033[H"
#define UNDERLINE_ON "\033[4m"
#define UNDERLINE_OFF "\033[24m"

void pause_step() {
    usleep(DELAY);
}

void display() {
    printf(CLEAR_SCREEN MOVE_CURSOR_HOME);
    printf("quicksort\n");
    printf("elements: %d\n", n);
    printf("mode: %s\n\n", mode == 0 ? "list" : "bars");

    if (mode == 0) {
        printf("[");
        for (int i = 0; i < n; i++) {
            printf("%d", arr[i]);
            if (i < n - 1) printf(",");
        }
        printf("]\n");
    } else {
        for (int i = 0; i < n; i++) {
            for (int h = 0; h < arr[i]; h++) printf("\u25A1");
            printf("\n");
        }
    }
    fflush(stdout);
}

void display_highlight(int i, int j) {
    printf(CLEAR_SCREEN MOVE_CURSOR_HOME);
    printf("quicksort\n");
    printf("elements: %d\n", n);
    printf("mode: %s\n\n", mode == 0 ? "list" : "bars");

    if (mode == 0) {
        printf("[");
        for (int k = 0; k < n; k++) {
            if (k == i || k == j) printf(UNDERLINE_ON);
            printf("%d", arr[k]);
            if (k == i || k == j) printf(UNDERLINE_OFF);
            if (k < n - 1) printf(",");
        }
        printf("]\n");
    } else {
        for (int k = 0; k < n; k++) {
            if (k == i || k == j) printf(UNDERLINE_ON);
            for (int h = 0; h < arr[k]; h++) printf("\u25A1");
            if (k == i || k == j) printf(UNDERLINE_OFF);
            printf("\n");
        }
    }
    fflush(stdout);
}

int partition(int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        display_highlight(j, high);
        pause_step();
        if (arr[j] < pivot) {
            i++;
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
            display_highlight(i, j);
            pause_step();
        }
    }
    int tmp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = tmp;
    display_highlight(i+1, high);
    pause_step();
    return i + 1;
}

void quicksort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quicksort(low, pi - 1);
        quicksort(pi + 1, high);
    }
}

int main() {
    srand(time(NULL));
    printf("Choose input mode:\n");
    printf("1 = random list\n");
    printf("2 = manual entry\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Enter number of elements (max %d): ", MAXN);
        scanf("%d", &n);
        for (int i = 0; i < n; i++) arr[i] = rand() % 20 + 1;
    } else {
        printf("Enter number of elements: "); scanf("%d", &n);
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    }

    printf("Choose display mode:\n");
    printf("0 = list\n");
    printf("1 = bars\n");
    scanf("%d", &mode);

    display();
    pause_step();
    quicksort(0, n - 1);

    // final
    display();
    printf("\nSorting complete.\n");
    return 0;
}
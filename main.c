#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  // for usleep

#define MAX_N 100
#define DELAY 200000  // microseconds (0.2s)

int arr[MAX_N];
int n;
int mode; // 1 = list, 2 = bars

// ANSI escape codes
#define CLEAR_SCREEN "\033[2J"
#define MOVE_HOME   "\033[H"

void clear_console() {
    printf(CLEAR_SCREEN MOVE_HOME);
}

void display_list(int low, int high) {
    printf("Mode: %s\n", mode==1?"List":"Bars");
    printf("Elements: %d\n", n);
    if (mode == 1) {
        printf("[");
        for (int i = 0; i < n; i++) {
            if (i == low || i == high) printf("_%d_", arr[i]);
            else printf("%d", arr[i]);
            if (i < n-1) printf(", ");
        }
        printf("]\n");
    } else {
        int maxv=0;
        for (int i=0;i<n;i++) if (arr[i]>maxv) maxv=arr[i];
        for (int i=0;i<n;i++) {
            for (int j=0;j< arr[i]; j+=maxv/20+1) printf(mode==2?"█":"#");
            if (i==low || i==high) printf(" <-");
            printf("\n");
        }
    }
    fflush(stdout);
}

void swap(int *a, int *b) {
    int t=*a; *a=*b; *b=t;
}

int partition(int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
        clear_console(); display_list(j, high);
        usleep(DELAY);
    }
    swap(&arr[i+1], &arr[high]);
    clear_console(); display_list(i+1, high);
    usleep(DELAY);
    return i+1;
}

void quicksort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quicksort(low, pi - 1);
        quicksort(pi + 1, high);
    }
}

void bubble_sort() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
            clear_console(); display_list(j, j+1);
            usleep(DELAY);
        }
    }
}

void merge(int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        clear_console(); display_list(k, -1);
        usleep(DELAY);
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
        clear_console(); display_list(k-1, -1);
        usleep(DELAY);
    }

    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
        clear_console(); display_list(k-1, -1);
        usleep(DELAY);
    }
}

void merge_sort(int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(l, m);
        merge_sort(m + 1, r);
        merge(l, m, r);
    }
}

void generate_random() {
    srand(time(NULL));
    for (int i = 0; i < n; i++) arr[i] = rand() % 50 + 1;
}

int main() {
    printf("Enter number of elements (max %d): ", MAX_N);
    scanf("%d", &n);
    if (n < 1 || n > MAX_N) return 1;

    printf("Choose input mode:\n1 - Random\n2 - Manual\n");
    int input_mode;
    scanf("%d", &input_mode);
    if (input_mode == 1) {
        generate_random();
    } else {
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    }

    printf("Choose display mode:\n1 - List\n2 - Bars\n");
    scanf("%d", &mode);

    printf("Choose sorting algorithm:\n1 - Quicksort\n2 - Bubble Sort\n3 - Merge Sort\n");
    int sort_mode;
    scanf("%d", &sort_mode);

    clear_console();
    printf("Starting sorting visualization...\n");
    usleep(1000000);

    if (sort_mode == 1) quicksort(0, n-1);
    else if (sort_mode == 2) bubble_sort();
    else if (sort_mode == 3) merge_sort(0, n-1);

    clear_console(); display_list(-1, -1);
    printf("Sorting complete!\n");
    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

int* generateRandomArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }
    return arr;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int size, int* comparisons, int* moves) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j+1]) {
                (*moves)++;
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void selectionSort(int arr[], int size, int* comparisons, int* moves) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            (*comparisons)++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            (*moves)++;
            swap(&arr[i], &arr[minIndex]);
        }
    }
}

void insertionSort(int arr[], int size, int* comparisons, int* moves) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            (*comparisons)++;
            (*moves)++;
            arr[j+1] = arr[j];
            j--;
        }
        (*comparisons)++;
        arr[j+1] = key;
    }
}

int partition(int arr[], int low, int high, int* comparisons, int* moves) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++;
        if (arr[j] < pivot) {
            i++;
            (*moves)++;
            swap(&arr[i], &arr[j]);
        }
    }
    (*moves)++;
    swap(&arr[i+1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high, int* comparisons, int* moves) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons, moves);
        quickSort(arr, low, pi - 1, comparisons, moves);
        quickSort(arr, pi + 1, high, comparisons, moves);
    }
}

void shellSort(int arr[], int size, int* comparisons, int* moves) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int key = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > key) {
                (*comparisons)++;
                (*moves)++;
                arr[j] = arr[j - gap];
                j -= gap;
            }
            (*comparisons)++;
            arr[j] = key;
        }
    }
}

void heapify(int arr[], int n, int i, int* comparisons, int* moves) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) {
        *comparisons += 1;
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        *comparisons += 1;
        largest = right;
    }
    if (largest != i) {
        *moves += 3;
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest, comparisons, moves);
    }
}

void heapSort(int arr[], int n, int* comparisons, int* moves) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comparisons, moves);
    }
    for (int i = n - 1; i >= 0; i--) {
        *moves += 3;
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0, comparisons, moves);
    }
}

void merge(int* arr, int left, int mid, int right, int* compareCount, int* moveCount) {
    int i = left;
    int j = mid + 1;
    int k = 0;
    int* temp = (int*)malloc((right - left + 1) * sizeof(int));
    while (i <= mid && j <= right) {
        *compareCount += 1;
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
        *moveCount += 1;
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
        *moveCount += 1;
    }
    while (j <= right) {
        temp[k++] = arr[j++];
        *moveCount += 1;
    }
    for (int m = 0; m < k; m++) {
        arr[left + m] = temp[m];
        *moveCount += 1;
    }
    free(temp);
}

void mergeSort(int* arr, int left, int right, int* compareCount, int* moveCount) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid, compareCount, moveCount);
        mergeSort(arr, mid + 1, right, compareCount, moveCount);
        merge(arr, left, mid, right, compareCount, moveCount);
    }
}

struct cmp{
    double time=0;
    int cmpcnt=0;
    int movcnt=0;
};

int main(){
    int dataSize = 10000;
    int* arr;
    cmp cmpSort[7];
    //Ã°ÅÝÅÅÐò
    for (int i = 0; i < 5; i++) {
        arr = generateRandomArray(dataSize);
        int compareCount = 0;
        int moveCount = 0;
        clock_t start = clock();
        bubbleSort(arr, dataSize, &compareCount, &moveCount);
        clock_t end = clock();
        cmpSort[0].time=cmpSort[0].time+(double)(end - start) / CLOCKS_PER_SEC;
        cmpSort[0].cmpcnt=cmpSort[0].cmpcnt+compareCount;
        cmpSort[0].movcnt=cmpSort[0].movcnt+moveCount;
        free(arr);
    }
    cmpSort[0].time=cmpSort[0].time/5;
    cmpSort[0].cmpcnt=cmpSort[0].cmpcnt/5;
    cmpSort[0].movcnt=cmpSort[0].movcnt/5;

    //Ñ¡ÔñÅÅÐò
    for (int i = 0; i < 5; i++) {
        arr = generateRandomArray(dataSize);
        int compareCount = 0;
        int moveCount = 0;
        clock_t start = clock();
        selectionSort(arr, dataSize, &compareCount, &moveCount);
        clock_t end = clock();
        cmpSort[1].time=cmpSort[1].time+(double)(end - start) / CLOCKS_PER_SEC;
        cmpSort[1].cmpcnt=cmpSort[1].cmpcnt+compareCount;
        cmpSort[1].movcnt=cmpSort[1].movcnt+moveCount;
        free(arr);
    }
    cmpSort[1].time=cmpSort[1].time/5;
    cmpSort[1].cmpcnt=cmpSort[1].cmpcnt/5;
    cmpSort[1].movcnt=cmpSort[1].movcnt/5;

    //Ö±½ÓÑ¡ÔñÅÅÐò
    for (int i = 0; i < 5; i++) {
        arr = generateRandomArray(dataSize);
        int compareCount = 0;
        int moveCount = 0;
        clock_t start = clock();
        insertionSort(arr, dataSize - 1, &compareCount, &moveCount);
        clock_t end = clock();
        cmpSort[2].time=cmpSort[2].time+(double)(end - start) / CLOCKS_PER_SEC;
        cmpSort[2].cmpcnt=cmpSort[2].cmpcnt+compareCount;
        cmpSort[2].movcnt=cmpSort[2].movcnt+moveCount;
        free(arr);
    }
    cmpSort[2].time=cmpSort[2].time/5;
    cmpSort[2].cmpcnt=cmpSort[2].cmpcnt/5;
    cmpSort[2].movcnt=cmpSort[2].movcnt/5;

    //¿ìËÙÅÅÐò
    for (int i = 0; i < 5; i++) {
        arr = generateRandomArray(dataSize);
        int compareCount = 0;
        int moveCount = 0;
        clock_t start = clock();
        quickSort(arr,0, dataSize - 1, &compareCount, &moveCount);
        clock_t end = clock();
        cmpSort[3].time=cmpSort[3].time+(double)(end - start) / CLOCKS_PER_SEC;
        cmpSort[3].cmpcnt=cmpSort[3].cmpcnt+compareCount;
        cmpSort[3].movcnt=cmpSort[3].movcnt+moveCount;
        free(arr);
    }
    cmpSort[3].time=cmpSort[3].time/5;
    cmpSort[3].cmpcnt=cmpSort[3].cmpcnt/5;
    cmpSort[3].movcnt=cmpSort[3].movcnt/5;

    //Ï£¶ûÅÅÐò
    for (int i = 0; i < 5; i++) {
        arr = generateRandomArray(dataSize);
        int compareCount = 0;
        int moveCount = 0;
        clock_t start = clock();
        shellSort(arr, dataSize, &compareCount, &moveCount);
        clock_t end = clock();
        cmpSort[4].time=cmpSort[4].time+(double)(end - start) / CLOCKS_PER_SEC;
        cmpSort[4].cmpcnt=cmpSort[4].cmpcnt+compareCount;
        cmpSort[4].movcnt=cmpSort[4].movcnt+moveCount;
        free(arr);
    }
    cmpSort[4].time=cmpSort[4].time/5;
    cmpSort[4].cmpcnt=cmpSort[4].cmpcnt/5;
    cmpSort[4].movcnt=cmpSort[4].movcnt/5;

    //¶ÑÅÅÐò
    for (int i = 0; i < 5; i++) {
        arr = generateRandomArray(dataSize);
        int compareCount = 0;
        int moveCount = 0;
        clock_t start = clock();
        heapSort(arr, dataSize, &compareCount, &moveCount);
        clock_t end = clock();
        cmpSort[5].time=cmpSort[5].time+(double)(end - start) / CLOCKS_PER_SEC;
        cmpSort[5].cmpcnt=cmpSort[5].cmpcnt+compareCount;
        cmpSort[5].movcnt=cmpSort[5].movcnt+moveCount;
        free(arr);
    }
    cmpSort[5].time=cmpSort[5].time/5;
    cmpSort[5].cmpcnt=cmpSort[5].cmpcnt/5;
    cmpSort[5].movcnt=cmpSort[5].movcnt/5;

    // ¹é²¢ÅÅÐò
    for (int i = 0; i < 5; i++) {
        arr = generateRandomArray(dataSize);
        int compareCount = 0;
        int moveCount = 0;
        clock_t start = clock();
        mergeSort(arr, 0, dataSize - 1, &compareCount, &moveCount);
        clock_t end = clock();
        cmpSort[6].time=cmpSort[6].time+(double)(end - start) / CLOCKS_PER_SEC;
        cmpSort[6].cmpcnt=cmpSort[6].cmpcnt+compareCount;
        cmpSort[6].movcnt=cmpSort[6].movcnt+moveCount;
        free(arr);
    }
    cmpSort[6].time=cmpSort[6].time/5;
    cmpSort[6].cmpcnt=cmpSort[6].cmpcnt/5;
    cmpSort[6].movcnt=cmpSort[6].movcnt/5;
    std::cout<<std::setw(14)<<" ";
    std::cout<<"ÆðÅÝÅÅÐò"<<std::setw(13)<<"Ö±½ÓÅÅÐò"
    <<std::setw(14)<<"Ñ¡ÔñÅÅÐò"<<std::setw(14)<<"¿ìËÙÅÅÐò"
    <<std::setw(13)<<"Ï£¶ûÅÅÐò"<<std::setw(13)<<"¶ÑÅÅÐò"<<std::setw(14)<<"¹é²¢ÅÅÐò";
    printf("\nÅÅÐòÊ±¼ä£º");
    for (int i = 0; i < 7; ++i) {
        std::cout<<std::setw(12)<<cmpSort[i].time;
    }
    printf("\n±È½Ï´ÎÊý£º");
    for (int i = 0; i < 7; ++i) {
        std::cout<<std::setw(12)<<cmpSort[i].cmpcnt;
    }
    printf("\nÒÆ¶¯´ÎÊý£º");
    for (int i = 0; i < 7; ++i) {
        std::cout<<std::setw(12)<<cmpSort[i].movcnt;
    }
}
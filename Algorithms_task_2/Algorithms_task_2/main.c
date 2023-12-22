//
//  main.c
//  Algorithms_task_2
//
//  Created by 김도윤 on 2022/10/11.
//

//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//
//int n = 100000;
//int Limits[] = { 1,100,500,1000 };
//int Limit;
//
//int* createArray();
//int* copyArray(int* A);
//void quickSort(int* A, int mode);
//void rQuickSort(int* A, int l, int r, int mode);
//void insertionSort(int* A);
//int findPrivot(int* A, int l, int r, int mode);
//int findIndexOfMedianOfThree(int* A, int a, int b, int c);
//void inPlacePartition(int* A, int l, int r, int k, int* a, int* b);
//void swapElem(int* a, int* b);
//
//int main(void) {
//    int* A, * Acopy;
//    int i, j;
//
//    srand((unsigned int)time(NULL)); // 난수 초기화
//
//    clock_t start, finish; // 정렬 함수들의 걸리는 시간을 측정하기 위해 시작시간과 마지막시간을 저장하기 위한 변수
//    double duration; // 정렬 함수들이 걸리는 시간을 저장하기 위한 double형 변수
//
//    A = createArray();
//
//    printf("%5s  %-10s  %-10s  %-10s  %-10s\n", "Limit", "결정적1", "결정적3", "무작위1", "무작위3");
//    for (i = 0; i < 4; i++) {
//        Limit = Limits[i];
//
//        printf("%-5d", Limit);
//        for (j = 0; j < 4; j++) {
//            Acopy = copyArray(A); //copy
//
//            start = clock();
//            quickSort(Acopy, j);
//            finish = clock();
//            duration = (double) (finish - start) / CLOCKS_PER_SEC;
//            printf("     %-10.8f", duration);
//
//            free(Acopy);
//        }
//        printf("\n");
//    }
//
//    free(A);
//
//    return 0;
//}
//
//int* createArray() {
//    int* A = (int*)malloc(sizeof(int) * n);
//    long r;
//
//    for (int i = 0; i < n; i++) {
//        r = ((((long)rand() << 15) | rand()) % n) + 1;
//        A[i] = (int)r;
//    }
//
//    return A;
//} //A[n] 생성
//
//int* copyArray(int* A) {
//    int* Acopy = (int*)malloc(sizeof(int) * n);
//
//    for (int i = 0; i < n; i++) {
//        Acopy[i] = A[i];
//    }
//
//    return Acopy;
//} //복제
//
//void quickSort(int* A, int mode) {
//    rQuickSort(A, 0, n - 1, mode);
//
//    if (Limit > 1) {
//        insertionSort(A);
//    }
//}
//
//void rQuickSort(int* A, int l, int r, int mode) {
//    int k;
//    int* a = l, * b = r;
//
//    if (r - l >= Limit) {
//        k = findPrivot(A, l, r, mode);
//        inPlacePartition(A, l, r, k, &a, &b); //a,b에 값 저장
//
//        rQuickSort(A, l, a - 1, mode);
//        rQuickSort(A, b + 1, r, mode);
//    }
//}
//
//void insertionSort(int* A) {
//    int* arr = A;
//    int i = 1, j, target;
//
//    while (i < n) {
//        j = i - 1;
//        target = arr[i];
//        while (arr[j] > target&& j >= 0) {
//            arr[j + 1] = arr[j];
//            j--;
//        }
//        arr[j + 1] = target;
//        i++;
//    }
//}//삽입정렬
//
//int findPrivot(int* A, int l, int r, int mode) {
//    long num;
//
//    if (r - l == 1) return l;
//
//    if (mode == 0) return r; //deterministic1
//    else if (mode == 1) { //deterministic3
//        if (r - l < 3) return l;
//
//        return findIndexOfMedianOfThree(A, l, (l + r) / 2, r);
//    }
//    if (mode == 2) return ((((long)rand() << 15) | rand()) % (r - l + 1)) + l; //randomized1
//
//    else { //randomized3
//        if (r - l < 3) return l;
//
//        int a = ((((long)rand() << 15) | rand()) % (r - l + 1)) + l;
//        int b = ((((long)rand() << 15) | rand()) % (r - l + 1)) + l;
//        int c = ((((long)rand() << 15) | rand()) % (r - l + 1)) + l;
//
//        return findIndexOfMedianOfThree(A, a, b, c);
//    }
//}
//
//int findIndexOfMedianOfThree(int* A, int a, int b, int c) {
//    if (A[a] >= A[b]) {
//        if (A[b] >= A[c]) return b; //a>b>c
//        else if (A[a] <= A[c]) return c; //c>a>b
//        else return c; //a>c>b
//    }
//    else if (A[a] >= A[c]) return a; //b>a>c
//    else if (A[b] >= A[c]) return c; //b>c>a
//    else return b; //c>b>a
//
//} //중앙값
//
//void inPlacePartition(int* A, int l, int r, int k, int* a, int* b) {
//    int p = A[k];
//    int i, j;
//
//    swapElem(A + k, A + r);
//
//    i = l; j = r - 1;
//
//    //a값
//    while (i <= j) {
//        while (i <= j && A[i] <= p) i++;
//        while (j >= i && A[j] >= p) j--;
//        if (i < j) swapElem(A + i, A + j);
//    }
//    *a = i;
//
//
//    //b값
//    j = r - 1;
//    while (i <= j) {
//
//        while (i <= j && A[i] == p) i += 1;
//        while (j >= i && A[j] > p) j -= 1;
//        if (i < j) swapElem(A + i, A + j);
//    }
//
//    *b = i;
//    swapElem(A + i, A + r);
//} //분할
//
//void swapElem(int* a, int* b) {
//    int tmp;
//    tmp = *b;
//    *b = *a;
//    *a = tmp;
//}


//#include <stdio.h> // 과제 2
//#include <string.h>
//#include <stdlib.h>
//#include <time.h>
//
///* 전역 변수 */
//int n = 100000;
//int Limits[4] = {1, 100, 500, 1000};
//int Limit;
///* 함수 */
//int *createArray (); // 배열 만드는 함수 -> 배열 반환
//int *copyArray (int *A); // 배열을 복사하는 함수 -> 배열 반환
//void quickSort (int *A, int mode); // Limit까지 퀵정렬 (mode 변수는 결정적 1,3과 무작위 1,3을 구분해주는 변수)
//void rQuicSort (int *A, int l, int r, int mode); // 재귀적으로 l부터 r까지 퀵정렬(mode 변수는 결정적 1,3과 무작위 1,3을 구분해주는 변수)
//void insertionSort (int *A); // 삽입정렬
//int findPivot (int *A, int l, int r, int mode); // 퀵정렬에 사용할 피벗을 찾아주는 함수
//int findIndexOfMedianOfThree (int *A, int a, int b, int c); // 3-중앙값 구하는 함수
//int *inPlacePartition (int *A, int l, int r, int k); // 제자리 분할하는 함수 -> LT, EQ, GT로 분할하여 EQ의 범위를 반환하는 함수
//void swap (int *a, int *b);
//
//int main () {
//
//    srand((unsigned int)time(NULL)); // 난수 초기화
//
//    clock_t start, finish; // 정렬 함수들의 걸리는 시간을 측정하기 위해 시작시간과 마지막시간을 저장하기 위한 변수
//    double duration; // 정렬 함수들이 걸리는 시간을 저장하기 위한 double형 변수
//
//    int *A, *Acopy = NULL;
//
//    A = createArray();
//
//    printf("%5s     %-10s     %-10s     %-10s     %-10s\n", "Limit", "결정적 1", "결정적 3", "무작위 1", "무작위 3");
//
//    A = createArray();
//
//    for (int i = 0; i < 4; i++) {
//        Limit = Limits[i];
//
//        printf("%-5d", Limits[i]);
//
//        for (int j = 0; j < 4; j++) {
//            Acopy = copyArray(A);
//
//            start = clock();
//            quickSort(Acopy, j);
//            finish = clock();
//
//            duration = (double) (finish - start) / CLOCKS_PER_SEC;
//
//            printf("     %-10f", duration);
//        }
//        printf("\n");
//    }
//
//    return 0;
//}
//
//int *createArray () {
//
//    int *new = NULL;
//
//    new = (int *) malloc(n * sizeof(int));
//
//    for (int i = 0; i < n; i++) {
//        new[i] = ((((long) rand() << 15) | rand()) % n) + 1;
//    }
//
//    return new;
//} // 배열 만드는 함수 -> 배열 반환
//int *copyArray (int *A) {
//
//    int *Acopy = NULL;
//
//    Acopy = (int *) malloc(n * sizeof(int));
//
//    for (int i = 0; i < n; i++) {
//        Acopy[i] = A[i];
//    }
//
//    return Acopy;
//} // 배열을 복사하는 함수 -> 배열 반환
//void quickSort (int *A, int mode) {
//
//    rQuicSort(A, 0, n - 1, mode);
//
//    if (Limit > 1) {
//        insertionSort(A);
//    }
//
//    return;
//} // Limit까지 퀵정렬 (mode 변수는 결정적 1,3과 무작위 1,3을 구분해주는 변수)
//void rQuicSort (int *A, int l, int r, int mode) {
//
//    int k = 0;
//    int *loc = 0;
//    int a, b = 0;
//
//    if (r - l >= Limit) {
//        k = findPivot(A, l, r, mode);
//        loc = inPlacePartition(A, l, r, k);
//        a = loc[0];
//        b = loc[1];
//
//        rQuicSort(A, l, a - 1, mode);
//        rQuicSort(A, b + 1, r, mode);
//    }
//
//    return;
//} // 재귀적으로 l부터 r까지 퀵정렬(mode 변수는 결정적 1,3과 무작위 1,3을 구분해주는 변수)
//void insertionSort (int *A) {
//
//    int target = 0;
//    int j = 0;
//
//    for (int i = 1; i < n; i++) {
//        target = A[i];
//        j = i - 1;
//        while ((j >= 0) && (A[j] > target)) {
//            A[j + 1] = A[j];
//            j -= 1;
//        }
//        A[j + 1] = target;
//        j = 0;
//    }
//
//    return;
//} // 삽입정렬
//int findPivot (int *A, int l, int r, int mode) {
//
//    if (r - l == 1) {
//        return l;
//    }
//
//    switch (mode) {
//        case 0: // deterministic1
//            return r;
//            break;
//        case 1: // deterministic3
//            if (r - l < 3) {
//                return l;
//            }
//            return findIndexOfMedianOfThree(A, l, (l + r) / 2, r);
//            break;
//        case 2: // randomized1
//            return ((((long) rand() << 15) | rand()) % (r - l + 1)) + l;
//            break;
//        case 3: // randomized3
//            if (r - l < 3) {
//                return l;
//            }
//            int a, b, c = 0;
//
//            a = ((((long) rand() << 15) | rand()) % (r - l + 1)) + l;
//            b = ((((long) rand() << 15) | rand()) % (r - l + 1)) + l;
//            c = ((((long) rand() << 15) | rand()) % (r - l + 1)) + l;
//
//            return findIndexOfMedianOfThree(A, a, b, c);
//            break;
//        default:
//            break;
//    }
//
//    return -1;
//} // 퀵정렬에 사용할 피벗을 찾아주는 함수
//int findIndexOfMedianOfThree (int *A, int a, int b, int c) {
//
//    if (A[a] >= A[b]) {
//        if (A[b] >= A[c]) {
//            return b; // a > b > c
//        }
//        else if (A[a] <= A[c]) {
//            return a; // c > a > b
//        }
//        else {
//            return c; // a > c > b
//        }
//    }
//    else if (A[a] >= A[c]) {
//        return a; // b > a > c
//    }
//    else if (A[b] >= A[c]) {
//        return c; // b > c > a
//    }
//    else {
//        return b; // c > b > a
//    }
//
//} // 3-중앙값 구하는 함수
//int *inPlacePartition (int *A, int l, int r, int k) {
//
//    int p = 0;
//    int i, j = 0;
//    int *ans = NULL;
//    ans = (int *) malloc(2 * sizeof(int));
//
//    p = A[k];
//    swap(A + k, A + r);
//
//    i = l;
//    j = r - 1;
//
//    /* 피봇을 기준으로 작은 원소를 LT로 모으고 크고"같은" 원소를 GT로 모으기 */
//    while (i <= j) {
//        while (i <= j && A[i] < p) {
//            i += 1;
//        }
//        while (j >= i && A[j] >= p) {
//            j -= 1;
//        }
//        if (i < j) {
//            swap(A + i, A + j);
//        }
//    }
//
//    ans[0] = i;
//
//    /* 피봇을 기준으로 GT에서 피봇과 같은 원소를 왼쪽으로 정렬하기*/
//    j = r - 1;
//    while (i <= j) {
//        while (i <= j && A[i] == p) {
//            i += 1;
//        }
//        while (i <= j && A[j] > p) {
//            j -= 1;
//        }
//        if (i < j) {
//            swap(A + i, A + j);
//        }
//    }
//
//    ans[1] = i;
//
//    swap(A + i, A + r);
//
//    return ans;
//} // 제자리 분할하는 함수 -> LT, EQ, GT로 분할하여 EQ의 범위를 반환하는 함수
//void swap (int *a, int *b) {
//
//    int tmp = 0;
//
//    tmp = *a;
//    *a = *b;
//    *b = tmp;
//
//    return;
//}


//#include <stdio.h> // 과제 2
//#include <string.h>
//#include <stdlib.h>
//#include <time.h>
//
///* 전역 변수 */
//int n = 100000;
//int Limits[4] = {1, 100, 500, 1000};
//int Limit;
///* 함수 */
//int *createArray (void); // 배열 만드는 함수 -> 배열 반환
//int *copyArray (int *A); // 배열을 복사하는 함수 -> 배열 반환
//void quickSort (int *A, int mode); // 부트리 크기가 Limit까지 퀵정렬 -> 그 다음은 삽입 정렬로 마무리 (mode 변수는 결정적 1,3과 무작위 1,3을 구분해주는 변수)
//void rQuickSort (int *A, int l, int r, int mode); // 재귀적으로 l부터 r까지, 부트리의 크기가 Limit보다 클때까지 퀵정렬(mode 변수는 결정적 1,3과 무작위 1,3을 구분해주는 변수)
//void insertionSort (int *A); // 삽입정렬
//int findPivot (int *A, int l, int r, int mode); // 퀵정렬에 사용할 피벗을 찾아주는 함수
//int findIndexOfMedianOfThree (int *A, int a, int b, int c); // 3-중앙값 구하는 함수
//int *inPlacePartition (int *A, int l, int r, int k); // 제자리 분할 -> LT, EQ, GT로 분할하여 EQ의 범위 구함
//void swap (int *a, int *b);
//
//int main () {
//
//    srand((unsigned int)time(NULL)); // 난수 초기화
//
//    clock_t start, finish; // 정렬 함수들의 걸리는 시간을 측정하기 위해 시작시간과 마지막시간을 저장하기 위한 변수
//    double duration; // 정렬 함수들이 걸리는 시간을 저장하기 위한 double형 변수
//
//    int *A = NULL;
//    int *Acopy = NULL;
//
//    A = createArray(); // 배열 A 만들기
//
//    printf("%-5s     %-15s     %-15s     %-15s     %-15s\n", "Limit", "결정적 1", "결정적 3", "무작위 1", "무작위 3");
//
//    for (int i = 0; i < 4; i++) {
//        Limit = Limits[i]; // Limits 배열에서 필요한 정보 Limit에 저장
//
//        printf("%-5d", Limits[i]);
//
//        for (int j = 0; j < 4; j++) {
//            Acopy = copyArray(A); // 배열 A 복사
//
//            start = clock();
//            quickSort(Acopy, j); // 퀵정렬 실행
//            finish = clock();
//
//            duration = (double) (finish - start) / CLOCKS_PER_SEC;
//
//            printf("     %-10.8f", duration);
//
//            free(Acopy);
//        }
//        printf("\n");
//    }
//
//    free(A);
//
//    return 0;
//}
//
//int *createArray (void) {
//
//    int *new = NULL;
//
//    new = (int *) malloc(n * sizeof(int));
//
//    for (int i = 0; i < n; i++) {
//        new[i] = ((((long) rand() << 15) | rand()) % n) + 1; // 1부터 n(100000) 사이의 임의 수 배열에 저장
//    }
//
//    return new;
//} // 배열 만드는 함수 -> 배열 반환
//int *copyArray (int *A) {
//
//    int *Acopy = NULL;
//
//    Acopy = (int *) malloc(n * sizeof(int));
//
//    for (int i = 0; i < n; i++) {
//        Acopy[i] = A[i];
//    }
//
//    return Acopy;
//} // 배열을 복사하는 함수 -> 배열 반환
//void quickSort (int *A, int mode) {
//
//    rQuickSort(A, 0, n - 1, mode); // 부트리의 크기가 Limit 크기까지만 퀵정렬 실행 (mode에 따라 피봇이 달라짐)
//
//    if (Limit > 1) {
//        insertionSort(A); // 부트리의 크기가 Limit 크기까지 퀵정렬 실행 이후 삽입 정렬 실행
//    }
//
//    return;
//} // Limit까지 퀵정렬 (mode 변수는 결정적 1,3과 무작위 1,3을 구분해주는 변수)
//void rQuickSort (int *A, int l, int r, int mode) {
//
//    int k = 0; // 피봇을 저장할 변수
//    int *range = NULL;
//    range = (int *) malloc(2 * sizeof(int));
//    int a, b = 0; // EQ의 범위를 저장할 변수
//
//    if (r - l >= Limit) {
//        k = findPivot(A, l, r, mode); // findPivot 함수를 불러 k에 피봇 저장
//        range = inPlacePartition(A, l, r, k); // inPlacePartition 함수를 불러 EQ의 범위 반환
//
//        a = range[0];
//        b = range[1];
//
//        /* 재귀적으로 퀵정렬 실행 */
//        rQuickSort(A, l, a - 1, mode);
//        rQuickSort(A, b + 1, r, mode);
//    }
//
//    return;
//} // 재귀적으로 l부터 r까지 퀵정렬(mode 변수는 결정적 1,3과 무작위 1,3을 구분해주는 변수)
//void insertionSort (int *A) {
//
//    int target = 0; // 삽입정렬을 당할 원소를 저장할 변수
//    int j = 0; // 삽입정렬되어 target이 위치할 곳을 저장할 변수
//
//    for (int i = 1; i < n; i++) {
//        target = A[i];
//        j = i - 1;
//        while ((j >= 0) && (A[j] > target)) {
//            A[j + 1] = A[j];
//            j -= 1;
//        }
//        A[j + 1] = target;
//    }
//
//    return;
//} // 삽입정렬
//int findPivot (int *A, int l, int r, int mode) {
//
//    if (mode == 0) { // deterministic1
//        return r;
//    }
//
//    if (mode == 2) { // randomized1
//        return ((((long) rand() << 15) | rand()) % (r - l + 1)) + l;
//    }
//
//    if (r - l == 1) {
//        return l;
//    }
//
//    int a = 0;
//    int b = 0;
//    int c = 0;
//
//    switch (mode) {
//        case 1: // deterministic3
//            if (r - l < 3) {
//                return l;
//            }
//            a = l;
//            b = (l + r) / 2;
//            c = r;
//
//            break;
//        case 3: // randomized3
//            if (r - l < 3) {
//                return l;
//            }
//
//            a = ((((long) rand() << 15) | rand()) % (r - l + 1)) + l;
//            b = ((((long) rand() << 15) | rand()) % (r - l + 1)) + l;
//            c = ((((long) rand() << 15) | rand()) % (r - l + 1)) + l;
//
//            break;
//        default:
//            break;
//    }
//
//    return findIndexOfMedianOfThree(A, a, b, c);
//} // 퀵정렬에 사용할 피벗을 찾아주는 함수
//int findIndexOfMedianOfThree (int *A, int a, int b, int c) {
//
//    if (A[a] >= A[b]) {
//        if (A[b] >= A[c]) {
//            return b; // a > b > c
//        }
//        else if (A[a] <= A[c]) {
//            return a; // c > a > b
//        }
//        else {
//            return c; // a > c > b
//        }
//    }
//    else if (A[a] >= A[c]) {
//        return a; // b > a > c
//    }
//    else if (A[b] >= A[c]) {
//        return c; // b > c > a
//    }
//    else {
//        return b; // c > b > a
//    }
//
//} // 3-중앙값 구하는 함수
//int *inPlacePartition (int *A, int l, int r, int k) {
//
//    int p = 0; // 피봇을 저장할 변수
//    int i, j = 0;
//    int *ans = NULL;
//    ans = (int *) malloc(2 * sizeof(int));
//
//    p = A[k];
//    swap(A + k, A + r);
//
//    i = l;
//    j = r - 1;
//
//    /* 피봇을 기준으로 작은 원소를 LT로 모으고 크고"같은" 원소를 GT로 모으기 */
//    while (i <= j) {
//        while (i <= j && A[i] < p) {
//            i += 1;
//        }
//        while (j >= i && A[j] >= p) {
//            j -= 1;
//        }
//        if (i < j) {
//            swap(A + i, A + j);
//        }
//    }
//
//    ans[0] = i; // EQ범위 시작 위치
//
//    /* 피봇을 기준으로 GT에서 피봇과 같은 원소를 왼쪽으로 정렬하기*/
//    j = r - 1;
//    while (i <= j) {
//        while (i <= j && A[i] == p) {
//            i += 1;
//        }
//        while (i <= j && A[j] > p) {
//            j -= 1;
//        }
//        if (i < j) {
//            swap(A + i, A + j);
//        }
//    }
//
//    ans[1] = i; // EQ범위의 끝 위치
//
//    swap(A + i, A + r);
//
//    return ans;
//} // 제자리 분할하는 함수 -> LT, EQ, GT로 분할하여 EQ의 범위를 반환하는 함수
//void swap (int *a, int *b) {
//
//    int tmp = 0;
//
//    tmp = *a;
//    *a = *b;
//    *b = tmp;
//
//    return;
//}


#include <stdio.h> // 과제 2
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* 전역 변수 */
int n = 100000;
int Limits[4] = {1, 100, 500, 1000};
int Limit;
/* 함수 */
int *createArray (void); // 배열 만드는 함수 -> 배열 반환
int *copyArray (int *A); // 배열을 복사하는 함수 -> 배열 반환
void quickSort (int *A, int mode); // 부트리 크기가 Limit까지 퀵정렬 -> 그 다음은 삽입 정렬로 마무리 (mode 변수는 결정적 1,3과 무작위 1,3을 구분해주는 변수)
void rQuicSort (int *A, int l, int r, int mode); // 재귀적으로 l부터 r까지, 부트리의 크기가 Limit보다 클때까지 퀵정렬(mode 변수는 결정적 1,3과 무작위 1,3을 구분해주는 변수)
void insertionSort (int *A); // 삽입정렬
int findPivot (int *A, int l, int r, int mode); // 퀵정렬에 사용할 피벗을 찾아주는 함수
int findIndexOfMedianOfThree (int *A, int a, int b, int c); // 3-중앙값 구하는 함수
void inPlacePartition (int *A, int l, int r, int k, int *a, int *b); // 제자리 분할 -> LT, EQ, GT로 분할하여 EQ의 범위 구함
void swap (int *a, int *b);

int main () {

    srand((unsigned int)time(NULL)); // 난수 초기화

    clock_t start, finish; // 정렬 함수들의 걸리는 시간을 측정하기 위해 시작시간과 마지막시간을 저장하기 위한 변수
    double duration; // 정렬 함수들이 걸리는 시간을 저장하기 위한 double형 변수

    int *A, *Acopy = NULL;

    A = createArray(); // 배열 A 만들기

    printf("%-5s     %-15s     %-15s     %-15s     %-15s\n", "Limit", "결정적 1", "결정적 3", "무작위 1", "무작위 3");

    for (int i = 0; i < 4; i++) {
        Limit = Limits[i]; // Limits 배열에서 필요한 정보 Limit에 저장

        printf("%-5d", Limits[i]);

        for (int j = 0; j < 4; j++) {
            Acopy = copyArray(A); // 배열 A 복사

            start = clock();
            quickSort(Acopy, j); // 퀵정렬 실행
            finish = clock();

            duration = (double) (finish - start) / CLOCKS_PER_SEC;

            printf("     %-10.8f", duration);
            
            free(Acopy);
        }
        printf("\n");
    }

    free(A);

    return 0;
}

int *createArray (void) {

    int *new = NULL;

    new = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        new[i] = ((((long) rand() << 15) | rand()) % n) + 1; // 1부터 n(100000) 사이의 임의 수 배열에 저장
    }

    return new;
} // 배열 만드는 함수 -> 배열 반환
int *copyArray (int *A) {

    int *Acopy = NULL;

    Acopy = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        Acopy[i] = A[i];
    }

    return Acopy;
} // 배열을 복사하는 함수 -> 배열 반환
void quickSort (int *A, int mode) {

    rQuicSort(A, 0, n - 1, mode); // 부트리의 크기가 Limit 크기까지만 퀵정렬 실행 (mode에 따라 피봇이 달라짐)

    if (Limit > 1) {
        insertionSort(A); // 부트리의 크기가 Limit 크기까지 퀵정렬 실행 이후 삽입 정렬 실행
    }

    return;
} // Limit까지 퀵정렬 (mode 변수는 결정적 1,3과 무작위 1,3을 구분해주는 변수)
void rQuicSort (int *A, int l, int r, int mode) {

    int k = 0; // 피봇을 저장할 변수
    int a, b = 0; // EQ의 범위를 저장할 변수

    if (r - l >= Limit) {
        k = findPivot(A, l, r, mode); // findPivot 함수를 불러 k에 피봇 저장
        inPlacePartition(A, l, r, k, &a, &b); // inPlacePartition 함수를 불러 EQ의 범위 변수 a, b에 저장

        /* 재귀적으로 퀵정렬 실행 */
        rQuicSort(A, l, a - 1, mode);
        rQuicSort(A, b + 1, r, mode);
    }

    return;
} // 재귀적으로 l부터 r까지 퀵정렬(mode 변수는 결정적 1,3과 무작위 1,3을 구분해주는 변수)
void insertionSort (int *A) {

    int target = 0; // 삽입정렬을 당할 원소를 저장할 변수
    int j = 0; // 삽입정렬되어 target이 위치할 곳을 저장할 변수

    for (int i = 1; i < n; i++) {
        target = A[i];
        j = i - 1;
        while ((j >= 0) && (A[j] > target)) {
            A[j + 1] = A[j];
            j -= 1;
        }
        A[j + 1] = target;
        j = 0;
    }

    return;
} // 삽입정렬
int findPivot (int *A, int l, int r, int mode) {

    if (mode == 0) { // deterministic1
        return r;
    }

    if (mode == 2) { // randomized1
        return ((((long) rand() << 15) | rand()) % (r - l + 1)) + l;
    }

    if (r - l == 1) {
        return l;
    }

    int a = 0;
    int b = 0;
    int c = 0;

    switch (mode) {
        case 1: // deterministic3
            if (r - l < 3) {
                return l;
            }
            a = l;
            b = (l + r) / 2;
            c = r;

            break;
        case 3: // randomized3
            if (r - l < 3) {
                return l;
            }

            a = ((((long) rand() << 15) | rand()) % (r - l + 1)) + l;
            b = ((((long) rand() << 15) | rand()) % (r - l + 1)) + l;
            c = ((((long) rand() << 15) | rand()) % (r - l + 1)) + l;

            break;
        default:
            break;
    }

    return findIndexOfMedianOfThree(A, a, b, c);
} // 퀵정렬에 사용할 피벗을 찾아주는 함수
int findIndexOfMedianOfThree (int *A, int a, int b, int c) {

    if (A[a] >= A[b]) {
        if (A[b] >= A[c]) {
            return b; // a > b > c
        }
        else if (A[a] <= A[c]) {
            return a; // c > a > b
        }
        else {
            return c; // a > c > b
        }
    }
    else if (A[a] >= A[c]) {
        return a; // b > a > c
    }
    else if (A[b] >= A[c]) {
        return c; // b > c > a
    }
    else {
        return b; // c > b > a
    }

} // 3-중앙값 구하는 함수
void inPlacePartition (int *A, int l, int r, int k, int *a, int *b) {

    int p = 0; // 피봇을 저장할 변수
    int i, j = 0;

    p = A[k];
    swap(A + k, A + r);

    i = l;
    j = r - 1;

    /* 피봇을 기준으로 작은 원소를 LT로 모으고 크고"같은" 원소를 GT로 모으기 */
    while (i <= j) {
        while (i <= j && A[i] < p) {
            i += 1;
        }
        while (j >= i && A[j] >= p) {
            j -= 1;
        }
        if (i < j) {
            swap(A + i, A + j);
        }
    }

    *a = i; // EQ범위 시작 위치

    /* 피봇을 기준으로 GT에서 피봇과 같은 원소를 왼쪽으로 정렬하기*/
    j = r - 1;
    while (i <= j) {
        while (i <= j && A[i] == p) {
            i += 1;
        }
        while (i <= j && A[j] > p) {
            j -= 1;
        }
        if (i < j) {
            swap(A + i, A + j);
        }
    }

    *b = i; // EQ범위의 끝 위치

    swap(A + i, A + r);

    return;
} // 제자리 분할하는 함수 -> LT, EQ, GT로 분할하여 EQ의 범위를 반환하는 함수
void swap (int *a, int *b) {

    int tmp = 0;

    tmp = *a;
    *a = *b;
    *b = tmp;

    return;
}

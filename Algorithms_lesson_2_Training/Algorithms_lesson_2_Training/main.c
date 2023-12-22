//
//  main.c
//  Algorithms_lesson_2_Training
//
//  Created by 김도윤 on 2022/09/10.
//

//#include <stdio.h> // 문제 1
//#include <string.h>
//#include <stdlib.h>
//
//void selection_sort (int *arr, int n); // 선택 정렬 함수
//
//int main () {
//
//    int n = 0;
//
//    scanf("%d", &n);
//
//    int *arr = NULL;
//
//    arr = (int *) malloc(n * sizeof(n));
//    if (arr == NULL) {
//        return -1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        scanf("%d", arr + i);
//    }
//
//    selection_sort(arr, n);
//
//    for (int i = 0; i < n; i++) {
//        printf(" %d", *(arr + i));
//    }
//    printf("\n");
//
//    if (arr != NULL) {
//        free(arr);
//    }
//
//    return 0;
//}
//
//void selection_sort (int *arr, int n) { // 선택 정렬 함수
//
//    int b_num = -1; // 가장 큰 수를 담을 변수
//    int b_num_loc = 0; // 가장 큰 수가 리스트에서 위치한 순위 저장 변수
//    int temp = 0;
//
//    for (int i = n - 1; i >= 0; i--) {
//        for (int j = 0; j <= i; j++) {
//            if (b_num < *(arr + j)) {
//                b_num = *(arr + j);
//                b_num_loc = j;
//            }
//        }
//        temp = *(arr + i);
//        *(arr + i) = *(arr + b_num_loc);
//        *(arr + b_num_loc) = temp;
//
//        b_num_loc = 0;
//        b_num = -1;
//    }
//
//}


//#include <stdio.h> // 문제 1 - 강의 자료에 있는 의사코드르 기반으로 짠 코드
//#include <string.h>
//#include <stdlib.h>
//
//void selection_sort (int *arr, int n); // 선택 정렬 함수
//
//int main () {
//
//    int n = 0;
//
//    scanf("%d", &n);
//
//    int *arr = NULL;
//
//    arr = (int *) malloc(n * sizeof(int));
//    if (arr == NULL) {
//        return -1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        scanf("%d", arr + i);
//    }
//
//    selection_sort(arr, n);
//
//    for (int i = 0; i < n; i++) {
//        printf(" %d", *(arr + i));
//    }
//    printf("\n");
//
//    if (arr != NULL) {
//        free(arr);
//    }
//
//    return 0;
//}
//
//void selection_sort (int *arr, int n) { // 선택 정렬 함수
//
//    int b_num_loc = -1; // 가장 큰 수가 리스트에서 위치한 순위 저장 변수
//    int temp = 0;
//
//    for (int i = n - 1; i >= 0; i--) {
//        b_num_loc = i;
//
//        for (int j = i - 1; j >= 0; j--) {
//            if (*(arr + j) > *(arr + b_num_loc)) {
//                b_num_loc = j;
//            }
//        }
//
//        if (b_num_loc != -1) {
//            temp = *(arr + i);
//            *(arr + i) = *(arr + b_num_loc);
//            *(arr + b_num_loc) = temp;
//        }
//
//        b_num_loc = 0;
//    }
//
//}


//#include <stdio.h> // 문제 2
//#include <string.h>
//#include <stdlib.h>
//
//void insertion_sort (int *arr, int n); // 삽입 정렬 함수
//
//int main () {
//
//    int n = 0;
//
//    scanf("%d", &n);
//
//    int *arr = NULL;
//
//    arr = (int *) malloc(n * sizeof(int));
//    if (arr == NULL) {
//        return -1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        scanf("%d", arr + i);
//    }
//
//    insertion_sort(arr, n);
//
//    for (int i = 0; i < n; i++) {
//        printf(" %d", *(arr + i));
//    }
//    printf("\n");
//
//    return 0;
//}
//
//void insertion_sort (int *arr, int n) {
//
//    int temp = 0; // 정렬해야할 새로운 원소를 저장할 변수
//    int loc = -1; // 새로운 원소가 있어야할 위치를 저장할 변수
//
//    for (int i = 1; i < n; i++) {
//        temp = *(arr + i);
//        for (int j = i - 1; j >= 0; j--) {
//            if (temp < *(arr + j)) {
//                *(arr + j + 1) = *(arr + j);
//                loc = j;
//            }
//        }
//
//        *(arr + loc) = temp;
//
//        loc = -1;
//    }
//
//}


#include <stdio.h> // 문제 2 - 강의 자료에 있는 의사코드르 기반으로 짠 코드
#include <string.h>
#include <stdlib.h>

void insertion_sort (int *arr, int n); // 삽입 정렬 함수

int main () {

    int n = 0;

    scanf("%d", &n);

    int *arr = NULL;

    arr = (int *) malloc(n * sizeof(int));
    if (arr == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }

    insertion_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf(" %d", *(arr + i));
    }
    printf("\n");

    if (arr != NULL) {
        free(arr);
    }

    return 0;
}

void insertion_sort (int *arr, int n) { // 삽입 정렬 함수

    int temp = 0; // 정렬해야할 새로운 원소를 저장할 변수
    int loc = -1; // 새로운 원소가 있어야할 위치를 저장할 변수

    for (int i = 1; i < n; i++) {
        temp = *(arr + i);
        loc = i - 1;

        while ((loc >= 0) & (*(arr + loc) > temp)) {
            *(arr + loc + 1) = *(arr + loc);
            loc -= 1;
        }

        *(arr + loc + 1) = temp;

        loc = -1;
    }

}


///*
// * 문제 3 - clock()을 이용하여 측정 (어차피 출력을 ms로 하면 되기 때문에 무방하다고 생각함) + 실행환경이 맥북이어서 windows.h를 사용할 수 없음.
// * 약 5회정도 n = 100000로 놓고 실행해본 결과 선택정렬 함수가 약 6ms정도 걸리고, 삽입정렬 함수가 약 3ms정도 걸리는 것을 알 수 있었다.
// * 이를 통해 삽입정렬 함수와 선택정렬 함수가 O(n^2)으로 동일하지만 실행시간은 삽입정렬 함수가 훨씬 더 짧게 걸린다는 것을 알 수 있었다.
// * 또한, n의 크기가 작아질수록 삽입정렬의 시간이 선택정렬에 비해 엄청 짧아진다는 것도 알 수 있었다. -> 배열의 크기가 작을수록 삽입정렬의 효율성이 좋다고 유추할 수 있었다.
// * 실행 환경: 맥북 프로 - cpu : M1 Pro
// */
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <time.h>
//
///*
// *arr = 정수 배열 A의 포인터 값
// n = 정렬할 원소의 개수
// */
//void selection_sort (int *arr, int n); // 선택 정렬 함수 (오름차순 정렬)
///*
// *arr = 정수 배열 B의 포인터 값
// n = 정렬할 원소의 개수
// */
//void insertion_sort (int *arr, int n); // 삽입 정렬 함수 (오름차순 정렬)
//
//int main () {
//
//    srand((unsigned int)time(NULL)); // 난수 초기화
//
//    clock_t start, finish; // 정렬 함수들의 걸리는 시간을 측정하기 위해 시작시간과 마지막시간을 저장하기 위한 변수
//    double duration; // 정렬 함수들이 걸리는 시간을 저장하기 위한 double형 변수
//
//    int n = 0; // 정렬할 원소의 개수
//
//    scanf("%d", &n);
//
//    int *arr_A = NULL; // 선택 정렬 함수에 쓸 배열 A 선언
//
//    arr_A = (int *) malloc(n * sizeof(int)); // 선택 정렬 함수에 쓸 배열 A 동적할당
//    if (arr_A == NULL) {
//        return -1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        *(arr_A + i) = rand() + 1; // 배열 A를 양의 정수로 초기화 -> rand()에 + 1을 한 이유
//    }
//
//    start = clock(); // 처음 시간 측정
//    selection_sort(arr_A, n); // 선택 정렬 함수
//    finish = clock(); // 마지막 시간 측정
//
//    duration = (double) (finish - start) / CLOCKS_PER_SEC; // 선택 정렬 함수가 걸리는 시간 계산
//    printf("%.9fms\n", duration); // 선택 정렬 함수가 걸리는 시간 출력
//
//    int *arr_B = NULL; // 삽입 정렬 함수에 쓸 배열 B 선언
//
//    arr_B = (int *) malloc(n * sizeof(int)); // 삽입 정렬 함수에 쓸 배열 B 동적할당
//    if (arr_B == NULL) {
//        return -1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        *(arr_B + i) = rand() + 1; // 배열 B를 양의 정수로 초기화 -> rand()에 + 1을 한 이유
//    }
//
//    start = clock(); // 처음 시간 측정
//    insertion_sort(arr_B, n); // 삽입 정렬 함수
//    finish = clock(); // 마지막 시간 측정
//
//    duration = (double) (finish - start) / CLOCKS_PER_SEC; // 삽입 정렬 함수가 걸리는 시간 계산
//    printf("%.9fms\n", duration); // 삽입 정렬 함수가 걸리는 시간 출력
//
//    // 동적할당한 배열 초기화
//    if (arr_A != NULL) {
//        free(arr_A);
//    }
//    if (arr_B != NULL) {
//        free(arr_B);
//    }
//
//    return 0;
//}
//
//void selection_sort (int *arr, int n) { // 선택 정렬 함수 (오름차순 정렬)
//
//    int s_num_loc = -1; // 가장 작은 수가 리스트에서 위치한 순위를 저장할 변수
//    int temp = 0; // swap할 때 사용할 임시 변수
//
//    for (int i = 0; i < n - 1; i++) {
//        s_num_loc = i;
//
//        for (int j = i + 1; j < n; j++) { // 정렬된 부분을 제외한 나머지 부분에서 가장 작은 수를 찾는 for문
//            if (*(arr + s_num_loc) > *(arr + j)) {
//                s_num_loc = j;
//            }
//        }
//        temp = *(arr + s_num_loc); // swap하는 부분
//        *(arr + s_num_loc) = *(arr + i);
//        *(arr + i) = temp;
//    }
//
//}
//void insertion_sort (int *arr, int n) { // 삽입 정렬 함수 (오름차순 정렬)
//
//    int temp = 0; // 정렬해야할 새로운 원소를 저장할 변수
//    int loc = -1; // 새로운 원소가 있어야할 위치를 저장할 변수
//
//    for (int i = 1; i < n; i++) {
//        temp = *(arr + i);
//        loc = i - 1;
//
//        while ((loc >= 0) & (*(arr + loc) > temp)) { // 새로운 원소가 있어야할 위치를 찾는 while문
//            *(arr + loc + 1) = *(arr + loc);
//            loc -= 1;
//        }
//
//        *(arr + loc + 1) = temp; // 새로운 원소가 있어야할 위치에 원소를 대입
//
//        loc = -1;
//    }
//
//}


//#include <stdio.h> // 문제 3
//#include <string.h>
//#include <stdlib.h>
//#include <time.h>
//#include <unistd.h> // == #include <windows.h>
//
//void insertion_sort (int *arr, int n); // 삽입 정렬 함수
//void selection_sort (int *arr, int n); // 선택 정렬 함수
//
//int main () {
//
//    LARGE_INTEGER ticksPerSec;
//    LARGE_INTEGER start, end, diff;
//
//    srand(time(NULL));
//
//    int n = 0;
//
//    scanf("%d", &n);
//
//    int *arr = NULL;
//
//    arr = (int *) malloc(n * sizeof(n));
//    if (arr == NULL) {
//        return -1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        *(arr + i) = rand() % n;
//    }
//
//    QueryPerformanceFrequency(&ticksPerSec);
//    QueryPerformanceCounter(&start);
//    insertion_sort(arr, n);
//    QueryPerformanceCounter(&end);
//
//    diff.QuadPart = end.QuadPart - start.QuadPart;
//    printf("time: %.12f sec\n\n", ((double)diff.QuadPart/(double)ticksPerSec.QuadPart));
//
//    int *arr2 = NULL;
//
//    arr2 = (int *) malloc(n * sizeof(n));
//    if (arr2 == NULL) {
//        return -1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        *(arr2 + i) = rand() % n;
//    }
//
//    QueryPerformanceFrequency(&ticksPerSec);
//    QueryPerformanceCounter(&start);
//    selection_sort(arr2, n);
//    QueryPerformanceCounter(&end);
//
//    diff.QuadPart = end.QuadPart – start.QuadPart;
//    printf("time: %.12f sec\n\n", ((double)diff.QuadPart/(double)ticksPerSec.QuadPart));
//
//    return 0;
//}
//
//void insertion_sort (int *arr, int n) {
//
//    int temp = 0; // 정렬해야할 새로운 원소를 저장할 변수
//    int loc = -1; // 새로운 원소가 있어야할 위치를 저장할 변수
//
//    for (int i = 1; i < n; i++) {
//        temp = *(arr + i);
//        for (int j = i - 1; j >= 0; j--) {
//            if (temp < *(arr + j)) {
//                *(arr + j + 1) = *(arr + j);
//                loc = j;
//            }
//        }
//
//        *(arr + loc) = temp;
//
//        loc = -1;
//    }
//
//}
//void selection_sort (int *arr, int n) {
//
//    int b_num = -1; // 가장 큰 수를 담을 변수
//    int b_num_loc = 0; // 가장 큰 수가 리스트에서 위치한 순위 저장 변수
//    int temp = 0;
//
//    for (int i = n - 1; i >= 0; i--) {
//        for (int j = 0; j <= i; j++) {
//            if (b_num < *(arr + j)) {
//                b_num = *(arr + j);
//                b_num_loc = j;
//            }
//        }
//        temp = *(arr + i);
//        *(arr + i) = *(arr + b_num_loc);
//        *(arr + b_num_loc) = temp;
//
//        b_num_loc = 0;
//        b_num = -1;
//    }
//
//}


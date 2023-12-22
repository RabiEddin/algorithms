//
//  main.c
//  Algorithms_lesson_5_Training
//
//  Created by 김도윤 on 2022/09/29.
//

//#include <stdio.h> // 문제 1 - 합병정렬 (******** 다시 짜보기 *********)
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct Node {
//    int elem;
//    struct Node *next;
//}NODE;
//
//void getNode (NODE **tmp, int key); // 새로운 노드 생성하는 함수
//void addNode (NODE **L, int key); // 새로운 노드를 기존 노드에 있는 마지막 부분에 연결하는 함수
//NODE *mergeSort (NODE *L, int n); // 단일연결리스트 L의 원소들을 합병 정렬하여 정렬된 결과를 오름차순으로 정렬
//NODE *rmergeSort (NODE *L, int s, int e); // rmergesort를 재귀하여 오름차순으로 정렬하는 함수
//NODE *merge (NODE **L1, NODE **L2); // 분할되어 정렬된 리스트 L1과 L2를 합병하는 함수
//void partition (NODE *L, NODE **L1, NODE **L2, int k); // 호출된 리스트 L을 L1과 L2로 분할하는 함수
//void Print (NODE *L); // 출력하는 함수
//
//int main () {
//
//    NODE *L = NULL;
//    int n = 0;
//    int key = 0;
//
//    scanf("%d", &n);
//
//    for (int i = 0; i < n; i++) {
//        scanf("%d", &key);
//        addNode(&L, key);
//    }
//
//    L = mergeSort(L, n);
//
//    Print(L);
//
//    free(L);
//
//    return 0;
//}
//
//void getNode (NODE **tmp, int key) {
//
//    *tmp = (NODE *) malloc(sizeof(NODE));
//    (*tmp)->elem = key;
//    (*tmp)->next = NULL;
//
//    return;
//}
//void addNode (NODE **L, int key) {
//
//    NODE *p = *L;
//    NODE *new = NULL;
//    getNode(&new, key);
//
//    if (*L == NULL) {
//        *L = new;
//    }
//    else {
//        while (p->next != NULL) {
//            p = p->next;
//        }
//        p->next = new;
//    }
//
//    return;
//}
//NODE *mergeSort (NODE *L, int n) {
//
//    L = rmergeSort(L, 0, n - 1);
//
//    return L;
//}
//NODE *rmergeSort (NODE *L, int s, int e) {
//
//    int m = 0;
//    NODE *L1 = NULL;
//    NODE *L2 = NULL;
//
//    if (s < e) {
//        m = (s + e) / 2; // 단일 연결리스트 L 분리 크기
//        partition(L, &L1, &L2, m); // 단일 연결리스트 L을 L1, L2로 분리
//        L1 = rmergeSort(L1, 0, m);
//        L2 = rmergeSort(L2, 0, e - m - 1);
//
//        L = merge(&L1, &L2);
//
//    }
//
//    return L;
//}
//NODE *merge (NODE **L1, NODE **L2) {
//
//    NODE *ans_H = NULL; // L1, L2를 합칠때 쓸 해더 노드
//    NODE *ans = NULL; // 헤더 노드를 가리키고 있는 노드
//    NODE *P_L1 = *L1, *P_L2 = *L2;
//
//    /* 처음 시작 노드를 L1과 L2중에 어느 것을 선택할 건지 */
//    if (P_L1->elem <= P_L2->elem) {
//        ans_H = P_L1;
//        P_L1 = P_L1->next;
//        ans = ans_H;
//    }
//    else {
//        ans_H = P_L2;
//        P_L2 = P_L2->next;
//        ans = ans_H;
//    }
//
//    /* L1과 L2를 비교하면서 합치는 과정 */
//    while ((P_L1 != NULL) && (P_L2 != NULL)) {
//        if (P_L1->elem <= P_L2->elem) {
//            ans_H->next = P_L1;
//            P_L1 = P_L1->next;
//            ans_H = ans_H->next;
//        }
//        else {
//            ans_H->next = P_L2;
//            P_L2 = P_L2->next;
//            ans_H = ans_H->next;
//        }
//    }
//
//    /* 그 외에 남은 원소들 고대로 넣는 과정 */
//    while (P_L1 != NULL) {
//        ans_H->next = P_L1;
//        P_L1 = P_L1->next;
//        ans_H = ans_H->next;
//    }
//    while (P_L2 != NULL) {
//        ans_H->next = P_L2;
//        P_L2 = P_L2->next;
//        ans_H = ans_H->next;
//    }
//
//
//    return ans;
//
//}
//void partition (NODE *L, NODE **L1, NODE **L2, int k) {
//
//    NODE *p = L;
//
//    *L1 = L;
//
//    for (int i = 0; i < k; i++) {
//        p = p->next;
//    }
//
//    *L2 = p->next;
//    p->next = NULL;
//
//}
//void Print (NODE *L) {
//
//    while (L != NULL) {
//        printf(" %d", L->elem);
//        L = L->next;
//    }
//    printf("\n");
//
//    return;
//}


//#include <stdio.h> // 문제 2
//#include <string.h>
//#include <stdlib.h>
//#include <time.h>
//
//void inPlaceQuickSort (int *arr, int l, int r); // 제자리 퀵정렬하는 함수
//int inPlacePartition (int *arr, int l, int r, int k); // 제자리 분할하는 함수
//int findPivot (int *arr, int l, int r); // 무작위로 피봇을 정하여 반환하는 함수
//void swap (int *a, int *b);
//void printQuickSortresult (int *arr, int n);
//
//int main () {
//
//    int n = 0;
//
//    scanf("%d", &n);
//
//    int *L = NULL;
//    L = (int *) malloc(n * sizeof(int));
//    if (L == NULL) {
//        return -1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        scanf("%d", &L[i]);
//    }
//
//    inPlaceQuickSort(L, 0, n - 1);
//
//    printQuickSortresult(L, n);
//
//    return 0;
//}
//
//void inPlaceQuickSort (int *arr, int l, int r) {
//
//    int pivot = 0;
//    int EQ_range = 0; // EQ의 범위
//
//    if (l >= r) {
//        return;
//    }
//
//    pivot = findPivot(arr, l, r);
//
//    EQ_range = inPlacePartition(arr, l, r, pivot);
//
//    inPlaceQuickSort(arr, l, EQ_range - 1);
//    inPlaceQuickSort(arr, EQ_range + 1, r);
//
//}
//int inPlacePartition (int *arr, int l, int r, int k) {
//
//    int p = 0;
//    int i, j = 0;
//
//    p = arr[k];
//    swap(&arr[k], &arr[r]);
//
//    i = l;
//    j = r - 1;
//
//    while (i <= j) {
//        while (i <= j && arr[i] <= p) {
//            i += 1;
//        }
//        while (j >= i && arr[j] >= p) {
//            j -= 1;
//        }
//        if (i < j) {
//            swap(&arr[i], &arr[j]);
//        }
//    }
//
//    swap(&arr[i], &arr[r]);
//
//    return i;
//}
//int findPivot (int *arr, int l, int r) {
//
//    srand((unsigned int)time(NULL)); // 난수 초기화
//
//    int pivot = 0;
//
//    pivot = rand() % (r - l + 1) + l; // l부터 r 사이의 변수 무작위로 피봇 설정
//
//    return pivot;
//}
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
//void printQuickSortresult (int *arr, int n) {
//
//    for (int i = 0; i < n; i++) {
//        printf(" %d", arr[i]);
//    }
//    printf("\n");
//
//    return;
//}


//#include <stdio.h> // 문제 2
//#include <string.h>
//#include <stdlib.h>
//#include <time.h>
//
//void inPlaceQuickSort (int *arr, int l, int r); // 제자리 퀵정렬하는 함수
//int *inPlacePartition (int *arr, int l, int r, int k); // 제자리 분할하는 함수
//int findPivot (int *arr, int l, int r); // 무작위로 피봇을 정하여 반환하는 함수
//void swap (int *a, int *b);
//void printQuickSortresult (int *arr, int n);
//
//int main () {
//
//    int n = 0;
//
//    scanf("%d", &n);
//
//    int *L = NULL;
//    L = (int *) malloc(n * sizeof(int));
//    if (L == NULL) {
//        return -1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        scanf("%d", &L[i]);
//    }
//
//    inPlaceQuickSort(L, 0, n - 1);
//
//    printQuickSortresult(L, n);
//
//    free(L);
//
//    return 0;
//}
//
//void inPlaceQuickSort (int *arr, int l, int r) {
//
//    int pivot = 0;
//    int *EQ_range = 0; // EQ의 범위
//
//    if (l >= r) {
//        return;
//    }
//
//    pivot = findPivot(arr, l, r);
//
//    EQ_range = inPlacePartition(arr, l, r, pivot);
//
//    inPlaceQuickSort(arr, l, EQ_range[0] - 1);
//    inPlaceQuickSort(arr, EQ_range[1] + 1, r);
//
//}
//int *inPlacePartition (int *arr, int l, int r, int k) {
//
//    int p = 0; // 피봇
//    int i, j = 0;
//    int num = 0; // 피봇과 같은 수의 개수
//
//    p = arr[k];
//    swap(&arr[k], &arr[r - num]);
//
//    for (int m = 0; m < r - 1; m++) {
//        if (p == arr[m] && m < r - num) {
//            num++;
//            swap(&arr[m], &arr[r - num]);
//        }
//    }
//    num++;
//
//    i = l;
//    j = r - num;
//
//    while (i <= j) {
//        while (i <= j && arr[i] <= p) {
//            i++;
//        }
//        while (j >= i && arr[j] >= p) {
//            j--;
//        }
//        if (i < j) {
//            swap(&arr[i], &arr[j]);
//        }
//    }
//
//    for (int m = 0; m < num; m++) {
//        swap(&arr[i + m], &arr[r - m]);
//    }
//
//    int *EQ_range = NULL;
//    EQ_range = (int *) malloc(2 * sizeof(int));
//    EQ_range[0] = i;
//    EQ_range[1] = i + num - 1;
//
//    return EQ_range;
//}
//int findPivot (int *arr, int l, int r) {
//
//    srand((unsigned int)time(NULL)); // 난수 초기화
//
//    int pivot = 0;
//
//    pivot = rand() % (r - l + 1) + l; // l부터 r 사이의 변수 무작위로 피봇 설정
//
//    return pivot;
//}
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
//void printQuickSortresult (int *arr, int n) {
//
//    for (int i = 0; i < n; i++) {
//        printf(" %d", arr[i]);
//    }
//    printf("\n");
//
//    return;
//}
//
//


//#include <stdio.h> // 문제 2
//#include <string.h>
//#include <stdlib.h>
//#include <time.h>
//
//void inPlaceQuickSort (int *arr, int l, int r); // 제자리 퀵정렬하는 함수
//int *inPlacePartition (int *arr, int l, int r, int k); // 제자리 분할하는 함수 -> LT, EQ, GT로 분할되어 EQ의 범위를 반환한다.
//int findPivot (int *arr, int l, int r); // 무작위로 피봇을 정하여 반환하는 함수
//void swap (int *a, int *b);
//void printQuickSortresult (int *arr, int n);
//
//int main () {
//
//    int n = 0;
//
//    scanf("%d", &n);
//
//    int *L = NULL;
//    L = (int *) malloc(n * sizeof(int));
//    if (L == NULL) {
//        return -1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        scanf("%d", &L[i]);
//    }
//
//    inPlaceQuickSort(L, 0, n - 1);
//
//    printQuickSortresult(L, n);
//
//    return 0;
//}
//
//void inPlaceQuickSort (int *arr, int l, int r) {
//
//    int pivot = 0;
//    int *EQ_range = NULL; // EQ의 범위
//
//    if (l >= r) {
//        return;
//    }
//
//    pivot = findPivot(arr, l, r);
//
//    EQ_range = inPlacePartition(arr, l, r, pivot);
//
//    inPlaceQuickSort(arr, l, EQ_range[0] - 1);
//    inPlaceQuickSort(arr, EQ_range[1] + 1, r);
//
//}
//int *inPlacePartition (int *arr, int l, int r, int k) {
//
//    int p = 0;
//    int i, j = 0;
//
//    p = arr[k];
//    swap(&arr[k], &arr[r]);
//
//    i = l;
//    j = r - 1;
//
//    while (i <= j) {
//        while (i <= j && arr[i] <= p) {
//            i += 1;
//        }
//        while (j >= i && arr[j] >= p) {
//            j -= 1;
//        }
//        if (i < j) {
//            swap(&arr[i], &arr[j]);
//        }
//    }
//
//    swap(&arr[i], &arr[r]);
//
//    /* EQ의 범위를 구하기 위한 코드 */
//    int tmp = 0;
//    int *ans = NULL;
//    ans = (int *) malloc(2 * sizeof(int));
//
//    ans[0] = i;
//    ans[1] = i;
//
//    tmp = ans[1];
//
//    while (1) {
//        if (arr[tmp] != arr[ans[1]]) {
//            ans[0] = tmp + 1;
//            break;
//        }
//        tmp--;
//    }
//
//    return ans;
//}
//int findPivot (int *arr, int l, int r) {
//
//    srand((unsigned int)time(NULL)); // 난수 초기화
//
//    int pivot = 0;
//
//    pivot = rand() % (r - l + 1) + l; // l부터 r 사이의 변수 무작위로 피봇 설정
//
//    return pivot;
//}
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
//void printQuickSortresult (int *arr, int n) {
//
//    for (int i = 0; i < n; i++) {
//        printf(" %d", arr[i]);
//    }
//    printf("\n");
//
//    return;
//}


#include <stdio.h> // 문제 2
#include <string.h>
#include <stdlib.h>
#include <time.h>

void inPlaceQuickSort (int *arr, int l, int r); // 제자리 퀵정렬하는 함수
int *inPlacePartition (int *arr, int l, int r, int k); // 제자리 분할하는 함수 -> LT, EQ, GT로 분할되어 EQ의 범위를 반환한다.
int findPivot (int *arr, int l, int r); // 무작위로 피봇을 정하여 반환하는 함수
void swap (int *a, int *b);
void printQuickSortresult (int *arr, int n);

int main () {

    int n = 0;

    scanf("%d", &n);

    int *L = NULL;
    L = (int *) malloc(n * sizeof(int));
    if (L == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &L[i]);
    }

    inPlaceQuickSort(L, 0, n - 1);

    printQuickSortresult(L, n);

    return 0;
}

void inPlaceQuickSort (int *arr, int l, int r) {

    int pivot = 0;
    int *EQ_range = NULL; // EQ의 범위

    if (l >= r) {
        return;
    }

    pivot = findPivot(arr, l, r);

    EQ_range = inPlacePartition(arr, l, r, pivot);

    inPlaceQuickSort(arr, l, EQ_range[0] - 1);
    inPlaceQuickSort(arr, EQ_range[1] + 1, r);

}
int *inPlacePartition (int *arr, int l, int r, int k) {

    int p = 0;
    int i, j = 0;
    int *ans = NULL;
    ans = (int *) malloc(2 * sizeof(int));

    p = arr[k];
    swap(arr + k, arr + r);

    i = l;
    j = r - 1;

    /* 피봇을 기준으로 작은 원소를 LT로 모으고 크고"같은" 원소를 GT로 모으기 */
    while (i <= j) {
        while (i <= j && arr[i] < p) {
            i += 1;
        }
        while (j >= i && arr[j] >= p) {
            j -= 1;
        }
        if (i < j) {
            swap(arr + i, arr + j);
        }
    }

    ans[0] = i;
    
    /* 피봇을 기준으로 GT에서 피봇과 같은 원소를 왼쪽으로 정렬하기*/
    j = r - 1;
    while (i <= j) {
        while (i <= j && arr[i] == p) {
            i += 1;
        }
        while (i <= j && arr[j] > p) {
            j -= 1;
        }
        if (i < j) {
            swap(arr + i, arr + j);
        }
    }
    
    ans[1] = i;
    
    swap(arr + i, arr + r);
    
    return ans;
}
int findPivot (int *arr, int l, int r) {

    srand((unsigned int)time(NULL)); // 난수 초기화

    int pivot = 0;

    pivot = rand() % (r - l + 1) + l; // l부터 r 사이의 변수 무작위로 피봇 설정

    return pivot;
}
void swap (int *a, int *b) {

    int tmp = 0;

    tmp = *a;
    *a = *b;
    *b = tmp;

    return;
}
void printQuickSortresult (int *arr, int n) {

    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    return;
}

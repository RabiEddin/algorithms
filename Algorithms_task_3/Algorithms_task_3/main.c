//
//  main.c
//  Algorithms_task_3
//
//  Created by 김도윤 on 2022/11/08.
//

//#include <stdio.h> // 과제 3 - 활성화인경우: 0 - 99사이의 정수 값을 가짐, 비활성화인경우: -2 값을 가짐, 비어있는 경우: -1 값을 가짐
//#include <string.h>
//#include <stdlib.h>
//// 전역 변수 설정
//int MAX = 23;
//
//int h_x (int key, int m); // 해시함수 1
//int hprime_x (int x, int q); // 해시함수 2
//void intitBucketArray (int *H); // 초기화
//int findElement (int *H, int k); // 탐색
//void insertItem (int *H, int k, int q); // 삽입
//int removeElement (int *H, int k, int q); // 삭제
//void printBucketArray (int *H, int m); // 출력
////void deactivate (int *d ); // 버켓 d를 비활성화
////void activate (int *d); // 버켓 d를 활성화
////int inactivate (int *d); // 버켓 d가 비활성인지 여부를 반환
////int active (int *d); // 버켓 d가 활성인지 여부를 반환
//
//int main () {
//
//    int q = 7;
//
//    int *H = NULL;
//    H = (int *) malloc(MAX * sizeof(int));
//    if (H == NULL) {
//        return -1;
//    }
//
//    intitBucketArray(H);
//
//    char mode = '0';
//    int key = 0;
//    int num = 0;
//
//    while (mode != 'q') {
//        scanf("%c", &mode);
//
//        switch (mode) {
//            case 'f':
//                scanf("%d", &key);
//                num = findElement(H, key);
//                if (num == -1) {
//                    printf("NoSuchKey\n");
//                }
//                else {
//                    printf("%d\n", num);
//                }
//                break;
//            case 'i':
//                scanf("%d", &key);
//                insertItem(H, key, q);
//                break;
//            case 'r':
//                scanf("%d", &key);
//                num = removeElement(H, key, q);
//                if (num == -1) {
//                    printf("NoSuchKey\n");
//                }
//                else {
//                    printf("%d\n", num);
//                }
//                break;
//            case 'p':
//                printBucketArray(H, MAX);
//                break;
//            case 'q':
//                break;
//            default:
//                break;
//        }
//        getchar();
//    }
//
//    return 0;
//}
//
//int h_x (int key, int m) {
//
//    return key % m;
//} // 해시함수 1
//int hprime_x (int x, int q) {
//
//    return q - (x % q);
//} // 해시함수 2
//void intitBucketArray (int *H) {
//
//    for (int i = 0; i < MAX; i++) {
//        H[i] = -1;
//    }
//
//    return;
//} // 초기화
//int findElement (int *H, int k) {
//
//    for (int i = 0; i < MAX; i++) {
//        if (H[i] == k) {
//            return k;
//        }
//    }
//
//    return -1;
//
//} // 탐색
//void insertItem (int *H, int k, int q) {
//
//    int i = 0;
//    int v = h_x(k, MAX);
//
//    if (k < 0 && k > 99) {
//        return;
//    }
//
//    while (i < MAX) { // 충돌인 경우 다음 걸로 원형으로 넘어가는 반복문
//
//        if (H[v] == -1 || H[v] == -2) {
//            H[v] = k;
//            printf("%d\n", H[v]);
//            return;
//        }
//        else {
//            if (H[v] == k) {
//                printf("The same value is in the hash table!!!\n"); // 중복 키인 경우
//                return;
//            }
//            v = h_x(v + hprime_x(k, q), MAX);
//            i++;
//        }
//    }
//
//    printf("Hashtable is full!!!\n"); // 해시 테이블이 만원일 경우
//
//    return;
//
//} // 삽입
//int removeElement (int *H, int k, int q) {
//
//    int i = 0;
//    int v = h_x(k, MAX);
//    int e = 0;
//
//    while (i < MAX) {
//
//        if (H[v] == -1) {
//            return -1;
//        }
//        else if ((0 <= H[v] && H[v] <= 99) && (H[v] == k)) {
//            e = H[v];
//            H[v] = -2;
//            return e;
//        }
//        else {
//            v = h_x(v + hprime_x(k, q), MAX);
//            i++;
//        }
//    }
//
//    return -1;
//} // 삭제
//void printBucketArray (int *H, int m) {
//
//    for (int i = 0; i < m; i++) {
//        if (i > 9) {
//            printf(" %d", i);
//        }
//        else {
//            printf("  %d", i);
//        }
//    }
//    printf("\n");
//
//    for (int i = 0; i < m; i++) {
//        if (H[i] == -1 || H[i] == -2) {
//            printf("  .");
//        }
//        else if (H[i] > 9) {
//            printf(" %d", H[i]);
//        }
//        else {
//            printf("  %d", H[i]);
//        }
//
//    }
//    printf("\n");
//
//    return;
//} // 출력
////void deactivate (int *d ); // 버켓 d를 비활성화
////void activate (int *d); // 버켓 d를 활성화
////int inactivate (int *d); // 버켓 d가 비활성인지 여부를 반환
////int active (int *d); // 버켓 d가 활성인지 여부를 반환



#include <stdio.h> // 과제 3
#include <string.h>
#include <stdlib.h>
// 전역 변수 설정
int MAX = 23;
// 구조체 배열 선언
typedef struct hash {
    int key;
    int mode; // 활성화인경우: 1, 비어있는 경우: 0, 비활성화인경우: -1,
}HASH;
// 함수 선언
int h_x (int key, int m); // 해시함수 1
int hprime_x (int x, int q); // 해시함수 2
void intitBucketArray (HASH *H); // 초기화
int findElement (HASH *H, int k, int q); // 탐색
void insertItem (HASH *H, int k, int q); // 삽입
int removeElement (HASH *H, int k, int q); // 삭제
void printBucketArray (HASH *H, int m); // 출력

int main () {

    int q = 7; // 두번째 해시함수에서 사용할 변수 지정

    HASH *H = NULL;
    H = (HASH *) malloc(MAX * sizeof(HASH));
    if (H == NULL) {
        return -1;
    }

    intitBucketArray(H); // 해시테이블 원소값 -1로 초기화 + 비어있는 경우(0)로 초기화

    char mode = '0';
    int key = 0;
    int num = 0;

    while (mode != 'q') {
        scanf("%c", &mode);

        switch (mode) {
            case 'f':
                scanf("%d", &key);
                num = findElement(H, key, q);
                if (num == -1) {
                    printf("NoSuchKey\n");
                }
                else {
                    printf("%d\n", num);
                }
                break;
            case 'i':
                scanf("%d", &key);
                insertItem(H, key, q);
                break;
            case 'r':
                scanf("%d", &key);
                num = removeElement(H, key, q);
                if (num == -1) {
                    printf("NoSuchKey\n");
                }
                else {
                    printf("%d\n", num);
                }
                break;
            case 'p':
                printBucketArray(H, MAX);
                break;
            case 'q':
                break;
            default:
                break;
        }
        getchar();
    }

    return 0;
}

int h_x (int key, int m) {

    return key % m;
} // 해시함수 1 - ok
int hprime_x (int x, int q) {

    return q - (x % q);
} // 해시함수 2 - ok
void intitBucketArray (HASH *H) {

    for (int i = 0; i < MAX; i++) {
        H[i].key = -1; // 키값 -1로 초기화
        H[i].mode = 0; // 비어있는 경우로 초기화
    }

    return;
} // 초기화 - ok
int findElement (HASH *H, int k, int q) {

    int i = 0;
    int v = h_x(k, MAX);
    int index = 0;
    
    if (k < 0 || k > 99) { // 저장 원소 범위에 맞지 않는 원소를 찾는 경우
        return -1;
    }
    
    while (i < MAX) {
        index = h_x(v + i * hprime_x(k, q), MAX);
        
        if (H[index].mode == 0) { // 해당 해시테이블이 비어 있는 경우
            return -1;
        }
        else if (H[index].mode == 1 && H[index].key == k) { // 해당 해시테이블의 원소(키)값이 찾는 원소(키)값과 일치하고 활성화인 경우
            return k;
        }
        else {
            i++;
        }
    }

    return -1;

} // 탐색 - ok
void insertItem (HASH *H, int k, int q) {

    int i = 0;
    int v = h_x(k, MAX);
    int index = 0;

    if (k < 0 || k > 99) { // 저장 원소 범위에 맞지 않는 원소를 저장하려고 하는 경우
        return;
    }

    while (i < MAX) { // 중복 키인지 확인하는 while문
        index = h_x(v + i * hprime_x(k, q), MAX);
        
        if (H[index].mode == 1 && H[index].key == k) { // 해당 해시테이블의 원소(키)값이 이미 있고, 활성화인 경우 (즉, 중복키인 경우)
            printf("The same value is in the hash table!!!\n");
            return;
        }
        else {
            i++;
        }
    }
    
    i = 0;
    index = 0;
    
    while (i < MAX) { // 중복키가 아닌 경우 삽입을 하는 while문
        index = h_x(v + i * hprime_x(k, q), MAX);
        
        if (H[index].mode == 0 || H[index].mode == -1) { // 해당 해시테이블이 비어있거나 비활성화인 경우, 그 위치에 삽입
            H[index].mode = 1; // 해당 해시테이블 활성화로 바꿈.
            H[index].key = k;
            printf("%d\n", H[index].key);
            return;
        }
        else {
            i++;
        }
    }
    
    printf("Hashtable is full!!!\n"); // 해시 테이블이 만원인 경우

    return;

} // 삽입 - ok
int removeElement (HASH *H, int k, int q) {

    int i = 0;
    int v = h_x(k, MAX);
    int e = 0;
    int index = 0;

    if (k < 0 || k > 99) { // 삭제하려는 원소가 저장 원소 범위에 맞지 않는 원소를 삭제하는 경우
        return -1;
    }

    while (i < MAX) {
        index = h_x(v + i * hprime_x(k, q), MAX);
        
        if (H[index].mode == 0) { // 해당 헤시테이블이 비어 있는 경우
            return -1;
        }
        // 해당 해시테이블이 활성화이고 해당 해시테이블의 원소가 삭제하려는 원소와 일치하는 경우
        else if ((H[index].mode == 1) && (H[index].key == k)) {
            e = H[index].key;
            H[index].mode = -1; // 비활성화
            return e;
        }
        else {
            i++;
        }
    }

    return -1;
} // 삭제 - ok
void printBucketArray (HASH *H, int m) {

    for (int i = 0; i < m; i++) {
        if (i > 9) {
            printf(" %d", i);
        }
        else {
            printf("  %d", i);
        }
    }
    printf("\n");

    for (int i = 0; i < m; i++) {
        if (H[i].mode == 0 || H[i].mode == -1) { // 비활성화이거나 비어있는 경우 점으로 표현
            printf("  .");
        }
        else if (H[i].key > 9 && H[i].mode == 1) {
            printf(" %d", H[i].key);
        }
        else if (H[i].key <= 9 && H[i].mode == 1) {
            printf("  %d", H[i].key);
        }

    }
    printf("\n");

    return;
} // 출력 - ok



//
//  main.c
//  Algorithms_lesson_9_Training
//
//  Created by 김도윤 on 2022/10/27.
//

//#include <stdio.h> // 문제 1 ****** 삭제 함수 이해하기 *********
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct Node {
//
//    int key;
//    struct Node *next;
//
//}NODE;
//
//NODE *getNode (int key);
//int h_x (int key, int m); // 해시 함수
//void initBucketArray (NODE **H, int m); // 초기화
//void insertItem (NOiDE **H, int key, int m); // 삽입
//int findElement (NODE **H, int key, int m); // 원소 탐색
//int removeElement (NODE **H, int key, int m); // 삭제
//void printBucketArray (NODE **H, int m); // 출력
//
//int main () {
//
//    int m = 0;
//
//    scanf("%d", &m);
//    getchar();
//
//    NODE **H = NULL;
//    H = (NODE **) malloc(m * sizeof(NODE *));
//    if (H == NULL) {
//        return -1;
//    }
//    initBucketArray(H, m);
//
//    char mode = '0';
//    int key = 0;
//
//    while (mode != 'e') {
//        scanf("%c", &mode);
//
//        switch (mode) {
//            case 'i':
//                scanf("%d", &key);
//                insertItem(H, key, m);
//                break;
//            case 's':
//                scanf("%d", &key);
//                printf("%d\n", findElement(H, key, m));
//                break;
//            case 'd':
//                scanf("%d", &key);
//                printf("%d\n", removeElement(H, key, m));
//                break;
//            case 'p':
//                printBucketArray(H, m);
//                break;
//            case 'e':
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
//NODE *getNode (int key) {
//
//    NODE *new = NULL;
//
//    new = (NODE *) malloc(sizeof(NODE));
//
//    new->key = key;
//    new->next = NULL;
//
//    return new;
//}
//int h_x (int key, int m) {
//
//    return key % m;
//}
//void initBucketArray (NODE **H, int m) {
//
//    for (int i = 0; i < m; i++) {
//        H[i] = NULL;
//    }
//
//    return;
//}
//void insertItem (NODE **H, int key, int m) {
//
//    NODE *new = NULL;
//    NODE *tmp = NULL;
//    int v = 0;
//
//    new = getNode(key);
//
//    v = h_x(key, m);
//
//    if (H[v] == NULL) { // 지정된 해시값의 해시테이블에 처음 원소를 입력하는 경우
//        H[v] = new;
//    }
//    else { // 그 외의 경우
//        tmp = H[v];
//        H[v] = new;
//        new->next = tmp;
//    }
//
//    return;
//}
//int findElement (NODE **H, int key, int m) {
//
//    NODE *tmp = NULL;
//    int v = 0;
//    int cnt = 0;
//
//    v = h_x(key, m);
//
//    if (H[v] == NULL) {
//        return 0;
//    }
//    else {
//        tmp = H[v];
//
//        while (tmp != NULL) {
//            cnt++;
//
//            if (tmp->key == key) {
//                return cnt;
//            }
//
//            tmp = tmp->next;
//        }
//    }
//
//    return 0;
//}
//int removeElement (NODE **H, int key, int m) {
//
//    NODE *node = NULL;
//    NODE *del = NULL;
//    NODE *before = NULL;
//    int v = 0;
//    int cnt = findElement(H, key, m);
//
//    v = h_x(key, m);
//
//    if (cnt == 0) {
//        return 0;
//    }
//
//    node = H[v];
//    del = H[v];
//    before = H[v];
//
//    for (int i = 1; i < cnt; i++) {
//            if (i == cnt - 2) before = node; //중간에 끼어있는 경우
//            node = node->next;
//        }
//        del = node;
//
//        if (del->next == NULL) { //tail인 경우
//            if (H[v] == del) {
//                H[v] = NULL; //원소가 하나였던 경우
//            }
//            else {
//                before->next = NULL;
//            }
//        }
//
//        else {
//            if (H[v] == del) {
//                H[v] = del->next;//head인 경우
//            }
//            else {
//                before->next = del->next;
//            }
//        }
//
//    return cnt;
//
//}
//void printBucketArray (NODE **H, int m) {
//
//    NODE *tmp = NULL;
//
//    for (int i = 0; i < m; i++) {
//        if (H[i] == NULL) {
//            continue;
//        }
//        else {
//            tmp = H[i];
//            while (tmp != NULL) {
//                printf(" %d", tmp->key);
//                tmp = tmp->next;
//            }
//        }
//    }
//    printf("\n");
//
//    return;
//}


//#include <stdio.h> // 문제 2
//#include <string.h>
//#include <stdlib.h>
//
//int h_x (int key, int m); // 해시함수
//void intitBucketArray (int *H, int m); // 초기화
//int findElement (int *H, int k, int m); // 탐색
//void insertItem (int *H, int k, int m); // 삽입
//
//int main () {
//
//    int m = 0;
//    int n = 0;
//
//    scanf("%d %d", &m, &n);
//    getchar();
//
//    int *H = NULL;
//    H = (int *) malloc(m *sizeof(int));
//    if (H == NULL) {
//        return -1;
//    }
//
//    char mode = '0';
//    int key = 0;
//    int cnt = 0;
//
//    while (mode != 'e') {
//        scanf("%c", &mode);
//
//        switch (mode) {
//            case 'i':
//                scanf("%d", &key);
//                if (cnt >= n) {
//                    continue;
//                }
//                else {
//                    insertItem(H, key, m);
//                    cnt++;
//                }
//                break;
//            case 's':
//                scanf("%d", &key);
//                if (findElement(H, key, m) == -1) {
//                    printf("%d\n", -1);
//                }
//                break;
//            case 'e':
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
//}
//void intitBucketArray (int *H, int m) {
//
//    for (int i = 0; i < m; i++) {
//        H[i] = 0;
//    }
//
//    return;
//}
//int findElement (int *H, int k, int m) {
//
//    for (int i = 0; i < m; i++) {
//        if (H[i] == k) {
//            printf("%d %d\n", i, k);
//            return k;
//        }
//    }
//
//    return -1;
//}
//void insertItem (int *H, int k, int m) {
//
//    int v = h_x(k, m);
//
//    while (H[v] != 0) { // 충돌인 경우 다음 걸로 원형으로 넘어가는 반복문
//        printf("C");
//        v = h_x(v + 1, m);
//    }
//    printf("%d\n", v);
//
//    H[v] = k;
//
//    return;
//}


#include <stdio.h> // 문제 2
#include <string.h>
#include <stdlib.h>

int h_x (int key, int m); // 해시함수 1
int hprime_x (int x, int q); // 해시함수 2
void intitBucketArray (int *H, int m); // 초기화
int findElement (int *H, int k, int m); // 탐색
void insertItem (int *H, int k, int m, int q); // 삽입
void printBucketArray (int *H, int m); // 출력

int main () {
    
    int m = 0;
    int n = 0;
    int q = 0;
    
    scanf("%d %d %d", &m, &n, &q);
    getchar();
    
    int *H = NULL;
    H = (int *) malloc(m *sizeof(int));
    if (H == NULL) {
        return -1;
    }
    
    char mode = '0';
    int key = 0;
    int cnt = 0;
    
    while (mode != 'e') {
        scanf("%c", &mode);
        
        switch (mode) {
            case 'i':
                scanf("%d", &key);
                if (cnt >= n) {
                    continue;
                }
                else {
                    insertItem(H, key, m, q);
                    cnt++;
                }
                break;
            case 's':
                scanf("%d", &key);
                if (findElement(H, key, m) == -1) {
                    printf("%d\n", -1);
                }
                break;
            case 'p':
                printBucketArray(H, m);
                break;
            case 'e':
                printBucketArray(H, m);
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
}
int hprime_x (int x, int q) {
    
    return q - (x % q);
}
void intitBucketArray (int *H, int m) {
    
    for (int i = 0; i < m; i++) {
        H[i] = 0;
    }
    
    return;
}
int findElement (int *H, int k, int m) {
    
    for (int i = 0; i < m; i++) {
        if (H[i] == k) {
            printf("%d %d\n", i, k);
            return k;
        }
    }
    
    return -1;
}
void insertItem (int *H, int k, int m, int q) {
    
    int v = h_x(k, m);
    
    while (H[v] != 0) { // 충돌인 경우 다음 걸로 원형으로 넘어가는 반복문
        printf("C");
        v = h_x(v + hprime_x(k, q), m);
    }
    printf("%d\n", v);
    
    H[v] = k;
    
    return;
}
void printBucketArray (int *H, int m) {
    
    for (int i = 0; i < m; i++) {
        printf(" %d", H[i]);
    }
    printf("\n");
    
    return;
}

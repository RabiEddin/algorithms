//
//  main.c
//  Algorithms_lesson_4_Training
//
//  Created by 김도윤 on 2022/09/22.
//

#include <stdio.h> // 문제 1, 2
#include <string.h>
#include <stdlib.h>

int H[100] = { 0 };
int n = 0;

void inPlaceHeapSort ();
void printArray ();
void downHeap (int index, int last); // 루트노드의 원소를 삭제 한 후 가장 마지막 노드에 있는 원소를 루트 노드로 이동
                            // -> 루트 노드에 있는 원소를 크기에 맞는 위치로 이동 + last 변수 추가(이유: 정렬할 범위가 계속 축소 되기 때문)
void insertItem (int key, int now_loc); // heap에서 가장 마지막 노드에 key 입력
void upHeap (int index); // heap에서 가장 마지막 부분에 저장된 key를 크기에 맞는 위치로 이동
                        //(key값이 작으면 그 위치 거의 고대로 있을거고, key 값이 작으면 루트노드쪽으로 가까이 갈거임)
void rBuildHeap (int index); // 재귀 방식으로 상향식 힙 생성 -> 재귀 함수를 통해 후위순회 방식으로(왼쪽자식->오른쪽자식->부모) 정렬해 나가는 방식
void BuildHeap (); // 비재귀 방식으로 상향식 힙 생성 -> 힙의 높이가 n - 1에 있는 노드의 오른쪽 -> 왼쪽으로 정렬 -> 힙의 높이가 n - 2에 있는 노드의 오른쪽 -> 왼쪽으로 정렬 ... 반복

int main () {

    int key = 0;

    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &key);
        insertItem(key, i); // 제자리 힙 정렬 - 1기 (삽입식 힙)
//        H[i] = key;
//        BuildHeap(); // 제자리 힙 정렬 - 1기 (상향십 힙), 비재귀적 방식
//        rBuildHeap(1); // 제자리 힙 정렬 - 1기 (상향십 힙), 재귀적 방식
    }

    inPlaceHeapSort();

    printArray();

    return 0;
}

void inPlaceHeapSort () { // n개의 키로 구성된 무순배열을 제자리 힙 정렬

    int tmp = 0;

    for (int i = n; i > 1; i--) { // 제자리 힙 정렬 - 2기
        tmp = H[1];
        H[1] = H[i];
        H[i] = tmp;
        // 가장 큰 원소가 저장되어 있는 루트노드를 맨 뒤로 이동
        downHeap(1, i - 1); // 맨 뒤로 이동되어 있는 가장 큰 원소를 제외하고 정렬
    }

    return;
}
void printArray () {

    for (int i = 1; i <= n; i++) {
        printf(" %d", H[i]);
    }
    printf("\n");

    return;
}
void downHeap (int index, int last) { // 힙 내 위치 i에 저장된 키를 크기에 맞는 위치로 하향 이동 + last 변수 추가

    int bigger_index = 0;
    int temp = 0; // swap할 때 이용할 변수 선언

    if (index * 2 > last) { // 자식노드가 없는 경우 (정렬할 범위까지 자식노드가 없는 경우)
        return;
    }

    bigger_index = index * 2; // 가장 큰 원소는 왼쪽 자식노드라 가정
    if (bigger_index + 1 <= n && bigger_index + 1 <= last) { // 만약 오른쪽 자식노드가 있는 경우
        if (H[bigger_index + 1] > H[bigger_index]) { // 오른쪽 자식노드 > 왼족 자식노드
            bigger_index += 1; // 가장 큰 원소는 오른쪽 자식노드로 바꿈
        }
    }

    if (H[index] >= H[bigger_index]) { // 현재 노드 >= 자식노드
        return;
    }

    // 그 외의 경우 swap 진행
    temp = H[index];
    H[index] = H[bigger_index];
    H[bigger_index] = temp;

    downHeap(bigger_index, last);

    return;
}
void insertItem (int key, int now_loc) { // now_loc 위치에 key 삽입, upHeap(now_loc) 호출 수행

    H[now_loc] = key;
    upHeap(now_loc);

    return;
}
void upHeap (int index) { // 힙 내 위치 i에 저장된 키를 크기에 맞는 위치로 상향 이동

    int temp = 0; // swap할 때 이용할 변수 선언

    if (index == 1) { // n의 크기가 1일때는 따로 상향 이동할 것이 없기 떄문에 리턴
        return;
    }
    if (H[index] <= H[index/2]) { // 부모노드의 원소 >= 자식노드(현재 위치한 노드)
        return;
    }

    // 그 외의 경우 swap 진행
    temp = H[index];
    H[index] = H[index/2];
    H[index/2] = temp;

    upHeap(index/2);

    return;
}
void rBuildHeap (int index) { // 재귀 방식으로 상향식 힙 생성

    if (index > n) {
        return;
    }

    rBuildHeap(2 * index); // 현재 부트리의 좌 부트리를 힙 생성
    rBuildHeap(2 * index + 1); // 현재 부트리의 우 부트리를 힙 생성

    downHeap(index, n); // 현재 부트리의 루트와 좌우 부트리를 합친 힙 생성

    return;
}
void BuildHeap () { // 비재귀 방식으로 상향식 힙 생성

    for (int i = n/2; i > 0; i--) {
        downHeap(i, n);
    }

    return;
}

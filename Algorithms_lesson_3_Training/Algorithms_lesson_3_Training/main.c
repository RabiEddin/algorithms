//
//  main.c
//  Algorithms_lesson_3_Training
//
//  Created by 김도윤 on 2022/09/15.
//

//#include <stdio.h> // 문제 1
//#include <string.h>
//#include <stdlib.h>
//
//int H[100] = { 0 };
//int n = 0;
//
//void insertItem (int key); // heap에서 가장 마지막 노드에 key 입력
//int removeMax (); // 루트노드에 있는 가장 큰 원소 삭제
//void upHeap (int index); // heap에서 가장 마지막 부분에 저장된 key를 크기에 맞는 위치로 이동
//                        //(key값이 작으면 그 위치 거의 고대로 있을거고, key 값이 작으면 루트노드쪽으로 가까이 갈거임)
//void downHeap (int index); // 루트노드의 원소를 삭제 한 후 가장 마지막 노드에 있는 원소를 루트 노드로 이동
//                            // -> 루트 노드에 있는 원소를 크기에 맞는 위치로 이동
//void printHeap (); // 출력 (전위순회 방식)
//
//int main () {
//
//    char cm = '0'; // 명령어(i, d, p, q)
//    int key = 0;
//
//    while (1) {
//        scanf("%c", &cm);
//
//        if (cm == 'q') {
//            break;
//        }
//
//        switch (cm) {
//            case 'i':
//                scanf("%d", &key);
//                insertItem(key);
//                printf("0\n");
//                break;
//            case 'd':
//                printf("%d\n", removeMax());
//                break;
//            case 'p':
//                printHeap();
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
//void insertItem (int key) { // n 위치에 key 삽입, upHeap(n) 호출 수행 후 n(총 키 개수)을 갱신
//
//    n++;
//    H[n] = key;
//    upHeap(n);
//
//    return;
//}
//int removeMax () { // downHeap 호출 수행 후 n(총 키 개수)을 갱신
//
//    int ans = 0; // 삭제하는 루트노드의 원소를 저장할 변수 선언
//
//    ans = H[1];
//    H[1] = H[n];
//    n--;
//    downHeap(1);
//
//    return ans;
//}
//void upHeap (int index) { // 힙 내 위치 i에 저장된 키를 크기에 맞는 위치로 상향 이동
//
//    int temp = 0; // swap할 때 이용할 변수 선언
//
//    if (index == 1) { // n의 크기가 1일때는 따로 상향 이동할 것이 없기 떄문에 리턴
//        return;
//    }
//    if (H[index] <= H[index/2]) { // 부모노드의 원소 >= 자식노드(현재 위치한 노드)
//        return;
//    }
//
//    // 그 외의 경우 swap 진행
//    temp = H[index];
//    H[index] = H[index/2];
//    H[index/2] = temp;
//
//    upHeap(index/2);
//
//    return;
//}
//void downHeap (int index) { // 힙 내 위치 i에 저장된 키를 크기에 맞는 위치로 하향 이동
//
//    int bigger_index = 0;
//    int temp = 0; // swap할 때 이용할 변수 선언
//
//    if (index * 2 > n) { // 자식노드가 없는 경우
//        return;
//    }
//
//    bigger_index = index * 2; // 가장 큰 원소는 왼쪽 자식노드라 가정
//    if (bigger_index + 1 <= n) { // 만약 오른쪽 자식노드가 있는 경우
//        if (H[bigger_index + 1] > H[bigger_index]) { // 오른쪽 자식노드 > 왼족 자식노드
//            bigger_index += 1; // 가장 큰 원소는 오른쪽 자식노드로 바꿈
//        }
//    }
//
//    if (H[index] >= H[bigger_index]) { // 현재 노드 >= 자식노드
//        return;
//    }
//
//    // 그 외의 경우 swap 진행
//    temp = H[index];
//    H[index] = H[bigger_index];
//    H[bigger_index] = temp;
//
//    downHeap(bigger_index);
//
//    return;
//}
//void printHeap () { // 출력 (전위순회 방식)
//
//    for (int i = 1; i < n + 1; i++) {
//        printf(" %d", H[i]);
//    }
//    printf("\n");
//
//    return;
//}


//#include <stdio.h> // 문제 2
//#include <string.h>
//#include <stdlib.h>
//
//int H[100] = { 0 };
//int n = 0;
//
//void rBuildHeap (int index); // 재귀 방식으로 상향식 힙 생성 -> 재귀 함수를 통해 후위순회 방식으로(왼쪽자식->오른쪽자식->부모) 정렬해 나가는 방식
//void BuildHeap (); // 비재귀 방식으로 상향식 힙 생성 -> 힙의 높이가 n - 1에 있는 노드의 오른쪽 -> 왼쪽으로 정렬 -> 힙의 높이가 n - 2에 있는 노드의 오른쪽 -> 왼쪽으로 정렬 ... 반복
//void downHeap (int index); // 루트노드의 원소를 삭제 한 후 가장 마지막 노드에 있는 원소를 루트 노드로 이동
//                            // -> 루트 노드에 있는 원소를 크기에 맞는 위치로 이동
//void printHeap (); // 출력 (전위순회 방식)
//
//int main () {
//
//    scanf("%d", &n); // 힙의 크기 입력
//
//    for (int i = 1; i < n + 1; i++) {
//        scanf("%d", &H[i]);
//    }
//
//    rBuildHeap(1); // 재귀 방식으로 상향식 힙 생성
//
////    BuildHeap(); // 비재귀 방식으로 상향식 힙 생성
//
//    printHeap();
//
//    return 0;
//}
//
//void rBuildHeap (int index) { // 재귀 방식으로 상향식 힙 생성
//
//    if (index > n) {
//        return;
//    }
//
//    rBuildHeap(2 * index); // 현재 부트리의 좌 부트리를 힙 생성
//    rBuildHeap(2 * index + 1); // 현재 부트리의 우 부트리를 힙 생성
//
//    downHeap(index); // 현재 부트리의 루트와 좌우 부트리를 합친 힙 생성
//
//    return;
//}
//void BuildHeap () { // 비재귀 방식으로 상향식 힙 생성
//
//    for (int i = n/2; i > 0; i--) {
//        downHeap(i);
//    }
//
//    return;
//}
//void downHeap (int index) { // 힙 내 위치 i에 저장된 키를 크기에 맞는 위치로 하향 이동
//
//    int bigger_index = 0;
//    int temp = 0; // swap할 때 이용할 변수 선언
//
//    if (index * 2 > n) { // 자식노드가 없는 경우
//        return;
//    }
//
//    bigger_index = index * 2; // 가장 큰 원소는 왼쪽 자식노드라 가정
//    if (bigger_index + 1 <= n) { // 만약 오른쪽 자식노드가 있는 경우
//        if (H[bigger_index + 1] > H[bigger_index]) { // 오른쪽 자식노드 > 왼족 자식노드
//            bigger_index += 1; // 가장 큰 원소는 오른쪽 자식노드로 바꿈
//        }
//    }
//
//    if (H[index] >= H[bigger_index]) { // 현재 노드 >= 자식노드
//        return;
//    }
//
//    // 그 외의 경우 swap 진행
//    temp = H[index];
//    H[index] = H[bigger_index];
//    H[bigger_index] = temp;
//
//    downHeap(bigger_index);
//
//    return;
//}
//void printHeap () { // 출력 (전위순회 방식)
//
//    for (int i = 1; i < n + 1; i++) {
//        printf(" %d", H[i]);
//    }
//    printf("\n");
//
//    return;
//}

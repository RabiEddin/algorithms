//
//  main.c
//  Algorithms_task_1
//
//  Created by 김도윤 on 2022/09/29.
//

#include <stdio.h> // 과제 1
#include <string.h>
#include <stdlib.h>
#include <time.h>

int findKthSmallest (int *arr, int n, int k); // n개 정수 원소들로 이루어진 리스트 L의 원소 가운데 k-번째로 작은 원소를 찾아내 반환
int removeRootnode (int *arr, int n); // 루트노드에 있는 값 반환
void rBuildHeap (int *arr, int index, int n); // 재귀 방식으로 상향식 힙 생성
void downHeap (int *arr, int index, int last); // 힙 내 위치 index에 저장된 키를 크기에 맞는 위치로 하향 이동
int *buildlist (int n, int min, int max); // 난수함수를 이용하여 min~max 사이의 중복이 있을 수 있는 정수 n개의 무작위 무순리스트를 만들어 반환
int *copylist (int *arr, int n); // 리스트 복사
void writeList (int *arr, int n); // 리스트 출력

int main () {

    srand((unsigned int)time(NULL)); // 난수 초기화

    clock_t start, finish; // 정렬 함수들의 걸리는 시간을 측정하기 위해 시작시간과 마지막시간을 저장하기 위한 변수
    double duration; // 정렬 함수들이 걸리는 시간을 저장하기 위한 double형 변수

    /* n = 10*/
    
    int *L = NULL; // 리스트 L
    int *arr1 = NULL; // 리스트 L을 복사하여 저장할 변수 arr1

    int output[4] = { 0 };
    L = buildlist(10, 1, 100); // 1과 100 사이의 정수 10개로 이루어진 리스트를 만들어 L에 저장

    writeList(L, 10); // 무순리스트 L 출력

    for (int i = 1; i <= 3; i++) {
        arr1 = copylist(L, 10); // 리스트 L에 있는 정보를 arr1에 복사
        output[i] = findKthSmallest(arr1, 10, i); //arr1을 이용하여 리스트 내에 있는 i번째로 작은 원소 output 배열에 저장
    }

    writeList(output, 3); // ouput에 저장되어있는 정보 출력

    free(L);
    free(arr1);

    /* n = 100000*/
    
    int karray[4] = {1, 100, 99900, 99999};
    int *arr2 = NULL;
    int e = 0;

    L = buildlist(100000, 1, 1000000);

    for (int i = 0; i < 4; i++) {
        arr2 = copylist(L, 100000); // 리스트 L에 있는 정보를 arr2에 복사

        start = clock(); // 처음 시간 측정
        e = findKthSmallest(arr2, 100000, karray[i]); //arr2을 이용하여 리스트 내에 있는 karray[i]번째로 작은 원소 e에 저장
        finish = clock(); // 마지막 시간 측정

        duration = (double) (finish - start) / CLOCKS_PER_SEC; // karray[i]번째로 작은 원소를 찾아내는데 걸리는 시간 계산
        printf("e : %d t : %.8fms\n", e, duration); // karray[i]번째로 작은 원소를 찾아내는데 걸리는 시간과 값 출력
    }
    
    free(L);
    free(arr2);

    return 0;
}

int findKthSmallest (int *arr, int n, int k) {
    
    /* *arr = 리스트 L, n = 리스트 L의 크기, k = k번째로 작은 원소할 때 그 k의 값 */

    int kthsmallestKey = 0; // k번째로 작은 원소를 저장할 변수

    rBuildHeap(arr, 1, n); // 재귀 방식으로 상향식 힙 생성

    for (int i = 0; i < k; i++) { // k번째로 작은 수: O(k)
        kthsmallestKey = removeRootnode(arr, n - i); // k번째로 작은 원소로 업데이트 (1 -> k번째까지), root노드 삭제: O(log n)
    }
    //O(k*log n)
    
    return kthsmallestKey;
}
int removeRootnode (int *arr, int n) {

    /* *arr = 리스트 L, n = 리스트 L의 크기 */
    
    int ans = 0; // 반환할 값을 저장할 변수

    /* 가장 작은 원소(루트 노드)를 ans에 저장 후 가장 마지막 노드를 루트노드로 이동 */
    ans = arr[1];
    arr[1] = arr[n];

    n -= 1; // 루트노드의 원소가 삭제되어 n -= 1
    downHeap(arr, 1, n); // 다운힙을 통해 크기에 맞는 위치로 하향 이동

    return ans;
}
void rBuildHeap (int *arr, int index, int n) {

    if (index > n) {
        return;
    }

    rBuildHeap(arr, 2 * index, n); // 현재 부트리의 좌 부트리를 힙 생성
    rBuildHeap(arr, 2 * index + 1, n); // 현재 부트리의 우 부트리를 힙 생성

    downHeap(arr, index, n); // 현재 부트리의 루트와 좌우 부트리를 합친 힙 생성

    return;

}
void downHeap (int *arr, int index, int last) {

    int smaller_index = 0;
    int temp = 0; // swap할 때 이용할 변수 선언

    if (index * 2 > last) { // 자식노드가 없는 경우 (정렬할 범위까지 자식노드가 없는 경우)
        return;
    }

    smaller_index = index * 2; // 가장 작은 원소는 왼쪽 자식노드라 가정
    if (smaller_index + 1 <= last) { // 만약 오른쪽 자식노드가 있는 경우
        if (arr[smaller_index + 1] < arr[smaller_index]) { // 오른쪽 자식노드 작은 왼족 자식노드
            smaller_index += 1; // 가장 작은 원소는 오른쪽 자식노드로 바꿈
        }
    }

    if (arr[index] <= arr[smaller_index]) { // 현재 노드 <= 자식노드
        return;
    }

    // 그 외의 경우 swap 진행
    temp = arr[index];
    arr[index] = arr[smaller_index];
    arr[smaller_index] = temp;

    downHeap(arr, smaller_index, last);

    return;

}
int *buildlist (int n, int min, int max) {

    int *arr = NULL;
    arr = (int *) malloc((n + 1) * sizeof(int));

    for (int i = 1; i <= n; i++) {
        arr[i] = ((((long) rand() << 15) | rand()) % max) + min; // 난수함수를 통해 min - max 범위에 있는 무작위 값 리스트에 저장
    }

    return arr;
}
int *copylist (int *arr, int n) {

    int *copy = NULL;
    copy = (int *) malloc((n + 1) * sizeof(int));

    for (int i = 1; i <= n; i++) {
        copy[i] = arr[i];
    }

    return copy;
}
void writeList (int *arr, int n) {

    for (int i = 1; i <= n; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    return;
}


//#include<stdio.h>
//#include<string.h>
//#include <stdlib.h>
//#include<time.h>
//
//int* buildList(int n, int min, int max); //��������Ʈ ����
//int* copyList(int* L, int n); //��������Ʈ L�� ����
//void buildHeap(int* H, int n); //��������Ʈ�� ������
//int findKthSmallest(int* H, int n, int k); //k��°�� ���� �� ã��
//int removeMin(int* H, int n); //�ּҰ� ����
//void downHeap(int* H, int i, int n);
//void swapElements(int* H, int i, int j);
//void writeList(int* L, int n);
//
//int main(void) {
//    int* L, * H;
//    int output[5], karray[5] = { 1, 100, 99900, 99999 };
//    int e, k;
//
//    clock_t start, finish; // 정렬 함수들의 걸리는 시간을 측정하기 위해 시작시간과 마지막시간을 저장하기 위한 변수
//    double duration; // 정렬 함수들이 걸리는 시간을 저장하기 위한 double형 변수
//
//    srand((unsigned int)time(NULL));
//
//    /* n = 10 */
//    L = buildList(10, 1, 100);
//
//    writeList(L, 10); //��������Ʈ L ���
//
//    for (k = 1; k <= 3; k++) { //k(=1,2,3) ��°�� ���� �� ã�� ���
//        H = copyList(L, 10); //H�� L�� ����
//        output[k] = findKthSmallest(H, 10, k);
//    }
//    writeList(output, 3);
//
//    free(L); free(H);
//
//    /* n = 100000 */
//    L = buildList(100000, 1, 1000000);
//
//    for (k = 0; k < 4; k++) { //k(=1,100,99900,99999) ��°�� ���� �� ã�� ���
//        H = copyList(L, 100000); //H�� L�� ����
//
//        start = clock(); // 처음 시간 측정
//
//        e = findKthSmallest(H, 100000, karray[k]);
//
//        finish = clock(); // 마지막 시간 측정
//        duration = (double) (finish - start) / CLOCKS_PER_SEC; // 선택 정렬 함수가 걸리는 시간 계산
//        printf("e : %d t : %.8fms\n", e, duration); // 선택 정렬 함수가 걸리는 시간 출력
//    }
//
//    free(L); free(H);
//
//    return 0;
//}
//
//int* buildList(int n, int min, int max) {
//    int *L = (int*)malloc(sizeof(int) * (n + 1));
//
//    for (int i = 1; i <= n; i++) { //min ~ max ������ rand �� �Ҵ�
//        L[i] = ((((long)rand() << 15) | rand()) % max) + min;
//    }
//
//    return L;
//}
//
//int* copyList(int* L, int n) {
//    int* H = (int*)malloc(sizeof(int) * (n + 1));
//
//    for (int i = 1; i <= n; i++) {
//        H[i] = L[i]; //�ʱ� ��������Ʈ L�� ���� H�� ����
//    }
//
//    return H;
//}
//
//void buildHeap(int* H, int n) {
//    for (int i = n / 2; i >= 1; i--) {
//        downHeap(H, i, n); //�� ���� �Ӽ� ����
//    }
//}
//
//int findKthSmallest(int* H, int n, int k) {
//    int smaller = 0;
//
//    buildHeap(H, n); //����� �� ���� : O(n)
//
//    for (int i = 0; i < k; i++) { //k��°�� ���� �� : O(k)
//        smaller = removeMin(H, n); //root ���� : O(log n)
//        n--;
//    }//O(k*log n)
//
//
//    return smaller;
//}
//
//int removeMin(int* H, int n) {
//    int key;
//
//    //root�� ������ ��� �� ����
//    key = H[1];
//    H[1] = H[n];
//
//    downHeap(H, 1, --n); //������ ��� ���� �� ������ �Ӽ� ����
//
//    return key; //���� root �� ��ȯ
//}
//
//void downHeap(int *H, int i, int n) {
//    int smaller;
//
//    if (i * 2 > n) return; //�ڽ��� ������
//
//    //���� �ڽİ� ������ �ڽ� �� ���� ���� ����
//    smaller = i * 2;
//    if (n >= i * 2 + 1 && H[smaller] > H[i * 2 + 1]) {
//        smaller = i * 2 + 1;
//    }
//
//    //�ڽĺ��� �θ� �� ���� ���̸�
//    if (H[i] <= H[smaller]) return;
//
//    //�ڽ��� �θ𺸴� �� ������
//    swapElements(H, i, smaller);
//
//    downHeap(H, smaller, n);
//}
//
//void swapElements(int* H, int i, int j) {
//    int temp;
//
//    temp = H[i];
//    H[i] = H[j];
//    H[j] = temp;
//}
//
//void writeList(int* L, int n) {
//    for (int i = 1; i <= n; i++) {
//        printf("%d ", L[i]);
//    }
//    printf("\n");
//}

//
//  main.c
//  Algorithms_lesson_6_Training
//
//  Created by 김도윤 on 2022/10/06.
//

//#include <stdio.h> // 문제 1 - 이진 탐색 트리 재귀버전으로 구성
//#include <string.h>
//#include <stdlib.h>
//
//int findElementloc (int *arr, int k, int n); // x ≤ k 를 만족하는 사전의 키 x 중 가장 큰 값의 위치를 찾는 함수
//int rFEl (int *arr, int k, int s, int e); // 이진 탐색 트리를 이용하여 x ≤ k 를 만족하는 사전의 키를 재귀버전으로 구성
//
//int main () {
//
//    int n, k = 0;
//
//    scanf("%d %d", &n, &k);
//
//    int *arr = NULL;
//    arr = (int *) malloc(n * sizeof(int));
//    if (arr == NULL) {
//        return -1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        scanf("%d", arr + i);
//    }
//
//    printf(" %d\n", findElementloc(arr, k, n));
//
//    free(arr);
//
//    return 0;
//}
//
//int findElementloc (int *arr, int k, int n) {
//
//    /* x ≤ k 를 만족하는 사전의 키 x가 존재하지 않는 경우 = 즉, 0번 원소가 k보다 큰 경우 밖에 없다 -> 이 경우만 -1로 출력 */
//    if (arr[0] > k) {
//        return -1;
//    }
//    /* 그 외의 경우 */
//    else {
//        return rFEl(arr, k, 0, n - 1);
//    }
//
//}
//int rFEl (int *arr, int k, int s, int e) {
//
//    int mid = 0;
//
//    /* x ≤ k 를 만족하는 사전의 키를 찾는 거여서 s > e인 경우가 되면 배열의 원소들 중에 k보다 큰 가장 작은 원소로 mid가 이동하게 된다.->s - 1 반환 */
//    if (s > e) {
//        return s - 1;
//    }
//
//    mid = (s + e) / 2;
//
//    if (k == arr[mid]) {
//        return mid;
//    }
//    else if (k < arr[mid]) {
//        return rFEl(arr, k, s, mid - 1);
//    }
//    else {
//        return rFEl(arr, k, mid + 1, e);
//    }
//}


//#include <stdio.h> // 문제 2 - 이진 탐색 트리 비재귀버전으로 구성
//#include <string.h>
//#include <stdlib.h>
//
//int findElementloc (int *arr, int k, int n); // x ≥ k 를 만족하는 사전의 키 x 중 가장 작은 값의 위치를 찾는 함수
//int FEl (int *arr, int k, int s, int e); // 이진 탐색 트리르 이용하여 x ≥ k 를 만족하는 사전의 키를 비재귀버전으로 구성
//
//int main () {
//
//    int n, k = 0;
//
//    scanf("%d %d", &n, &k);
//
//    int *arr = NULL;
//    arr = (int *) malloc(n * sizeof(int));
//    if (arr == NULL) {
//        return -1;
//    }
//
//    for (int i = 0; i < n; i++) {
//        scanf("%d", arr + i);
//    }
//
//    printf(" %d\n", findElementloc(arr, k, n));
//
//    free(arr);
//
//    return 0;
//}
//
//int findElementloc (int *arr, int k, int n) {
//
//    /* x ≥ k 를 만족하는 사전의 키 x가 존재하지 않는 경우 = 즉, n - 1번 원소(마지막 원소)가 k보다 작은 경우 밖에 없다 -> 이 경우만 n으로 출력*/
//    if (arr[n - 1] < k) {
//        return n;
//    }
//    /* 그 외의 경우 */
//    else {
//        return FEl(arr, k, 0, n - 1);
//    }
//
//}
//int FEl (int *arr, int k, int s, int e) {
//
//    int mid = 0;
//
//    /* 비재귀 버전으로 구성 -> while문 이용하여 구성함*/
//    /* x ≥ k 를 만족하는 사전의 키를 찾는 거여서 s > e인 경우가 되면 배열의 원소들 중에 k보다 큰 가장 작은 원소로 mid가 이동하게 된다. -> s 반환 */
//    while (1) {
//        if (s > e) {
//            return s;
//        }
//
//        mid = (s + e) / 2;
//
//        if (k == arr[mid]) {
//            return mid;
//        }
//        else if (k < arr[mid]) {
//            e = mid - 1;
//        }
//        else {
//            s = mid + 1;
//        }
//    }
//
//}


#include <stdio.h> // 문제 3 -> 스무고개와 비슷한 문제지만, 매 질문이 답에 따라 범위가 달라지만 한다. 고로 범위를 답에 따라 바꾸어 시작과 끝의 범위가                   같아질 때만 실행하면 된다.
#include <string.h>
#include <stdlib.h>

int main () {

    int a, b = 0;
    int num = 0;

    scanf("%d %d %d", &a, &b, &num);
    getchar();

    char ans = '0';

    for (int i = 0; i < num; i++) {
        scanf("%c", &ans);

        switch (ans) {
            case 'Y':
                a = (a + b) / 2 + 1;
                break;
            case 'N':
                b = (a + b) / 2;
                break;
            default:
                break;
        }
    }

    printf("%d\n", a);

    return 0;
}

//
//  main.c
//  Algorithms_task_4
//
//  Created by 김도윤 on 2022/11/23.
//

#include <stdio.h> // 과제 4 - 분할통치, 동적프로그래밍 모두 정방향 버전으로 해결할 것이다.
#include <string.h>
#include <stdlib.h>
#include <time.h>
// 전역변수 설정
#define MAX 30
int A[MAX];
int H[MAX];
// 함수 선언
int airtelDC (int n, int s, int d); // 분할통치법 - 정방향 해결 버전
int rairtelDC (int s, int d); // 분할통치법 - 재귀함수
int airtelDP (int n, int s, int d); // 동적프로그래밍 - 정방향 해결 버전

int main () {

    srand((unsigned int)time(NULL)); // 난수 초기화

    clock_t start, finish; // 정렬 함수들의 걸리는 시간을 측정하기 위해 시작시간과 마지막시간을 저장하기 위한 변수
    double duration; // 정렬 함수들이 걸리는 시간을 저장하기 위한 double형 변수

    int minitest[3][2] = {{0,4}, {2, 5}, {2, 4}}; // n = 6일때 실행할 s와 d의 값이 들어있는 배열
    int n, s, d, mincost = 0;

    A[0] = 0;
    A[1] = 1;
    for (int i = 2; i < MAX; i++) {
        A[i] = A[i - 1] + A[i - 1] % 5 + 3; // A = {0, 1, 5, 8, 14, 21, ...}
    }

    H[0] = 0;
    H[1] = 5;
    for (int i = 2; i < MAX; i++) {
        H[i] = (H[i - 1] + i) % 9 + 1; // H = {0, 5, 8, 3, 8, 5, 3, 2, 2, ...}
    }

    printf("%-3c %-3c %-3c %-9s %-8s %-10s\n", 'n', 's', 'd', "mincost", "version", "cputime"); // 표 위에 종류 표시

    //Test run for mini input
    n = 6;
    for (int i = 0; i < 3; i++) {
        s = minitest[i][0];
        d = minitest[i][1];

        // 분할통치방법
        start = clock();
        mincost = airtelDC(n, s, d);
        finish = clock();

        duration = (double) (finish - start) / CLOCKS_PER_SEC;

        printf("%-3d %-3d %-3d %-9d %-8s %-10.8f\n", n, s, d, mincost, "DC", duration);

        // 동적프로그래밍방법
        start = clock();
        mincost = airtelDP(n, s, d);
        finish = clock();

        duration = (double) (finish - start) / CLOCKS_PER_SEC;

        printf("%-3d %-3d %-3d %-9d %-8s %-10.8f\n", n, s, d, mincost, "DP", duration);
    }

    //Main run for big input
    n = MAX;

    s = 1;
    d = n-2;

    start = clock();
    mincost = airtelDC(n, s, d);
    finish = clock();

    duration = (double) (finish - start) / CLOCKS_PER_SEC;

    printf("%-3d %-3d %-3d %-9d %-8s %-10.8f\n", n, s, d, mincost, "DC", duration);

    // 동적프로그래밍방법
    start = clock();
    mincost = airtelDP(n, s, d);
    finish = clock();

    duration = (double) (finish - start) / CLOCKS_PER_SEC;

    printf("%-3d %-3d %-3d %-9d %-8s %-10.8f\n", n, s, d, mincost, "DP", duration);

    return 0;
}

int airtelDC (int n, int s, int d) {

    return rairtelDC(s, d);

} // 분할통치법 - 정방향 해결 버전 - O(2^n)
int rairtelDC (int s, int d) {

    int mincost = 0;
    int cost = 0;

    // 출발지와 목적지 같은 경우
    if (s == d) {
        return 0;
    }

    mincost = 99999; // 무한에 가까운 수

    // 그 외의 경우 (cf. k = 중간에 거쳐가는 도시의 위치
    for (int k = s; k < d; k++) {
        if (k == s) { // 중간에 거쳐가는 도시 없이 바로 목적지로 가는 경우에는 출발지에서 호텔에 묵지 않기 때문에 따로 빼서 H[k]의 값을 지우고 계산
            cost = rairtelDC(s, k) + A[d - k];
            mincost = mincost <= cost ? mincost : cost;
        } else { // 중간에 거쳐가는 도시가 있는 경우
            cost = rairtelDC(s, k) + H[k] + A[d - k];
            mincost = mincost <= cost ? mincost : cost;
        }
    }

    return mincost;
} // 분할통치법 - 재귀함수
int airtelDP (int n, int s, int d) {

    int cost = 0;
    int *m = NULL;
    m = (int *) malloc(n * sizeof(int));
    if (m == NULL) {
        return -1;
    }

    m[s] = 0;
    // 목적지를 순차적으로 늘려가는 과정 - 중간 목적지까지 도달하는 최소비용을 이용하여 최종목적지까지의 최소 비용을 구한다.
    for (int i = s + 1; i <= d; i++) {
        m[i] = 99999;

        for (int k = s; k < i; k++) {
            if (k == s) { // 경유지 없이 바로 목적지로 가는 경우에는 출발지에서 호텔에 묵지 않기 때문에 따로 빼서 H[k]의 값을 지우고 계산
                cost = m[k] + A[i - k];
                m[i] = m[i] <= cost ? m[i] : cost;
            } else { // 경유지가 있는 경우
                cost = m[k] + H[k] + A[i - k];
                m[i] = m[i] <= cost ? m[i] : cost;
            }
        }
    }
    
    free(m);

    return m[d];
} // 동적프로그래밍 - 정뱡항 해결 버전 - O(n^2)


//#include <stdio.h>
//#include <stdlib.h>
//#include<time.h>
//
//#define MAX 30
//
//int H[MAX];
//int A[MAX];
//
//int minimum(int x, int y);
//int airtelDC(int n, int s, int d);
//int rAirtelDC(int s, int d);
//int airtelDP(int n, int s, int d);
//
//int main() {
//    int mini[3][2] = { {0,4},{2,5},{2,4} }; //mini test (s,d)
//    int n, s, d, mincost;
//    int i;
//
//    srand((unsigned int)time(NULL)); // 난수 초기화
//
//    clock_t start, finish; // 정렬 함수들의 걸리는 시간을 측정하기 위해 시작시간과 마지막시간을 저장하기 위한 변수
//    double duration; // 정렬 함수들이 걸리는 시간을 저장하기 위한 double형 변수
//
//    A[0] = 0; A[1] = 1; //항공요금
//    for (i = 2; i < MAX; i++) {
//        A[i] = A[i - 1] + (A[i - 1] % 5) + 3;
//    }
//
//    H[0] = 0; H[1] = 5; //숙박요금
//    for (i = 2; i < MAX; i++) {
//        H[i] = (H[i - 1] + i) % 9 + 1;
//    }
//
//    //header
//    printf("%-3c %-3c %-3c %-8s %-8s %-10s\n", 'n', 's', 'd', "mincost", "version", "cputime");
//
//    //Test run for mini input
//    n = 6;
//    for (i = 0; i < 3; i++) {
//        s = mini[i][0];
//        d = mini[i][1];
//
//        //DC
//        start = clock();
//        mincost = airtelDC(n, s, d);
//        finish = clock();
//
//        duration = (double) (finish - start) / CLOCKS_PER_SEC;
//        printf("%-3d %-3d %-3d %-8d %-8s %-10.8f\n", n, s, d, mincost, "DC", duration);
//
//        //DP
//        start = clock();
//        mincost = airtelDP(n, s, d);
//        finish = clock();
//
//        duration = (double) (finish - start) / CLOCKS_PER_SEC;
//        printf("%-3d %-3d %-3d %-8d %-8s %-10.8f\n", n, s, d, mincost, "DP", duration);
//    }
//
//    //Main run for big input
//    n = MAX;
//    s = 1;
//    d = n - 2;
//
//    //DC
//    start = clock();
//    mincost = airtelDC(n, s, d);
//    finish = clock();
//
//    duration = (double) (finish - start) / CLOCKS_PER_SEC;
//    printf("%-3d %-3d %-3d %-8d %-8s %-10.8f\n", n, s, d, mincost, "DC", duration);
//
//    //DP
//    start = clock();
//    mincost = airtelDP(n, s, d);
//    finish = clock();
//
//    duration = (double) (finish - start) / CLOCKS_PER_SEC;
//    printf("%-3d %-3d %-3d %-8d %-8s %-10.8f\n", n, s, d, mincost, "DP", duration);
//
//    return 0;
//}
//
//int minimum(int x, int y) {
//    if (x < y) return x;
//    else return y;
//}
//
//int airtelDC(int n, int s, int d) { //분할통치법
//    return rAirtelDC(s, d);
//}
//
//int rAirtelDC(int s, int d) { //정방향
//    int mincost = 99999; //infinite
//    int cost;
//
//    if (s == d) return 0;
//
//    for (int k = 0; k < d; k++) {
//        cost = rAirtelDC(s, k) + H[k] + A[d - k];
//        mincost = minimum(mincost, cost);
//    }
//
//    return mincost;
//} //O(2^n)
//
//int airtelDP(int n, int s, int d) { //동적프로그래밍-정방향
//    int* m = (int*)malloc(sizeof(int) * n);
//    int cost;
//
//    m[s] = 0;
//
//    for (int i = s + 1; i <= d; i++) {
//        m[i] = 99999; ////infinite
//
//        for (int k = s; k < i; k++) {
//            cost = m[k] + H[k] + A[i - k];
//            m[i] = minimum(m[i], cost);
//        }
//    }
//
//    return m[d];
//} //O(n^2)

//
//  main.c
//  Algorithms_lesson_13_Training
//
//  Created by 김도윤 on 2022/11/27.
//

//#include <stdio.h> // 문제 1 - ************** 다시 풀어보기 **********************
//#include <string.h>
//#include <stdlib.h>
//// 간선에 대한 정보 저장 구조체
//typedef struct incidence_list {
//    int loc;
//    struct incidence_list *next;
//}INCIDENCE;
//// 정점에 대한 정보를 저장하는 구조체
//typedef struct vertex {
//    int name;
//    int distance;
//    INCIDENCE *header;
//}VERTEX;
//// edge에 대한 정보를 저장하는 구조체 (어떤 정점 2개가 어떠한 가중치의 간선으로 연결되어 있는지에 대한 정보)
//typedef struct edge {
//    int v1;
//    int v2;
//    int weight;
//}EDGE;
//// 그래프 전체 틀을 잡아줄 구조체
//typedef struct graph {
//    VERTEX *vertex;
//    EDGE *edge;
//    int n, m; // 정점과 간선의 개수
//}GRAPH;
//// 우선순위 큐(힙)에 MST에 없는 정점들을 저장
//typedef struct heap {
//    int key;
//    int weight;
//}HEAP;
//// 전역변수 설정
//#define MAX 2147483647
//GRAPH graph;
//// 함수 선언
//void buildgraph (void);
//void initgraph (void);
//void insertVertex (int id);
//void insertIncidentEdge (int v1, int v2, int w, int i);
//void addFirst (INCIDENCE *H, int i);
//
//void PrimJarnikMST (void);
//
//HEAP *buildHeap (void);
//void upHeap (HEAP* heap, int index);
//void downHeap (HEAP* heap, int index, int size);
//int removeMin (HEAP *heap, int i);
//int opposite (int u, int e);
//int isInclude (HEAP *heap, int id, int z);
//void replaceKey (HEAP *heap, int id, int z, int w);
//
//int main () {
//
//    buildgraph();
//
//    PrimJarnikMST();
//
//    return 0;
//}
//
//void buildgraph (void) {
//
//    scanf("%d %d", &graph.n, &graph.m);
//
//    initgraph();
//
//    int v1, v2, w = 0;
//
//    for (int i = 0; i < graph.m; i++) {
//        scanf("%d %d %d", &v1, &v2, &w);
//        insertIncidentEdge(v1, v2, w, i);
//    }
//
//    return;
//}
//void initgraph (void) {
//
//    graph.vertex = (VERTEX *) malloc((graph.n + 1) * sizeof(VERTEX)); // 1부터 시작 -> 이유: 힙에 넣고 빼는 과정에서 편리성 추구.
//    graph.edge = (EDGE *) malloc(graph.m * sizeof(EDGE));
//
//    for (int i = 1; i < graph.n + 1; i++) {
//        insertVertex(i);
//    }
//
//    return;
//}
//void insertVertex (int id) {
//
//    graph.vertex[id].name = id;
//
//    graph.vertex[id].header = (INCIDENCE *) malloc(sizeof(INCIDENCE));
//    graph.vertex[id].header->next = NULL;
//
//    return;
//}
//void insertIncidentEdge (int v1, int v2, int w, int i) {
//
//    graph.edge[i].v1 = v1;
//    graph.edge[i].v2 = v2;
//    graph.edge[i].weight = w;
//
//    addFirst(graph.vertex[v1].header, i);
//    addFirst(graph.vertex[v2].header, i);
//
//    return;
//}
//void addFirst (INCIDENCE *H, int i) {
//
//    INCIDENCE *node = NULL;
//    node = (INCIDENCE *) malloc(sizeof(INCIDENCE));
//
//    node->loc = i;
//    node->next = H->next;
//    H->next = node;
//
//    return;
//}
//void PrimJarnikMST (void) {
//
//    HEAP *heap = NULL;
//
//    for (int i = 1; i < graph.n + 1; i++) { // 초기화
//        graph.vertex[i].distance = MAX;
//    }
//    graph.vertex[1].distance = 0; // 문제에서 시작 정점을 1로 지정하였음.
//
//    heap = buildHeap();
//
//    INCIDENCE *p = NULL;
//    int sum = 0;
//    int i, u, z = 0;
//
//    i = graph.n;
//
//    while (i > 0) {
//        u = removeMin(heap, i);
//        printf(" %d", graph.vertex[u].name);
//
//        sum += graph.vertex[u].distance;
//
//        p = graph.vertex[u].header->next;
//        while (p != NULL) {
//            z = opposite(u, p->loc); // 부착 간선이 가리키는 edge의 위치를 통해 인접정점을 구하는 과정
//
//            if (isInclude(heap, i, z) && graph.edge[p->loc].weight < graph.vertex[z].distance) {
//                graph.vertex[z].distance = graph.edge[p->loc].weight; // 가중치 업데이트
//                replaceKey(heap, i, z, graph.vertex[z].distance); // 큐 내에서 z의 거리(가중치)에 따라 위치 업데이트
//            }
//            p = p->next;
//        }
//
//        i--;
//    }
//    printf("\n");
//
//    printf("%d\n", sum);
//
//    return;
//}
//HEAP *buildHeap (void) {
//
//    HEAP *heap = NULL;
//    heap = (HEAP *) malloc((graph.n + 1) * sizeof(HEAP));
//
//    for (int i = 1; i < graph.n + 1; i++) { // 초기화
//        heap[i].key = graph.vertex[i].name;
//        heap[i].weight = graph.vertex[i].distance;
//    }
//
//    for (int i = graph.n / 2; i >= 1; i--) { // 상향식 힙 생성
//        downHeap(heap, i, graph.n);
//    }
//
//    return heap;
//}
//void upHeap (HEAP* heap, int index) {
//
//    if (index == 1 || heap[index].weight >= heap[index/2].weight) {
//        return;
//    }
//
//    HEAP tmp = { 0 };
//
//    tmp = heap[index];
//    heap[index] = heap[index/2];
//    heap[index/2] = tmp;
//
//    upHeap(heap, index/2);
//
//    return;
//}
//void downHeap (HEAP* heap, int index, int size) {
//
//    int left = 2 * index;
//    int right = 2 * index + 1;
//    int smaller = 0;
//    HEAP tmp = { 0 };
//
//    if (left > size) {
//        return;
//    }
//
//    smaller = left;
//    if (right <= size) {
//        if (heap[right].weight < heap[left].weight) {
//            smaller = right;
//        }
//    }
//
//    if (heap[index].weight <= heap[smaller].weight) {
//        return;
//    }
//
//    tmp = heap[index];
//    heap[index] = heap[smaller];
//    heap[smaller] = tmp;
//
//    downHeap(heap, smaller, size);
//
//    return;
//}
//int removeMin (HEAP *heap, int i) {
//
//    HEAP result = { 0 };
//    HEAP tmp = { 0 };
//
//    if (i == 0) {
//        return  -1;
//    }
//
//    result = heap[1];
//
//    tmp = heap[1];
//    heap[1] = heap[i];
//    heap[i] = tmp;
//
//    i -= 1;
//    downHeap(heap, 1, i);
//
//    return result.key;
//}
//int opposite (int u, int e) {
//
//    if (graph.edge[e].v1 == u) {
//        return graph.edge[e].v2;
//    } else {
//        return graph.edge[e].v1;
//    }
//
//}
//int isInclude (HEAP *heap, int id, int z) {
//
//    for (int i = 1; i < id; i++) {
//        if (heap[i].key == z) {
//            return 1;
//        }
//    }
//
//    return 0;
//}
//void replaceKey (HEAP *heap, int id, int z, int w) {
//
//    int loc = 0;
//
//    for (int i = 1; i < id; i++) {
//        if (heap[i].key == z) {
//            heap[i].weight = w;
//            loc = i;
//            break;
//        }
//    }
//
//    upHeap(heap, loc);
//
//    return;
//}


#include <stdio.h> // 문제 2
#include <string.h>
#include <stdlib.h>

int main () {
    
    
    
    return 0;
}

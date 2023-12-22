//
//  main.c
//  Algorithms_lesson_14_Training
//
//  Created by 김도윤 on 2022/12/01.
//

#include <stdio.h> // 문제 1
#include <string.h>
#include <stdlib.h>
// 간선에 대한 정보 저장 구조체
typedef struct incidence_list {
    int loc;
    struct incidence_list *next;
}INCIDENCE;
// 정점에 대한 정보를 저장하는 구조체
typedef struct vertex {
    int name;
    int distance;
    INCIDENCE *header;
}VERTEX;
// edge에 대한 정보를 저장하는 구조체 (어떤 정점 2개가 어떠한 가중치의 간선으로 연결되어 있는지에 대한 정보)
typedef struct edge {
    int v1;
    int v2;
    int weight;
}EDGE;
// 그래프 전체 틀을 잡아줄 구조체
typedef struct graph {
    VERTEX *vertex;
    EDGE *edge;
    int n, m, s; // 정점과 간선의 개수 + 시작 정점의 위치
}GRAPH;
// 우선순위 큐(힙)에 MST에 없는 정점들을 저장
typedef struct heap {
    int key;
    int weight;
}HEAP;
// 전역변수 설정
int MAX;
GRAPH graph;
// 함수 선언
void buildgraph (void);
void initgraph (void);
void insertVertex (int id);
void insertIncidentEdge (int v1, int v2, int w, int i);
void addFirst (INCIDENCE *H, int i);

void DijkstraShortestPaths (void);

HEAP *buildHeap (void);
void upHeap (HEAP* heap, int index);
void downHeap (HEAP* heap, int index, int size);
int removeMin (HEAP *heap, int i);
int opposite (int u, int e);
int isInclude (HEAP *heap, int id, int z);
void replaceKey (HEAP *heap, int id, int z, int w);

int main () {

    buildgraph();

    DijkstraShortestPaths();

    return 0;
}

void buildgraph (void) {

    scanf("%d %d %d", &graph.n, &graph.m, &graph.s);

    initgraph();

    int v1, v2, w = 0;

    MAX = -1;

    for (int i = 0; i < graph.m; i++) {
        scanf("%d %d %d", &v1, &v2, &w);
        insertIncidentEdge(v1, v2, w, i);

        if (MAX <= w) {
            MAX = w;
        }
    }

    MAX = MAX * graph.m + 1;

    return;
}
void initgraph (void) {

    graph.vertex = (VERTEX *) malloc((graph.n + 1) * sizeof(VERTEX)); // 1부터 시작 -> 이유: 힙에 넣고 빼는 과정에서 편리성 추구.
    graph.edge = (EDGE *) malloc(graph.m * sizeof(EDGE));

    for (int i = 1; i < graph.n + 1; i++) {
        insertVertex(i);
    }

    return;
}
void insertVertex (int id) {

    graph.vertex[id].name = id;

    graph.vertex[id].header = (INCIDENCE *) malloc(sizeof(INCIDENCE));
    graph.vertex[id].header->next = NULL;

    return;
}
void insertIncidentEdge (int v1, int v2, int w, int i) {

    graph.edge[i].v1 = v1;
    graph.edge[i].v2 = v2;
    graph.edge[i].weight = w;

    addFirst(graph.vertex[v1].header, i);
    addFirst(graph.vertex[v2].header, i);

    return;
}
void addFirst (INCIDENCE *H, int i) {

    INCIDENCE *node = NULL;
    node = (INCIDENCE *) malloc(sizeof(INCIDENCE));

    node->loc = i;
    node->next = H->next;
    H->next = node;

    return;
}
void DijkstraShortestPaths (void) {

    HEAP *heap = NULL;

    for (int i = 1; i < graph.n + 1; i++) { // 초기화
        graph.vertex[i].distance = MAX;
    }
    graph.vertex[graph.s].distance = 0;

    heap = buildHeap();

    INCIDENCE *p = NULL;
    int i, u, z = 0;

    i = graph.n;

    while (i > 0) {
        u = removeMin(heap, i);

        p = graph.vertex[u].header->next;
        while (p != NULL) {
            z = opposite(u, p->loc); // 부착 간선이 가리키는 edge의 위치를 통해 인접정점을 구하는 과정

            if (isInclude(heap, i, z) && graph.edge[p->loc].weight + graph.vertex[u].distance < graph.vertex[z].distance) {
                graph.vertex[z].distance = graph.edge[p->loc].weight + graph.vertex[u].distance; // 가중치 업데이트
                replaceKey(heap, i, z, graph.vertex[z].distance); // 큐 내에서 z의 거리(가중치)에 따라 위치 업데이트
            }
            p = p->next;
        }

        i--;
    }

    for (int i = 1; i < graph.n + 1; i++) {
        if (i != graph.s && graph.vertex[i].distance < MAX) {
            printf("%d %d\n", graph.vertex[i].name, graph.vertex[i].distance);
        }
    }

    return;
}
HEAP *buildHeap (void) {

    HEAP *heap = NULL;
    heap = (HEAP *) malloc((graph.n + 1) * sizeof(HEAP));

    for (int i = 1; i < graph.n + 1; i++) { // 초기화
        heap[i].key = graph.vertex[i].name;
        heap[i].weight = graph.vertex[i].distance;
    }

    for (int i = graph.n / 2; i >= 1; i--) { // 상향식 힙 생성
        downHeap(heap, i, graph.n);
    }

    return heap;
}
void upHeap (HEAP* heap, int index) {

    if (index == 1 || heap[index].weight >= heap[index/2].weight) {
        return;
    }

    HEAP tmp = { 0 };

    tmp = heap[index];
    heap[index] = heap[index/2];
    heap[index/2] = tmp;

    upHeap(heap, index/2);

    return;
}
void downHeap (HEAP* heap, int index, int size) {

    int left = 2 * index;
    int right = 2 * index + 1;
    int smaller = 0;
    HEAP tmp = { 0 };

    if (left > size) {
        return;
    }

    smaller = left;
    if (right <= size) {
        if (heap[right].weight < heap[left].weight) {
            smaller = right;
        }
    }

    if (heap[index].weight <= heap[smaller].weight) {
        return;
    }

    tmp = heap[index];
    heap[index] = heap[smaller];
    heap[smaller] = tmp;

    downHeap(heap, smaller, size);

    return;
}
int removeMin (HEAP *heap, int i) {

    HEAP result = { 0 };
    HEAP tmp = { 0 };

    if (i == 0) {
        return  -1;
    }

    result = heap[1];

    tmp = heap[1];
    heap[1] = heap[i];
    heap[i] = tmp;

    i -= 1;
    downHeap(heap, 1, i);

    return result.key;
}
int opposite (int u, int e) {

    if (graph.edge[e].v1 == u) {
        return graph.edge[e].v2;
    } else {
        return graph.edge[e].v1;
    }

}
int isInclude (HEAP *heap, int id, int z) {

    for (int i = 1; i < id; i++) {
        if (heap[i].key == z) {
            return 1;
        }
    }

    return 0;
}
void replaceKey (HEAP *heap, int id, int z, int w) {

    int loc = 0;

    for (int i = 1; i < id; i++) {
        if (heap[i].key == z) {
            heap[i].weight = w;
            loc = i;
            break;
        }
    }

    upHeap(heap, loc);

    return;
}


//#include <stdio.h> // 문제 2
//#include <string.h>
//#include <stdlib.h>
//// 정점에 대한 정보를 저장하는 구조체
//typedef struct vertex {
//    int name;
//    int distance;
//}VERTEX;
//// edge에 대한 정보를 저장하는 구조체 (어떤 정점 2개가 어떠한 가중치의 간선으로 연결되어 있는지에 대한 정보)
//typedef struct edge {
//    int v1; // 시작 정점
//    int v2; // 목적지 정점
//    int weight;
//}EDGE;
//// 그래프 전체 틀을 잡아줄 구조체
//typedef struct graph {
//    VERTEX *vertex;
//    EDGE *edge;
//    int n, m, s; // 정점과 간선의 개수 + 시작 정점의 위치
//}GRAPH;
//// 전역변수 설정
//int MAX;
//GRAPH graph;
//// 함수 선언
//void buildgraph (void);
//void initgraph (void);
//void insertVertex (int id);
//void insertIncidentEdge (int v1, int v2, int w, int i);
//
//void BellmanFordShortestPaths (void);
//
//int main () {
//
//    buildgraph();
//
//    BellmanFordShortestPaths();
//
//    return 0;
//}
//
//void buildgraph (void) {
//
//    scanf("%d %d %d", &graph.n, &graph.m, &graph.s);
//
//    initgraph();
//
//    int v1, v2, w = 0;
//
//    MAX = -1;
//
//    for (int i = 0; i < graph.m; i++) {
//        scanf("%d %d %d", &v1, &v2, &w);
//        insertIncidentEdge(v1, v2, w, i);
//
//        if (MAX <= w) {
//            MAX = w;
//        }
//    }
//
//    MAX = MAX * graph.m + 1;
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
//    return;
//}
//void insertIncidentEdge (int v1, int v2, int w, int i) {
//
//    graph.edge[i].v1 = v1;
//    graph.edge[i].v2 = v2;
//    graph.edge[i].weight = w;
//
//    return;
//}
//void BellmanFordShortestPaths (void) {
//
//    for (int i = 1; i < graph.n + 1; i++) {
//        graph.vertex[i].distance = MAX;
//    }
//    graph.vertex[graph.s].distance = 0;
//
//    int u, z = 0;
//
//    for (int i = 1; i < graph.n; i++) {
//        for (int j = 0; j < graph.m; j++) {
//            u = graph.edge[j].v1;
//            z = graph.edge[j].v2;
//            if (graph.vertex[u].distance != MAX) {
//                graph.vertex[z].distance = graph.vertex[z].distance < graph.vertex[u].distance + graph.edge[j].weight ? graph.vertex[z].distance : graph.vertex[u].distance + graph.edge[j].weight;
//            }
//            // **중요** if구문을 추가한 이유(oj: +30): u 정점이 무한대인경우에는 무한대에서 아주 작은 수를 뺴거나 더 해도 무한대이다. but, 여기서 MAX는 무한대 아닌 가장 큰 가중치 * 간선 수이므로 예외(오류)[예시 만약에 MAX = 3, u->z 가중치 = -2, z정점의 가중치가 2인 경우]가 발생할 수 있다. 그래서 if문을 추가하여 u정점이 무한대인 경우 (이 경우는 따로 업데이트를 하지 않아도 됨. 이유: u정점 가중치 = 무한대, w정점 가중치 = 무한대 : 어차피 w정점 가중치 = 무한대, u정점 가중치 = 무한대, w정점 가중치 = 무한대 : 어차피 w정점 가중치 = 상수 => 어차피 w정점의 가중치는 그대로 (무한대 = u정점에 도달할 수 있는 방법이 없다는 것을 의미하기 때문)
//        }
//    }
//
//    for (int i = 1; i < graph.n + 1; i++) {
//        if (i != graph.s && graph.vertex[i].distance < MAX) {
//            printf("%d %d\n", graph.vertex[i].name, graph.vertex[i].distance);
//        }
//    }
//
//    return;
//}
//

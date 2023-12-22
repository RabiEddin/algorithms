//
//  main.c
//  Algorithms_task_5
//
//  Created by 김도윤 on 2022/12/05.
//

//과제문제의 정점이 문자로 되어있는 부분은 코드를 짜는 경우에서 매우 복잡하게 만든다고 생각하여 처음 초기화하는 부분에서 문자를 정수로 변환하였다. (A->1, B->2, ...)
#include <stdio.h> // 과제 5
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
    int way; // 각 정점에 시작 정점으로부터 도달할 수 있는 경로의 수를 저장하는 변수
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
    int n, m, s, t; // 정점과 간선의 개수 + 시작 정점, 목적지 정점의 위치
}GRAPH;
// 우선순위 큐(힙)에 MST에 없는 정점들을 저장
typedef struct heap {
    int key;
    int weight;
}HEAP;
typedef struct sampleGraphinfo { // 처음 그래프를 초기화할때 그래프 구성에 대한 정보를 저장할 변수 선언
    char v1;
    char v2;
    int w;
}G_info;
// 전역변수 설정
int MAX;
GRAPH graph;
// 함수 선언
void buildgraph (void); // 그래프를 만드는 전체적인 큰 틀을 잡아주는 함수
void initgraph (void); // 처음에 그래프를 초기화하는 함수
void insertVertex (int id); // 처음에 정점에 대한 정보를 초기화하는 함수
void insertIncidentEdge (int v1, int v2, int w, int i); // 처음에 간선에 대한 정보를 초기화하는 함수
void addFirst (INCIDENCE *H, int i); // 인접정점에 대한 정보를 각 정점에 대한 간선 리스트에 저장하는 함수

void DijkstraShortestPaths (void); // 다익스트라 알고리즘 함수

HEAP *buildHeap (void); // 우선순위 큐를 힙으로 구현하는 함수
void upHeap (HEAP* heap, int index);
void downHeap (HEAP* heap, int index, int size);
int removeMin (HEAP *heap, int i); // 힙에서 가중치가 최솟값인 정점의 번호를 반환하는 함수
int opposite (int u, int e); // 정점 u와 부착간선 e를 통해 연결되어 있는 인접정점을 반환하는 함수
int isInclude (HEAP *heap, int id, int z); // 힙에 포함되어있는 정점인지 확인하는 함수
void replaceKey (HEAP *heap, int id, int z, int w); // 힙 내부에서 업데이트된 가중치 값을 토대로 정점들의 위치를 갱신하는 함수

int main () {

    char info[4][2] = { {'C', 'A'}, {'C', 'F'}, {'F', 'C'}, {'B', 'D'}}; //출력해야하는 시작정점과 목적지 정점에 대한 정보를 담은 리스트
    
    graph.n = 6; // 정점 수
    graph.m = 9; // 간선 수
    
    for (int i = 0; i < 4; i++) {
        
        graph.s = info[i][0] - 'A' + 1;
        graph.t = info[i][1] - 'A' + 1;
        
        buildgraph();

        DijkstraShortestPaths();
        
        // 다음 출력을 위해 시작정점과 목적지 정점에 대한 정보를 초기화하는 과정
        graph.s = 0;
        graph.t = 0;
        
    }

    return 0;
}

void buildgraph (void) {

    initgraph();

    G_info g_info[9] = {{'A', 'B', 8}, {'A', 'C', 1}, {'A', 'D', 4}, {'B', 'C', 7}, {'C', 'D', 5}, {'B', 'E', 4}, {'E', 'C', 3}, {'C', 'F', 9}, {'F', 'D', 4}}; // 그래프 구성시에 필요한 정보를 담은 리스트
    MAX = -1;
    
    int v1, v2, w = 0;

    for (int i = 0; i < graph.m; i++) {
        v1 = g_info[i].v1 - 'A' + 1;
        v2 = g_info[i].v2 - 'A' + 1;
        w = g_info[i].w;
        
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
        graph.vertex[i].way = 0; // 시작정점으로 부터 각 정점에 도달하는 경로의 수는 처음에 0으로 초기화
    }
    graph.vertex[graph.s].distance = 0;
    graph.vertex[graph.s].way = 1; // 시작정점에서 시작정점으로 도달하는 경로의 수 = 1

    heap = buildHeap();

    INCIDENCE *p = NULL;
    int i, u, z = 0;

    i = graph.n;

    while (i > 0) {
        u = removeMin(heap, i);

        p = graph.vertex[u].header->next;
        while (p != NULL) {
            z = opposite(u, p->loc); // 부착 간선이 가리키는 edge의 위치를 통해 인접정점을 구하는 과정

            if (isInclude(heap, i, z)) {
                if (graph.edge[p->loc].weight + graph.vertex[u].distance < graph.vertex[z].distance) {
                    graph.vertex[z].distance = graph.edge[p->loc].weight + graph.vertex[u].distance; // 가중치 업데이트
                    graph.vertex[z].way = graph.vertex[u].way; // 가중치가 업데이트 되면 u정점에 있는 경로의 수를 z정점에 업데이트 (이유: 시작정점 -> u = 상수, u -> z = 1 따라서 상수 * 1 = 상수)
                    replaceKey(heap, i, z, graph.vertex[z].distance); // 큐 내에서 z의 거리(가중치)에 따라 위치 업데이트
                } else if (graph.edge[p->loc].weight + graph.vertex[u].distance == graph.vertex[z].distance) {
                    graph.vertex[z].way += graph.vertex[u].way; // 만약에 거리가 같으면 z정점에 있는 경로에 u정점을 통해서 z정점으로 갈 수 있는 방법이 추가되는 것이므로 더한다.
                }
            }
            p = p->next;
        }

        i--;
    }

    printf("%c, %c : 최단거리 = %d, 최단경로 수 = %d\n", 'A' + graph.s - 1, 'A' + graph.t - 1, graph.vertex[graph.t].distance, graph.vertex[graph.t].way); // 출력

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

//
//  main.c
//  Algorithms_lesson_12_Training
//
//  Created by 김도윤 on 2022/11/20.
//

#include <stdio.h> // 문제 1
#include <string.h>
#include <stdlib.h>
// 그래프 구조체 구성에 대한 설명
// 간선에 대한 정보 저장 구조체
typedef struct incidence_list {
    int loc; // 간선에 대한 정보가 담겨 있는 edge의 위치
    struct incidence_list *next;
}INCIDENCE;
// 정점에 대한 정보를 저장하는 구조체
typedef struct vertex {
    char name; // 정점 이름
    INCIDENCE *inEdges; // 진입간선
    INCIDENCE *outEdges; // 진출간선
    int inDegree;
}VERTEX;
// edge에 대한 정보를 저장하는 구조체 (어떤 정점 2개가 어떠한 가중치의 간선으로 연결되어 있는지에 대한 정보)
typedef struct edge {
    int start; // 시작 노드
    int end; // 목적지 노드
}EDGE;
// 그래프 전체 틀을 잡아줄 구조체
typedef struct graph {
    VERTEX *vertices; // 정점의 개수로 구조체 배열 생성
    EDGE *edges; // 간선이 생길 수 있는 모든 경우의 개수로 구조체 배열 생성
}GRAPH;
// 전역변수 설정
GRAPH graph;
int n, m;
int topOrder[101];
int Q[100];
int Q_s, Q_e;
// 함수 설정
void buildGraph (void);
void initializeGraph (void);
void insertVertex (char vName, int i);
void insertDirectedEdge (char uName, char wName, int i);
int findIndex (char vName);
void addFirst (INCIDENCE *H, int i);
void topologicalSort (void);
int isEmpty (void);
void enqueue (int v);
int dequeue (void);

int main () {
    
    buildGraph();
    
    topologicalSort();
    
    if (topOrder[0] == 0) {
        printf("0\n");
    }
    else {
        for (int i = 1; i <= n; i++) {
            printf("%c ", graph.vertices[topOrder[i]].name);
        }
        printf("\n");
    }
    
    return 0;
}

void buildGraph (void) {
    
    char vName, uName, wName = '0';
    
    initializeGraph();
    
    scanf("%d", &n);
    getchar();
    
    for (int i = 0; i < n; i++) {
        scanf("%c", &vName);
        getchar();
        insertVertex(vName, i);
    }
    
    scanf("%d", &m);
    getchar();
    
    for (int i = 0; i < m; i++) {
        scanf("%c %c", &uName, &wName);
        getchar();
        insertDirectedEdge(uName, wName, i);
    }
    
    return;
}
void initializeGraph (void) {
    
    graph.vertices = (VERTEX *) malloc(100 * sizeof(VERTEX));
    graph.edges = (EDGE *) malloc(1000 * sizeof(EDGE));
    
}
void insertVertex (char vName, int i) {
    
    graph.vertices[i].name = vName;
    
    graph.vertices[i].outEdges = NULL;
    graph.vertices[i].outEdges = (INCIDENCE *) malloc(sizeof(INCIDENCE));
    graph.vertices[i].outEdges->next = NULL;
    graph.vertices[i].inEdges = NULL;
    graph.vertices[i].inEdges = (INCIDENCE *) malloc(sizeof(INCIDENCE));
    graph.vertices[i].inEdges->next = NULL;
    
    graph.vertices[i].inDegree = 0;
    
    return;
}
void insertDirectedEdge (char uName, char wName, int i) {
    
    int u, w = 0;
    
    u = findIndex(uName);
    w = findIndex(wName);
    
    graph.edges[i].start = u;
    graph.edges[i].end = w;
    
    addFirst(graph.vertices[u].outEdges, i);
    addFirst(graph.vertices[w].inEdges, i);
    
    graph.vertices[w].inDegree++;
    
}
int findIndex (char vName) {
    
    for (int i = 0; i < n; i++) {
        if (graph.vertices[i].name == vName) {
            return i;
        }
    }
    
    return -1;
}
void addFirst (INCIDENCE *H, int i) {
    
    INCIDENCE *node = NULL;
    node = (INCIDENCE *) malloc(sizeof(INCIDENCE));
    
    node->loc = i;
    node->next = H->next;
    H->next = node;
    
    return;
}
void topologicalSort (void) {
    
    int in[100] = { 0 };
    
    Q_s = 0;
    Q_e = 0;
    for (int i = 0; i < 100; i++) {
        Q[i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        in[i] = graph.vertices[i].inDegree;
        
        if (in[i] == 0) {
            enqueue(i);
        }
    }
    
    int t, u, w = 0;
    INCIDENCE *e = NULL;
    
    t = 1;
    
    while (!isEmpty()) {
        u = dequeue();
        topOrder[t] = u;
        t += 1;
        
        e = graph.vertices[u].outEdges;
        e = e->next;
        
        while (e != NULL) {
            w = graph.edges[e->loc].end;
            
            in[w] -= 1;
            if (in[w] == 0) {
                enqueue(w);
            }
            e = e->next;
        }
    }
    
    if (t <= n) {
        topOrder[0] = 0;
    }
    else {
        topOrder[0] = 1;
    }
    
}
int isEmpty (void) {
    
    if (Q_s == Q_e) {
        return 1;
    }
    else {
        return 0;
    }
    
}
void enqueue (int v) {
    
    Q[Q_e] = v;
    Q_e = (Q_e + 1) % 100;
    
    return;
}
int dequeue (void) {
    
    int ans = 0;
    
    ans = Q[Q_s];
    Q_s = (Q_s + 1) % 100;
    
    return ans;
}

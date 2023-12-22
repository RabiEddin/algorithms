//
//  main.c
//  Algorithms_lesson_11_Training
//
//  Created by 김도윤 on 2022/11/13.
//

//#include <stdio.h> // 문제 1
//#include <string.h>
//#include <stdlib.h>
//// 간선에 대한 정보 저장 구조체
//typedef struct incidence_list {
//    int loc;
//    struct incidence_list *next;
//}INCIDENCE;
//// 정점에 대한 정보를 저장하는 구조체
//typedef struct vertex {
//    int id;
//    INCIDENCE *header;
//    int label;
//}VERTEX;
//// edge에 대한 정보를 저장하는 구조체 (어떤 정점 2개가 어떠한 가중치의 간선으로 연결되어 있는지에 대한 정보)
//typedef struct edge {
//    int v1;
//    int v2;
//    int label;
//}EDGE;
//// 그래프 전체 틀을 잡아줄 구조체
//typedef struct graph {
//    VERTEX *vertices; // 정점의 개수로 구조체 배열 생성
//    EDGE *edges; // 간선이 생길 수 있는 모든 경우의 개수로 구조체 배열 생성
//    int edge_size; // edge 개수를 계속해서 업데이트하는 변수
//}GRAPH;
//
//INCIDENCE *getIncidence (int edge) { // 새로운 간선을 만들어 반환하는 함수
//
//    INCIDENCE *new = NULL;
//    new = (INCIDENCE *) malloc(sizeof(INCIDENCE));
//
//    new->loc = edge;
//    new->next = NULL;
//
//    return new;
//}
//
//void makeGraph (GRAPH *graph, int n, int m);
//void insertEdge (int v1, int v2, GRAPH *graph); // 처음에 그래프 중 edge를 만드는 함수
//void insertIncidence (int v1, int v2, INCIDENCE *incidence, GRAPH *graph); // 처음에 그래프 중 간선을 만드는 함수
//void DFS (GRAPH *graph, int s, int n, int m);
//void rDFS (GRAPH *graph, int v);
//
//int main () {
//
//    int n, m, s = 0;
//
//    scanf("%d %d %d", &n, &m, &s);
//
//    GRAPH *graph = NULL;
//    graph = (GRAPH *) malloc(sizeof(GRAPH));
//    if (graph == NULL) {
//        return -1;
//    }
//
//    makeGraph(graph, n, m);
//
//    int v1, v2 = 0;
//
//    for (int i = 0; i < m; i++) {
//        scanf("%d %d", &v1, &v2);
//        insertEdge(v1, v2, graph);
//    }
//
//    DFS(graph, s, n, m);
//
//    return 0;
//}
//
//void makeGraph (GRAPH *graph, int n, int m) {
//
//    graph->edge_size = 0;
//
//    graph->edges = NULL;
//    graph->vertices = (VERTEX *) malloc(n * sizeof(VERTEX));
//    graph->edges = (EDGE *) malloc(m *sizeof(EDGE));
//
//    for (int i = 0; i < n; i++) {
//        graph->vertices[i].id = i + 1;
//        graph->vertices[i].header = NULL;
//    }
//
//    return;
//}
//void insertEdge (int v1, int v2, GRAPH *graph) {
//
//    graph->edges[graph->edge_size].v1 = v1;
//    graph->edges[graph->edge_size].v2 = v2;
//
//    INCIDENCE *incidence1 = NULL;
//    INCIDENCE *incidence2 = NULL;
//
//    incidence1 = getIncidence(graph->edge_size);
//    incidence2 = getIncidence(graph->edge_size);
//
//    if (v1 != v2) {
//        insertIncidence(v1, v2, incidence1, graph);
//        insertIncidence(v2, v1, incidence2, graph);
//    }
//    else { // v1 == v2
//        insertIncidence(v1, v2, incidence1, graph);
//    }
//
//    graph->edge_size++;
//
//    return;
//} // 처음에 그래프 중 edge를 만드는 함수
//void insertIncidence (int v1, int v2, INCIDENCE *incidence, GRAPH *graph) {
//
//    INCIDENCE *p = NULL;
//    int otherVertex = 0;
//
//    p = graph->vertices[v1 - 1].header;
//
//    if (p == NULL) { // 정점에 처음으로 edge에 대한 정보가 들어가는 경우
//        graph->vertices[v1 - 1].header = incidence;
//    }
//    else { // 정점에 이미 1개 이상의 edge에 대한 정보가 들어간 경우
//        if (graph->edges[p->loc].v1 == v1) {
//            otherVertex = graph->edges[p->loc].v2;
//        }
//        else {
//            otherVertex = graph->edges[p->loc].v1;
//        }
//
//        if (otherVertex > v2) { // 첫 번째 edge에서 정렬이 가능한 경우
//            incidence->next = p;
//            graph->vertices[v1 - 1].header = incidence;
//        }
//        else {
//            while (p->next != NULL) {
//                if (graph->edges[p->next->loc].v1 == v1) {
//                    otherVertex = graph->edges[p->next->loc].v2;
//                }
//                else {
//                    otherVertex = graph->edges[p->next->loc].v1;
//                }
//
//                if (otherVertex > v2) {
//                    break;
//                }
//
//                p = p->next;
//            }
//            if (p->next == NULL) { // 오름차순으로 삽입할 때 중간에 끼는 경우가 아닌 가장 끝에 삽입되는 경우 while문 안에 있는 if문에 걸리지 않음.
//                p->next = incidence;
//            }
//            else {
//                incidence->next = p->next;
//                p->next = incidence;
//            }
//        }
//    }
//
//    return;
//} // 처음에 그래프 중 간선을 만드는 함수
//void DFS (GRAPH *graph, int s, int n, int m) {
//
//    for (int i = 0; i < n; i++) {
//        graph->vertices[i].label = 0;
//    }
//
//    for (int i = 0; i < m; i++) {
//        graph->edges[i].label = 0;
//    }
//
//    rDFS(graph, s - 1);
//
//    return;
//}
//void rDFS (GRAPH *graph, int v) {
//
//    graph->vertices[v].label = 1; // Visited
//
//    printf("%d\n", v + 1);
//
//    int otherVertex = 0;
//    INCIDENCE *p = NULL;
//    p = graph->vertices[v].header;
//
//    while (p != NULL) {
//        if (graph->edges[p->loc].label == 0) {
//            if (v + 1 == graph->edges[p->loc].v1) {
//                otherVertex = graph->edges[p->loc].v2;
//            }
//            else {
//                otherVertex = graph->edges[p->loc].v1;
//            }
//
//            if (graph->vertices[otherVertex - 1].label == 0) {
//                graph->edges[p->loc].label = 1;
//                rDFS(graph, otherVertex - 1);
//            }
//            else {
//                graph->edges[p->loc].label = -1;
//            }
//        }
//
//        p = p->next;
//    }
//
//    return;
//}


#include <stdio.h> // 문제 2
#include <string.h>
#include <stdlib.h>
// edge에 대한 정보를 저장하는 구조체 (어떤 정점 2개가 어떠한 가중치의 간선으로 연결되어 있는지에 대한 정보)
typedef struct edge {
    int v1;
    int v2;
    int label;
}EDGE;
// 정점에 대한 정보를 저장하는 구조체
typedef struct vertex {
    int id;
    int label;
}VERTEX;
// 그래프 전체 틀을 잡아줄 구조체
typedef struct graph {
    VERTEX *vertices; // 정점에 대한 정보를 구조체 배열로 생성
    int **adjacencyMatrix; // 간선에 대한 정보를 2차원 리스트로 생성(인접행렬)
    EDGE *edges; // 간선이 생길 수 있는 모든 경우의 개수로 구조체 배열 생성
    int edge_size; // edge 개수를 계속해서 업데이트하는 변수
}GRAPH;

void makeGraph (GRAPH *graph, int n, int m);
void insertEdge (int v1, int v2, GRAPH *graph); // 처음에 그래프 중 edge와 간선(인접행렬)을 만드는 함수
void BFS (GRAPH *graph, int n, int m, int s);
void BFS1 (GRAPH *graph, int v, int n, int m);

int main () {
    
    int n, m, s = 0;
    
    scanf("%d %d %d", &n, &m, &s);
    
    GRAPH *graph = NULL;
    graph = (GRAPH *) malloc(sizeof(GRAPH));
    if (graph == NULL) {
        return -1;
    }
    
    makeGraph(graph, n, m);
    
    int v1, v2 = 0;
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &v1, &v2);
        insertEdge(v1, v2, graph);
    }
    
    BFS(graph, n, m, s);
    
    return 0;
}

void makeGraph (GRAPH *graph, int n, int m) {
    
    graph->edge_size = 0;
    
    graph->edges = NULL;
    graph->edges = (EDGE *) malloc(m * sizeof(EDGE));
    graph->vertices = NULL;
    graph->vertices = (VERTEX *) malloc(n * sizeof(VERTEX));
    graph->adjacencyMatrix = NULL;
    graph->adjacencyMatrix = (int **) malloc(n * sizeof(int *));
    
    for (int i = 0; i < n; i++) {
        graph->vertices[i].id = i + 1;
        graph->adjacencyMatrix[i] = (int *) malloc(n * sizeof(int));
        
        for (int j = 0; j < n; j++) {
            graph->adjacencyMatrix[i][j] = -1;
        }
    }
    
    return;
}
void insertEdge (int v1, int v2, GRAPH *graph) {
    
    graph->edges[graph->edge_size].v1 = v1;
    graph->edges[graph->edge_size].v2 = v2;

    if (v1 != v2) {
        graph->adjacencyMatrix[v1 - 1][v2 - 1] = graph->edge_size;
        graph->adjacencyMatrix[v2 - 1][v1 - 1] = graph->edge_size;
    }
    else {
        graph->adjacencyMatrix[v1 - 1][v2 - 1] = graph->edge_size;
    }

    graph->edge_size++;

    return;
} // 처음에 그래프 중 edge와 간선(인접행렬)을 만드는 함수
void BFS (GRAPH *graph, int n, int m, int s) {
    
    for (int i = 0; i < n; i++) {
        graph->vertices[i].label = 0;
    }
    
    for (int i = 0; i < m; i++) {
        graph->edges[i].label = 0;
    }
    
    BFS1(graph, s - 1, n, m);
    
    return;
}
void BFS1 (GRAPH *graph, int v, int n, int m) {
    
    int otherVertex = 0;
    int cnt = 0;
    int **tmp = NULL;
    tmp = (int **) malloc(n * sizeof(int*));
    
    for (int i = 0; i < n; i++) {
        tmp[i] = (int *) malloc(n * sizeof(int));
        
        for (int j = 0; j < n; j++) {
            tmp[i][j] = 0;
        }
    }
    
    tmp[0][0] = v + 1;
    graph->vertices[v].label = 1;
    
    printf("%d\n", v + 1);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; tmp[i][j] != 0; j++) {
            for (int k = 0; k < n; k++) {
                if (graph->adjacencyMatrix[tmp[i][j] - 1][k] != -1) {
                    if (graph->edges[graph->adjacencyMatrix[tmp[i][j] - 1][k]].v1 == tmp[i][j]) {
                        otherVertex = graph->edges[graph->adjacencyMatrix[tmp[i][j] - 1][k]].v2;
                    }
                    else {
                        otherVertex = graph->edges[graph->adjacencyMatrix[tmp[i][j] - 1][k]].v1;
                    }
                    
                    if (graph->vertices[otherVertex -1].label == 0) {
                        printf("%d\n", otherVertex);
                        graph->edges[graph->adjacencyMatrix[tmp[i][j] - 1][k]].label = 1;
                        graph->vertices[otherVertex -1].label = 1;
                        tmp[i + 1][cnt] = otherVertex;
                        cnt++;
                    }
                    else {
                        graph->edges[graph->adjacencyMatrix[tmp[i][j] - 1][k]].label = -1;
                    }
                }
            }
        }
        cnt = 0;
    }
        
    return;
}

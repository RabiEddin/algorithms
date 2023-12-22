//
//  main.c
//  Algorithms_lesson_10_Training
//
//  Created by 김도윤 on 2022/11/02.
//

#include <stdio.h> // 문제 1 - 그래프의 정보의 개수가 정적이어서 배열로 인접리스트를 구현할 것이다.
#include <string.h>
#include <stdlib.h>
// 간선에 대한 정보 저장 구조체
typedef struct incidence_list {
    int loc;
    struct incidence_list *next;
}INCIDENCE;
// 정점에 대한 정보를 저장하는 구조체
typedef struct vertex {
    int id;
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
    VERTEX vertices[6]; // 정점의 개수로 구조체 배열 생성
    EDGE edges[21]; // 간선이 생길 수 있는 모든 경우의 개수로 구조체 배열 생성
    int edge_size; // edge 개수를 계속해서 업데이트하는 변수
}GRAPH;

INCIDENCE *getIncidence (int edge) { // 새로운 간선을 만들어 반환하는 함수

    INCIDENCE *new = NULL;
    new = (INCIDENCE *) malloc(sizeof(INCIDENCE));

    new->loc = edge;
    new->next = NULL;

    return new;
}

void makeGraph (GRAPH *graph);
void insertEdge (int v1, int v2, int w, GRAPH *graph); // 처음에 그래프 중 edge를 만드는 함수
void updateEdge (int v1, int v2, int w, GRAPH *graph); // mode가 m인 경우 중 w != 0인 경우 사용하는 함수
void deleteEdge (int v1, int v2, int w, GRAPH *graph); // mode가 m인 경우 중 w == 0인 경우 사용하는 함수
void insertIncidence (int v1, int v2, INCIDENCE *incidence, GRAPH *graph); // 처음에 그래프 중 간선을 만드는 함수
void deleteIncidence (int v1, int v2, GRAPH *graph); // mode가 m인 경우 중 w == 0인 경우 사용하는 함수
void printnode_a (int vertex, GRAPH *graph); // mode가 a인 경우 출력하는 함수

int main () {

    GRAPH graph;

    makeGraph(&graph);

    char mode = '0';
    int node_num = 0;
    int a = 0;
    int b = 0;
    int w = 0;

    while (mode != 'q') {
        scanf("%c", &mode);

        switch (mode) {
            case 'a':
                scanf("%d", &node_num);
                printnode_a(node_num, &graph);
                break;
            case 'm':
                scanf("%d %d %d", &a, &b, &w);
                if (w != 0) {
                    updateEdge(a, b, w, &graph);
                }
                else {
                    deleteEdge(a, b, w, &graph);
                }
                break;
            case 'q':
                break;
            default:
                break;
        }
        getchar();
    }

    return 0;
}

void makeGraph (GRAPH *graph) {

    for (int i = 0; i < 6; i++) { // 구조체 그래프내에 있는 정점 배열을 초기화하는 과정
        graph->vertices[i].id = i + 1;
        graph->vertices[i].header = NULL;
    }

    graph->edge_size = 0;

    insertEdge(1, 2, 1, graph);
    insertEdge(2, 3, 1, graph);
    insertEdge(1, 3, 1, graph);
    insertEdge(1, 4, 1, graph);
    insertEdge(1, 6, 2, graph);
    insertEdge(3, 5, 4, graph);
    insertEdge(5, 5, 4, graph);
    insertEdge(5, 6, 3, graph);

    return;
}
void insertEdge (int v1, int v2, int w, GRAPH *graph) {

    // 그래프 edge 만들기 + edge의 크기 업데이트 (+1)
    graph->edges[graph->edge_size].v1 = v1;
    graph->edges[graph->edge_size].v2 = v2;
    graph->edges[graph->edge_size].weight = w;

    INCIDENCE *incidence1 = NULL;
    INCIDENCE *incidence2 = NULL;

    incidence1 = getIncidence(graph->edge_size);
    incidence2 = getIncidence(graph->edge_size);

    if (v1 != v2) {
        insertIncidence(v1, v2, incidence1, graph);
        insertIncidence(v2, v1, incidence2, graph);
    }
    else { // v1 == v2
        insertIncidence(v1, v2, incidence1, graph);
    }

    graph->edge_size++;

    return;
}
void updateEdge (int v1, int v2, int w, GRAPH *graph) {

    INCIDENCE *p = NULL;
    int otherVertex = 0;
    int flag = 0;

    p = graph->vertices[v1 - 1].header;

    if (v1 < 1 || v1 > 6 || v2 < 1 || v2 > 6) {
        printf("-1\n");
        return;
    }
    else if (p == NULL) {
        insertEdge(v1, v2, w, graph);
    }
    else {
        while (p != NULL) {
            if (graph->edges[p->loc].v1 == v1) {
                otherVertex = graph->edges[p->loc].v2;
            }
            else {
                otherVertex = graph->edges[p->loc].v1;
            }

            if (v2 == otherVertex) {
                graph->edges[p->loc].weight = w;
                flag = 1;
                break;
            }

            p = p->next;
        }
        if (flag == 1) {
            return;
        }
        else {
            insertEdge(v1, v2, w, graph);
        }
    }

}
void deleteEdge (int v1, int v2, int w, GRAPH *graph) {

    INCIDENCE *p = NULL;
    int otherVertex = 0;
    int flag = 0;

    p = graph->vertices[v1 - 1].header;

    if (v1 < 1 || v1 > 6 || v2 < 1 || v2 > 6) {
        printf("-1\n");
        return;
    }
    else if (p == NULL) {
        printf("-1\n");
        return;
    }
    else {
        while (p != NULL) {
            if (graph->edges[p->loc].v1 == v1) {
                otherVertex = graph->edges[p->loc].v2;
            }
            else {
                otherVertex = graph->edges[p->loc].v1;
            }

            if (v2 == otherVertex) {
                flag = 1;
                break;
            }

            p = p->next;
        }
        if (flag == 0) {
            printf("-1\n");
            return;
        }
        else {
            if (v1 != v2) {
                deleteIncidence(v1, v2, graph);
                deleteIncidence(v2, v1, graph);
            }
            else {
                deleteIncidence(v1, v2, graph);
            }
        }
    }

}
void insertIncidence (int v1, int v2, INCIDENCE *incidence, GRAPH *graph) { // else 부분에 대해서 조금 더 복습하기

    INCIDENCE *p = NULL;
    int otherVertex = 0;

    p = graph->vertices[v1 - 1].header;

    if (p == NULL) { // 정점에 처음으로 edge에 대한 정보가 들어가는 경우
        graph->vertices[v1 - 1].header = incidence;
    }
    else { // 정점에 이미 1개 이상의 edge에 대한 정보가 들어간 경우
        if (graph->edges[p->loc].v1 == v1) {
            otherVertex = graph->edges[p->loc].v2;
        }
        else {
            otherVertex = graph->edges[p->loc].v1;
        }

        if (otherVertex > v2) { // 첫 번째 edge에서 정렬이 가능한 경우
            incidence->next = p;
            graph->vertices[v1 - 1].header = incidence;
        }
        else {
            while (p->next != NULL) {
                if (graph->edges[p->next->loc].v1 == v1) {
                    otherVertex = graph->edges[p->next->loc].v2;
                }
                else {
                    otherVertex = graph->edges[p->next->loc].v1;
                }

                if (otherVertex > v2) {
                    break;
                }

                p = p->next;
            }
            if (p->next == NULL) { // 오름차순으로 삽입할 때 중간에 끼는 경우가 아닌 가장 끝에 삽입되는 경우 while문 안에 있는 if문에 걸리지 않음.
                p->next = incidence;
            }
            else {
                incidence->next = p->next;
                p->next = incidence;
            }
        }
    }

    return;
}
void deleteIncidence (int v1, int v2, GRAPH *graph) {

    INCIDENCE *p = NULL;
    int otherVertex = 0;

    p = graph->vertices[v1 - 1].header;

    if (graph->edges[p->loc].v1 == v1) {
        otherVertex = graph->edges[p->loc].v2;
    }
    else {
        otherVertex = graph->edges[p->loc].v1;
    }

    if (otherVertex == v2) { // 첫 번째 edge를 삭제하는 경우
        graph->vertices[v1 - 1].header = p->next;
    }
    else {
        while (p->next != NULL) {
            if (graph->edges[p->next->loc].v1 == v1) {
                otherVertex = graph->edges[p->next->loc].v2;
            }
            else {
                otherVertex = graph->edges[p->next->loc].v1;
            }

            if (otherVertex == v2) {
                p->next = p->next->next;
                break;
            }

            p = p->next;
        }
    }

    return;
}
void printnode_a (int vertex, GRAPH *graph) {

    INCIDENCE *p = NULL;
    int otherVertex = 0;

    p = graph->vertices[vertex - 1].header;

    if ((vertex < 1 || vertex > 6) || (p == NULL)) {
        printf("-1\n");
        return;
    }
    else {
        while (p != NULL) {
            if (graph->edges[p->loc].v1 == vertex) {
                otherVertex = graph->edges[p->loc].v2;
            }
            else {
                otherVertex = graph->edges[p->loc].v1;
            }

            printf(" %d %d", otherVertex, graph->edges[p->loc].weight);

            p = p->next;


        }
        printf("\n");
    }

    return;
}


//#include <stdio.h> // 문제 2 - 그래프의 정보의 개수가 정적이어서 배열로 인접행렬를을 구현할 것이다.
//#include <string.h>
//#include <stdlib.h>
//
//// edge에 대한 정보를 저장하는 구조체 (어떤 정점 2개가 어떠한 가중치의 간선으로 연결되어 있는지에 대한 정보)
//typedef struct edge {
//    int v1;
//    int v2;
//    int weight;
//}EDGE;
//// 그래프 전체 틀을 잡아줄 구조체
//typedef struct graph {
//    int vertices[6]; // 정점에 대한 정보를 배열로 생성
//    int adjacencyMatrix[6][6]; // 간선에 대한 정보를 2차원 리스트로 생성(인접행렬)
//    EDGE edges[21]; // 간선이 생길 수 있는 모든 경우의 개수로 구조체 배열 생성
//    int edge_size; // edge 개수를 계속해서 업데이트하는 변수
//}GRAPH;
//
//void makeGraph (GRAPH *graph);
//void insertEdge (int v1, int v2, int w, GRAPH *graph); // 처음에 그래프 중 edge와 간선(인접행렬)을 만드는 함수
//void updateEdge (int v1, int v2, int w, GRAPH *graph); // mode가 m인 경우 중 w != 0인 경우 사용하는 함수
//void deleteEdge (int v1, int v2, int w, GRAPH *graph); // mode가 m인 경우 중 w == 0인 경우 사용하는 함수
//void printnode_a (int v, GRAPH *graph);
//
//int main () {
//
//    GRAPH graph;
//
//    makeGraph(&graph);
//
//    char mode = '0';
//    int node_num = 0;
//    int a = 0;
//    int b = 0;
//    int w = 0;
//
//    while (mode != 'q') {
//        scanf("%c", &mode);
//
//        switch (mode) {
//            case 'a':
//                scanf("%d", &node_num);
//                printnode_a(node_num, &graph);
//
//                break;
//            case 'm':
//                scanf("%d %d %d", &a, &b, &w);
//                if (w != 0) {
//                    updateEdge(a, b, w, &graph);
//                }
//                else {
//                    deleteEdge(a, b, w, &graph);
//                }
//                break;
//            case 'q':
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
//void makeGraph (GRAPH *graph) {
//
//    for (int i = 0; i < 6; i++) {
//        graph->vertices[i] = i + 1;
//        for (int j = 0; j < 6; j++) {
//            graph->adjacencyMatrix[i][j] = -1;
//        }
//    }
//
//    graph->edge_size = 0;
//
//    insertEdge(1, 2, 1, graph);
//    insertEdge(2, 3, 1, graph);
//    insertEdge(1, 3, 1, graph);
//    insertEdge(1, 4, 1, graph);
//    insertEdge(1, 6, 2, graph);
//    insertEdge(3, 5, 4, graph);
//    insertEdge(5, 5, 4, graph);
//    insertEdge(5, 6, 3, graph);
//
//    return;
//}
//void insertEdge (int v1, int v2, int w, GRAPH *graph) {
//
//    graph->edges[graph->edge_size].v1 = v1;
//    graph->edges[graph->edge_size].v2 = v2;
//    graph->edges[graph->edge_size].weight = w;
//
//    if (v1 != v2) {
//        graph->adjacencyMatrix[v1 - 1][v2 - 1] = graph->edge_size;
//        graph->adjacencyMatrix[v2 - 1][v1 - 1] = graph->edge_size;
//    }
//    else {
//        graph->adjacencyMatrix[v1 - 1][v2 - 1] = graph->edge_size;
//    }
//
//    graph->edge_size++;
//
//    return;
//}
//void updateEdge (int v1, int v2, int w, GRAPH *graph) {
//
//    if (v1 < 1 || v1 > 6 || v2 < 1 || v2 > 6) {
//        printf("-1\n");
//        return;
//    }
//    else if (graph->edges[graph->adjacencyMatrix[v1 - 1][v2 - 1]].weight == -1) {
//        insertEdge(v1, v2, w, graph);
//    }
//    else {
//        graph->edges[graph->adjacencyMatrix[v1 - 1][v2 - 1]].weight = w;
//    }
//
//    return;
//}
//void deleteEdge (int v1, int v2, int w, GRAPH *graph) {
//
//    if (v1 < 1 || v1 > 6 || v2 < 1 || v2 > 6) {
//        printf("-1\n");
//        return;
//    }
//    else if (graph->adjacencyMatrix[v1 - 1][v2 - 1] == -1) {
//        printf("-1\n");
//        return;
//    }
//    else {
//        graph->adjacencyMatrix[v1 - 1][v2 - 1] = -1;
//        graph->adjacencyMatrix[v2 - 1][v1 - 1] = -1;
//    }
//
//    return;
//}
//void printnode_a (int v, GRAPH *graph) {
//
//    if (v < 1 || v > 6) {
//        printf("-1\n");
//        return;
//    }
//    else {
//        for (int i = 0; i < 6; i++) {
//            if (graph->adjacencyMatrix[v - 1][i] != -1) {
//                printf(" %d %d", i + 1, graph->edges[graph->adjacencyMatrix[v - 1][i]].weight);
//            }
//        }
//        printf("\n");
//    }
//
//    return;
//}

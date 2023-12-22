//
//  main.c
//  Algorithms_lesson_1_Training
//
//  Created by 김도윤 on 2022/09/01.
//

#include <stdio.h> // 문제 1
#include <string.h>
#include <stdlib.h>

typedef struct node {
    char elem;
    struct node *prev;
    struct node *next;
}NODE;

void add (NODE *h, NODE *t, int r, int e); // 이중연결리스트에 원소 추가
void delete (NODE *h, NODE *t, int r); // 이중연결리스트에서 원소 삭제
char get (NODE *h, NODE *t, int r); // 이중연결리스트에서 r위치에 있는 원소 main함수로 반환
void Print (NODE *h, NODE *t); // 이중연결리스트 출력

int main () {

    NODE header, trailer;
    header.next = &trailer;
    header.prev = 0;
    trailer.prev = &header;
    trailer.next = 0;

    int num = 0;
    int loc = 0;
    char cal, el = 0;
    char get_ans = -1;

    scanf("%d", &num); // 연산 개수 입력
    getchar();

    for (int i = 0; i < num; i++) {
        scanf("%c", &cal); // 어떤 연산을 수행할지 입력
        switch (cal) { // 스위치 구문은 통해 연산의 종류 구분
            case 'A':
                scanf("%d %c", &loc, &el); // 순위와 원소 입력
                getchar();
                add(&header, &trailer, loc, el); // 원소 추가 함수 호출
                break;
            case 'D':
                scanf("%d", &loc); // 순위 입력
                getchar();
                delete(&header, &trailer, loc); // 원소 삭제 함수 호출
                break;
            case 'G':
                scanf("%d", &loc); // 순위 입력
                getchar();
                get_ans = get(&header, &trailer, loc); // loc에 위치해있는 순위의 원소를 함수 호출하여 get_ans로 반환
                if (get_ans != -1) {
                    printf("%c\n", get_ans);
                }
                break;
            case 'P':
                getchar();
                Print(&header, &trailer); // 출력 함수 호출
                break;
            default:
                break;
        }
    }

    return 0;
}

void add (NODE *h, NODE *t, int r, int e) {

    if (r == 0) { // 순위 정보가 유효하지 않는 경우
        printf("invalid position\n");
        return;
    }

    NODE *temp = h;
    NODE *new = NULL;
    new = (NODE *) malloc(sizeof(NODE));
    new->elem = e;


    for (int i = 0; i < r; i++) {
        if (temp->next == 0) { // 순위 정보까지 도달하기 전에 이중연결리스트에 정보가 없는 경우
            printf("invalid position\n");
            return;
        }
        temp = temp->next;
    }
    temp = temp->prev;
    // 이중연결리스트에 새로운 원소 정보 노드로 만들어서 추가
    new->prev = temp;
    new->next = temp->next;
    temp->next->prev = new;
    temp->next = new;

}
void delete (NODE *h, NODE *t, int r) {

    if (r == 0) { // 순위 정보가 유효하지 않는 경우
        printf("invalid position\n");
        return;
    }

    NODE *temp = h;

    for (int i = 0; i < r; i++) {
        if (temp->next == 0) { // 순위 정보까지 도달하기 전에 이중연결리스트에 정보가 없는 경우
            printf("invalid position\n");
            return;
        }
        temp = temp->next;
    }
    if (temp->next == 0) { // 순위 정보가 trailer까지 도달한 경우 -> 이 경우는 순위 정보가 없는 경우여서 if문을 추가
        printf("invalid position\n");
        return;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

}
char get (NODE *h, NODE *t, int r) {

    if (r == 0) { // 순위 정보가 유효하지 않는 경우
        printf("invalid position\n");
        return -1;
    }

    char ans = 0;

    NODE *temp = h;

    for (int i = 0; i < r; i++) {
        if (temp->next == 0) { // 순위 정보까지 도달하기 전에 이중연결리스트에 정보가 없는 경우
            printf("invalid position\n");
            return -1;
        }
        temp = temp->next;
    }
    if (temp->next == 0) { // 순위 정보가 trailer까지 도달한 경우 -> 이 경우는 순위 정보가 없는 경우여서 if문을 추가
        printf("invalid position\n");
        return -1;
    }

    ans = temp->elem;

    return ans;
}
void Print (NODE *h, NODE *t) {

    NODE *temp = h;

    temp = temp->next;
    while (temp->next != 0) {
        printf("%c", temp->elem);
        temp = temp->next;
    }
    printf("\n");

}


//// 전위순회 순서대로 데이터 제공 -> 전위순회 순서대로 데이터 찾아가는 방식으로 전위순회 순서대로 데이터 입력//
//#include <stdio.h> // 문제 2
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct TREENODE {
//    int data;
//    struct TREENODE *left;
//    struct TREENODE *right;
//}TREENODE;
//
//void get_Node (TREENODE **p); // -> 새로운 노드 생성
//void get_Tree (TREENODE **root, int data, int left_data, int right_data); // -> 새로운 트리 생성
//void add_Tree (TREENODE **root, int new_data, int left_new_data, int right_new_data); // -> 트리 중간에 노드 투입
//void Search_Tree (TREENODE **root, char *infor); // -> 트리 속에 있는 원하는 데이터 찾기
//
//int main () {
//
//    TREENODE *root = NULL;
//    get_Node(&root);
//
//    int num = 0;
//    int data, left_data, right_data = 0;
//
//    scanf("%d", &num);
//
//    scanf("%d %d %d", &data, &left_data, &right_data);
//    get_Tree(&root, data, left_data, right_data); // -> 초기 루트 노드를 만들기 위해 get_Tree 함수 호출
//
//    for (int i = 1; i < num; i++) {
//        scanf("%d %d %d", &data, &left_data, &right_data);
//        add_Tree(&root, data, left_data, right_data); //-> 전위순회 방식으로 노드를 추가하기 위해 add_Tree 함수 호출
//    }
//
//    char info[101] = { 0 };
//
//    scanf("%d", &num);
//
//    for (int i = 0; i < num; i++) {
//        scanf("%s", info);
//        getchar();
//        Search_Tree(&root, info); // -> 입력 받은 탐색정보를 통해 출력하기 위해 Search_Tree 함수 호출
//    }
//
//    return 0;
//}
//
//void get_Node (TREENODE **p) { // -> 새로운 노드 생성
//
//    (*p) = (TREENODE *) malloc(sizeof(TREENODE));
//    (*p)->left = NULL;
//    (*p)->right = NULL;
//
//}
//void get_Tree (TREENODE **root, int data, int left_data, int right_data) { // ->새로운 트리 생성 (즉,초기 루트 노드를 만들때만 사용)
//
//    TREENODE *left_new = NULL;
//    get_Node(&left_new);
//    left_new->data = left_data;
//    TREENODE *right_new = NULL;
//    get_Node(&right_new);
//    right_new->data = right_data;
//
//    (*root)->data = data;
//    (*root)->left = left_new;
//    (*root)->right = right_new;
//
//}
//void add_Tree (TREENODE **root, int new_data, int left_new_data, int right_new_data) { // -> 트리 중간에 노드 투입
//
//    if ((*root) == NULL) {
//        return;
//    }
//    // 전위 순회 방식으로 노드 추가
//    if ((*root)->data == new_data) {
//        if (left_new_data != 0) {
//            TREENODE *left_node = NULL;
//            get_Node(&left_node);
//            left_node->data = left_new_data;
//            (*root)->left = left_node;
//        }
//        if (right_new_data != 0) {
//            TREENODE *right_node = NULL;
//            get_Node(&right_node);
//            right_node->data = right_new_data;
//            (*root)->right = right_node;
//        }
//    }
//
//    add_Tree(&(*root)->left, new_data, left_new_data, right_new_data);
//    add_Tree(&(*root)->right, new_data, left_new_data, right_new_data);
//
//}
//void Search_Tree (TREENODE **root, char *infor) {
//
//    char new_info[100] = { 0 };
//
//    if (root == NULL) {
//        return;
//    }
//    else {
//        printf(" %d", (*root)->data);
//        strcpy(new_info, (infor + 1)); // 문자열로 입력 받았어도 코드 상에서는 첫 번째 원소만 사용하기 때문에 다음 단계에서 실행할 정보를 첫 번째                               원소로 앞당기기 위해 사용함.
//
//        if (infor[0] == 'L') {
//            Search_Tree(&(*root)->left, new_info);
//        }
//        if (infor[0] == 'R') {
//            Search_Tree(&(*root)->right, new_info);
//        }
//    }
//
//}

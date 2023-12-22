//
//  main.c
//  Algorithms_lesson_7_Training
//
//  Created by 김도윤 on 2022/10/13.
//

//#include <stdio.h> // 문제 1 ********* 다시 풀어보기 *********
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct node {
//    int key;
//    struct node *parent;
//    struct node *lChild;
//    struct node *rChild;
//}NODE;
//
//void getNode (NODE **tree);
//int findElement (NODE *tree, int k);
//void insertItem (NODE *tree, int k);
//NODE *treeSearch (NODE *tree, int k);
//int removeElement (NODE **tree, int k);
//int isExternal (NODE *w);
//int isInternal (NODE *w);
//void expandExternal (NODE *w);
//NODE *reduceExternal (NODE **tree, NODE *z);
//NODE *inOrderSucc (NODE *p);
//NODE *sibling (NODE *tree, NODE *w);
//void printNode (NODE *tree);
//
//int main () {
//
//    NODE *tree = NULL;
//    getNode(&tree);
//
//    char cmd = '0';
//    int key = 0;
//    int check = 0;
//
//    while (cmd != 'q') {
//        scanf("%c", &cmd);
//
//        switch (cmd) {
//            case 'i':
//                scanf("%d", &key);
//                getchar();
//                insertItem(tree, key);
//                break;
//            case 'd':
//                scanf("%d", &key);
//                getchar();
//                check = removeElement(&tree, key);
//                if (check == -1) {
//                    printf("X\n");
//                }
//                else {
//                    printf("%d\n", check);
//                }
//                break;
//            case 's':
//                scanf("%d", &key);
//                getchar();
//                check = findElement(tree, key);
//                if (check == -1) {
//                    printf("X\n");
//                }
//                else {
//                    printf("%d\n", check);
//                }
//                break;
//            case 'p':
//                printNode(tree);
//                printf("\n");
//                getchar();
//                break;
//            case 'q':
//                break;
//            default:
//                break;
//        }
//    }
//
//    return 0;
//}
//
//void getNode (NODE **tree) { // ok
//
//    (*tree) = (NODE *) malloc(sizeof(NODE));
//    (*tree)->key = 0;
//    (*tree)->parent = NULL;
//    (*tree)->lChild = NULL;
//    (*tree)->rChild = NULL;
//
//    return;
//}
//int findElement (NODE *tree, int k) { // ok
//
//    NODE *w = NULL;
//
//    w = treeSearch(tree, k);
//
//    if (isExternal(w) == 0) {
//        return -1;
//    }
//    else {
//        return w->key;
//    }
//
//}
//void insertItem (NODE *tree, int k) { // ok
//
//    NODE *loc = NULL;
//
//    loc = treeSearch(tree, k);
//
//    if (isInternal(loc) == 0) {
//        return;
//    }
//    else {
//        loc->key = k;
//        expandExternal(loc);
//    }
//
//    return;
//}
//NODE *treeSearch (NODE *tree, int k) { // ok
//
//    if (isExternal(tree) == 0) {
//        return tree;
//    }
//    if (tree->key == k) {
//        return tree;
//    }
//    else if (tree->key > k) {
//        return treeSearch(tree->lChild, k);
//    }
//    else {
//        return treeSearch(tree->rChild, k);
//    }
//
//}
//int removeElement (NODE **tree, int k) { // ok
//
//    NODE *loc = NULL;
//
//    loc = treeSearch(*tree, k);
//
//    if (isExternal(loc) == 0) {
//        return -1;
//    }
//
//    int e = 0;
//    NODE *z = NULL;
//    NODE *y = NULL;
//
//    e = loc->key;
//    z = loc->lChild;
//
//    if (isExternal(z) == 1) {
//        z = loc->rChild;
//    }
//    if (isExternal(z) == 0) {
//        reduceExternal(tree, z);
//    }
//    else {
//        y = inOrderSucc(loc);
//        z = y->lChild;
//        loc->key = y->key;
//        reduceExternal(tree, z);
//    }
//
//    return e;
//}
//int isExternal (NODE *w) { // ok
//
//    if (w->lChild == NULL && w->rChild == NULL) {
//        return 0;
//    } else {
//        return 1;
//    }
//
//}
//int isInternal (NODE *w) { // ok
//
//    if (w->lChild != NULL || w->rChild != NULL) {
//        return 0;
//    } else {
//        return 1;
//    }
//
//}
//void expandExternal (NODE *w) { // ok
//
//    NODE *left = NULL;
//    NODE *right = NULL;
//
//    getNode(&left);
//    getNode(&right);
//
//    w->lChild = left;
//    w->rChild = right;
//
//    left->parent = w;
//    right->parent = w;
//
//    return;
//}
//NODE *reduceExternal (NODE **tree, NODE *z) { // ok
//
//    NODE *w, *zs, *g = NULL;
//
//    w = z->parent;
//    zs = sibling(*tree, z);
//
//    if (w == *tree) {
//        zs->parent = NULL;
//        *tree = zs;
//    }
//    else {
//        g = w->parent;
//        zs->parent = g;
//
//        if (w == g->lChild) {
//            g->lChild = zs;
//        }
//        else if (w == g->rChild) {
//            g->rChild = zs;
//        }
//    }
//
//    free(z);
//    free(w);
//
//    return zs;
//}
//NODE *inOrderSucc (NODE *p) { // ok
//
//    NODE *w = NULL;
//
//    w = p->rChild;
//
//    if (isExternal(w) == 0) {
//        return w;
//    }
//
//    while (isInternal(w->lChild) == 0) {
//        w = w->lChild;
//    }
//
//    return w;
//}
//NODE *sibling (NODE *tree, NODE *w) { // ok
//
//    if (tree == w) {
//        return tree;
//    }
//    if (w->parent->lChild == w) {
//        return w->parent->rChild;
//    }
//    else {
//        return w->parent->lChild;
//    }
//
//}
//void printNode (NODE *tree) { // ok
//
//    if (isExternal(tree) == 0) {
//        return;
//    }
//
//    printf(" %d", tree->key);
//
//    printNode(tree->lChild);
//    printNode(tree->rChild);
//
//}


//#include <stdio.h> // 문제 2
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct node {
//    int key;
//    int height;
//    struct node *parent;
//    struct node *lChild;
//    struct node *rChild;
//}NODE;
//
//void getNode (NODE **tree);
//int findElement (NODE *tree, int k);
//void insertItem (NODE *tree, int k);
//NODE *treeSearch (NODE *tree, int k);
//void searchAndFixAfterInsertion (NODE *w);
//int isRoot (NODE *w);
//int updateHeight (NODE *w);
//int isBalanced (NODE *w);
//NODE *restructure (NODE *x, NODE *y, NODE *z);
//int isExternal (NODE *w);
//int isInternal (NODE *w);
//void expandExternal (NODE *w);
//NODE *reduceExternal (NODE **tree, NODE *z);
//NODE *inOrderSucc (NODE *p);
//NODE *sibling (NODE *tree, NODE *w);
//void printNode (NODE *tree);
//
//NODE *root = NULL;
//
//int main () {
//
//    getNode(&root);
//
//    char cmd = '0';
//    int key = 0;
//    int check = 0;
//
//    while (cmd != 'q') {
//        scanf("%c", &cmd);
//
//        switch (cmd) {
//            case 'i':
//                scanf("%d", &key);
//                getchar();
//                insertItem(root, key);
//                break;
//            case 's':
//                scanf("%d", &key);
//                getchar();
//                check = findElement(root, key);
//                if (check == -1) {
//                    printf("X\n");
//                }
//                else {
//                    printf("%d\n", check);
//                }
//                break;
//            case 'p':
//                printNode(root);
//                printf("\n");
//                getchar();
//                break;
//            case 'q':
//                break;
//            default:
//                break;
//        }
//    }
//
//    return 0;
//}
//
//void getNode (NODE **tree) { // ok
//
//    (*tree) = (NODE *) malloc(sizeof(NODE));
//    (*tree)->key = 0;
//    (*tree)->parent = NULL;
//    (*tree)->lChild = NULL;
//    (*tree)->rChild = NULL;
//
//    return;
//}
//int findElement (NODE *tree, int k) { // ok
//
//    NODE *w = NULL;
//
//    w = treeSearch(tree, k);
//
//    if (isExternal(w)) {
//        return -1;
//    }
//    else {
//        return w->key;
//    }
//
//}
//void insertItem (NODE *tree, int k) {
//
//    NODE *loc = NULL;
//
//    loc = treeSearch(tree, k);
//
//    if (isInternal(loc)) {
//        return;
//    }
//    else {
//        loc->key = k;
//        expandExternal(loc);
//        searchAndFixAfterInsertion(loc);
//    }
//
//    return;
//}
//NODE *treeSearch (NODE *tree, int k) { // ok
//
//    if (isExternal(tree)) {
//        return tree;
//    }
//    if (tree->key == k) {
//        return tree;
//    }
//    else if (tree->key > k) {
//        return treeSearch(tree->lChild, k);
//    }
//    else {
//        return treeSearch(tree->rChild, k);
//    }
//
//}
//void searchAndFixAfterInsertion (NODE *w) {
//
//    w->lChild->height = 0;
//    w->rChild->height = 0;
//    w->height = 1;
//
//    if (isRoot(w)) {
//        return;
//    }
//
//    NODE *x = NULL;
//    NODE *y = NULL;
//    NODE *z = w->parent;
//
//    while (updateHeight(z) && isBalanced(z)) { // updateHeight(z)가 필요한 이유: 가장 끝 노드에 새로운 노드가 입력되었기 때문에 부모 노드의 높이를 업데이트를 해주어야됨
//        if (isRoot(z)) {
//            return;
//        }
//
//        z = z->parent;
//    }
//
//    if (isBalanced(z)) {
//        return;
//    }
//
//    if (z->lChild->height > z->rChild->height) {
//        y = z->lChild;
//    }
//    else {
//        y = z->rChild;
//    }
//
//    if (y->lChild->height > y->rChild->height) {
//        x = y->lChild;
//    }
//    else {
//        x = y->rChild;
//    }
//
//    restructure(x, y, z);
//
//    return;
//}
//int isRoot (NODE *w) {
//
//    if (w->parent == NULL) {
//        return 1;
//    }
//    else {
//        return 0;
//    }
//}
//int updateHeight (NODE *w) { // 루트노드의 높이 = 왼쪽 자식노드와 오른쪽 자식노드 중 높이가 큰 노드의 크기 + 1이다. 근데 이게 맞지 않는 것을 보정해주는 함수가 updateHeight함수이다.
//
//    int h = 0;
//
//    h = w->lChild->height > w->rChild->height ? w->lChild->height + 1 : w->rChild->height + 1;
//
//    if (h != w->height) {
//        w->height = h;
//        return 1;
//    }
//    else {
//        return 0;
//    }
//
//}
//int isBalanced (NODE *w) {
//
//    if (abs(w->lChild->height - w->rChild->height) < 2) {
//        return 1;
//    }
//    else {
//        return 0;
//    }
//
//}
//NODE *restructure (NODE *x, NODE *y, NODE *z) {
//
//    NODE *a, *b, *c = NULL;
//    NODE *T0, *T1, *T2, *T3 = NULL;
//
//    if ((z->key < y->key) && (y->key < x->key)) { // z < y < x
//        a = z;
//        b = y;
//        c = x;
//        T0 = a->lChild;
//        T1 = b->lChild;
//        T2 = c->lChild;
//        T3 = c->rChild;
//    }
//    else if ((x->key < y->key) && (y->key < z->key)) { // x < y < z
//        a = x;
//        b = y;
//        c = z;
//        T0 = a->lChild;
//        T1 = a->rChild;
//        T2 = b->rChild;
//        T3 = c->rChild;
//    }
//    else if ((z->key < x->key) && (x->key < y->key)) { // z < x < y
//        a = z;
//        b = x;
//        c = y;
//        T0 = a->lChild;
//        T1 = b->lChild;
//        T2 = b->rChild;
//        T3 = c->rChild;
//    }
//    else { // y < x < z
//        a = y;
//        b = x;
//        c = z;
//        T0 = a->lChild;
//        T1 = b->lChild;
//        T2 = b->rChild;
//        T3 = c->rChild;
//    }
//
//    if (isRoot(z)) {
//        root = b;
//        b->parent = NULL;
//    }
//    else if (z->parent->lChild == z) {
//        z->parent->lChild = b;
//        b->parent = z->parent;
//    }
//    else {
//        z->parent->rChild = b;
//        b->parent = z->parent;
//    }
//
//    a->lChild = T0;
//    a->rChild = T1;
//    T0->parent = a;
//    T1->parent = a;
//    updateHeight(a);
//
//    c->lChild = T2;
//    c->rChild = T3;
//    T2->parent = c;
//    T3->parent = c;
//    updateHeight(c);
//
//    b->lChild = a;
//    b->rChild = c;
//    a->parent = b;
//    c->parent = b;
//    updateHeight(b);
//
//    return b;
//}
//int isExternal (NODE *w) { // ok
//
//    if (w->lChild == NULL && w->rChild == NULL) {
//        return 1;
//    } else {
//        return 0;
//    }
//
//}
//int isInternal (NODE *w) { // ok
//
//    if (w->lChild != NULL || w->rChild != NULL) {
//        return 1;
//    } else {
//        return 0;
//    }
//
//}
//void expandExternal (NODE *w) { // w->height = 1; 추가 완료
//
//    NODE *left = NULL;
//    NODE *right = NULL;
//
//    getNode(&left);
//    getNode(&right);
//
//    w->lChild = left;
//    w->rChild = right;
//    w->height = 1;
//
//    left->parent = w;
//    left->height = 0;
//    right->parent = w;
//    right->height = 0;
//
//    return;
//}
//NODE *reduceExternal (NODE **tree, NODE *z) {
//
//    NODE *w, *zs, *g = NULL;
//
//    w = z->parent;
//    zs = sibling(*tree, z);
//
//    if (w == *tree) {
//        zs->parent = NULL;
//        *tree = zs;
//    }
//    else {
//        g = w->parent;
//        zs->parent = g;
//
//        if (w == g->lChild) {
//            g->lChild = zs;
//        }
//        else if (w == g->rChild) {
//            g->rChild = zs;
//        }
//    }
//
//    free(z);
//    free(w);
//
//    return zs;
//}
//NODE *inOrderSucc (NODE *p) {
//
//    NODE *w = NULL;
//
//    w = p->rChild;
//
//    if (isExternal(w)) {
//        return w;
//    }
//
//    while (isInternal(w->lChild)) {
//        w = w->lChild;
//    }
//
//    return w;
//}
//NODE *sibling (NODE *tree, NODE *w) {
//
//    if (tree == w) {
//        return tree;
//    }
//    if (w->parent->lChild == w) {
//        return w->parent->rChild;
//    }
//    else {
//        return w->parent->lChild;
//    }
//
//}
//void printNode (NODE *tree) { // ok
//
//    if (isExternal(tree)) {
//        return;
//    }
//
//    printf(" %d", tree->key);
//
//    printNode(tree->lChild);
//    printNode(tree->rChild);
//
//}


#include <stdio.h> // 문제 3 (문제 2에 다가 삭제 모드 추가한 거임)
#include <string.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int height;
    struct node *parent;
    struct node *lChild;
    struct node *rChild;
}NODE;

void getNode (NODE **tree); // 노드 새로 생성
int findElement (NODE *tree, int k); // k를 key값으로 가지고 있는 노드가 있는 key값 반환, 없으면 -1 반환
void insertItem (NODE *tree, int k); // k를 key값으로 가지고 있는 노드 추가
NODE *treeSearch (NODE *tree, int k); // k를 key값으로 가지고 있는 노드를 찾아가기 위한 재귀함수
void searchAndFixAfterInsertion (NODE *w); // AVL트리에서 새로운 노드를 추가하고 좌우부트리의 높이를 균형을 맞추는 함수
int isRoot (NODE *w); // w노드가 루트 노드인지 확인하는 함수
int updateHeight (NODE *w); // w노드의 높이 값을 업데이트하는 함수 (필요한 이유: 가장 끝 노드에 새로운 노드가 입력되었기 때문에 부모 노드의 높이를 업데이트를 해주어야됨)
int isBalanced (NODE *w); // 좌우 부트리의 높이가 균형이 맞는지 확인하는 함수
NODE *restructure (NODE *x, NODE *y, NODE *z); // 좌우부트리의 높이 균형을 맞추는 함수
int removeElement (NODE **tree, int k); //k를 key값으로 가지고 있는 노드를 삭제하는 함수
void searchAndFixAfterRemoval (NODE *z); // k를 key값으로 가지고 있는 노드를 삭제한 후 좌우부트리의 높이 균형을 맞추는 함수
int isExternal (NODE *w); // w노드가 외부노드인지 확인하는 함수
int isInternal (NODE *w); // w노드가 내부노드인지 확인하는 함수
void expandExternal (NODE *w); // w노드의 외부노드(즉, 새로운 자식노드)를 추가하는 함수
NODE *reduceExternal (NODE **tree, NODE *z); // key값을 가지고 있는 노드를 삭제하는 함수 내에서 필요한 함수 -> z노드를 삭제하고 그 빈자리를 채우고 그 빈자리를 채운 노드의 주소를 반환하는 함수
NODE *inOrderSucc (NODE *p); // key값을 가지고 있는 노드를 삭제하는 함수 내에서 필요한 함수 -> z노드의 좌우부트리(자식노드)가 내부노드인 경우 z노드를 삭제했을 때 그 빈자리르 채울 노드를 찾아서 그 주소 값을 반환하는 함수(z노드의 오른쪽 자식노드에서 가장 작은 자식노드를 찾는 함수이다.)
NODE *sibling (NODE *tree, NODE *w); // w노드가 부모의 왼쪽자식노드인지, 오른쪽 자식노드인지 알려주는 함수
void printNode (NODE *tree);
/* 나머지 함수와 변수에 대한 선언은 책과 강의노트를 기반으로 작성하여 이를 참고하면 됨 */

NODE *root = NULL;

int main () {

    getNode(&root);

    char cmd = '0';
    int key = 0;
    int check = 0;

    while (cmd != 'q') {
        scanf("%c", &cmd);

        switch (cmd) {
            case 'i':
                scanf("%d", &key);
                getchar();
                insertItem(root, key);
                break;
            case 'd':
                scanf("%d", &key);
                getchar();
                check = removeElement(&root, key);
                if (check == -1) {
                    printf("X\n");
                }
                else {
                    printf("%d\n", check);
                }
                break;
            case 's':
                scanf("%d", &key);
                getchar();
                check = findElement(root, key);
                if (check == -1) {
                    printf("X\n");
                }
                else {
                    printf("%d\n", check);
                }
                break;
            case 'p':
                printNode(root);
                printf("\n");
                getchar();
                break;
            case 'q':
                break;
            default:
                break;
        }
    }

    return 0;
}

void getNode (NODE **tree) { // ok

    (*tree) = (NODE *) malloc(sizeof(NODE));
    (*tree)->key = 0;
    (*tree)->parent = NULL;
    (*tree)->lChild = NULL;
    (*tree)->rChild = NULL;

    return;
}
int findElement (NODE *tree, int k) { // ok

    NODE *w = NULL;

    w = treeSearch(tree, k);

    if (isExternal(w)) {
        return -1;
    }
    else {
        return w->key;
    }

}
void insertItem (NODE *tree, int k) {

    NODE *loc = NULL;

    loc = treeSearch(tree, k);

    if (isInternal(loc)) {
        return;
    }
    else {
        loc->key = k;
        expandExternal(loc);
        searchAndFixAfterInsertion(loc);
    }

    return;
}
NODE *treeSearch (NODE *tree, int k) { // ok

    if (isExternal(tree)) {
        return tree;
    }
    if (tree->key == k) {
        return tree;
    }
    else if (tree->key > k) {
        return treeSearch(tree->lChild, k);
    }
    else {
        return treeSearch(tree->rChild, k);
    }

}
void searchAndFixAfterInsertion (NODE *w) {

    w->lChild->height = 0;
    w->rChild->height = 0;
    w->height = 1;

    if (isRoot(w)) {
        return;
    }

    NODE *x = NULL;
    NODE *y = NULL;
    NODE *z = w->parent;

    while (updateHeight(z) && isBalanced(z)) { // updateHeight(z)가 필요한 이유: 가장 끝 노드에 새로운 노드가 입력되었기 때문에 부모 노드의 높이를 업데이트를 해주어야됨
        if (isRoot(z)) {
            return;
        }

        z = z->parent;
    }

    if (isBalanced(z)) {
        return;
    }

    if (z->lChild->height > z->rChild->height) {
        y = z->lChild;
    }
    else {
        y = z->rChild;
    }

    if (y->lChild->height > y->rChild->height) {
        x = y->lChild;
    }
    else {
        x = y->rChild;
    }

    restructure(x, y, z);

    return;
}
int isRoot (NODE *w) {

    if (w->parent == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}
int updateHeight (NODE *w) { // 루트노드의 높이 = 왼쪽 자식노드와 오른쪽 자식노드 중 높이가 큰 노드의 크기 + 1이다. 근데 이게 맞지 않는 것을 보정해주는 함수가 updateHeight함수이다.

    int h = 0;

    h = w->lChild->height > w->rChild->height ? w->lChild->height + 1 : w->rChild->height + 1;

    if (h != w->height) {
        w->height = h;
        return 1;
    }
    else {
        return 0;
    }

}
int isBalanced (NODE *w) {

    if (abs(w->lChild->height - w->rChild->height) < 2) {
        return 1;
    }
    else {
        return 0;
    }

}
NODE *restructure (NODE *x, NODE *y, NODE *z) {

    NODE *a, *b, *c = NULL;
    NODE *T0, *T1, *T2, *T3 = NULL;

    if ((z->key < y->key) && (y->key < x->key)) { // z < y < x
        a = z;
        b = y;
        c = x;
        T0 = a->lChild;
        T1 = b->lChild;
        T2 = c->lChild;
        T3 = c->rChild;
    }
    else if ((x->key < y->key) && (y->key < z->key)) { // x < y < z
        a = x;
        b = y;
        c = z;
        T0 = a->lChild;
        T1 = a->rChild;
        T2 = b->rChild;
        T3 = c->rChild;
    }
    else if ((z->key < x->key) && (x->key < y->key)) { // z < x < y
        a = z;
        b = x;
        c = y;
        T0 = a->lChild;
        T1 = b->lChild;
        T2 = b->rChild;
        T3 = c->rChild;
    }
    else { // y < x < z
        a = y;
        b = x;
        c = z;
        T0 = a->lChild;
        T1 = b->lChild;
        T2 = b->rChild;
        T3 = c->rChild;
    }

    if (isRoot(z)) {
        root = b;
        b->parent = NULL;
    }
    else if (z->parent->lChild == z) {
        z->parent->lChild = b;
        b->parent = z->parent;
    }
    else {
        z->parent->rChild = b;
        b->parent = z->parent;
    }

    a->lChild = T0;
    a->rChild = T1;
    T0->parent = a;
    T1->parent = a;
    updateHeight(a);

    c->lChild = T2;
    c->rChild = T3;
    T2->parent = c;
    T3->parent = c;
    updateHeight(c);

    b->lChild = a;
    b->rChild = c;
    a->parent = b;
    c->parent = b;
    updateHeight(b);

    return b;
}
int removeElement (NODE **tree, int k) {
    
    NODE *w = NULL;
    NODE *z = NULL;
    NODE *zs = NULL;
    NODE *y = NULL;
    
    w = treeSearch(*tree, k);
    
    if (isExternal(w)) {
        return -1;
    }
    
    z = w->lChild;
    
    if (!isExternal(z)) {
        z = w->rChild;
    }
    if (isExternal(z)) {
        zs = reduceExternal(tree, z);
    }
    else {
        y = inOrderSucc(w);
        z = y->lChild;
        w->key = y->key;
        zs = reduceExternal(tree, z);
    }
    
    searchAndFixAfterRemoval(zs->parent);
    
    return k;
}
void searchAndFixAfterRemoval (NODE *z) {
    
    NODE *x = NULL;
    NODE *y = NULL;
    NODE *b = NULL;
    
    while (updateHeight(z) && isBalanced(z)) {
        if (isRoot(z)) {
            return;
        }
        z = z->parent;
    }
    if (isBalanced(z)) {
        return;
    }
    
    if (z->lChild->height > z->rChild->height) {
        y = z->lChild;
    }
    else {
        y = z->rChild;
    }
    if (y->lChild->height > y->rChild->height) {
        x = y->lChild;
    }
    else if (y->lChild->height < y->rChild->height) {
        x = y->rChild;
    }
    else {
        if (z->lChild == y) {
            x = y->lChild;
        }
        else {
            x = y->rChild;
        }
    }
    
    b = restructure(x, y, z);
    
    if (isRoot(b)) {
        return;
    }
    
    searchAndFixAfterRemoval(b->parent);
    
}
int isExternal (NODE *w) { // ok

    if (w->lChild == NULL && w->rChild == NULL) {
        return 1;
    } else {
        return 0;
    }

}
int isInternal (NODE *w) { // ok

    if (w->lChild != NULL || w->rChild != NULL) {
        return 1;
    } else {
        return 0;
    }

}
void expandExternal (NODE *w) { // w->height = 1; 추가 완료

    NODE *left = NULL;
    NODE *right = NULL;

    getNode(&left);
    getNode(&right);

    w->lChild = left;
    w->rChild = right;
    w->height = 1;

    left->parent = w;
    left->height = 0;
    right->parent = w;
    right->height = 0;

    return;
}
NODE *reduceExternal (NODE **tree, NODE *z) {

    NODE *w, *zs, *g = NULL;

    w = z->parent;
    zs = sibling(*tree, z);

    if (w == *tree) {
        zs->parent = NULL;
        *tree = zs;
    }
    else {
        g = w->parent;
        zs->parent = g;

        if (w == g->lChild) {
            g->lChild = zs;
        }
        else if (w == g->rChild) {
            g->rChild = zs;
        }
    }

    free(z);
    free(w);

    return zs;
}
NODE *inOrderSucc (NODE *p) {

    NODE *w = NULL;

    w = p->rChild;

    if (isExternal(w)) {
        return w;
    }

    while (isInternal(w->lChild)) {
        w = w->lChild;
    }

    return w;
}
NODE *sibling (NODE *tree, NODE *w) {

    if (tree == w) {
        return tree;
    }
    if (w->parent->lChild == w) {
        return w->parent->rChild;
    }
    else {
        return w->parent->lChild;
    }

}
void printNode (NODE *tree) { // ok

    if (isExternal(tree)) {
        return;
    }

    printf(" %d", tree->key);

    printNode(tree->lChild);
    printNode(tree->rChild);

}

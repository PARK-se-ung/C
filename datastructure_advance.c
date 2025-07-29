#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/*
    5. Tree/Heap
     1) tree? 계층 구조를 가지는 비선형 자료구조
       ! 용어
        - 노드(node) : 트리의 구성요소(포인터 + 데이터)
        - 간선(edge) : 노드를 연결하는 선
        - 리프(leaf) : 자식이 없는 노드
        - 루트(root) : 트리의 가장 위 노드
        - 깊이(depth) : 루트에서 특정 노드까지의 거리
        - 높이(height) : max(depth)
        - 서브트리(subtree) : 특정 노드를 루트로 하는 트리
       ! 특징
        - 하나의 루트 노드
        - 사이클 없음
        - 노드 간 부모-자식 관계로 연결
       ! 종류
        - 일반 트리 : 자식 수 제한 X
        - 이진 트리 : 각 노드가 최대 2개의 자식 노드 보유
        - 이진 탐색 트리 : 데이터 기준 - left < parent < right인 이진 트리
        - 균형 트리 : 높이 자동 조정 트리
        - 힙(heap) : 최소/최대 값이 루트에 오는 트리
        - 트라이(trie) : 문자열 저장 최적화
        - 세그먼트 트리(segment tree) : 구간 정보 저장 & 쿼리용 트리
*/


// binary tree node
typedef struct {
    int value;
    Node *left;
    Node *right;
} Node;

// binary search tree
typedef struct {
    Node *root;
    size_t size;
} BinarySearchTree;

Node* create_node(int value) {
    Node *node = malloc(sizeof(Node));
    if(node == NULL) return NULL;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BinarySearchTree* init_bst() {
    BinarySearchTree *bst = malloc(sizeof(BinarySearchTree));
    if(bst == NULL) return NULL;
    bst->root = NULL;
    bst->size = 0;
    return bst;
}
bool insert(BinarySearchTree *bst, int value) {
    if(bst == NULL || value == NULL) return false;
    Node *node = create_node(value);
    if(node == NULL) return false;

    if(bst->root == NULL) {
        bst->root = node;
    } else {

    }
    bst->size++;
    return true;
}

Node* search(BinarySearchTree *tree, int value) {

}

bool delete(BinarySearchTree *tree, int value) {

}

void preorder(Node *node) {

}

void inorder(Node *node) {

}

void postorder(Node *node) {

}

void free_tree(Node *node) {

}


/*
    6. Graph(adjust list/matrix)
*/


int main() {

}
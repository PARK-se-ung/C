#include <stdio.h>
#include <stdlib.h>

/*
    Data Structure
*/
/*
    1. Array
    - 같은 자료형의 데이터를 연속된 메모리 공간에 저장하는 자료구조 << 정적 할당
    ! 시간복잡도
        1). 인덱스 접근 O(1)
        2). 삽입/삭제 O(n)
        3). 전체 순회 O(n)
    ! 특징
        1). 인덱스 접근 빠름/연속된 메모리로 캐시 친화
        2). 크기 고정/삽입&삭제 비효율적
    1-A. Dynamic Array
    - 재할당을 통해 연속적이지만 유동적인 메모리 공간을 가지는 자료구조 << 동적 할당
    ! 시간복잡도
        1). 인덱스 접근 O(1)
        2). 삽입/삭제(tail) mortized O(1) & 삽입/삭제(middle) O(n) << shift 발생
        3). 전체 순회 O(n)
    ! 특징
        1). resize()가 발생할 경우 시간복잡도 O(n) 가능
        2). void* 방식 선언시 모든 타입 저장 가능
*/

// Dynamic Array
typedef struct DynamicArray
{
    void **arr; // type 미지정 
    size_t size; // 현재 요소 개수
    size_t cap; // 현재 요소 개수 상한
} DynamicArray;

// initialize function
DynamicArray* dynamicArray() {
    DynamicArray *da = malloc(sizeof(DynamicArray));
    da->size = 0;
    da->cap = 4;
    da->arr = malloc(sizeof(void*) * da->cap);
    return da;
}

// resize function
int resize(DynamicArray *da, size_t new_cap) {
    void **new_arr = realloc(da->arr, sizeof(void*) * new_cap);
    if(!new_arr) return -1;
    da->arr = new_arr;
    da->cap = new_cap;
    return 0;
}

// append function(python 12.5x% 증가 방식)
int append(DynamicArray *da, void* elem){
    if(da->size == da->cap) {
        if(da_resize(da, da->cap + (da->cap) >> 3 + (da->cap < 9? 3 : 6)) < 0) return -1;
    }
    da->arr[da->size++] = elem;
    return 0;
}

// free function
void da_free(DynamicArray *da) {
    free(da->arr);
    free(da);
}


/*
    2. Linked List(struct Node 기반)
      1). Single Linked List
        - Node: value와 next Node pointer를 가진 구조체 
        - LinkedList: Node 정보를 가진 구조체
         ! head only vs head + tail
          i) 시간복잡도: 끝부분 삽입/삭제 O(n) vs O(1)
          ii) 공간복잡도: 상대적으로 작음 vs pointer 1개 많음
          iii) 코드복잡도: 낮음 vs 높음
          iv) Queue 구현: 불리 vs 유리
         ! size까지 포함하는 경우 다수
      2). Doubly Linked List
      3). Circular Linked List
*/

// Next Only Node
typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Linked List
typedef struct {
    Node *head;
    Node *tail;
    size_t size;
} LinkedList;

LinkedList* linkedList() {
    LinkedList *linkedList = malloc(sizeof(LinkedList));
    linkedList->head = NULL;
    linkedList->tail = NULL;
    linkedList->size = 0;
    return linkedList;
}

Node* node(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

int append(LinkedList *linkedList, Node *node) {
    
}

/*
    3. Stack & Queue
*/

/*
    4. Hash(Set/Dictionary)
*/

/*
    5. Tree/Heap
*/

/*
    6. Graph
*/


int main() {
    
}
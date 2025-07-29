#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
     ! Dynamic Array와 다르게 Node기반 << free() 필요성 증가
      1). Single Linked List
        - Node: value와 next Node pointer를 가진 구조체 
        - LinkedList: Node 연결/관리 구조체
         ! head only vs head + tail
          i) 시간복잡도: 끝부분 삽입/삭제 O(n) vs O(1)
          ii) 공간복잡도: 상대적으로 작음 vs pointer 1개 많음
          iii) 코드복잡도: 낮음 vs 높음
          iv) Queue 구현: 불리 vs 유리
         ! size까지 포함하는 경우 다수
      2). Doubly Linked List
        - Node가 value와 next말고도 prev Node pointer를 가진 구조체인 경우
        ! 많은 부분에서 Single Linked List와 유사
          - 차이점?
           i) tail 삽입/삭제 최적화 가능
           ii) 양방향 탐색 (head -> tail/tail -> head) 가능
           iii) prev 포인터 관리 필요
      3). Circular Linked List
        - Single 방식과 Doubly 방식 존재(차이는 1), 2)와 유사)
          - 1), 2)와의 차이점?
           i) tail의 next가 head (doubly이면 head의 prev가 tail)
           ii) 순환 순회/Deque 구현 적합
      4). queue/stack/deque와의 연관성
        - queue: single linked list(head only) 구현 가능
        - stack: single linked list(head + tail) 구현 유리
        - deque: doubly linked list(head + tail) 구현 적합
          ! deque << circular linked list(head + tail) 구현 가능
*/

// Node
typedef struct Node {
    int value;
    struct Node *prev;
    struct Node *next;
} Node;

// Circular Linked List (CLL)
typedef struct {
    Node *head;
    Node *tail;
    size_t size;
} CircularLinkedList;

CircularLinkedList* init() {
    CircularLinkedList *cll = malloc(sizeof(CircularLinkedList));
    cll->head = NULL;
    cll->tail = NULL;
    cll->size = 0;
    return cll;
}

Node* create_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void appendleft(CircularLinkedList *cll, int value) {
    if(cll == NULL) return;
    Node *node = create_node(value);
    if(node == NULL) return;
    if(cll->head == NULL) {
        node->prev = node;
        node->next = node;
        cll->head = node;
        cll->tail = node;
    } else {
        node->prev = cll->tail;
        node->next = cll->head;
        cll->head->prev = node;
        cll->tail->next = node;
        cll->head = node;
    }
    cll->size++;
}

int popleft(CircularLinkedList *cll, bool *err) {
    if(cll == NULL || cll->size == 0){
        if(err) *err = false;
        return 0;
    }
    Node* temp = cll->head;
    int value = temp->value;
    if(cll->size == 1){
        cll->head = NULL;
        cll->tail = NULL;
    } else {
        cll->head = temp->next;
        cll->head->prev = cll->tail;
        cll->tail->next = temp->next;
    }
    free(temp);
    cll->size--;
    if(err) *err = true;
    return value;
}

void append(CircularLinkedList *cll, int value) {
    if(cll == NULL) return;
    Node *node = create_node(value);
    if(node == NULL) return;
    if(cll->head == NULL) {
        node->prev = node;
        node->next = node;
        cll->head = node;
        cll->tail = node;
    } else {
        node->prev = cll->tail;
        node->next = cll->head;
        cll->head->prev = node;
        cll->tail->next = node;
        cll->tail = node;
    }
    cll->size++;
}

int pop(CircularLinkedList *cll, bool *err) {
    if(cll == NULL || cll->size == 0){
        if(err) *err = false;
        return 0;
    }
    Node *temp = cll->tail;
    int value = temp->value;
    if(cll->size == 1){
        cll->head = NULL;
        cll->tail = NULL;
    } else {
        cll->head->prev = temp->prev;
        cll->tail = temp->prev;
        cll->tail->next = cll->head;
    }
    free(temp);
    cll->size--;
    if(err) *err = true;
    return value;
}

/*
    3. Queue & Stack & Deque
      - Queue?
       ! 선입선출(FIFO): 먼저 들어온 요소(First In)가 먼저 나가는(First Out) 형태
        ! 기반 자료구조 << LinkedList, CircularBuffer,...etc (Array / Dynamic Array는 비교적 큰 비용 발생)
          - LinkedList 기반: head에서 pop / tail에서 append
          - Circular Buffer 기반: array기반에 front/end를 modular 연산으로 처리
          - two stack 기반: 두개의 stack(in_stack, out_stack)을 사용 << out_stack이 empty일때 in_stack의 요소를 out_stack으로 이동
      - Stack?
       ! 후입선출(LIFO): 나중에 들어온 요소(Last In)가 먼저 나가는(First Out) 형태
        ! 기반 자료구조: Array / Dynamic Array / Linked List
          - Array 기반: 고정 크기 배열 + 최상단 index 기반 stack << 코드복잡도 낮음 / 배열 크기 고정
          - Dynamic Array 기반: Array 기반 + 동적 할당 << 배열 크기 동적 할당 가능
          - Linked List 기반 << 삽입/삭제 다수 존재시 유리
      - Deque?
       ! Double Ended Queue : queue + stack 모두 사용 가능 (양쪽 삽입/삭제 가능)
        ! 기반 자료구조: Linked List / CLL
*/

// Circular Buffer based Queue : 비교적 작은 공간과 크기 예측이 가능한 경우에 유리
typedef struct {
    int* arr;
    int front;
    int end;
    int capacity;
    int size;
} CircularBuffer;

CircularBuffer *init_circular_buffer(int capacity) {
    CircularBuffer *circular_buffer = malloc(sizeof(CircularBuffer));
    circular_buffer->arr = malloc(sizeof(int) * capacity);
    circular_buffer->capacity = capacity;
    circular_buffer->front = 0;
    circular_buffer->end = 0;
    circular_buffer->size = 0;
    return circular_buffer;
}

int dequeue(CircularBuffer *circularBuffer, bool *err) {
    if(circularBuffer == NULL || circularBuffer->size == 0) {
        if(err) *err = false;
        return 0;
    }
    int value = circularBuffer->arr[circularBuffer->front];
    circularBuffer->front = (circularBuffer->front + 1) % circularBuffer->capacity;
    circularBuffer->size--;
    if(err) *err = true;
    return value;
}

void enqueue(CircularBuffer *circularBuffer, int value) {
    if(circularBuffer == NULL || circularBuffer->size == circularBuffer->capacity) return;
    circularBuffer->arr[circularBuffer->end] = value;
    circularBuffer->end = (circularBuffer->end + 1) % circularBuffer->capacity;
    circularBuffer->size++;
}

void free_circular_buffer(CircularBuffer *circularBuffer) {
    if(circularBuffer){
        free(circularBuffer->arr);
        free(circularBuffer);
    }
}

// Dynamic Array 기반 Stack
typedef struct {
    int *arr;
    size_t cap;
    size_t size;
} Stack;

Stack *init(size_t cap){
    Stack *stack = malloc(sizeof(Stack));
    if(!stack) return NULL;
    stack->arr = malloc(sizeof(int) * cap);
    if (!stack->arr) {
        free(stack);
        return NULL;
    }
    stack->cap = cap;
    stack->size = 0;
    return stack;
};

void push(Stack *stack, int value) {
    if(stack->cap == stack->size) {
        int *new_arr = realloc(stack->arr, sizeof(int) * stack->cap * 2);
        if(!new_arr) return;
        stack->arr = new_arr;
        stack->cap *= 2;
    }
    stack->arr[stack->size++] = value;
}

int pop(Stack *stack, bool *err) {
    if(stack->size == 0) {
        if(err) *err=false;
        return 0;
    }
    int value = stack->arr[stack->size - 1];
    stack->size--;
    if(err) *err=true;
    return value;
}

/*
    4. Hash(Set/Dictionary)
     ! Hash Table?
      - key를 기준으로 value를 바로 찾을 수 있도록 설계된 자료구조
     ! Hash Function? 
      - Hash Table은 내부적으로 배열 기반 << index로 접근
      - key(hasable data)를 정수 index로 변환하는 함수가 Hash Function
      - key -> hash function -> index -> array -> value 
     ! Hash Collision
      - 서로 다른 키가 hash function에 의해 같은 index값을 가지는 경우 발생 << 해결필요
       1) 개별 체이닝(Seperate Chaining)
        - 동일 index에 자료구조(Linked List)를 두고 여러 요소 저장
        - 배열에 남은 공간이 없어도 저장 가능
        - 탐색시간 O(n) 가능성 존재
       2) 오픈 어드레싱(Open Addressing): 충돌시 빈공간 탐색후 저장
        - Linear Probing(선형 탐사) : index 순차 탐색
        - Quadratic Probing(이차 탐사) : i^2 단위 탐색
        - Double Hashing(더블 해싱) : 두개의 hash function 사용
         >> 구현의 용이성, 캐시 성능, 탐색 루프 + 디버깅 용이의 이유로 선형 탐사가 주로 사용됨
           ! 선형탐사 << 클러스터링 현상 발생 가능; 한 인덱스에 충돌이 몰리는 경우 여러 key들에 대해 충돌이 발생하여 탐색 성능 저하
     ! hashable vs mutable
       - hashable vs mutable : hash function 적용 가능 + key->hash가 bijective인 객체 vs 가변 객체(내부값 수정시 해시값 달라질 수 있음)
       - hashing할 key는 기본적으로 불변(immutable)할 필요 있음 << mutable한 값은 key로 사용 제한 필요(Python 등에서는 사용 불가)
     ! Set vs Dictionary
      1) 저장 구조: key만 저장 vs key:value쌍 저장
      2) 주요 기능: 중복없이 저장/추가/삭제/탐색 vs key로 value 접근 + key기반 값 설정/검색/삭제
      3) 중복 허용: key 중복 불가 vs key 중복 불가 + value 중복 가능
      ! Set/Dictionary << key를 통한 빠른 탐색(O(1)) 가능
*/

// Hashing Function(djb2)
unsigned long hash(const char* str) {
    unsigned long hash = 5381;
    int c;
    while((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
};

// Hash Table(Chaining 방식/key:value 방식)
typedef struct {
    char* key;
    int value;
    struct Entry* next;
} Entry;

typedef struct {
    Entry **entry;
    size_t capacity;
} HashTable;

HashTable *init(size_t capacity) {
    HashTable *hash_table = malloc(sizeof(HashTable));
    if(hash_table == NULL) return NULL;
    hash_table->entry = malloc(sizeof(Entry*) * capacity);
    if(hash_table->entry == NULL) {
        free(hash_table);
        return NULL;
    }
    for(size_t i = 0; i < capacity; i++) {
        hash_table->entry[i] = NULL;
    }
    hash_table->capacity = capacity;
    return hash_table;
}

void set(HashTable *ht, const char* key, int value) {
    size_t index = hash(key) % ht->capacity;
    Entry *entry = ht->entry[index];
    while(entry != NULL) {
        if(strcmp(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }

    Entry *new_entry = malloc(sizeof(Entry));
    if(new_entry == NULL) return;
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = ht->entry[index];
    ht->entry[index] = new_entry;
}

bool get(HashTable *ht, const char* key, int *value) {
    size_t index = hash(key) % ht->capacity;
    Entry *entry = ht->entry[index];
    while(entry != NULL) {
        if(strcmp(entry->key, key) == 0) {
            if(value) *value = entry->value;
            return true;
        }
        entry = entry->next;
    }
    return false;    
}

bool remove(HashTable *ht, const char* key) {
    size_t index = hash(key) % ht->capacity;
    Entry *entry = ht->entry[index];
    Entry *prev = NULL;
    while(entry != NULL) {
        if(strcmp(entry->key, key) == 0) {
            if(prev == NULL) {
                ht->entry[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry->key);
            free(entry);
            return true;
        }
        prev = entry;
        entry = entry->next;
    }
    return false;
}

void free_ht(HashTable *ht) {
    for (int i = 0; i < ht->capacity; i++) {
        Entry *entry = ht->entry[i];
        while (entry != NULL) {
            Entry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(ht->entry);
    free(ht);
}

typedef enum {
    EMPTY,
    OCCUPIED,
    DELETED
} Status;

typedef struct {
    char* key;
    Status status;
} Slot;

// Set(open addressing/key only방식)
typedef struct {
    Slot *table;
    size_t capacity;
    size_t size;
} Set;

Set* init_set(size_t capacity) {
    Set *set = malloc(sizeof(Set));
    if(set == NULL) return NULL;
    set->table = malloc(sizeof(Slot) * capacity);
    if(set->table == NULL) {
        free(set);
        return NULL;
    }
    for(size_t i = 0; i < capacity; i++){
        set->table[i].status = EMPTY;
    }
    set->capacity = capacity;
    set->size = 0;
    return set;
}

bool insert(Set* set, const char *key) {
    if(set == NULL || key == NULL) return false;
    size_t index = hash(key) % set->capacity;
    size_t start = index;
    size_t delete_index = SIZE_MAX;
    while(set->table[index].status != EMPTY) {
        if(set->table[index].status == OCCUPIED && 
            strcmp(set->table[index].key, key) == 0) return false;
        if(set->table[index].status == DELETED && delete_index == SIZE_MAX) {
            delete_index = index;
        }

        index = (index + 1) % set->capacity;
        if(start == index) break;
    }
    if(delete_index != SIZE_MAX) index = delete_index;
    set->table[index].key = malloc(sizeof(char) * strlen(key) + 1);
    if(set->table[index].key == NULL) return false;
    strcpy(set->table[index].key, key);
    set->table[index].status = OCCUPIED;
    set->size++;
    return true;
}

bool contains(Set* set, const char* key) {
    if(set == NULL || key == NULL) return false;
    size_t index = hash(key) % set -> capacity;
    size_t start = index;
    while(set->table[index].status != EMPTY) {
        if(set->table[index].status == OCCUPIED && 
            strcmp(set->table[index].key, key) == 0) {
                return true;
            }
        index = (index + 1) % set->capacity;
        if(start == index) break;
    }
    return false;

}

bool delete(Set* set, const char* key) {
    if(set == NULL) return false;
    size_t index = hash(key) % set -> capacity;
    size_t start = index;
    while(set->table[index].status != EMPTY) {
        if(set->table[index].status == OCCUPIED &&
            strcmp(set->table[index].key, key) == 0) {
            set->table[index].status = DELETED;
            free(set->table[index].key);
            set->size--;
            return true;
        }
        index = (index + 1) % set->capacity;
        if(start == index) break;
    }
    return false;
}

void free_set(Set* set){
    if(set == NULL) return;
    for(size_t i = 0; i < set->capacity; i++){
        if(set->table[i].key != NULL && set->table[i].status == OCCUPIED) {
            free(set->table[i].key);
        }
    }
    free(set->table);
    free(set);
}


int main() {
    
}
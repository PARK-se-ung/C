#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* 
    포인터(Pointer)
*/

int main() {
    /* 1. Basic Pointer
        1). 변수와 값
        - 변수 선언시 &연산으로 해당 변수의 포인터 주소를 가져올 수 있다.
          ! int x = 1;로 선언시
            변수 : x
            주소 : &x(= 0x1000)
            값 : x(= 1)

        2). 포인터 변수 선언
        - 최초부터 *를 통해 포인터 변수를 선언할 수 있다.
          ! int *p = &x;로 선언시
            변수 : p
            주소 : &p(= 0x2000)
            값 : p(= 0x1000)
            역참조 : *p(= 1)
    */    

   int x = 1;
   int *p = &x; // 포인터 변수임을 선언하기 위해 * 사용
   printf("%s\n", "====== 포인터 변수 ======");
   printf("주소값 : %p\n", p);  
   printf("실제값 : %d\n", *p); // 포인터 변수의 실제값을 가져오기 위해 * 사용
   
    /* 2. Array
        1) 배열 선언
        - 배열 선언시 메모리상 연속된 공간이 할당된다.
          ! int arr[3] = {1, 2, 3};으로 선언시
            0x1000, 0x1004, 0x1008에 각각 1, 2, 3으로 값 초기화
        - 인덱스와 포인터
          ! 인덱스 배열 접근
            변수 : arr[i] (arr의 i번째 요소)
            주소 : &arr[i] (= 0x1000, 0x1004, 0x1008,...)
            값 : arr[i] (= 1)
          ! 배열 살펴보기
            변수: arr
            주소: &arr(= &arr[0], 0x1000)
            값 : arr(= &arr[0], 0x1000)
            역참조 : *arr(= arr[0], 1)

        2) 배열과 포인터 연산
          - 주소(포인터)와 산술 연산(+, -)이 가능
          ! 배열처럼 메모리상 연속하는 공간이 존재하는 경우? 
          ! char chr[3] = {'a', 'b', 'c'}; 0x1000, 0x1001, 0x1002 가정
            - &chr[0] + 1 : &chr[1], 0x1001과 동일
            - &chr[1] - 1 : &chr[0], 0x1000과 동일
            - &chr[2] - &chr[0] : 2와 동일 << 같은 배열 내에서만 포인터 차를 계산가능

          ** arr와 &arr의 차이?
          - arr는 배열의 0번째 요소의 주소(0x1000), &arr는 배열 전체의 주소(0x1000) 
          - 실제로 값은 동일하나, 타입에서 차이 발생 << arr는 int* 타입 / &arr는 int(*)[n] 타입
          - 포인터 연산시 
                        arr + 1 = &arr[1] (char의 크기 1byte만큼 이동) 
                                            <---> 
            &arr + 1 = arr + 3 = undefined behavior (char의 크기와 배열의 크기 곱만큼 이동)

    */
    int arr[3] = {1, 2, 3};
    printf("%s\n", "====== 배열: 인덱스/포인터 ======");
    printf("arr[0] : %d\n", arr[0]); 
    printf("arr* : %d\n", *arr);     
    printf("arr : %p\n", arr);      
    printf("&arr[0] : %p\n", &arr[0]);
    printf("%s\n", "====== 배열: 포인터 연산 ======");
    printf("*(arr + 1) : %d\n", *(arr + 1));
    printf("*(&arr + 1) : %d\n", *(&arr + 1));
    
    /* 3. String
        1). 문자열 선언
           - 문자열은 배열방식 char[] vs 포인터 방식 char *로 선언이 가능하다.
            char str[] = "hello" vs char str* = "hello"
          ! 문자열은 char 배열과 많은 부분에서 동일
            - 인덱스 접근 가능 : str[0]
            - 역참조 : *str
            - 포인터 연산 : *(s + 2)
            ! 문자열은 항상 '\0' null 문자로 종료된다.
          ! 배열선언 vs 포인터 선언
            - 인덱스 접근후 수정 가능 vs 인덱스 접근후 수정 불가(읽기 전용)
            - 생성된 리터럴 문자열을 복사하여 저장(주소값 변경) vs 그대로 접근(리터럴과 동일한 주소값)
        2). 문자열 함수 (#include <string.h>)
          - strlen(char *str) : 문자열 길이 반환 << null 문자('\0') 조우시 종료 & null 문자전까지의 길이 반환; 시간복잡도 : O(n)
            ! sizeof()와의 차이점 : (배열) 배열크기 반환(null 문자 포함) / (포인터) 포인터 크기 반환(64bit 환경에서 8)
          - strcpy(char *dest, char *src) : 문자열 복사 << *dest의 배열 크기가 strlen(src) + 1이상이어야 안전(null 문자를 할당할 공간도 필요하다.)
            ! strncpy(char *dest, char *src, sizeof(dest)) : 최대 n바이트까지 안전 복사(null 문자 미포함 가능성으로 인해 권고되지 않음);
          - strcmp(char *str1, char *str2) : 두 문자열을 사전순으로 비교하여 숫자값 반환; 동일한 경우 0, str1이 사전순으로 앞선 경우 음수, 반대의 경우 양수
            ! strncmp(char *str1, char *str2, size_t n) : 앞에서 최대 n개까지 비교; 반환값은 strcmp()와 동일
            ! strcasecmp(char *str1, char *str2) : 대소문자 비교 X
          - strcat(char *dest, char *src) : dest 문자열 \0에 src를 연결;(dest 메모리 공간 확보 필요)
            ! strnchat(char *dest, char *src, n) : 최대 n개까지 연결
          - strtok(char *str, const char *delim): str을 delim 기준으로 분할, 읽기전용 문자열에서 사용불가
          - strchr(const char *str, int ch) : str 문자열의 특정 문자 포인터 반환; strrchr()의 경우 문자열 마지막부터 순회
          - strstr(const char *haystack, const char *needle) : haystack 문자열의 needle 문자열 조회후 needle 문자열부터 부분 문자열 반환
          - strspn(const char *s, const char *accept): 문자열 s에서 시작점부터 accept와 중복되는 문자 수 반환 
            ! strcspn(const char *s, const char *reject): 문자열 s에서 reject에 포함된 문자 등장 인덱스 반환

    */
    printf("%s\n", "====== 문자열 ======");
    char arrStr[] = "hello";
    char* pointerStr = "hello";
    printf("%p\n", &arrStr[0]); // 복사된 문자열 주소
    printf("%p\n", &pointerStr[0]); // 문자열 리터럴 주소

    printf("%c\n", *pointerStr); // 첫번째 문자
    printf("%p\n", *pointerStr + 1); // 아스키코드의 주소 (의미없는 값)

    printf("%c\n", *(pointerStr + 1)); // 두번째 문자
    printf("%s\n", pointerStr + 1); // 두번째 문자부터 \0까지 출력
    printf("%p\n", pointerStr + 1); // 두번째 문자 주소
    printf("====== 문자열 함수 ======\n");
    char *s = "abcde";
    printf("%d\n", strspn(s, "abd")); // 시작점부터 ab << 두개 중복
    printf("%d\n", strcspn(s, "cd")); // s[2] = 'c'
    

    /* 4. Advance Pointer
        1). 함수와 포인터
          - pass by value vs pass by reference
            ! 함수는 전달받은 매개변수 값을 복사하여 전달(pass by value) << 함수 내부에서 인자값을 변경해여도 복사본의 값만 변경
            ! 포인터 매개변수를 전달할 경우(pass by reference), 함수 내부에서 인자값 변경시 원본 값도 수정 가능
          - 배열도 포인터 방식으로 전달되기에 함수 내부에서 값 수정 가능
        2). 다차원 배열과 포인터
          ! int arr[3][4];로 선언시
           - 다차원 배열 타입 vs 포인터 타입
            ! arr + i == &arr[i] >> *(arr + i) == arr[i] >> *(arr + i) + j = &arr[i][j] >> *(*(arr + i) + j) = arr[i][j]
           - 함수의 매개변수로 배열을 받을 때, 타입을 명시해야 한다.
            ! func(int arr[4]) >> func(int (*arr)[4])
        3). 이중 포인터
          ! int a = 1; int *p = &a; int **pp = &p;로 선언시
           - p = &a, *p = a, pp = &p, *pp = p, **pp = a
           - 함수 내부에서 포인터 수정, 2차원 동적 배열 사용, 문자열 포인터 배열 사용시 이중 포인터 필요
           - 메모리 해제시 행 먼저, 이후 전체
          ! 이중 포인터 vs 이차원 배열
           - 메모리 구조 비연속(행마다 따로 malloc/캐시효율 나쁨) vs 메모리 구조 연속(하나로 할당/캐시효율 좋음)
           - 수동 메모리관리(free) 필요 vs 자동
        4). 포인터 형변환
        - 포인터에 저장된 데이터를 어떤 타입으로 해석할 지 결정할 수 있다.
          ! int num = 65;로 선언 << 아스키 코드 상으로 'A'
           - char *c = (char *) &num; << &num 메모리 주소에 할당된 값을 char 타입으로 간주하고 *c 포인터 변수에 해당 메모리 주소 대입
           - *c = 'A' << 실제로 해당 메모리 주소에 할당된 값을 char 타입의 'A'로 인식
    */

    /*
      5. Memory Structure & Dynamic Allocation
        1). 메모리 구조: 스택 vs 힙
          - 함수 호출시 지역변수/매개변수 저장 vs 프로그램 실행중(런타임중) 동적 메모리 할당
          - 함수 호출시 자동 할당/해제 vs malloc()/free()로 수동 할당/해제
        2). 동적할당 : malloc(), calloc(), realloc()
          - malloc(size): 크기 만큼 메모리 할당/초기화 X
          - calloc(n, size): n개의 요소를 size만큼 할당/모든 바이트 0으로 초기화
          - realloc(ptr, new_size): malloc()/calloc()으로 할당된 메모리를 새로운 크기로 재조정
    */
    
}
#include <stdio.h>
#include <string.h>
    /*
        구조체(Struct)
    */
int main() {
    /*
        1. basic struct
          - struct
           1) 정의 : struct 구조체명 { 멤버 선언 } or typedef struct 구조체명{멤버선언} 별칭;
           2) 선언 : struct 구조체명 변수명 [= {멤버, ...}];
           3) 접근 : 변수명.멤버명 vs 변수명 -> 멤버명
             ! . 연산 vs -> 연산 (둘 모두 멤버 접근 연산)
              - 접근대상: 구조체 변수 vs 구조체 포인터
              - 비교 : p.name vs (p*).name (= p->name)
           4) 초기화
             i) 일반 구조체 : 변수명.멤버명 = 값, 변수명 = { };
             ii) 포인터 구조체 : *변수명 = (struct 구조체명) {};
           5) 연산
             i) 복사 : struct 구조체명 변수명 = 변수명으로 복사(struct Person p2 = p2) << 포인터 멤버 포함시 얕은 복사; 동일 메모리 공유
             ii) 비교 : == 연산 지원 X << 필요시 직접 구현
             iii) 메모리 정렬 : 구조체 메모리 크기는 메모리 정렬로 인해 이격 발생 가능 << 멤버 선언 순서 영향
             iv) 구조체 함수 인자 전달 : 함수의 인자(매개변수)로 구조체 전달시 포인터 전달 권장(구조체 전달시 불필요한 복사-성능 저하 유발) << const struct *로 전달시 읽기 전용
           6) 배열 멤버 vs 포인터 멤버
            i) 직접 대입 : person.name = "name" 불가(strcpy() 필요) vs person.name = "name" 가능
            ii) 메모리 관리 : stack (자동 관리) vs heap or literal (직접 관리 필요, malloc,...)
    */
    struct Person {
        char name[20];
        int age;
        float height;
    };

    struct Person person;
    strcpy(person.name, "name");
    person.age = 26;
    person.height = 170.3;
    printf("%s, %d, %.1f", person.name, person.age, person.height);

    /*
        2. struct pointer and array
          - 구조체 포인터?
          ! 포인터 방식으로 선언된 구조체 (struct Person *p)
           1). 동적 할당 : p = malloc(sizeof(struct Person))
           2). -> 연산 : strcpy(p->name, "name"); p->age = 25;
           3). 해제 : free(p);
          ! 구조체 포인터의 멤버 접근시 -> 연산 사용

          - 구조체 배열?
          ! 객체들을 요소로 하는 배열 (struct 구조체명 배열명[사이즈])
           ex) struct People people[3]; 선언시
            인덱스접근 + .연산 접근: people[0].age = 27, ...
          - 구조체 배열과 동적할당
          ! 구조체 배열도 포인터 선언 & 동적 할당 가능
           ex) struct People *people = malloc(sizeof(struct People) * 3); 선언시
            1) 구조체 멤버값 초기화 :
               strcpy(people[0].name, "hikari"); people[0].age = 16;
               strcpy((people + 1)->name, "nozomi"); (people + 1)->age = 16;
            2) 동적 할당 해제 : free(people);
          ! 구조체에 포인터 멤버가 존재할 경우? << 각 구조체 포인터 멤버를 동적할당 > 해제시 멤버 먼저 해제
           ex) struct People *people = malloc(sizeof(struct People) * n);
             1) 구조체 포인터 멤버 동적 할당: people[0].name = malloc(sizeof(char) * 20);
             2) 구조체 멤버값 초기화
             3) 동적 할당 해제 : free(people[0].name) >> free(people)
          ! 동적 구조체 배열 vs 구조체 포인터 배열
           ex) struct Person *people = ... vs struct Person *people[3]
             1) 배열 요소 : 구조체 vs 구조체 포인터
             2) 메모리 : 연속됨 vs 연속 X
             3) 할당 : 자동할당(or 동적할당) vs 각 포인터 요소 동적 할당
             4) 멤버 접근 : .연산(구조체) vs ->연산(포인터)
             5) 요소 할당 : malloc(sizeof(struct Person) * n) vs for(int i = 0; i < n; ++i) {people[i] = malloc(sizeof(struct Person))}       
    */
}
/*
    0. 전처리기
     ! 컴파일 전에 코드 내 #으로 시작하는 명령 처리
      - 헤더 파일 : #include
      - 매크로 상수/함수 정의 : #define, #undef
        1). 상수 정의
        2). 매크로 함수(간단한 인라인 함수)
        3). 로그 출력
        4). 토큰 연결
      - 조건부 컴파일 : #ifdef, #ifndef, #if, #elif, #else, #endif, #error
        1). 플랫폼 분기
        2). 디버그용 코드
        3). 기능 활성화 토글
*/

#include <stdio.h>

// 1). 상수 정의
#define PI 3.14

// 2). 자주 사용하는 인라인 함수
#define SQUARE(x) ((x) * (x))

// 3). 로그 출력 매크로
#define LOG(msg) printf("[LOG] %s\n", msg)
// #define LOG(msg)

// 4). 토큰 연결
#define FUNC_NAME(prefix, name) prefix##name

void my_print() {
    printf("my_print 호출됨\n");
}

// 1) 조건부 컴파일로 플랫폼 분기
#if defined(_WIN32) || defined(_WIN64) // 자동으로 매크로 정의된 플랫폼설정 << 지금은 _WIN32
    #define PLATFORM "Windows"
#elif defined(__linux__)
    #define PLATFORM "Linux"
#elif defined(__APPLE__)
    #define PLATFORM "macOS"
#else
    #define PLATFORM "Unknown"
#endif

#define DEBUG
#define FEATURE_X_ENABLED 1
/*
    1. main 함수
    - C 프로그래밍의 기본이 되는 함수
*/
int main(int argc, char *argv[]) {
// 3) 로그 작성
LOG("log");
// 4) 토큰 연결
FUNC_NAME(my_, print)();

// 2) 디버그용 코드 포함 제외
#ifdef DEBUG
    printf("[DEBUG]");
#endif

// 3) 기능 활성화 토글
#if FEATURE_X_ENABLED
    // 기능 X 구현 코드
    printf("기능 X 활성화됨\n");
#else
    printf("기능 X 비활성화됨\n");
#endif



}
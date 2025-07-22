#include <stdio.h>

int main() {
    int total = 0;
    for(int i = 0; i < 4; i++) {
        int current;
        scanf("%d", &current);
        total += current;
    };
    if(1800 - total >= 300) {
        printf("%s", "Yes");
    } else {
        printf("%s", "No");
    }
}
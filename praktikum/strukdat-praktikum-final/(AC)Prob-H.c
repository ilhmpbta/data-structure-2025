#include <stdio.h>
#include <string.h>

int the_lonely_one(char *s) {
    int freq[26] = {0};

    for (int i = 0; s[i] != '\0'; ++i) {
        freq[s[i] - 'a']++;
    }

    for (int i = 0; s[i] != '\0'; ++i) {
        if (freq[s[i] - 'a'] == 1) {
            return i;
        }
    }

    return -1;
}

int main() {
    char s[100001];
    scanf("%s", s);
    printf("%d\n", the_lonely_one(s));
    return 0;
}

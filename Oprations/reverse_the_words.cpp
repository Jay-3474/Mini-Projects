#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverseWords(const char *str) {
    char words[100][100]; // stores up to 100 words, each up to 99 chars
    int n = 0, i = 0, j = 0, k;

    // split into words
    while (str[i] != '\0') {
        if (!isspace((unsigned char)str[i])) {
            words[n][j++] = str[i];
        } else if (j > 0) {
            words[n][j] = '\0';
            n++;
            j = 0;
        }
        i++;
    }
    if (j > 0) {
        words[n][j] = '\0';
        n++;
    }

    // print in reverse order
    for (k = n - 1; k >= 0; k--) {
        printf("%s", words[k]);
        if (k > 0) printf(" ");
    }
    printf("\n");
}

int main() {
    char s1[] = "name is  india";
    char s2[] = "I love india so  much";

    reverseWords(s1);  // output: "india is name"
    reverseWords(s2);  // output: "much so india love I"

    return 0;
}

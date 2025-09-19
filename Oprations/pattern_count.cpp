#include <stdio.h>
#include <string.h>

int main() {
    char s[] = "001010100001101";
    int count = 0;
    int length = strlen(s);

    for (int i = 0; i < length; i++) {
        if (s[i] == '1') {
            int j = i + 1;

            // move forward while there are 0's
            while (j < length && s[j] == '0') {
                j++;
            }

            // if we stopped at a '1' (after at least one '0'), it's a match
            if (j < length && j > i + 1 && s[j] == '1') {
                count++;
                i = j - 1; // move to this '1' to continue search
            }
        }
    }

    printf("The pattern '1[0]+1' occurs %d times.\n", count);
    return 0;
}

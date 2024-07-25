/* #include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    printf( "%s\n", readline( "test> " ) );
    return 0;
} */

#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello, this is a sample string";
    char delimiters[] = " ,s"; // Delimiters are space and comma
    char *token;

    // Get the first token
    token = strtok(str, delimiters);

    // Walk through other tokens
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delimiters);
    }

    return 0;
}
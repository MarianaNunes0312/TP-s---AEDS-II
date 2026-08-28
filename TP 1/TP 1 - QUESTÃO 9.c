#include <stdio.h>
#include <string.h>

char *ciframento(char *texto) {
 if (*texto == '\0') {
  return texto;
} if (*texto >= 'a' && *texto <= 'z') {
        *texto = ((*texto - 'a' + 3) % 26) + 'a';
} else if (*texto >= 'A' && *texto <= 'Z') {
        *texto = ((*texto - 'A' + 3) % 26) + 'A';
}
    return ciframento(texto + 1), texto;
}

int main(){
char palavra[100];

while (scanf("%s", palavra) != EOF && (palavra[0] != 'F' || palavra[1] != 'I' || palavra[2] != 'M' || palavra[3] != '\0')) {
        printf("%s\n", ciframento(palavra));
}

return 0;
}




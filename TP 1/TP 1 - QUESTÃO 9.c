#include <stdio.h>
#include <string.h>

char *ciframento(char *texto) {
if (*texto == '\0' || *texto == '\n' || *texto == '\r') {
return texto;
}

if (*texto != '\t') {
    *texto = *texto + 3;
}
    
return ciframento(texto + 1), texto;
}

int main() {
char palavra[500];

while (fgets(palavra, sizeof(palavra), stdin) != NULL) {
int i = 0;
        
while (palavra[i] != '\0') {
    if (palavra[i] == '\n' || palavra[i] == '\r') {
        palavra[i] = '\0';
            break;
}
    i++;
}

        
if (palavra[0] == 'F' && palavra[1] == 'I' && palavra[2] == 'M' && palavra[3] == '\0') {
    break;
}

ciframento(palavra);
printf("%s\n", palavra);
}

return 0;
}



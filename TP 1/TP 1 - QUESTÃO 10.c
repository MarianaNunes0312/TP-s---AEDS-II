#include <stdio.h>
#include <string.h>

int vogal(char *str) {
if (*str == '\0' || *str == '\n' || *str == '\r') {
    return 1;
}
    
char c = *str;
if (c >= 'A' && c <= 'Z') {
    c += 32;
}
    
if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
        return 0;
}
    
    return vogal(str + 1);
}


int consoante(char *str) {
if (*str == '\0' || *str == '\n' || *str == '\r') {
    return 1;
}
    
char c = *str;
if (c >= 'A' && c <= 'Z') {
    c += 32;
}
      
if (c < 'a' || c > 'z' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
     return 0;
}
    
return consoante(str + 1);
}

//
int inteiro(char *str) {
if (*str == '\0' || *str == '\n' || *str == '\r') {
    return 1;
}
    
if (*str < '0' || *str > '9') {
    return 0;
}
    
return inteiro(str + 1);
}


int real(char *str, int pontos) {
if (*str == '\0' || *str == '\n' || *str == '\r') {
        return 1;
}
    
if (*str == '.' || *str == ',') {
    if (pontos > 0) return 0; 
        return real(str + 1, pontos + 1);
}
    
if (*str < '0' || *str > '9') {
     return 0;
}
    
    return real(str + 1, pontos);
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

if (palavra[0] == '\0') {
    printf("NAO NAO NAO NAO\n");
        continue;
}

int x1 = vogal(palavra);
int x2 = consoante(palavra);
int x3 = inteiro(palavra);
int x4 = real(palavra, 0); 

printf("%s %s %s %s\n", x1 ? "SIM" : "NAO", x2 ? "SIM" : "NAO", x3 ? "SIM" : "NAO", x4 ? "SIM" : "NAO");
}

return 0;
}

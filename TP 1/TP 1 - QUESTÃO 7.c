#include <stdio.h>
#include <stdlib.h>

int maiorSub(char* string) {
int tamanho = 0;

while (string[tamanho] != '\0') {
tamanho++;
}

int maior = 0;

for (int i = 0; i < tamanho; i++) {

int javiu[256] = {0};
int count = 0;

for (int j = i; j < tamanho; j++) {
int letra = string[j];


if (javiu[letra] == 1) {
break;
}


javiu[letra] = 1;
count++;
}


if (count > maior) {
maior = count;
}
}

return maior;
}

int main (){
char palavra[100];
int resultado=0;

while(scanf("%99s", palavra) != EOF && (palavra[0]!='F'|| palavra[1]!='I' || palavra[2]!='M' || palavra[3] != '\0')){
int resultado = maiorSub(palavra);
printf("%d\n", resultado);
}

return 0;

}

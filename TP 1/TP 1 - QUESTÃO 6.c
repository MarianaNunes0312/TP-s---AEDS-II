#include <stdio.h>
#include <stdlib.h>

int anagrama (char *string1, char *string2){
int tamanho1 = 0, tamanho2 = 0, count=0;

while (string1[tamanho1] != '\0' && string2[tamanho2] != '\0') {
    tamanho1++;
    tamanho2++;
}

if (tamanho1 != tamanho2){
   return 0;
}


for (int i=0; i<tamanho1; i++){
    for (int j=0; j<tamanho1; j++){
        if (string1[i]==string2[j]){
            count++;
        }
    }
}

if (count==tamanho1){
    return 1;
} else {
    return 0;
}
}

int main(){
char palavra1[100], palavra2[100];

scanf ("%s %s", palavra1, palavra2);

if (anagrama(palavra1, palavra2)== 1){
    printf("SIM\n");
}else {
    printf("NÃO\n");
}

return 0;
}

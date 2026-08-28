#include <stdio.h>
#include <stdlib.h>

void inverter (char *string){
  int inicio = 0;
  int fim = 0;

while (string[fim] != '\0') {
        fim++;
}

fim--;


while (inicio < fim) {
   char temp = string[inicio];
   string[inicio] = string[fim];
   string[fim] = temp;

inicio++;
fim--;
}
}

int main(){
char palavra[100];

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

inverter(palavra);

printf("%s\n", palavra);
}

return 0; 
}
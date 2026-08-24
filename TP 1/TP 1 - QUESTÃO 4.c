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

scanf("%s", palavra);

inverter(palavra);

printf("%s", palavra);

return 0;
}

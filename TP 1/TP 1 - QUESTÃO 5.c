#include <stdio.h>
#include <stdlib.h>

int somaDigitos(int n) {
int soma = 0;

while (n > 0) {
soma += n % 10; 
n = n / 10;     
}

return soma;
}

int main() {
int num;
int resultado;

while (scanf("%d", &num) != EOF) {
        
if (num < 0) {
    break;
}

resultado = somaDigitos(num);
printf("%d\n", resultado);
}

return 0; 
}
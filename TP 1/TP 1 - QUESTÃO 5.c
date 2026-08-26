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

scanf("%d", &num);

resultado = somaDigitos(num);

printf("%d", resultado);

return 0;
}
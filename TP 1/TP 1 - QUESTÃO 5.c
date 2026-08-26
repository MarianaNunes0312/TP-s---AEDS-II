#include <stdio.h>
#include <stdlib.h>

int somaDigitos (int n){
if (n<10){
    return n;
}
else {
    return somaDigitos(n/10) + n%10; //se eu dividir 11 por 10, da 1 e sobra 1, logo 1+1=1
}
}

int main (){
int num;
int resultado;

scanf ("%d", &num);

resultado = somaDigitos(num);

printf("%d", resultado);

return 0;
}

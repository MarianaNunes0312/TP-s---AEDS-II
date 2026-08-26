import java.util.Scanner;

class Somadigitos{
public static int soma (int n){
  if (n<10){
    return n;
}
else {
    return soma(n/10) + n%10; //se eu dividir 11 por 10, da 1 e sobra 1, logo 1+1=1
}
}  

public static void main(String[] args){
int num;
Scanner sc = new Scanner(System.in);
num = sc.nextInt();

while(num != 0){
    System.out.println(soma(num));
    num = sc.nextInt();
}

sc.close();
}
}
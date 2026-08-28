import java.util.Random;
import java.util.Scanner;

class Aleatoria{
public static String alternarAleatoria (String s, Random gerador){

int tam = s.length();
String resultado = "";

char c1 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
char c2 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
    
for (int i = 0; i < tam; i++) {
    if (s.charAt(i) == c1) {
        resultado = resultado + c2; 
    } else {
        resultado = resultado + s.charAt(i); 
}
}

return resultado;
}

public static void main(String[] args){
Random gerador = new Random();
gerador.setSeed(4);

String s = "";
Scanner sc = new Scanner(System.in);
s = sc.nextLine();

while(s.length() != 3 || s.charAt(0)!='F' || s.charAt(1)!='I' || s.charAt(2)!='M'){
    System.out.println(alternarAleatoria(s, gerador));
    s = sc.nextLine();
}

sc.close();
}
}





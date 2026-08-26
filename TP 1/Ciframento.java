import java.util.Scanner;

class Ciframento{
public static String ciframento (String s, int tam){

String resultado = "";

for(int i=0; i<tam; i++){
    char original = s.charAt(i);
    char cifrada = (char)(original + 3);

    resultado += cifrada;
}

return resultado;

}

public static void main(String[] args){
String s = "";
Scanner sc = new Scanner(System.in);
s = sc.nextLine();

while(s.length() != 3 || s.charAt(0)!='F' || s.charAt(1)!='I' || s.charAt(2)!='M'){
    int tam = s.length();
    System.out.println(ciframento(s, tam));
    s = sc.nextLine();
}

sc.close();
}
}
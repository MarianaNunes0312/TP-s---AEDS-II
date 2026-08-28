import java.util.Scanner;

public class Validacao {

public static boolean validarSenha(String s) {

int tamanho = s.length();

if (tamanho < 8) {
    return false;
        
} else {

boolean maiuscula = false, minuscula = false, numero = false, especial = false;

for (int i = 0; i < tamanho; i++) {
char c = s.charAt(i);

    if (c >= 'A' && c <= 'Z') {
        maiuscula = true;
    } else if (c >= 'a' && c <= 'z') {
        minuscula = true;
    } else if (c >= '0' && c <= '9') {
        numero = true;
    } else {
        especial = true;
         }
    }

return maiuscula && minuscula && numero && especial;
    }
}

public static void main(String[] args){
Scanner sc = new Scanner(System.in);
String senha = sc.nextLine();
    
while (!(senha.length() == 3 && senha.charAt(0) == 'F' && senha.charAt(1) == 'I' && senha.charAt(2) == 'M')) {
        
        if (validarSenha(senha)) {
            System.out.println("SIM");
        } else {
            System.out.println("NÃO");
        }

        
        senha = sc.nextLine(); 
}

    sc.close();
}
}
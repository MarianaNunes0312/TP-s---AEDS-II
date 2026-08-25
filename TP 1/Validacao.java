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

public static void main(String[] args) {
Scanner sc = new Scanner(System.in);

    
 while (sc.hasNextLine()) {
            String senha = sc.nextLine();

            if (validarSenha(senha)) {
                System.out.println("SIM");
            } else {
                System.out.println("NÃO");
            }
        }

        sc.close();
    }
}
import java.util.Scanner;

class Inversao{
public static String inverter(String s, int i) {
    if (i < 0) {
        return "";
    } else {
        return s.charAt(i) + inverter(s, i - 1);
    }
}



public static void main(String[] args) {
Scanner sc = new Scanner(System.in);

    
 while (sc.hasNextLine()) {
            String palavra = sc.nextLine();
            System.out.println(inverter(palavra, palavra.length() - 1));
}

        sc.close();
    }
}
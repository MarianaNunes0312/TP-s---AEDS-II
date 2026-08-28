import java.util.Scanner;

class Inversao{
public static String inverter(String s, int i) {
    if (i < 0) {
        return "";
    } else {
        return s.charAt(i) + inverter(s, i - 1);
    }
}



public static void main(String[] args){
String s = "";
Scanner sc = new Scanner(System.in);
s = sc.nextLine();

    
 while (s.length() != 3 || s.charAt(0)!='F' || s.charAt(1)!='I' || s.charAt(2)!='M') {
    System.out.println(inverter(s, s.length() - 1));
    s = sc.nextLine();
}

        sc.close();
    }
}
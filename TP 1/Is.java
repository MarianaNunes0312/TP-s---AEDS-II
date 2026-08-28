import java.util.Scanner;

class Is{

public static boolean vogal (String s){
int tam = s.length();
int count=0;


for (int i=0; i<tam; i++){

char c = s.charAt(i);
if (c>='a'&& c<= 'z' || c>='A' && c<='Z'){
if(c=='a' || c=='A' || c=='e' || c=='E' || c=='i' || c=='I' || c=='o' || c=='O' || c=='u' || c=='U'){
count++;
}
}
}

if (count==tam){
return true;
} else {
return false;
}
}

public static boolean consoante (String s){
int tam = s.length();
int count=0;

for (int i=0; i<tam; i++){
char c = s.charAt(i);
if (c>='a'&& c<= 'z' || c>='A' && c<='Z'){
if (c!='a' && c!='A' && c!='e' && c!='E' && c!='i' && c!='I' && c!='o' && c!='O' && c!='u' && c!='U'){
count++;
}
}
}

if (count==tam){
return true;
} else {
return false;
}
}


public static boolean inteiro (String s){
int tam = s.length();

for (int i = 0; i < tam; i++) {
char c = s.charAt(i);
    if (c < '0' || c > '9') {
        return false; 
    }
}
return true;

}

public static boolean real (String s){
int tam = s.length();
boolean numero=false;
int pontos=0, virgulas=0;

for (int i = 0; i < tam; i++) {
char c = s.charAt(i);
    if (c >= '0' && c <= '9') {
        numero = true;
    } else if (c == '.') {
        pontos++;
    } else if (c == ',') {
        virgulas++;
    } else {
        return false; 
    }
}

if (numero && (pontos + virgulas <= 1)) {
    return true;
} else {
    return false;
}
}

public static void main(String[] args){
Scanner sc = new Scanner(System.in);
String s = sc.nextLine();

while (!(s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M')) {
String palavra = s;

String x1 = vogal(palavra) ? "SIM" : "NAO";
String x2 = consoante(palavra) ? "SIM" : "NAO";
String x3 = inteiro(palavra) ? "SIM" : "NAO";
String x4 = real(palavra) ? "SIM" : "NAO";

 System.out.println(x1 + " " + x2 + " " + x3 + " " + x4);

    
s = sc.nextLine();
}

sc.close();
}
}


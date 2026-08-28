#include <stdio.h>
#include <stdlib.h>

int verificar(char* s1, char* s2){
	int resp = 0;
	int quant = 0;
	int tamanho1 = 0;
	int tamanho2 = 0;

	while(s1[tamanho1]!='\0'){
		tamanho1++;
	}

	
	while(s2[tamanho2]!='\0'){
		tamanho2++;
	}

	if(tamanho1==tamanho2){
		for(int i=0; i<tamanho1; i++){
			for(int j=0; j<tamanho2; j++){
				if(s1[i] == s2[j] || s1[i] == s2[j] + 32 || s1[i] == s2[j] - 32){
					s2[j]=' ';
					quant++;
					break;
				}
			}
		}
	}
	
	if(quant==tamanho1){
		resp=1;
	}
	
	return resp;
}

int main(){
char primeiro[100];
char segunda[100];

while(scanf("%s %s", primeiro, segunda)!=EOF && (primeiro[0]!='F'|| primeiro[1]!='I' || primeiro[2]!='M' || primeiro[3] != '\0')){

	if(verificar(primeiro, segunda)){
		printf("SIM\n");
	}else{
		printf("NAO\n");
	}

}

return 0;
}
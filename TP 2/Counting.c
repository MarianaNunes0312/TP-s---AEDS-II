#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int ano;
    int mes;
    int dia;
} Data;







typedef struct {
    int id;
    char marca[100];
    char modelo[100];
    int ano;
    char categoria[100];
    char combustivel[100];
    int cilindros;
    double cilindrada;
    char transmissao[100];
    char tracao[100];
    double consumoCidade;
    double consumoEstrada;
    double co2;
    int turbo;
    Data dataRegistro;
} Veiculo;







Data parseData(char* s) {
    Data d;
    sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);
    return d;
}







void formatData(Data d, char* buffer) {
    sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}










Veiculo parseVeiculo(char* s) {
    Veiculo v;

    char *id = strtok(s, ",");
    char *marca = strtok(NULL, ",");
    char *modelo = strtok(NULL, ",");
    char *ano = strtok(NULL, ",");
    char *categoria = strtok(NULL, ",");
    char *combustivel = strtok(NULL, ",");
    char *cilindros = strtok(NULL, ",");
    char *cilindrada = strtok(NULL, ",");
    char *transmissao = strtok(NULL, ",");
    char *tracao = strtok(NULL, ",");
    char *consumoCidade = strtok(NULL, ",");
    char *consumoEstrada = strtok(NULL, ",");
    char *co2 = strtok(NULL, ",");
    char *turbo = strtok(NULL, ",");
    char *dataStr = strtok(NULL, ",");

    v.id = atoi(id);
    strcpy(v.marca, marca);
    strcpy(v.modelo, modelo);
    v.ano = atoi(ano);
    strcpy(v.categoria, categoria);
    v.cilindros = atoi(cilindros);
    v.cilindrada = atof(cilindrada);
    strcpy(v.transmissao, transmissao);
    strcpy(v.tracao, tracao);
    v.consumoCidade = atof(consumoCidade);
    v.consumoEstrada = atof(consumoEstrada);
    v.co2 = atof(co2);

    if (strcmp(turbo, "true") == 0) {
        v.turbo = 1;
    } else {
        v.turbo = 0;
    }

    strcpy(v.combustivel, "[");
    for (int i = 0; combustivel[i] != '\0'; i++) {
        if (combustivel[i] == ';') {
            strcat(v.combustivel, ", ");
        } else {
            char temp[2] = {combustivel[i], '\0'};
            strcat(v.combustivel, temp);
        }
    }
    strcat(v.combustivel, "]");

    v.dataRegistro = parseData(dataStr);

    return v;
}









void formatVeiculo(Veiculo v, char* buffer) {
    char dataFormatada[20];
    formatData(v.dataRegistro, dataFormatada);

    sprintf(buffer, "[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]",
            v.id, v.marca, v.modelo, v.ano, v.categoria, v.combustivel,
            v.cilindros, v.cilindrada, v.transmissao, v.tracao,
            v.consumoCidade, v.consumoEstrada, v.co2,
            v.turbo ? "true" : "false", dataFormatada);
}









Veiculo* lerCsv(char* caminhoArquivo, int* n) {
    FILE *f = fopen(caminhoArquivo, "r");
    if (!f) return NULL;

    char linha[1024];
    fgets(linha, sizeof(linha), f);

    Veiculo *vetor = (Veiculo*) malloc(2000 * sizeof(Veiculo));
    int total = 0;

    while (fgets(linha, sizeof(linha), f) != NULL) {
        linha[strcspn(linha, "\r\n")] = 0;
        if (strlen(linha) > 0) {
            vetor[total] = parseVeiculo(linha);
            total++;
        }
    }

    fclose(f);
    *n = total;
    return vetor;
}








void countingSort(Veiculo vetor[], int n) {
    if (n <= 0) return;

    int max = vetor[0].cilindros;
    for (int i = 1; i < n; i++) {
        if (vetor[i].cilindros > max) {
            max = vetor[i].cilindros;
        }
    }

    int *count = (int *)calloc(max + 1, sizeof(int));

   
    for (int i = 0; i < n; i++) {
        count[vetor[i].cilindros]++;
    }

   
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    Veiculo *saida = (Veiculo*)malloc (n*sizeof(Veiculo));
   
    for (int i = n - 1; i >= 0; i--) {
int pos = count[vetor[i].cilindros]-1;
        saida[pos] = vetor[i];
        count[vetor[i].cilindros]--;
    }

   
    for (int i = 0; i < n; i++) {
        vetor[i] = saida[i];
    }

   
    free(count);
    free(saida);
}






int main() {
    char *caminho = "/tmp/veiculos.csv";
    FILE *teste = fopen(caminho, "r");
    if (!teste) {
        caminho = "veiculos.csv";
    } else {
        fclose(teste);
   
    }

    int n=0;
    Veiculo vetor[2000];
    int totalveiculos = 0;
    Veiculo *veiculos = lerCsv(caminho, &n);

    if (veiculos == NULL) return 1;

    int idBusca;
    char bufferSaida[1024];

    while (scanf("%d", &idBusca) == 1 && idBusca != -1) {
        for (int i = 0; i < n; i++) {
            if (veiculos[i].id == idBusca) {
                vetor[totalveiculos] = veiculos[i];
                totalveiculos++;
                break;
            }
        }
    }

    countingSort(vetor, totalveiculos);

    for (int i = 0; i < totalveiculos; i++) {
        formatVeiculo(vetor[i], bufferSaida);
        printf("%s\n", bufferSaida);
    }

    free(veiculos);
    return 0;
}
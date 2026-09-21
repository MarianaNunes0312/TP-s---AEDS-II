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
    sprintf(v.marca, "%s", marca);
    sprintf(v.modelo, "%s", modelo);
    v.ano = atoi(ano);
    sprintf(v.categoria, "%s", categoria);
    v.cilindros = atoi(cilindros);
    v.cilindrada = atof(cilindrada);
    sprintf(v.transmissao, "%s", transmissao);
    sprintf(v.tracao, "%s", tracao);
    v.consumoCidade = atof(consumoCidade);
    v.consumoEstrada = atof(consumoEstrada);
    v.co2 = atof(co2);

    if (strcmp(turbo, "true") == 0) {
        v.turbo = 1;
    } else {
        v.turbo = 0;
    }

    v.combustivel[0] = '[';
    v.combustivel[1] = '\0';
    
    int pos = 1;
    for (int i = 0; combustivel[i] != '\0'; i++) {
        if (combustivel[i] == ';') {
            v.combustivel[pos++] = ',';
            v.combustivel[pos++] = ' ';
        } else {
            v.combustivel[pos++] = combustivel[i];
        }
    }
    v.combustivel[pos++] = ']';
    v.combustivel[pos] = '\0';

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







void removerQuebraLinha(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\r' || str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}





Veiculo* lerCsv(char* caminhoArquivo, int* n) {
    FILE *f = fopen(caminhoArquivo, "r");
    if (!f) return NULL;

    char linha[1024];
    fgets(linha, sizeof(linha), f);

    Veiculo *vetor = (Veiculo*) malloc(2000 * sizeof(Veiculo));
    int total = 0;

    while (fgets(linha, sizeof(linha), f) != NULL) {
        removerQuebraLinha(linha);
        if (linha[0] != '\0') {
            vetor[total] = parseVeiculo(linha);
            total++;
        }
    }

    fclose(f);
    *n = total;
    return vetor;
}










void swap(Veiculo vetor[], int a, int b) {
    Veiculo temp = vetor[a];
    vetor[a] = vetor[b];
    vetor[b] = temp;
}












void selectionSort(Veiculo vetor[], int n) {
    for (int i = 0; i < (n - 1); i++) {
        int menor = i;

        for (int j = (i + 1); j < n; j++) {
            if (strcmp(vetor[j].modelo, vetor[menor].modelo) < 0) {
                menor = j;
            }
        }

        swap(vetor, menor, i);
    }
}












int main() {
    char *caminho = "/tmp/veiculos.csv";
    FILE *teste = fopen(caminho, "r");
    if (!teste) {
        caminho = "veiculos.csv";
    } else {
        fclose(teste);
    }

    int n = 0;
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

    selectionSort(vetor, totalveiculos);

    for (int i = 0; i < totalveiculos; i++) {
        formatVeiculo(vetor[i], bufferSaida);
        printf("%s\n", bufferSaida);
    }

    free(veiculos);
    return 0;
}
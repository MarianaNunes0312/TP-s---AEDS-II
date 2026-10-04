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
    char combustivel[50][50];
    int numCombustiveis;
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
    char *combustivelStr = strtok(NULL, ",");
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

    v.numCombustiveis = 0;
    char *tokenComb = strtok(combustivelStr, ";");
    while (tokenComb != NULL && v.numCombustiveis < 50) {
        sprintf(v.combustivel[v.numCombustiveis], "%s", tokenComb);
        v.numCombustiveis++;
        tokenComb = strtok(NULL, ";");
    }

    v.dataRegistro = parseData(dataStr);

    return v;
}










void formatVeiculo(Veiculo v, char* buffer) {
    char dataFormatada[20];
    formatData(v.dataRegistro, dataFormatada);

    char textoCombustivel[200];
    int pos = 0;
    pos += sprintf(textoCombustivel + pos, "[");
    for (int i = 0; i < v.numCombustiveis; i++) {
        pos += sprintf(textoCombustivel + pos, "%s", v.combustivel[i]);
        if (i < v.numCombustiveis - 1) {
            pos += sprintf(textoCombustivel + pos, ", ");
        }
    }
    sprintf(textoCombustivel + pos, "]");

    sprintf(buffer, "[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]",
            v.id, v.marca, v.modelo, v.ano, v.categoria, textoCombustivel,
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
    if (fgets(linha, sizeof(linha), f) == NULL) {
        fclose(f);
        return NULL;
    }

    int capacidade = 2000;
    Veiculo *vetor = (Veiculo*) malloc(capacidade * sizeof(Veiculo));
    int total = 0;

    while (fgets(linha, sizeof(linha), f) != NULL) {
        removerQuebraLinha(linha);
        if (linha[0] != '\0') {
            if (total >= capacidade) {
                capacidade *= 2;
                vetor = (Veiculo*) realloc(vetor, capacidade * sizeof(Veiculo));
            }
            vetor[total] = parseVeiculo(linha);
            total++;
        }
    }

    fclose(f);
    *n = total;
    return vetor;
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
    Veiculo *veiculos = lerCsv(caminho, &n);

    if (veiculos == NULL) {
        return 0; 
    }

    int idBusca;
    char bufferSaida[1024];

    while (scanf("%d", &idBusca) == 1 && idBusca != -1) {
        for (int i = 0; i < n; i++) {
            if (veiculos[i].id == idBusca) {
                formatVeiculo(veiculos[i], bufferSaida);
                printf("%s\n", bufferSaida);
                break;
            }
        }
    }

    free(veiculos);
    return 0;
}

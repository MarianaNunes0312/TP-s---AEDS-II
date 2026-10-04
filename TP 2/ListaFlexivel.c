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





typedef struct Celula {
    Veiculo elemento;
    struct Celula* prox;
} Celula;






typedef struct {
    Celula* primeiro;
    Celula* ultimo;
} ListaFlexivel;









Celula* novaCelula(Veiculo elemento) {
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    nova->elemento = elemento;
    nova->prox = NULL;
    return nova;
}








void startLista(ListaFlexivel* l) {
    Veiculo dummy;
    l->primeiro = novaCelula(dummy);
    l->ultimo = l->primeiro;
}







int tamanho(ListaFlexivel* l) {
    int tam = 0;
    for (Celula* i = l->primeiro->prox; i != NULL; i = i->prox) {
        tam++;
    }
    return tam;
}







void inserirInicio(ListaFlexivel* l, Veiculo x) {
    Celula* tmp = novaCelula(x);
    tmp->prox = l->primeiro->prox;
    l->primeiro->prox = tmp;
    if (l->primeiro == l->ultimo) {
        l->ultimo = tmp;
    }
}








void inserirFim(ListaFlexivel* l, Veiculo x) {
    l->ultimo->prox = novaCelula(x);
    l->ultimo = l->ultimo->prox;
}









void inserir(ListaFlexivel* l, Veiculo x, int pos) {
    int tam = tamanho(l);
    if (pos < 0 || pos > tam) exit(1);

    if (pos == 0) {
        inserirInicio(l, x);
    } else if (pos == tam) {
        inserirFim(l, x);
    } else {
        Celula* p = l->primeiro;
        for (int i = 0; i < pos; i++) {
            p = p->prox;
        }
        Celula* tmp = novaCelula(x);
        tmp->prox = p->prox;
        p->prox = tmp;
    }
}














Veiculo removerInicio(ListaFlexivel* l) {
    if (l->primeiro == l->ultimo) exit(1);

    Celula* tmp = l->primeiro->prox;
    Veiculo resp = tmp->elemento;
    l->primeiro->prox = tmp->prox;
    if (tmp == l->ultimo) {
        l->ultimo = l->primeiro;
    }
    free(tmp);
    return resp;
}












Veiculo removerFim(ListaFlexivel* l) {
    if (l->primeiro == l->ultimo) exit(1);

    Celula* i;
    for (i = l->primeiro; i->prox != l->ultimo; i = i->prox);

    Veiculo resp = l->ultimo->elemento;
    free(l->ultimo);
    l->ultimo = i;
    l->ultimo->prox = NULL;
    return resp;
}











Veiculo remover(ListaFlexivel* l, int pos) {
    int tam = tamanho(l);
    if (l->primeiro == l->ultimo || pos < 0 || pos >= tam) exit(1);

    if (pos == 0) return removerInicio(l);
    if (pos == tam - 1) return removerFim(l);

    Celula* p = l->primeiro;
    for (int i = 0; i < pos; i++) {
        p = p->prox;
    }
    Celula* tmp = p->prox;
    Veiculo resp = tmp->elemento;
    p->prox = tmp->prox;
    free(tmp);
    return resp;
}








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
    if (combustivelStr != NULL) {
        char *tokenComb = strtok(combustivelStr, ";");
        while (tokenComb != NULL && v.numCombustiveis < 50) {
            sprintf(v.combustivel[v.numCombustiveis], "%s", tokenComb);
            v.numCombustiveis++;
            tokenComb = strtok(NULL, ";");
        }
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







Veiculo* buscarPorId(Veiculo* veiculos, int n, int id) {
    for (int i = 0; i < n; i++) {
        if (veiculos[i].id == id) {
            return &veiculos[i];
        }
    }
    return NULL;
}







void mostrarLista(ListaFlexivel* l) {
    char buffer[1024];
    for (Celula* i = l->primeiro->prox; i != NULL; i = i->prox) {
        formatVeiculo(i->elemento, buffer);
        printf("%s\n", buffer);
    }
}












void liberarLista(ListaFlexivel* l) {
    Celula* i = l->primeiro;
    while (i != NULL) {
        Celula* tmp = i;
        i = i->prox;
        free(tmp);
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
    Veiculo *veiculosBase = lerCsv(caminho, &n);
    if (veiculosBase == NULL) return 0;

    ListaFlexivel lista;
    startLista(&lista);

    int idBusca;
    while (scanf("%d", &idBusca) == 1 && idBusca != -1) {
        Veiculo *v = buscarPorId(veiculosBase, n, idBusca);
        if (v != NULL) {
            inserirFim(&lista, *v);
        }
    }

    int numOp;
    if (scanf("%d", &numOp) == 1) {
        for (int i = 0; i < numOp; i++) {
            char comando[5];
            scanf("%s", comando);

            if (strcmp(comando, "II") == 0) {
                int id;
                scanf("%d", &id);
                Veiculo *v = buscarPorId(veiculosBase, n, id);
                if (v != NULL) inserirInicio(&lista, *v);

            } else if (strcmp(comando, "IF") == 0) {
                int id;
                scanf("%d", &id);
                Veiculo *v = buscarPorId(veiculosBase, n, id);
                if (v != NULL) inserirFim(&lista, *v);

            } else if (strcmp(comando, "I*") == 0) {
                int pos, id;
                scanf("%d %d", &pos, &id);
                Veiculo *v = buscarPorId(veiculosBase, n, id);
                if (v != NULL) inserir(&lista, *v, pos);

            } else if (strcmp(comando, "RI") == 0) {
                Veiculo removido = removerInicio(&lista);
                printf("(R) %s %s\n", removido.marca, removido.modelo);

            } else if (strcmp(comando, "RF") == 0) {
                Veiculo removido = removerFim(&lista);
                printf("(R) %s %s\n", removido.marca, removido.modelo);

            } else if (strcmp(comando, "R*") == 0) {
                int pos;
                scanf("%d", &pos);
                Veiculo removido = remover(&lista, pos);
                printf("(R) %s %s\n", removido.marca, removido.modelo);
            }
        }
    }

    mostrarLista(&lista);

    liberarLista(&lista);
    free(veiculosBase);
    return 0;
}
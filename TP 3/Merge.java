import java.util.Scanner;
import java.io.File;
import java.lang.String;


public class Merge {

    public static void sort(Veiculo[] array, int inicio, int fim) {
        if (inicio < fim) {
            int meio = (inicio + fim) / 2;

            sort(array, inicio, meio);
            sort(array, meio + 1, fim);

            merge(array, inicio, meio, fim);
        }
    }






    private static void merge(Veiculo[] array, int inicio, int meio, int fim) {
        int n1 = meio - inicio + 1;
        int n2 = fim - meio;

        Veiculo[] esquerda = new Veiculo[n1];
        Veiculo[] direita = new Veiculo[n2];

        for (int i = 0; i < n1; i++) {
            esquerda[i] = array[inicio + i];
        }
        for (int j = 0; j < n2; j++) {
            direita[j] = array[meio + 1 + j];
        }

        int i = 0, j = 0;
        int k = inicio;

        while (i < n1 && j < n2) {
            boolean deveInserirEsquerda = false;
            
            if (esquerda[i].getConsumoEstrada() < direita[j].getConsumoEstrada()) {
                deveInserirEsquerda = true;
            } else if (esquerda[i].getConsumoEstrada() == direita[j].getConsumoEstrada()) {
                if (esquerda[i].getMarca().compareTo(direita[j].getMarca()) <= 0) {
                    deveInserirEsquerda = true;
                }
            }

            if (deveInserirEsquerda) {
                array[k] = esquerda[i];
                i++;
            } else {
                array[k] = direita[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            array[k] = esquerda[i];
            i++;
            k++;
        }

        while (j < n2) {
            array[k] = direita[j];
            j++;
            k++;
        }
    }
    






    public static void main(String[] args) throws Exception {
        String caminho = "/tmp/veiculos.csv";
        File f = new File(caminho);

        if (!f.exists()) {
            caminho = "veiculos.csv";
        }

        Veiculo[] veiculos = LeitorCsv.ler(caminho);
        Scanner sc = new Scanner(System.in);

        Veiculo[] pesquisados = new Veiculo[2000];
        int totalPesquisados = 0;

        while (sc.hasNextInt()) {
            int idBusca = sc.nextInt();
            if (idBusca == -1) {
                break;
            }

            for (int i = 0; i < veiculos.length; i++) {
                if (veiculos[i].getId() == idBusca) {
                    pesquisados[totalPesquisados] = veiculos[i];
                    totalPesquisados++;
                    break;
                }
            }
        }
        sc.close();

        sort(pesquisados, 0,  totalPesquisados - 1);

        for (int i = 0; i < totalPesquisados; i++) {
            System.out.println(pesquisados[i].format());
        }
    }
}






class Data {
    private int ano;
    private int mes;
    private int dia;

    public Data(int ano, int mes, int dia) {
        this.ano = ano;
        this.mes = mes;
        this.dia = dia;
    }

    public int getAno() { return ano; }
    public int getMes() { return mes; }
    public int getDia() { return dia; }

    public static Data parseData(String s) {
        String[] partes = s.split("-");
        int ano = Integer.parseInt(partes[0]);
        int mes = Integer.parseInt(partes[1]);
        int dia = Integer.parseInt(partes[2]);

        return new Data(ano, mes, dia);
    }

    public String format() {
        return String.format("%02d/%02d/%04d", dia, mes, ano);
    }
}










class Veiculo {
    private int id;
    private String marca;
    private String modelo;
    private int ano;
    private String categoria;
    private String[] combustivel;
    private int cilindros;
    private double cilindrada;
    private String transmissao;
    private String tracao;
    private double consumoCidade;
    private double consumoEstrada;
    private double co2;
    private boolean turbo;
    private Data dataRegistro;

    public Veiculo(int id, String marca, String modelo, int ano, String categoria, String[] combustivel, int cilindros, double cilindrada, String transmissao, String tracao, double consumoCidade, double consumoEstrada, double co2, boolean turbo, Data dataRegistro) {
        this.id = id;
        this.marca = marca;
        this.modelo = modelo;
        this.ano = ano;
        this.categoria = categoria;
        this.combustivel = combustivel;
        this.cilindros = cilindros;
        this.cilindrada = cilindrada;
        this.transmissao = transmissao;
        this.tracao = tracao;
        this.consumoCidade = consumoCidade;
        this.consumoEstrada = consumoEstrada;
        this.co2 = co2;
        this.turbo = turbo;
        this.dataRegistro = dataRegistro;
    }

    public int getId() { return id; }
    public String getMarca() { return marca; }
    public String getModelo() { return modelo; }
    public int getAno() { return ano; }
    public String getCategoria() { return categoria; }
    public String[] getCombustivel() { return combustivel; }
    public int getCilindros() { return cilindros; }
    public double getCilindrada() { return cilindrada; }
    public String getTransmissao() { return transmissao; }
    public String getTracao() { return tracao; }
    public double getConsumoCidade() { return consumoCidade; }
    public double getConsumoEstrada() { return consumoEstrada; }
    public double getCo2() { return co2; }
    public boolean isTurbo() { return turbo; }
    public Data getDataRegistro() { return dataRegistro; }

    public static Veiculo parseVeiculo(String s) {
        String[] atributos = s.split(",");

        int id = Integer.parseInt(atributos[0]);
        String marca = atributos[1];
        String modelo = atributos[2];
        int ano = Integer.parseInt(atributos[3]);
        String categoria = atributos[4];
        String[] combustivel = atributos[5].split(";");
        int cilindros = Integer.parseInt(atributos[6]);
        double cilindrada = Double.parseDouble(atributos[7]);
        String transmissao = atributos[8];
        String tracao = atributos[9];
        double consumoCidade = Double.parseDouble(atributos[10]);
        double consumoEstrada = Double.parseDouble(atributos[11]);
        double co2 = Double.parseDouble(atributos[12]);
        boolean turbo = Boolean.parseBoolean(atributos[13]);
        Data dataRegistro = Data.parseData(atributos[14]);

        return new Veiculo(id, marca, modelo, ano, categoria, combustivel, cilindros, cilindrada, transmissao, tracao, consumoCidade, consumoEstrada, co2, turbo, dataRegistro);
    }

    private String trocarVirgulaPorPonto(String texto) {
        char[] caracteres = texto.toCharArray();
        for (int i = 0; i < caracteres.length; i++) {
            if (caracteres[i] == ',') {
                caracteres[i] = '.';
            }
        }
        return new String(caracteres);
    }

    public String format() {
        String textoCombustivel = "[";
        for (int i = 0; i < combustivel.length; i++) {
            textoCombustivel += combustivel[i];
            if (i < combustivel.length - 1) {
                textoCombustivel += ", ";
            }
        }
        textoCombustivel += "]";

        String consumoC = trocarVirgulaPorPonto(String.format("%.2f", consumoCidade));
        String consumoE = trocarVirgulaPorPonto(String.format("%.2f", consumoEstrada));
        
        return "[" + id + " ## " + marca + " ## " + modelo + " ## " + ano + " ## " + categoria + " ## " + textoCombustivel + " ## " + cilindros + " ## " + cilindrada + " ## " + transmissao + " ## " + tracao + " ## " + consumoC + " ## " + consumoE + " ## " + co2 + " ## " + turbo + " ## " + dataRegistro.format() + "]";
    }
}













class LeitorCsv {

    public static Veiculo[] ler(String caminhoArquivo) throws Exception {
        File arquivo = new File(caminhoArquivo);
        Scanner sc = new Scanner(arquivo);
        
        if (sc.hasNextLine()) {
            sc.nextLine();
        }

        Veiculo[] veiculos = new Veiculo[2000];
        int total = 0;

        while (sc.hasNextLine()) {
            String linha = sc.nextLine();
            if (!linha.isEmpty()) {
                veiculos[total] = Veiculo.parseVeiculo(linha);
                total++;
            }
        }
        sc.close();

        Veiculo[] resultado = new Veiculo[total];
        for (int i = 0; i < total; i++) {
            resultado[i] = veiculos[i];
        }
        return resultado;
    }
}
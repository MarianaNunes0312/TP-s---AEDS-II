import java.util.Scanner;
import java.io.File;

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
        int ano = Integer.parseInt(partes[0].trim());
        int mes = Integer.parseInt(partes[1].trim());
        int dia = Integer.parseInt(partes[2].trim());

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







    public String format() {
        String textoCombustivel = "[";
        for (int i = 0; i < combustivel.length; i++) {
            textoCombustivel += combustivel[i];
            if (i < combustivel.length - 1) {
                textoCombustivel += ", ";
            }
        }
        textoCombustivel += "]";

        return String.format("[%d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %b ## %s]",
                id, marca, modelo, ano, categoria, textoCombustivel,
                cilindros, cilindrada, transmissao, tracao,
                consumoCidade, consumoEstrada, co2,
                turbo, dataRegistro.format());
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
            if (!linha.trim().isEmpty()) {
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







class Bucket {

    public static void insertionSort(Veiculo[] vet, int n) {
        for (int i = 1; i < n; i++) {
            Veiculo tmp = vet[i];
            int j = i - 1;

            while ((j >= 0) && (vet[j].getCilindrada() > tmp.getCilindrada())) {
                vet[j + 1] = vet[j];
                j--;
            }
            vet[j + 1] = tmp;
        }
    }



    public static void bucketSort(Veiculo[] vet, int n) {
        if (n <= 0) return;

        int numBaldes = 10;
        Veiculo[][] baldes = new Veiculo[numBaldes][n];
        int[] tamBaldes = new int[numBaldes];

        for (int i = 0; i < n; i++) {
            int idxBalde = (int) ((vet[i].getCilindrada() / 8.1) * numBaldes);
            if (idxBalde >= numBaldes) {
                idxBalde = numBaldes - 1;
            }
            baldes[idxBalde][tamBaldes[idxBalde]] = vet[i];
            tamBaldes[idxBalde]++;
        }

        for (int i = 0; i < numBaldes; i++) {
            insertionSort(baldes[i], tamBaldes[i]);
        }

        int idxVetor = 0;
        for (int i = 0; i < numBaldes; i++) {
            for (int j = 0; j < tamBaldes[i]; j++) {
                vet[idxVetor] = baldes[i][j];
                idxVetor++;
            }
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

        bucketSort(pesquisados, totalPesquisados);

        for (int i = 0; i < totalPesquisados; i++) {
            System.out.println(pesquisados[i].format());
        }
    }
}

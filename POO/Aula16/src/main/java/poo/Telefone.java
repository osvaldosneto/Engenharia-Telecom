package poo;

public class Telefone {

    private int codigo;
    private String numSerie, modelo;
    private float peso;
    private  Dimensao dim;

    public Telefone (int c, String s, String m, float p, Dimensao d){
        this.codigo = c;
        this.peso = p;
        this.dim = d;
        this.numSerie = s;
        this.modelo = m;

    }

    public void imprimirDados(){
        System.out.println("Cogido: " + this.codigo);
        System.out.println("Peso: " + this.peso);
        System.out.println("Numero de série: " + this.numSerie);
        System.out.println("Modelo: " + this.modelo);

    }

    @Override
    public String toString() {
        return "Telefone{" +
                "Codigo=" + codigo +
                "NumSerie='" + numSerie + '\'' +
                "Modelo='" + modelo + '\'' +
                "Peso=" + peso +
                "Dim=" + dim +
                '}';
    }

    public void ola(){
        System.out.println("Olá eu sou um telefone.");
    }

}

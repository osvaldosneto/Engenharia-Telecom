package poo;

public class Semfio extends Telefone{

    private float frequencia, distancia;
    private int canais;

    public Semfio(int c, String s, String m, float p, Dimensao d, float frequencia, float distancia, int canais) {
        super(c, s, m, p, d);
        this.frequencia = frequencia;
        this.distancia = distancia;
        this.canais = canais;
    }

    public void imprimirDados() {
        super.imprimirDados();
        System.out.println("Frequencia: " + this.frequencia);
        System.out.println("Distancia: " + this.distancia);
        System.out.println("Canais: " + this.canais);


    }

    @Override
    public String toString() {
        return "Semfio{" +
                "Frequencia = " + frequencia +
                "Distancia = " + distancia +
                "Canais = " + canais +
                '}';
    }
}

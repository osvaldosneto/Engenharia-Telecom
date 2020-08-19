package poo;

public class Dimensao {

    private float a, l, p;

    public Dimensao(float a, float l, float p) {
        this.a = a;
        this.l = l;
        this.p = p;
    }

    @Override
    public String toString() {
        return "Dimensao{" +
                "Altura = " + a +
                "Largura = " + l +
                "Profundidade = " + p +
                '}';
    }

}

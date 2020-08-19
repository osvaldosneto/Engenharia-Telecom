package Poo;

public class Soldado {

    private final int PRONTO = 10;
    private String arma;
    private int pos;
    private static int numeroSoldados;

    public Soldado() {
        numeroSoldados++;
    }

    public void movimenta(){
        pos ++;
        System.out.println("A posição do soldado é " + pos);
    }

    public void movimenta(int movimenta){
        pos += movimenta;
        System.out.println("A posição do soldado é " + pos);
    }

    public void atacar(String arma) {

        validaArma(arma);

        if (numeroSoldados >= PRONTO) {
            System.out.println("O soldado está atacando com " + this.arma + " na posição " + pos);
        } else {
            System.out.println("Exercito ainda em formação.");
        }
    }

    public void atacar(){
        if(numeroSoldados >= PRONTO){
            System.out.println("O soldado está atacando com o fuzil na posição "+ pos + ".");
        }else {
            System.out.println("Exercito ainda em formação.");
        }
    }

    public void validaArma(String arma){
        if(arma.equals("fuzil")) this.arma = "fuzil";
        else if(arma.equals("baioneta")) this.arma = "baioneta";
        else if(arma.equals("punho")) this.arma = "punho";
        else{
            this.arma = "fuzil";
        }
    }
}

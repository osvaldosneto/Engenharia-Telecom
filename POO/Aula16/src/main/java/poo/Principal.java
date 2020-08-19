package poo;

public class Principal {
    public static void main(String[] args) {


        Telefone t = new Telefone(123, "123456", "Pegate", 200, new Dimensao(120, 250, 125));

        Semfio sf = new Semfio(250, "524NE214", "Gudam", 350, new Dimensao(250, 150, 200), 250000, 50, 3);

        t.imprimirDados();
        System.out.println("\n");
        sf.imprimirDados();

        t.ola();
        System.out.println("\n");
        sf.ola();



    }



}

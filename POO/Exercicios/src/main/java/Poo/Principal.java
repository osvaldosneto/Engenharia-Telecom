package Poo;

import java.util.Scanner;

public class Principal {

    public static void main(String[] args) {

        Funcionario obj1 = new Funcionario();

        obj1.dataDeEntrada = "260783";
        FormatoData data = new FormatoData("260783");

        System.out.println(data.mostra());


    }
}

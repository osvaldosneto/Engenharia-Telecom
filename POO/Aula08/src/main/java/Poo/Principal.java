package Poo;

import java.util.Scanner;


public class Principal {

    public static void main(String[] args) {

        String caminho;
        char frente;
        int x, y, area;

        Scanner variavel = new Scanner(System.in);

        System.out.println("Informe o tamanho da área:");
        area = variavel.nextInt();

        System.out.println("Informe a posição do objeto:");
        x = variavel.nextInt();
        y = variavel.nextInt();

        System.out.println("Informe a frente do objeto:");
        frente = variavel.next().charAt(0);

        System.out.println("Informe o plano de exploração:");
        caminho = variavel.next();

        char letras[] = null;

        Robo obj = new Robo(area, x, y, frente);

        letras = caminho.toCharArray();

        for (int i=0; i < letras.length; i++){
            if((letras[i]=='D')||(letras[i]=='E')) {
                obj.rotaciona(letras[i]);
            }else if(letras[i]=='M'){
                obj.movimenta();
            }
        }

        System.out.printf(obj.toString());

        /*Tempo obj1 = new Tempo(10);

        Tempo obj2 = new Tempo(10,50);

        Tempo obj3 = new Tempo(24,20,40);

        System.out.println("Hora obj1:" + obj1.toString());

        System.out.println("Hora obj2:" + obj2.toString());

        System.out.println("Hora obj3:" + obj3.toString());

        System.out.println("Duração:" + obj3.tempoSegundos());*/

    }



}

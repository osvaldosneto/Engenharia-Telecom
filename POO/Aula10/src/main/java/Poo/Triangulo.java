package Poo;

public class Triangulo {

    private int a, b, c;



    public Triangulo(int a, int b, int c){
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public String tipoDoTriangulo(){

        if((a <= 0)||(b <= 0)||(c <= 0)){
            return "não é triangulo";
        }

        if((a == b)&&(b == c)){
            return "equilátero";
        }else if((a == b){

        }


    }




}

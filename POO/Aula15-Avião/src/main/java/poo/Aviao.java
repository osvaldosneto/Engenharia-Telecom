package poo;

import java.util.ArrayList;


public class Aviao {

    private int qtdademotor=0;
    private int peso=0;
    private int tripulante=0;
    private int passageiros=0;
    private boolean ligado;
    private ArrayList<Motor> lista = new ArrayList<>();



    /**
     * construtor para Avião
     *
     * @param qtdadomotor nos informa a quantidade de motores que o avião terá
     * @param peso nos informa o peso do avião
     * @param tripulante nos iniforma a quantidade de tripulantes no voo
     * @param passageiros nos iniforma a quantidade de passageiros no voo
     * @param tipomotor nos informa tipo do motor 1 para helice 2 para turbina
     * @param ligado igual false motor desligado;
     */
    public Aviao(int qtdadomotor, int peso, int tripulante, int passageiros, int tipomotor){
        this.qtdademotor = qtdadomotor;
        this.peso = peso;
        this.passageiros = passageiros;
        this.tripulante = tripulante;
        this.ligado = false;
        for(int i=0; i<qtdademotor; i++){
            Motor motor = new Motor(tipomotor);
            lista.add(motor);
        }
    }


    public boolean ligar(){
        if(ligado==false){
            for (Motor item : lista) {
                item.ligar();
            }
            ligado = true;
            return true;
        } else{
            return false;
        }
    }

    public boolean movimenta(int direcao, int intensidade){




            return true;

    }

    /**
     * faz soma de potencia de um motor específico
     * @param potencia nos informa a potencia a somar do motor
     * @param m nos informa o motor a somar
     * @return true caso seja somado potencia e false caso motor desligado
     */
    public boolean modificarPotencia(int potencia, int m){
        Motor mo = lista.get(m);
        return mo.modificarPotencia(potencia);
    }


    /**
     * faz soma de potencia nos motores do avião
     * @param potencia informa a potencia a somar no motor
     * @return true caso exista motor e false caso não tenha motor
     */
    public boolean modificarPotencia(int po){
        if(ligado==true){
            for(Motor item : lista) {
                item.modificarPotencia(po);
            }
            return true;
        }else{
            return false;
        }
    }










    public int getQtdademotor() {
        return qtdademotor;
    }

    public int getPeso() {
        return peso;
    }

    public int getTripulante() {
        return tripulante;
    }

    public int getPassageiros() {
        return passageiros;
    }


}

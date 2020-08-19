
package poo;

/**
 * Classe que realiza operações com o motor
  *
 * @author Osvaldo da Silva Neto
 */

public class Motor {

    /**
     * Faz a soma de dois inteiros
     * @param potencia nos informa a potencia atual do motor x
     * @param tipo informa se motor helice ou turbina
     * @param ligado true caso motor esteja ligado e false caso esteja desligado
     */

    private int potencia;
    private int tipo;
    private boolean ligado=false;


    /**
     * construtor do motor
     *
     * @param tipo nos fornece o tipo de motor 1 para hélice e 2 para turbina
     */
    public Motor(int tipo){
        this.tipo = tipo;
    }

    /**
     * faz a operação de ligar o motor x
     * @return true caso motor seja ligado e false caso ja esteja ligado
     */
    public boolean ligar(){
        if (ligado == false){
            ligado = true;
            potencia = 10;
            return true;
        } else {
            return false;
        }
    }


    /**
     * faz a operação de desligar o motor x
     * @return true caso motor seja desligado e false caso motor ja esteja desligado
     */
    public boolean desligar(){
        if(ligado == true){
            ligado = false;
            this.potencia = 0;
            return true;
        }else{
            return false;
        }
    }

    /**
     * faz a adição ou a subtração de potencia do motor x
     * @param potencia informa a potencia a somar
     * @return true caso a potencia esteja entre o limite de voo e false caso esteja o motor desligado
     *
     */
    public boolean modificarPotencia(int potencia){
        if(ligado==false){
            return false;
        }

        this.potencia = potencia + this.potencia;

        if(this.potencia >= 100){
            this.potencia=100;
            System.out.println("O motor ja está na máxima potência");
            return true;
        }else if(this.potencia<10){
            if(ligado==true) {
                System.out.println("O motor está na potência mínima de voo");
                this.potencia = 10;
                return true;
            }else{
                System.out.println("O motor está desligado");
                this.potencia = 0;
                return false;
            }
        }else{
            return true;
        }
    }

}

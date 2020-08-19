package Poo;

public class Tempo {

    private int hora, minuto, segundo;

    public Tempo(){
        hora = 0;
        minuto = 0;
        segundo = 0;
    }

    public Tempo(int hr){
       if(alteraHora(hr)==false) {
           hora = 0;
           minuto = 0;
           segundo = 0;
       }
    }

    public Tempo(int hr, int min){
        if((alteraHora(hr))==false||(alteraMin(min))==false){
            hora = 0;
            minuto = 0;
            segundo = 0;
        }
    }

    public Tempo(int hr, int min, int seg){

        if((alteraHora(hr)==false)||(alteraMin(min)==false)||(alteraSeg(seg))==false){
            hora = 0;
            minuto = 0;
            segundo = 0;
        }
    }

    public String toString() {
        return hora + ":" + minuto + ":" + segundo;
    }

    public Long tempoSegundos(){
        long duracao;

        duracao = hora * 3600;
        duracao = duracao + (minuto*60);
        duracao = duracao + segundo;

        return duracao;
    }

    public boolean alteraHora(int hr){
        if((hr>=0) && (hr<=24)){
            hora = hr;
            return true;
        }else{
            return false;
        }
    }

    public boolean alteraMin(int min){
        if((min>=0) && (min<=60)){
            minuto = min;
            return true;
        }else{
            return false;
        }
    }

    public boolean alteraSeg(int seg){
        if((seg>=0) && (seg<=60)){
            segundo = seg;
            return true;
        }else{
            return false;
        }
    }



}

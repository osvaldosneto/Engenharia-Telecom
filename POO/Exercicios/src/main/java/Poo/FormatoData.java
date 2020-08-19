package Poo;

public class FormatoData {

    private String data;

    public FormatoData(String date){
        data = date;
    }

    public String mostra(){

        String dd, mm, aa;

        dd = data.substring(0,2);
        mm = data.substring(2,4);
        aa = data.substring(4,6);

        return dd + "/" + mm + "/" + aa;
    }


}

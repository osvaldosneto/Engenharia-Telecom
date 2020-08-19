package poo;

import java.util.HashMap;
import java.util.Map;

public class Email {

    private HashMap<String,String> dados = new HashMap<>();


    public boolean add(String rotulo, String email){

        if(dados.containsKey(rotulo)){
            return false;
        }else{
            dados.put(rotulo, email);
            return true;
        }

    }

    public boolean remove(String rotulo){

        if(dados.containsKey(rotulo)){
            dados.remove(rotulo);
            return true;
        }else{
            return false;
        }

    }

    public boolean update(String rotulo, String email){

        if(dados.containsKey(rotulo)){
            dados.put(rotulo, email);
            return true;
        }else{
            return false;
        }

    }

    public HashMap<String, String> getDados() {
        return dados;
    }

    @Override
    public String toString() {
        String emails = ".";

        for(Map.Entry<String, String> item : dados.entrySet()){
            emails = emails + "\n" + item.getKey() + " : " + item.getValue();
        }

        return emails;
    }
}

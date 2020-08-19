package poo;

import java.util.HashMap;
import java.util.Map;

public class Telefone {

    private HashMap<String,String> dados = new HashMap<>();
/
    public boolean add(String rotulo, String fone){

        if(dados.containsKey(rotulo)){
            return false;
        }else{
            dados.put(rotulo, fone);
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

    public boolean update(String rotulo, String fone){

        if(dados.containsKey(rotulo)){
            dados.put(rotulo, fone);
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

        String telefones = ".";

        for(Map.Entry<String, String> item : dados.entrySet()){
            telefones = telefones + "\n" + item.getKey() + " : " + item.getValue();
        }

        return telefones;
    }


}

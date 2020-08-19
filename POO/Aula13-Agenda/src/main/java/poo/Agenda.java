package poo;

import java.util.ArrayList;

public class Agenda {

    private ArrayList<Pessoa> contatos = new ArrayList<>();

    public void addPessoa(Pessoa pessoa){
        if(!contatos.contains(pessoa)){
            contatos.add(pessoa);
        }
    }

    public boolean removePessoa(String nome, String sobrenome){
        int pessoaindex = -1;

        for (Pessoa item : contatos){
            if (item.getNome().contentEquals(nome) && item.getSobrenome().contentEquals(sobrenome)){
                pessoaindex = contatos.indexOf(item);
                break;
            }
        }

        if(pessoaindex < 0){
            return false;
        }else{
            contatos.remove(pessoaindex) ;
            return true;
        }

    }

    public boolean addTelefone(String rotulo, String fone, int pindex){
        Pessoa p = contatos.get(pindex);
        return p.addTelefone(rotulo, fone);
    }

    public boolean addEmail(String rotulo, String email, int pindex){
        Pessoa p = contatos.get(pindex);
        return p.addEmail(rotulo, email);
    }

    public boolean updateTelefone(String rotulo, String fone, int pindex){
        Pessoa p = contatos.get(pindex);
        return p.updateTelefone(rotulo, fone);
    }

    public boolean updateEmail(String rotulo, String email, int pindex){
        Pessoa p = contatos.get(pindex);
        return p.updateEmail(rotulo, email);
    }

    public boolean removeTelefone(String rotulo, int pindex){
        Pessoa p = contatos.get(pindex);
        return p.removeTelefone(rotulo);
    }

    public boolean removeEmail(String rotulo, int pindex){
        Pessoa p = contatos.get(pindex);
        return p.removeEmail(rotulo);
    }

    public ArrayList<Pessoa> getContatos() {
        return contatos;
    }

    @Override
    public String toString() {
        return "Agenda{" +
                "contatos=" + contatos +
                '}';
    }
}

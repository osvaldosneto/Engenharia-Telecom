package poo;

import java.security.SecureRandom;
import java.time.LocalDate;

public class Pessoa {

    private String nome, sobrenome;
    private LocalDate datanascimento;
    private Telefone telefone;
    private Email email;

    Pessoa(String nome, String sobrenome, Telefone telefone, Email email, LocalDate datanasc){

        this.nome = nome;
        this.sobrenome = sobrenome;
        this.telefone = telefone;
        this.email = email;
        this.datanascimento = datanasc;

    }

    Pessoa(String nome, String sobrenome){

        this.nome = nome;
        this.sobrenome = sobrenome;
        this.telefone = new Telefone();
        this.email = new Email();

    }

    public boolean addTelefone(String rotulo, String numero){

        return telefone.add(rotulo, numero);

    }

    public boolean addEmail(String rotulo, String e){

         return email.add(rotulo, e);

    }

    public boolean removeTelefone(String rotulo){

        return telefone.remove(rotulo);

    }

    public boolean removeEmail(String rotulo){

        return email.remove(rotulo);

    }

    public boolean updateTelefone(String rotulo, String nome){

        return telefone.update(rotulo, nome);

    }

    public boolean updateEmail(String rotulo, String e){

        return email.update(rotulo, e);

    }

    public String getNome() {
        return nome;
    }

    public String getSobrenome() {
        return sobrenome;
    }

    public LocalDate getDatanascimento() {
        return datanascimento;
    }

    public Telefone getTelefone() {
        return telefone;
    }

    public Email getEmail() {
        return email;
    }

    @Override
    public String toString() {

        String fone = telefone.toString();
        String mail = email.toString();


        return "Nome: " + getNome() + "\n" +
                "Sobrenome: " + getSobrenome() + "\n" +
                fone + "\n" +
                mail;

    }
}

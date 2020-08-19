package poo;

import org.junit.Assert;
import org.junit.Test;

import static org.junit.Assert.*;

public class AgendaTest {

    @Test
    public void addPessoa() {



    }

    @Test
    public void removePessoa() {
        Pessoa p1 = new Pessoa("Jairo", "Tadeu");
        Pessoa p2 = new Pessoa("J", "T");
        Pessoa p3 = new Pessoa("Ja", "Ta");
        Pessoa p4 = new Pessoa("Jai", "Tad");

        Agenda ag1 = new Agenda();

        ag1.addPessoa(p1);
        ag1.addPessoa(p2);
        ag1.addPessoa(p3);
        ag1.addPessoa(p4);

        Assert.assertEquals(true, ag1.removePessoa("Jairo", "Tadeu"));
        Assert.assertEquals(true, ag1.removePessoa("J", "T"));
        Assert.assertEquals(false, ag1.removePessoa("Jok", "Tkj"));
        Assert.assertEquals(false, ag1.removePessoa("J", "Tkj"));
        Assert.assertEquals(false, ag1.removePessoa("Jrf", "T"));
        Assert.assertEquals(false, ag1.removePessoa("Jairo", "Tadeu"));
        Assert.assertEquals(true, ag1.removePessoa("Ja", "Ta"));

    }

    @Test
    public void addTelefone() {
    }

    @Test
    public void addEmail() {
        Agenda ag1 = new Agenda();

        Pessoa p1 = new Pessoa("A", "a");
        p1.addEmail("Celular", "4891755501");

        Pessoa p2 = new Pessoa("B", "b");
        p2.addEmail("Celular", "4891755501");

        Pessoa p3 = new Pessoa("C", "c");
        p3.addEmail("Celular", "4891755501");

        Pessoa p4 = new Pessoa("D", "d");
        p4.addEmail("Celular", "4891755501");

        ag1.addPessoa(p1);
        ag1.addPessoa(p2);
        ag1.addPessoa(p3);
        ag1.addPessoa(p4);


        Assert.assertEquals(true, ag1.updateEmail("Celular","00000000",0));
        Assert.assertEquals(true, ag1.updateEmail("Celular","00000000",1));
        Assert.assertEquals(true, ag1.updateEmail("Celular","00000000",2));
        Assert.assertEquals(true, ag1.updateEmail("Celular","00000000",3));
        Assert.assertEquals(false, ag1.updateEmail("Celulare","00000000",3));

    }

    @Test
    public void updateTelefone() {
        Agenda ag1 = new Agenda();

        Pessoa p1 = new Pessoa("A", "a");
        p1.addTelefone("Celular", "4891755501");

        Pessoa p2 = new Pessoa("B", "b");
        p2.addTelefone("Celular", "4891755501");

        Pessoa p3 = new Pessoa("C", "c");
        p3.addTelefone("Celular", "4891755501");

        Pessoa p4 = new Pessoa("D", "d");
        p4.addTelefone("Celular", "4891755501");

        ag1.addPessoa(p1);
        ag1.addPessoa(p2);
        ag1.addPessoa(p3);
        ag1.addPessoa(p4);


        Assert.assertEquals(true, ag1.updateTelefone("Celular","00000000",0));
        Assert.assertEquals(true, ag1.updateTelefone("Celular","00000000",1));
        Assert.assertEquals(true, ag1.updateTelefone("Celular","00000000",2));
        Assert.assertEquals(true, ag1.updateTelefone("Celular","00000000",3));
        Assert.assertEquals(false, ag1.updateTelefone("Celulare","00000000",3));


    }

    @Test
    public void updateEmail() {
        Email e1 = new Email();
        e1.add("email", "oij@jou.com");
        Email e2 = new Email();
        e2.add("email", "oij@jou.com");
        Email e3 = new Email();
        e3.add("email", "oij@jou.com");
        Email e4 = new Email();
        e4.add("email", "oij@jou.com");

        Telefone t1 = new Telefone();
        t1.add("Celular", "4891755501");
        Telefone t2 = new Telefone();
        t2.add("Celular", "4891755502");
        Telefone t3 = new Telefone();
        t3.add("Celular", "4891755503");
        Telefone t4 = new Telefone();
        t4.add("Celular", "4891755504");


    }

    @Test
    public void removeTelefone() {
    }

    @Test
    public void removeEmail() {
    }
}
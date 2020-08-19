package poo;

import org.junit.Assert;
import org.junit.Test;

import static org.junit.Assert.*;

public class PessoaTest {

    @Test
    public void addTelefone() {
        Pessoa p1 = new Pessoa("João", "Francisco");

        Assert.assertEquals(true, p1.addTelefone("celular", "4896587412"));
        Assert.assertEquals(false, p1.addTelefone("celular", "4896587412"));


    }

    @Test
    public void addEmail() {
        Pessoa p1 = new Pessoa("João", "Francisco");

        Assert.assertEquals(true, p1.addEmail("email", "carvalho@var.com"));
        Assert.assertEquals(false, p1.addEmail("email", "carvalho@var.com"));

    }

    @Test
    public void removeTelefone() {
        Pessoa p1 = new Pessoa("Jairo", "Tadeu");

        Assert.assertEquals(false, p1.removeTelefone("celular"));
        p1.addTelefone("celular","1458796353");
        Assert.assertEquals(true, p1.removeTelefone("celular"));
        Assert.assertEquals(false, p1.removeTelefone("celular"));

    }

    @Test
    public void removeEmail() {
        Pessoa p1 = new Pessoa("Jairo", "Tilanga");

        Assert.assertEquals(false, p1.removeEmail("email1"));
        p1.addEmail("email1", "osvaldosneto@hmai.com");
        Assert.assertEquals(true, p1.removeEmail("email1"));
        Assert.assertEquals(false, p1.removeEmail("email1"));

    }

    @Test
    public void updateTelefone() {
        Pessoa p1 = new Pessoa("Jairo", "Tilanga");




    }

    @Test
    public void updateEmail() {
    }
}
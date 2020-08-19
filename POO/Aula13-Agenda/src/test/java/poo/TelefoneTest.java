package poo;

import org.junit.Assert;
import org.junit.Test;

import static org.junit.Assert.*;

public class TelefoneTest {

    @Test
    public void add() {
        Telefone t1 = new Telefone();

        Assert.assertEquals(true, t1.add("Amanda", "Braga"));
        Assert.assertEquals(true, t1.add("tilanda 3", "Braga"));
        Assert.assertEquals(false, t1.add("Amanda", "Braga"));


    }

    @Test
    public void remove() {
        Telefone t1 = new Telefone();

        t1.add("Celular", "4891755524");

        Assert.assertEquals(true, t1.remove("Celular"));
        Assert.assertEquals(false, t1.remove("Celular"));

        t1.add("Celu", "123456789");
        Assert.assertEquals(false, t1.remove("Celur"));
        Assert.assertEquals(true, t1.remove("Celu"));


    }

    @Test
    public void update() {
        Telefone t1 = new Telefone();

        t1.add("Celular", "854796321");

        Assert.assertEquals(true, t1.update("Celular", "12345678"));
        Assert.assertEquals(false, t1.update("casa", "12458796"));


    }
}
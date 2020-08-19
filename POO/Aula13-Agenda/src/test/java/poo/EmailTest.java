package poo;

import org.junit.Assert;
import org.junit.Test;

import static org.junit.Assert.*;

public class EmailTest {
    @Test
    public void add() {
        Email e1 = new Email();

        Assert.assertEquals(true, e1.add("Amanda", "Braga"));
        Assert.assertEquals(true, e1.add("tilanda 3", "Braga"));


    }

    @Test
    public void remove() {
        Email e1 = new Email();

        e1.add("Amanda", "4891755524");

        Assert.assertEquals(true, e1.remove("Amanda"));
        Assert.assertEquals(false, e1.remove("Amanda"));

        e1.add("Amand", "123456789");
        Assert.assertEquals(false, e1.remove("Ama"));
        Assert.assertEquals(true, e1.remove("Amand"));


    }

    @Test
    public void update() {
        Email e1 = new Email();

        e1.add("Amanda", "854796321");

        Assert.assertEquals(true, e1.update("Amanda", "12345678"));
        Assert.assertEquals(false, e1.update("Joana", "12458796"));


    }

}
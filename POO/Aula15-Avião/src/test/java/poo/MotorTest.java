package poo;

import org.junit.Assert;
import org.junit.Test;

import static org.junit.Assert.*;

public class MotorTest {

    @Test
    public void ligar() {
        Motor m1 = new Motor(1);

        Assert.assertEquals(true, m1.ligar());
        Assert.assertEquals(false,m1.ligar());


    }

    @Test
    public void desligar() {

        Motor m1 = new Motor(1);

        m1.ligar();

        Assert.assertEquals(true, m1.desligar());
        Assert.assertEquals(false,m1.desligar());

    }

    @Test
    public void modificarPotencia() {
        Motor m1 = new Motor(1);

        Assert.assertEquals(false, m1.modificarPotencia(50));

        m1.ligar();

        Assert.assertEquals(true, m1.modificarPotencia(0));
        Assert.assertEquals(true, m1.modificarPotencia(90));
        Assert.assertEquals(true, m1.modificarPotencia(100));
        Assert.assertEquals(true, m1.modificarPotencia(-90));
        Assert.assertEquals(true, m1.modificarPotencia(-90));



    }
}
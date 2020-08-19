package poo;

import org.junit.Assert;
import org.junit.Test;

import static org.junit.Assert.*;

public class AviaoTest {

    @Test
    public void ligar() {

        Aviao a1 = new Aviao(2,100,10,5, 1);

        Assert.assertEquals(true, a1.ligar());
        Assert.assertEquals(false, a1.ligar());

    }

    @Test
    public void movimenta() {

    }

    @Test
    public void modificarPotencia() {
        Aviao a1 = new Aviao(2,100,10,5, 1);
        a1.ligar();
        Assert.assertEquals(true,a1.modificarPotencia(15,0));
        Assert.assertEquals(true,a1.modificarPotencia(50));
        Assert.assertEquals(true,a1.modificarPotencia(150));

    }
}
package Poo;

import org.junit.Test;
import org.junit.Assert;

public class TestaTriangulo {

    @Test
    public void testarTriangulo(){

        Triangulo triangulo = new Triangulo();

        Assert.assertEquals("Teste falhou triangulo enviado 10, 1, 2","escaleno", triangulo.tipoDoTriangulo(10,1,2));
        Assert.assertEquals("Teste falhou triangulo enviado 1, 1, 1","escaleno", triangulo.tipoDoTriangulo(1,1,1));
        Assert.assertEquals("Teste falhou triangulo enviado 1, 1, 2" ,"isósceles", triangulo.tipoDoTriangulo(1,1,2));
        Assert.assertEquals("Teste falhou triangulo enviado 1, 2, 2","isósceles", triangulo.tipoDoTriangulo(1, 2, 2));
        Assert.assertEquals("Teste falhou triangulo enviado 1, 2, 1" ,"isósceles", triangulo.tipoDoTriangulo(1,2,1));
        Assert.assertEquals("Valor não confere", "não é um triangulo", triangulo.tipoDoTriangulo(0,10,2));
        Assert.assertEquals("Valor não confere", "não é um triangulo", triangulo.tipoDoTriangulo(10,0,2));
        Assert.assertEquals("Valor não confere", "não é um triangulo", triangulo.tipoDoTriangulo(10,10,0));
        Assert.assertEquals("Valor não confere", "não é um triangulo", triangulo.tipoDoTriangulo(0,0,2));
        Assert.assertEquals("Valor não confere", "não é um triangulo", triangulo.tipoDoTriangulo(0,0,0));
        Assert.assertEquals("Valor não confere", "não é um triangulo", triangulo.tipoDoTriangulo(10,0,0));
        Assert.assertEquals("Valor não confere", "não é um triangulo", triangulo.tipoDoTriangulo(0,10,0));

        Assert.assertEquals("Valor não confere", "não é um triangulo", triangulo.tipoDoTriangulo(100,1,1));
        Assert.assertEquals("Valor não confere", "não é um triangulo", triangulo.tipoDoTriangulo(1,100,1));
        Assert.assertEquals("Valor não confere", "não é um triangulo", triangulo.tipoDoTriangulo(1,1,100));



    }

}

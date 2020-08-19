package Poo;

public class Funcionario {

    public String nome, departamento, dataDeEntrada, rg;
    public long salario;
    public boolean estaNaEmpresa;



    public String getNome() {
        return nome;
    }

    public String getDepartamento() {
        return departamento;
    }

    public String getDataDeEntrada() {
        return dataDeEntrada;
    }

    public String getRg() {
        return rg;
    }

    public long getSalario() {
        return salario;
    }

    public void mostra(){
        FormatoData obj = new FormatoData(dataDeEntrada);
        String dataFormato = obj.mostra();

        System.out.println(dataFormato);

    }

}


/* Modeleumfuncionário. Ele deve ter o nome do funcionário, o departamento onde trabalha, seu salário
(double),a data de entrada no banco(String)e seu RG(String).
Você deve criar alguns métodos de acordo com sua necessidade. Além deles, crie um método
recebeAumento que aumenta o salario do funcionário de acordo com o parâmetro passado como ar-
gumento. Crietambémummétodo calculaGanhoAnual,quenãorecebeparâmetroalgum,devolvendo
ovalordosaláriomultiplicadoporÕó..
Aideiaaquiéapenasmodelar,istoé,sóidentique informaçõessãoimportanteseoqueumfuncionáriofaz.
Desenhe no papel tudo o que um Funcionario tem e tudo que ele faz.*/
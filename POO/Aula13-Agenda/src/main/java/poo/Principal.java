package poo;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Principal {

    public static int verificaUsuario(String n, String s, Agenda ag){
        int indexagenda=-1;
        Agenda agenda = ag;

        for (Pessoa item : agenda.getContatos()) {
            if (item.getNome().contentEquals(n) && item.getSobrenome().contentEquals(s)) {
                indexagenda = agenda.getContatos().indexOf(item);
                break;
            }
        }

        if (indexagenda < 0) {
            System.out.println("Contato inválido.");
            return -1;
        }
        return indexagenda;
    }


    public static void main(String[] args) {

        String opcao = "1";
        Scanner scan = new Scanner(System.in);
        Agenda agenda = new Agenda();

        while (opcao.equals("1")||opcao.equals("2")||opcao.equals("3")||opcao.equals("4")||opcao.equals("5")) {

            System.out.println("\nInforme a alternativa desejada referente ao menu abaixo:");
            System.out.println("1 - Listar os contatos");
            System.out.println("2 - Inserir novo contato");
            System.out.println("3 - Editar contato");
            System.out.println("4 - Apagar contato");
            System.out.println("5 - Mostrar contato");

            opcao = scan.next();

            if (opcao.equals("1")) {

                ArrayList<Pessoa> lista = agenda.getContatos();

                for(int i=0; i<lista.size(); i++){
                    Pessoa p = agenda.getContatos().get(i);
                    System.out.println("------------------------------------------------------------");
                    System.out.println(p.toString() + "\n");
                }

            } else if (opcao.equals("2")) {

                String op = "S";
                System.out.println("Informe o nome e sobrenome:");
                String nome = scan.next();
                String sobrenome = scan.next();
                Pessoa pessoa = new Pessoa(nome, sobrenome);

                while (op.equals("S") || op.equals("s")) {
                    System.out.println("Informe o rotulo e o telefone:");
                    String rotulo = scan.next();
                    String fone = scan.next();
                    pessoa.addTelefone(rotulo, fone);
                    System.out.println("Deseja adicionar outro rotulo para telefone 'S' ou 'N':");
                    op = scan.next();
                }

                op = "S";

                while (op.equals("S") || op.equals("s")) {
                    System.out.println("Informe o rotulo e o email:");
                    String rotulo2 = scan.next();
                    String email = scan.next();
                    pessoa.addEmail(rotulo2, email);
                    System.out.println("Deseja adicionar outro rotulo para email 'S' ou 'N':");
                    op = scan.next();
                }

            agenda.addPessoa(pessoa);

            } else if (opcao.equals("3")) {

                //Editar contato
                int indexagenda=-1;
                String rotulo = null;
                String telefone = null;
                String email = null;

                while(indexagenda<0) {
                    System.out.println("Informe o nome e sobrenome do contato:");
                    String nome = scan.next();
                    String sobrenome = scan.next();
                    indexagenda = verificaUsuario(nome, sobrenome, agenda);
                }

                System.out.println("Digite:");
                System.out.println("1 - Alterar telefone");
                System.out.println("2 - Alterar email");
                System.out.println("3 - Adicionar rotulo");
                System.out.println("4 - Excuir rotulo");
                String op = scan.next();

                if(op.equals("1")){
                    System.out.println("Informe o rotulo e telefone:");
                    rotulo = scan.next();
                    telefone = scan.next();
                    while(true) {
                        if (agenda.updateTelefone(rotulo, telefone, indexagenda)) {
                            break;
                        }
                        System.out.println("Rótulo inexistente, informe um rótulo válido:");
                        rotulo = scan.next();
                    }
                } else if (op.equals("2")) {
                    System.out.println("Informe o rotulo e email:");
                    rotulo = scan.next();
                    email = scan.next();
                    while(true) {
                        if(agenda.updateEmail(rotulo, email, indexagenda)){
                            break;
                        }
                        System.out.println("Rótulo inexistente, informe um rótulo válido:");
                        rotulo = scan.next();
                    }
                } else if (op.equals("3")) {
                    System.out.println("Digite '1' para rotulo telefone ou '2' para rotulo email");
                    String opca = scan.next();

                    if(opca.equals("1")){
                        System.out.println("Informe o rótulo e o telefone a adicionar:");
                        rotulo = scan.next();
                        telefone = scan.next();
                        agenda.addTelefone(rotulo, telefone, indexagenda);
                    } else {
                        System.out.println("Informe o rótulo e o email a adicionar:");
                        rotulo = scan.next();
                        email = scan.next();
                        agenda.addEmail(rotulo, email, indexagenda);
                    }
                } else {
                    System.out.println("Digite '1' para rotulo telefone ou '2' para rotulo email:");
                    String opca = scan.next();
                    if (opca.equals("1")) {
                        System.out.println("Informe o rótulo do telefone a excluir:");
                        rotulo = scan.next();
                        while (true) {
                            if (agenda.removeTelefone(rotulo, indexagenda)) {
                                break;
                            }
                            System.out.println("Rótulo inválido, informe rótulo:");
                            rotulo = scan.next();
                        }
                    } else {
                        System.out.println("Informe o rótulo do email a excluir:");
                        rotulo = scan.next();
                        while (true) {
                            if (agenda.removeEmail(rotulo, indexagenda)) {
                                break;
                            }
                            System.out.println("Rótulo inválido, informe rótulo:");
                            rotulo = scan.next();
                        }
                    }
                }

            } else if (opcao.equals("4")) {
                System.out.println("Informe o nome e sobrenome:");
                String nome = scan.next();
                String sobrenome = scan.next();

                if (agenda.removePessoa(nome, sobrenome)) {
                    System.out.println("Contato removido.");
                } else {
                    System.out.println("Contato inexistente");
                }

            } else {
                //mostrar contato
                int indexagenda=-1;

                while(indexagenda<0) {
                    System.out.println("Informe o nome e sobrenome do contato a exibir:");
                    String nome = scan.next();
                    String sobrenome = scan.next();
                    indexagenda = verificaUsuario(nome, sobrenome, agenda);
                }

                Pessoa p = agenda.getContatos().get(indexagenda);
                System.out.println(p.toString());

            }
        }
    }
}

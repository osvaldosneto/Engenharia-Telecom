package Poo;

public class Robo {

    private int area, x, y;
    private char frente;


    public Robo(int tam, int x1, int y1, char front){
        area = tam;
        x = x1;
        y = y1;
        frente = front;
    }

    public void rotaciona(char a){

        switch (a){
            case 'E':
                switch (frente){
                    case 'S':
                        frente = 'L';
                        break;
                    case 'L':
                        frente = 'N';
                        break;
                    case 'O':
                        frente = 'S';
                        break;
                    case 'N':
                        frente = 'O';
                        break;
                }break;

            case 'D':
                switch (frente){
                    case 'S':
                        frente = 'O';
                        break;
                    case 'L':
                        frente = 'S';
                        break;
                    case 'O':
                        frente = 'N';
                        break;
                    case 'N':
                        frente = 'L';
                        break;
                }break;
            default:
                break;
        }

    }

    public void movimenta(){

        if(frente == 'N'){
            y++;
            if(y>area){
                y=area;
            }
        }else if(frente == 'S'){
            y--;
            if(y<0){
                y=0;
            }
        }else if(frente == 'L'){
            x++;
            if(x>area){
                x=area;
            }
        }else if(frente == 'O'){
            x--;
            if(x<0){
                x=0;
            }
        }
    }

    public String toString() {
        return "Posição: " + x + "; " + y + "\nFrente:" + frente + "\n";
    }
}

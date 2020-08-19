//#include <cstdlib>
//#include <queue> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//#include <iostream>
#include <unistd.h>

int main(){
    
    int ret;
    
    ret = fork();
    
    if(ret < 0){
        printf("erro na criação do filho \n");
    } if(ret == 0){
        printf("processo filho criado - %i \n", getpid());
        
        //criação dos netos
        for (int i=0; i<3; i++){
            int neto = fork();
            if(neto<0){
                printf("erro na criação do neto \n");
            }if(neto == 0){
                printf("processo neto criado - %i - pid pai - %i\n", getpid(), getppid());
				exit(1);
            }
            for (int j=0; j<3; j++){
                    wait(NULL);
            }
        }
		exit(1);      
    } else {

		printf("processo filho criado - %i \n", getpid());
		for (int i=0; i<3; i++){
            int neto = fork();
            if(neto<0){
                printf("erro na criação do neto \n");
            }if(neto == 0){
                printf("processo neto criado - %i - pid pai - %i\n", getpid(), getppid());
				exit(1);
            }
            for (int j=0; j<3; j++){
                    wait(NULL);
            }
        }
		for (int j=0; j<3; j++){
                    wait(NULL);
        }
    }
        
}
    
    
    
    
    
    
    


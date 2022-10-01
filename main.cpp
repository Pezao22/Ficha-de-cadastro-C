/*
BASE PARA O PROJETO, CRIAR UM MENU COM AS SEGUINTES OPCOES

1 - inserir contato
2 - remover contato
3 - pesquisar um contato pelo nome
4 - listar todos contatos existentes
5 - listar contatos iniciam com uma dada letra
6 - imprimir os aniversarios do mes
7 - sair

Os arquivos serão salvos como binarios e ao iniciar o programa os dados binarios devem ser incluidos novamente ao programa
desta forma criando uma agenda completa.

*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

typedef struct data DATA;

struct data {
    int dia;
    int mes;
    int ano;
};

typedef struct contato CONTATO;
struct contato
{
    char nome[30];
    char fone[15];
    DATA aniv;
};

void cabecalho();
void inputData();
void remover();
void listar();
void pesquisar();
void pesquisarletra();
void anivMes();

main(){
    setlocale(LC_ALL,"Portuguese");
    int opcao;
    
    do
    {
        cabecalho();
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Pesquisar pelo nome\n");
        printf("4 - Listar todos\n");
        printf("5 - Listar por uma inicial\n");
        printf("6 - Imprimir aniversariantes do mes\n");
        printf("7 - Sair\n\n");
        printf("Escolha uma opaçao: ");
        scanf("%d",&opcao);


        switch (opcao){

            case 1:
            // inserir
            	inputData();
            break;
            
            case 2:
            // remover
            remover();
			break;

            case 3:
            //pesquisar
            	pesquisar();
            break;

            case 4:
            //listar todos
            	listar();
            break;

            case 5:
            //listar inicial
            pesquisarletra();
            break;

            case 6:
            // imprimir aniversariantes
            	anivMes();
            break;

            case 7:
                printf("Obrigado por sua visita!\n");
                getch();
            break;
            
            default:
                printf("Opcao invalida !!\n");
                getch();
            break;
        }
    } while (opcao != 7);
}

void cabecalho(){
    system("cls");
    system("color A");
    printf("--------------------------------------------------\n");
    printf("AGENDA ELETRONICA\n");
    printf("                                                          Desenvolvido Por: Pezao\n");
    printf("--------------------------------------------------\n\n");
}

void inputData(){
    FILE* arquivo;
    CONTATO ctt;

    arquivo = fopen("arquivo.txt","ab");

    if (arquivo == NULL){
        printf("Problema na abertuda do arquivo\n");
    }
    else{
        do{
        	cabecalho();
            fflush(stdin);
            printf("Digite o nome: ");
            gets(ctt.nome);

            fflush(stdin);
            printf("Digite o fone: ");
            gets(ctt.fone);

            printf("Digite o aniversario: ");
            scanf("%d %d %d",&ctt.aniv.dia,&ctt.aniv.mes,&ctt.aniv.ano);

            fwrite(&ctt,sizeof(CONTATO), 1, arquivo);

            printf("Deseja continuar (s/n)?");


        }while(getche() == 's');

        fclose(arquivo);        
    }
}
void remover(){
	FILE* arquivo;
	FILE* temp;
	CONTATO ctt;
	
	char nome[30];
	arquivo = fopen("arquivo.txt","rb");//abrir em modo rb leitura binaria
	temp = fopen("tmp.txt","wb");//abrir em modo wb ele limpa e grava binario
	if(arquivo==NULL&&temp==NULL){
		printf("Problemas na abertura do arquivo!\n");
		getch();
	}else{
		cabecalho();
		fflush(stdin);
		printf("Digite o nome a deletar: ");
		gets(nome);
		while(fread(&ctt,sizeof(CONTATO),1,arquivo)==1){
			if(strcmp(nome,ctt.nome)==0){
				printf("Nome: %s\n",ctt.nome);
				printf("Fone: %s\n",ctt.fone);
				printf("Aniversário: %d/%d/%d\n",ctt.aniv.dia,ctt.aniv.mes,ctt.aniv.ano);
				printf("-------------------------------------------------\n");
			}else{
				fwrite(&ctt,sizeof(CONTATO),1,temp);//gravando os dados no arquivo temp
			}
		}
	fclose(arquivo);//fechar o arq
	fclose(temp);//fechar o temp
	fflush(stdin);
	printf("Deseja deletar (s/n)? ");
	
	if(getche()=='s'){
   //vamos remover o arquivo "agenda.txt" e renomear o arquivo "tmp.txt" para "agenda.txt"
		if(remove("arquivo.txt")==0&&rename("tmp.txt","arquivo.txt")==0){//verifica se as operacoes foram realizadas com sucesso!
			printf("\nOperacao realizada com sucesso!");
		}else{
			remove("tmp.txt");//remover o arquivo tmp se acondicao foi "n" na hora de deletar
			}
		}
		
	fclose(temp);
	fclose(arquivo);
	getch();
	
	} 
}

void listar(){
	FILE* arquivo;
    CONTATO ctt;

    arquivo = fopen("arquivo.txt","rb");
    
	cabecalho();
    if (arquivo == NULL){
        printf("Problema na abertuda do arquivo\n");
    }
    else{
    	while( fread(&ctt, sizeof(CONTATO), 1,arquivo)==1){
    		printf("Nome: %s\n",ctt.nome);
    		printf("Fone: %s\n",ctt.fone);
    		printf("Aniversario: %d/%d/%d\n",ctt.aniv.dia,ctt.aniv.mes,ctt.aniv.ano);
    		printf("----------------------------------------------\n\n");
		}
    	
	}
	fclose(arquivo);
	getch();
}

void pesquisar(){
	FILE* arquivo;
	CONTATO ctt;
	char nome[30];
	
	arquivo = fopen("arquivo.txt","rb");
	
	cabecalho();
    if (arquivo == NULL){
        printf("Problema na abertuda do arquivo\n");
    }
    else{
    	
    	fflush(stdin);
    	printf("Digite o nome pesquisar: ");
    	gets(nome);
    	
    	while( fread(&ctt, sizeof(CONTATO), 1, arquivo)==1){
    		if(strcmp(nome, ctt.nome )==0 ){
    		
	    		printf("\nNome: %s\n",ctt.nome);
	    		printf("Fone: %s\n",ctt.fone);
	    		printf("Aniversario: %d/%d/%d\n",ctt.aniv.dia,ctt.aniv.mes,ctt.aniv.ano);
	    		printf("----------------------------------------------\n\n");    		
    		}
		}		    	
	}	
	fclose(arquivo);
	getch();
}

void pesquisarletra(){
	FILE* arquivo;
	CONTATO ctt;
	char nome[30];
	
	arquivo = fopen("arquivo.txt","rb");
	
	cabecalho();
    if (arquivo == NULL){
        printf("Problema na abertuda do arquivo\n");
    }
    else{
    	
    	fflush(stdin);
    	printf("Digite a letra a pesquisar: ");
    	gets(nome);
    	
    	while( fread(&ctt, sizeof(CONTATO), 1, arquivo)==1){
    		if(ctt.nome[0]==nome[0]){
    		
	    		printf("\nNome: %s\n",ctt.nome);
	    		printf("Fone: %s\n",ctt.fone);
	    		printf("Aniversario: %d/%d/%d\n",ctt.aniv.dia,ctt.aniv.mes,ctt.aniv.ano);
	    		printf("----------------------------------------------\n\n");    		
    		}
		}		    	
	}	
	fclose(arquivo);
	getch();
}

void anivMes(){
	FILE* arquivo;
	CONTATO ctt;
	
	arquivo = fopen("arquivo.txt","rb");
	cabecalho();
	if (arquivo == NULL){
        printf("Problema na abertuda do arquivo\n");
    }
    else{
    	int mes;
    	
    	printf("Digite o mes: ");
    	scanf("%d",&mes);
    	
    	while( fread(&ctt, sizeof(CONTATO), 1, arquivo)==1){
    		if(mes == ctt.aniv.mes){
    			printf("\nNome: %s\n",ctt.nome);
	    		printf("Fone: %s\n",ctt.fone);
	    		printf("Aniversario: %d/%d/%d\n",ctt.aniv.dia,ctt.aniv.mes,ctt.aniv.ano);
	    		printf("----------------------------------------------\n\n");      			
			}    	
		}    	
	}	
	fclose(arquivo);	
	getch();
}


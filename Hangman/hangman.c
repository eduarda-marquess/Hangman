#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "forca.h"
#include <time.h>
#include <stdlib.h>


char palavraSecreta[20];
char chutes[26];
int chutesDados = 0;


//Pequena recepção do jogo 
void abertura(){
    printf("/*********************************/\n");
    printf("/      BEM VINDO AO HANGMAN       /\n");
    printf("/********************************/\n\n");

}

//Recebe o chute do jogador e armazena o chute 
void chuta(){
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
    chutesDados++;
}

//Verifica se a letra esta na palavra
int jaChutou(char letra) {
	int achou = 0;
	for(int j = 0; j < chutesDados; j++) {
		if(chutes[j] == letra) {
			achou = 1;
			break;
		}

	}
    return achou;
}

//preenche com a letra que foi achada 
void desenhaForca(){

    
    printf("Você ja deu %d chutes\n", chutesDados);

    for(int i=0; i < (int)strlen(palavraSecreta); i++){
        if(jaChutou(palavraSecreta[i])){
            printf("%c ", palavraSecreta[i]);
        }else{
            printf("_ ");
        }
    }
    
    printf("\n");

}


//Escolhe as palavras randomicamente atraves do arquivo palavras.txt
void escolhePalavra(){
    
    //devolve um ponteiro de um arquivo
    //abre o arquivo palavras.txt
    FILE* f = fopen("palavras.txt", "r");

    //verifica se o arquivo não retorna, então envia uma mensagem ao usuário.
    if(f == 0){
        printf("Desculpe, banco de dados não disponivel\n\n");
        exit(1);
    }
    //Aqui ele lê a quantidade de palavras do arquivo, que é dado na primeira linha.
    int qtdDePalavras;
    fscanf(f, "%d", &qtdDePalavras);

    //Calculo do numero randomico: de 0 a quant de palavras 
    srand(time(0));
    int randomico = rand() % qtdDePalavras;


    //Laço para escolher a palavra aleatoria do arquivo e ler ela 
    for(int i=0; i <= randomico; i++){
        fscanf(f, "%s", palavraSecreta);
    }

    //fecha o arquivo 
    fclose(f);
}

//lmita as chances de tentativas do jogardor ao saber quantos erros ele teve.
int enforcou(){
    int erros = 0;

    for(int i = 0; i < chutesDados; i++){

        int existe = 0;

        for(int j = 0; j < (int)strlen(palavraSecreta); j++){
            if(chutes[i] == palavraSecreta[j]){
                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    printf("Tentativas restantes: %d\n", 5 - erros);

    return erros >= 5;
}


//verifica se o jogador ganhou
int ganhou(){
    for(int i = 0; i < (int)strlen(palavraSecreta); i++){
        if(!jaChutou(palavraSecreta[i])){
            return 0;
        }
    }
    return 1;
}


int main(){

    setlocale(LC_ALL, "portuguese");
    
    abertura();
    escolhePalavra();

    do{
        desenhaForca();
        chuta();

    }while(!ganhou() && !enforcou());

    if(ganhou()){
        printf("\n-----YOU WIN!-----\n");
    }else{
        printf("-----YOU LOSE!-----\n");
    }
    printf("A palavra era: %s\n", palavraSecreta);
    return 0;
}
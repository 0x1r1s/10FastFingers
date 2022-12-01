#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define NOMBRE_MOTS_MAX 1000000

bool verifMot(char *essai, char *mot);
void afficheMessage();
char * readFile(FILE *fichier);
int parseContenu(char * dict[], char * content, int sizeFile);
int getLength(FILE *fichier);

int main(int argc, char *argv[]){
    FILE *fichier=fopen("ods6.txt","r");
    int score=0;
    int sizeFile=getLength(fichier);
    char *dict[NOMBRE_MOTS_MAX]={NULL};
    char * content=NULL;
    content=readFile(fichier);
    int nbLignes=parseContenu(dict, content, sizeFile);
    fclose(fichier);
    char answer[20]={0};
    int indice;
    srand(time(NULL));
    while(1){
        int indice=rand()%nbLignes;
        //printf("%d", indice);
        strcpy(answer, dict[indice]);
        for(int i=0;i<strlen(answer);i++){
            answer[i]=tolower(answer[i]);
        }
        printf("le mot a copier est:%s\n", answer);
        char *input=NULL;
        input=malloc(strlen(answer)*sizeof(char));
        if(input==NULL){
            exit(0);
        }
        scanf("%s", input);
        if(verifMot(answer, input)==false){
            break;
        }
        free(input);
        score++;
    }
    printf("your score is:%d\n",score);
    free(content);
    return 0;
}




bool verifMot(char *essai, char *mot){
    if(strcmp(essai, mot)==0){
        return true;
    }
    else{
        printf("\nWrong guess\n");
        return false;
    }
}

char * readFile(FILE *fichier){
    char *contenu=NULL;
    int sizeFile=getLength(fichier);
    contenu=(char *)malloc(sizeFile*sizeof(char));
    if(contenu==NULL){
        exit(-1);
    }
    fread(contenu, sizeof(char), sizeFile, fichier);
    return contenu;
}


void afficheMessage(){
}

int parseContenu(char * dict[], char * content, int sizeFile){
    int nbLignes=0;
    dict[0]=&(*content);
    for(int i=1;i<sizeFile;i++){
        if(*(content+i)=='\n'){
            *(content+i)='\0';
            dict[nbLignes+1]=&(*(content+i+1));
            nbLignes++; 
        }
    }
    return nbLignes;
}

int getLength(FILE *fichier){
    fseek(fichier, 0L, SEEK_END);
    int sizeFile=ftell(fichier);
    fseek(fichier,  0L , SEEK_SET);
    return sizeFile;
}
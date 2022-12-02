#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#define NOMBRE_MOTS_MAX 1000000

void genereTexte(char * listeMots[], int nbMots);
char * readFile(FILE *fichier);
int parseContenu(char * dict[], char * content, int sizeFile);
int getLength(FILE *fichier);

void genereTexte(char * listeMots[], int nbMots){
    FILE *fichier=fopen("ods6.txt","r");
    int sizeFile=getLength(fichier);
    char *dict[NOMBRE_MOTS_MAX]={NULL};
    char * content=NULL;
    content=readFile(fichier);
    int nbLignes=parseContenu(dict, content, sizeFile);
    srand(time(NULL));
    for (int i=0;i<nbMots;i++){
        int indice=rand()%nbLignes;
        listeMots[i]=dict[indice];
    }
    fclose(fichier);
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
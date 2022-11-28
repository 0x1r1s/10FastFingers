#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TAILLE_MAX_MOT 100
#define NOMBRE_LIGNES_MAX 1000

bool verifMot(char *essai, char *mot);
void afficheMessage();
void readFile(char *nomFichier, char * dict[]);

int main(int argc, char *argv[]){
    int score=0;
    char answer[]="avon";
    char *dict[NOMBRE_LIGNES_MAX]={NULL};
    readFile("dictionnaire.txt",dict);
    printf("%s",dict[3]);
    while(1){
        printf("%s\n", answer);
        char *input=NULL;
        input=malloc(strlen(answer)*sizeof(char));
        if(input==NULL){
            exit(0);
        }
        scanf("%s", input);
        //printf("Your guess is:%s", input);
        if(verifMot(answer, input)==false){
            printf("your score is:%d",score);
            return 0;
        }
        free(input);
        score++;
    }
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

void readFile(char *nomFichier, char * dict[]){
    FILE *fichier=fopen(nomFichier,"r");
    char chaine[TAILLE_MAX_MOT]="";
    if (fichier!=NULL){
        int i=0;
        while (fgets(chaine, TAILLE_MAX_MOT, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            dict[i]=chaine;
            printf("%p", *dict[i]);
            printf("%d", i);
            printf("%s", dict[i]); // On affiche la chaîne qu'on vient de lire
            i++;
        }
        fclose(fichier);
    }
}

void afficheMessage(){
}
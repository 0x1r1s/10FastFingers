#ifndef NGUI_H_
#define NGUI_H_

void genereTexte(char * listeMots[], int nbMots);
char * readFile(FILE *fichier);
int parseContenu(char * dict[], char * content, int sizeFile);
int getLength(FILE *fichier);

#endif //NGUI_H_
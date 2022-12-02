#include <stdio.h>
#include <ncurses.h>
#include <ctype.h>
#include "ngui.h"
#include <string.h>
#include <time.h>
#include <math.h>
#define NOMBRE_MOTS 20
#define DUREE_TEST 60

int main(){
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);

    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    timeout(1000);
    int countdown=1;
    int gameState=1, ch=0;
    float wpm=0;
    char buffer[100]={0}, *s=buffer;
    char *listeMots[NOMBRE_MOTS]={NULL};
    genereTexte(listeMots, NOMBRE_MOTS);

    int indice=0 , score=1;
    int tableau[NOMBRE_MOTS]={3};
    time_t init=time(NULL);
    while(gameState!=0 && countdown>0){
        erase();    
        countdown=DUREE_TEST-difftime(time(NULL), init);
        if(countdown!=DUREE_TEST){
            wpm=(float)score/(DUREE_TEST-countdown);
        }
        else
            wpm=5;
        mvprintw(0, 0, "countdown: %d  score:%d WPM:%f",countdown, score, wpm);
        move(1, 0);
        if(indice>=NOMBRE_MOTS){
            genereTexte(listeMots, NOMBRE_MOTS);
            indice=0;
            for(int h=0;h<NOMBRE_MOTS;h++){
                tableau[h]=3;
            }
            
        }
        for (int i=0;i<NOMBRE_MOTS;i++){
            attron(COLOR_PAIR(tableau[i]));
            printw("%s ", listeMots[i]);
            attroff(COLOR_PAIR(tableau[i]));
            }
        mvprintw(4,0, "answer:%s", buffer);
        refresh();
        if((ch=getch())!=ERR){
            if(ch==' '){
                if(strcmp(buffer,listeMots[indice])==0){
                    score++;
                    tableau[indice]=1;
                }
                else{
                    tableau[indice]=2;
                }
                indice++;
                *s = 0;
                sscanf(buffer, "%d", &gameState);
                s = buffer;
                *s = 0;
            }
            else if(ch==KEY_BACKSPACE){
                if(s>buffer)
                    *--s=0;
            }
            else if(ch=='\n'){

            }

            else if(s-buffer<(long)sizeof buffer-1){
                *s++=ch;
                *s=0;
            }
        }
    }
    endwin();
    return 0;
}
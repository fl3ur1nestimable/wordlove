#include "struct.h"
#include "mot.h"
#include "arbre.h"
#include "pattern.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>

int main(){
    //int taille[5][2];
    /*
    for(int i = 0;i<5;i++){
        taille[i][0]=i+4;
        arbre_mots *arbre = arbre_init();
        lecture_fichier(arbre,i+4);
        char str[10] = "";
        mot *m = mot_create(str);
        time_t t0 = time(NULL);
        mot_generate_best(arbre,m,i+4);
        time_t t1 = time(NULL);
        int n = arbre->nb_mots;
        unsigned long sec = (unsigned long)difftime(t1,t0);
        printf("Nombre de mots : %d, Temps pour avoir le meilleur mot : %ld\n",n,sec);
        printf("Meilleur mot : %s\n",m->val);
        taille[i][1]=n;
        arbre_destroy(arbre);
        mot_destroy(m);
    
    }
    */
    FILE* f;
    FILE* f2;

    char liste_premiers_mots[][10] = {"RAIE", "TAIRE","TRAINE","NOTAIRE","SOUCIANT"};
    char *liste_noms_fichiers[] = {"../test4.txt","../test5.txt","../test6.txt","../test7.txt","../test8.txt"};
    int n[]={1672,4007,7146,10028,11657};
    for (int t = 4;t<9;t++){
        f=fopen("../liste_78k.txt","r");
        f2 = fopen(liste_noms_fichiers[t-4],"w");
        char c[20];
    
        double perf = 0;
        while (fgets(c,sizeof(c),f)!=NULL)
        {   
            c[strlen(c)-1]='\0';
            if ((int)strlen(c)==t){
                arbre_mots *arbre = arbre_init();
                lecture_fichier(arbre,t);
                int essais = 1;
                //printf("%s\n",liste_premiers_mots[t-4]);
                char str[12];
                strcpy(str,liste_premiers_mots[t-4]);
                mot *m = mot_create(str);
                
                
                while(strcmp(c,m->val)!=0){
                    pattern *pat = pattern_from_mot(m->val,c,t);
                    
                    //pattern_print(pat);
                    //printf("GUESS : %s / MOT solution : %s\n",m->val,c);
                    arbre_update(arbre,m,pat);
                    essais++;
                    mot_generate_best(arbre,m,t);
                    pattern_destroy(pat);
                }
                //printf("GUESS : %s / MOT solution : %s / ESSAIS : %d\n",m->val,c,essais);
                mot_destroy(m);
                fprintf(f2,"%s %d\n",c,essais);
                perf += essais;
                arbre_destroy(arbre);
                
            } 
        }
        printf("%f\n",perf/(double)n[t-4]);
        fprintf(f2,"%f\n",perf/(double)n[t-4]);

        fclose(f2);
        fclose(f);
    }
    

    return EXIT_SUCCESS;

}

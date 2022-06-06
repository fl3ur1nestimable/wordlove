#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "pattern.h"
#include "arbre.h"
#include "mot.h"
#include <stdlib.h>
#include <string.h>

bool is_in_possibilities(int proposition, int taille){
    int nbr_possibilites = pow(3,taille);
    int possibilities[nbr_possibilites];
    int i;
    for(i=0;i<nbr_possibilites;i++){
        possibilities[i]=base3(i);
        if(proposition==possibilities[i]){
            return 1;
        }
    }
    return 0;
}

int get_word_len(){
    FILE*f;
    f=fopen("../wsolf.txt","r");
    char c[5];
    fgets(c,sizeof(c),f);
    int len = atoi(c);
    if ( len < 4 || len > 10){
        printf("Invalid length\n");
        exit(EXIT_FAILURE);
    }
    fclose(f);
    return len;
}

int main(){
    int taille = get_word_len();
    int nb_essais;
    printf("Taille du mot : %d\n", taille);
    printf("Entrez le nombre d'essais : \n");
    scanf("%d",&nb_essais);
    int guess[taille];
    int power = pow(3,taille);
    int possibilites[power];
    bool not_win = true;
    int i = nb_essais;


    printf("Vos réponse doivent être de la forme xxx où il y'a autant de x que la taille du mot et où x vaut 0,1, ou 2 \n");
    printf("0 sont les lettres n'étant pas dans le mot, 2 les lettres bien placées et 1 les lettres mal placées \n");
    while(i!=0 && not_win){
        char* mot_propose = "oui"; // cela sera égal à la fonction qui renvoit la meilleure proposition de mots
        printf("%s",mot_propose);
        int somme = 2*taille;
        int result;
        printf("Entrez le résultat pour le mot : \n");
        scanf("%d",&result);

        if(result==-1){
            printf("Arrêt");
            return 0;
        }
        
        while(!(is_in_possibilities(result,taille))){
            printf("Votre mot n'est pas dans les possibilités : \nEntrez le résultat pour le mot : \n");
            scanf("%d",&result);
            if(result==-1){
                printf("Arrêt");
                return 0;
            }
        }
        
        guess[0]=result*pow(10,-(taille-1));
        somme = somme - guess[0];
        int j;
        int a = result;
        for(j=1;j<taille;j++){
            a=a-guess[j-1]*pow(10,taille-j);
            guess[j]=a*pow(10,-(taille-1-j));
            somme = somme - guess[j];
            printf("%d \n",guess[j]);
        }

        // il faut envoyer le tableau guess a la fonction

        i=i-1;

        if(somme == 0){
            printf(" Trouvé ! ");
            not_win = false;
        }
        else{
            printf("Sorry");
        }
    }
    return 0;  
}

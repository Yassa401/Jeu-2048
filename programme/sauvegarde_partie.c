#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include "jeu_initiale.h"
#include "sauvegarde_partie.h"

/*
 * fonction qui récupère les valeurs des cases , le score et le nom du joueur à partir du fichier de sauvegarde dans le dossier parties_sauvegardees
 */
void recup_partie (int n,char *  str,int mat[NB_MAX][NB_MAX], int *score, char *nom_joueur){
    FILE* fichier = NULL;
    int i,j, valeur;
    char str_tmp[50] = "NULL";

    valeur = 0;
    
    sprintf(str_tmp,"parties_sauvegardees/%s",str);

    fichier = fopen(str_tmp, "r");
    if( fichier == NULL){
        fprintf(stderr,"Erreur dans l'ouverture du fichier !\n");
        exit(EXIT_FAILURE);
    }

    if (fscanf(fichier,"%s", nom_joueur) != 1){
        fprintf(stderr,"Erreur dans l'ouverture du fichier !\n");
        return ;
    };
    
    if (fscanf(fichier,"%d", &valeur) != 1){
        fprintf(stderr,"Erreur dans l'ouverture du fichier !\n");
        return ;
    };
    
    *score = valeur ;
    for (i = 0; i<n; i++){
        for (j = 0; j<n; j++){
            if (fscanf(fichier,"%d", &valeur) != 1){
                fprintf(stderr,"Erreur dans l'ouverture du fichier !\n");
                return ;
            };
            mat[i][j] = valeur ;
        }
    }    
}

/*!
 * fonction qui sauvegarde le nouveau meilleur score dans le fichier "meilleur_score.txt" s'il est atteint
 */
void sauvegarde_score(int meilleur_score){

  FILE* fichier=NULL;

  fichier=fopen("meilleur_score.txt","w+");

  if(fichier==NULL){

    printf("impossible d'ouvrir le fichier\n");

    exit(EXIT_FAILURE);

  }

  fprintf(fichier,"%d",meilleur_score);;

  fclose(fichier);
  
  return ;
}
void meilleur(int *meilleur_score,int score_actuelle){

    if(score_actuelle > *meilleur_score){
        *meilleur_score = score_actuelle ;
        sauvegarde_score( *meilleur_score ) ;
    }
    return ;
}

/*!
 * récupere le meilleur score au début de chaque partie pour pouvoir l'afficher
 */
void recup_meilleure_score(int *meilleur_score){
    int valeur;
    FILE* fichier = NULL;

    valeur = 0;
    fichier = fopen("meilleur_score.txt","r");
    if ( fichier == NULL){
        printf("impossible d'ouvrir le fichier \n");
        return ;
    }
    if ( fscanf( fichier, "%d" , &valeur ) != 1){
        printf("impossible de récuperer le meilleur score !");
    }
    printf("le score récuperé est %d \n", valeur);
    
    *meilleur_score = valeur;
  
    fclose(fichier);
}

/*!
 * fonction qui sauvegarde la partie dans un fichier .txt dans le dossier "parties_sauvegardees"
 * la sauvegarde comprend : nom_joueur , score et les valeurs de la matrice de jeu
 */
void sauvegarde_partie(int n, int mat[NB_MAX][NB_MAX], int score, char* nom_joueur){
    int i,j ;
    FILE* fichier= NULL;
    char fichier_str[50];
    
    /*!
     * recupération du nom du joueur dans l'argument text
     * nommer le fichier où la partie sera sauvegardé nom_joueur.txt
     */
    sprintf(fichier_str,"./parties_sauvegardees/%s.txt",nom_joueur);
    fichier= fopen(fichier_str,"w+");

    if(fichier==NULL){
        printf("impossible d'ouvrir le fichier \n");
        exit(EXIT_FAILURE);
    }

    fprintf(fichier,"%s\n",nom_joueur);
    fprintf(fichier,"%d \n",score);

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            fprintf(fichier,"%d ",mat[i][j]);
        }
        fprintf(fichier,"\n");
    }
    fclose(fichier);

    return ;
}


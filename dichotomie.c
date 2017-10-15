/* ======================================================================
 *
 * Dichotomy guessing game
 *
 * Version: 1.0 
 * Author: VZ Nigolian(EPFL, 2017)
 * ======================================================================
 */

#include <stdio.h>

/* ======================================================================
 * Asks for two numbers
 */
void demander_nombres(int* a, int* b);

/* ======================================================================
 * Given a lower- and upper-limit, guesses the number that the user
 * was thinking of using dichotomy 
 */
int trouver_nombre_avec_limites(int gauche,int droite);

/* ======================================================================
 * Guesses the number the user was thiking of without boundary numbers
 * Used as an argument-less mask to trouver_nombre_sans_limites 
 */
int trouver_nombre_sans_limites();

/* ======================================================================
 * Guesses the number the user was thinking of by recursively looking for
 * the boundary numbers and then guessing the number between those
 * numbers.
 */
int trouver_nombre_sans_limites_rec(int power);

/* ======================================================================
 * Computes a^b if both a and b are positive and if they're not both 
 * equal to zero
 */
int pow_rec(int a, int b);

int main(){
	int a,b;
	printf("Pensez à un nombre...\n");
	printf("Nous allons commencer par définir deux bornes et trouver votre nombre entre ces bornes\n");
	demander_nombres(&a,&b);
	trouver_nombre_avec_limites(a,b);
	
	printf("Pensez maintenant à n'importe quel nombre (plus petit que 2^31)\n");
	trouver_nombre_sans_limites();
	return 0;
}

int trouver_nombre_avec_limites(int gauche, int droite){
	if(droite<gauche){
		printf("ERREUR, vous avez donné des bornes erronées\n");
		return -1;
	}else{
		if(droite==gauche){
			printf("Trouvé ! Le nombre choisi était %i\n",droite);
		}else{
			int pivot = (gauche+droite)/2;
			printf("Votre nombre est-il <, > ou = à %i ?\n",pivot);
			char rep;
			scanf("%c",&rep);
			while(rep!='<' && rep!='>' && rep!='='){
				printf("Réponse invalide, répondez par <, > ou =\n");
				scanf("%c",&rep);
			}
			if(rep=='>'){
				return trouver_nombre_avec_limites(pivot,droite);
			}else if(rep=='<'){
				return trouver_nombre_avec_limites(gauche,pivot);
			}else{
				printf("Trouvé, le nombre choisi était %i\n",pivot);
				return pivot;
			}
		}
	}
	return -1;
	
}

int trouver_nombre_sans_limites_rec(int power){
	int pow2 = pow_rec(2,power);
	printf("Votre nombre est-il plus petit ou plus grand que %i ? \n",pow2);
	char rep;
	scanf("%c",&rep);
	while(rep!='<' && rep!='>' && rep!='='){
		printf("Réponse invalide, répondez par <, > ou =\n");
		scanf("%c",&rep);
	}
	if(rep=='>'){
		return trouver_nombre_sans_limites_rec(power+1);
	}else if(rep=='<'){
		return trouver_nombre_avec_limites(pow2/2,pow2);
	}else{
		printf("Trouvé, le nombre choisi était %i\n",pow2);
		return pow2;
	}
	return -1;
}


int pow_rec(int a, int b){
	if(a<0 || b<0){
		return -1;
	}else if(a==0 && b==0){
		return -1;
	}else if(b==0){
		return 1;
	}else{
		return a*pow_rec(a,b-1);
	}
}

int trouver_nombre_sans_limites(){
	return trouver_nombre_sans_limites_rec(1);
}

void demander_nombres(int* a, int* b)
{
    printf("entrez la borne inférieure puis la borne supérieur entre lesquelles est votre nombre :\n");
    scanf("%i",a);
    scanf("%i",b);
}

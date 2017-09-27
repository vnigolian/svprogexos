/**
 * ***********************************************************
 * Tri par insertion
 * Classe fournissant l'algorithme de tri ainsi que les éléments
 * d'informations permettant de le tester empiriquement
 * ************************************************************
 */
class InsertionSort extends Tri {

	// Constructeur de l'objet tri par insertion
	public InsertionSort() {
		nomTri = "Tri par insertion";
		nomOp = "swap";
	}

	// Tri par insertion: si l'on part d'un tableau trié et qu'on lui ajoute un
	// élément à la bonne place on obtient de nouveau un tableau trié
	// On commence avec le premier élément comme tableau trié initial
	public void algorithmeTri(int g, int d) {
		int i, j;
		int temp;
		for (i = g + 1; i <= d; i++) {
			temp = tableauTrie[i];
			j = i - 1;
			while ((j >= 0) && (tableauTrie[j] > temp)) {
				tableauTrie[j + 1] = tableauTrie[j];
				nbrOp++;
				nbrTest++; // On compte les comparaisons et permutations
				j--;
			}
			tableauTrie[j + 1] = temp;
		}
	}

}

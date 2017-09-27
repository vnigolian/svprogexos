import java.util.Scanner;
class Dichotomie {
	private static Scanner scanner = new Scanner(System.in);

	final static int MINIMUM = 0;
	final static int MAXIMUM = 20;

	public static void main(String[] args) {
		System.out.println("Pensez à un nombre entre " + MINIMUM + " et " +
				MAXIMUM);
		System.out.println("Votre nombre était: " +
				cherche(MINIMUM, MAXIMUM));
	}

	/**
	 * Cherche un nombre dans l'intervalle [gauche, droite] en fonction des
	 * indications données par l'utilisateur.
	 * @param gauche La borne inférieure de l'intervalle
	 * @param droite La borne supérieure de l'intervalle
	 * @return Le pivot
	 */
	static int cherche(int gauche, int droite) {
		if (droite < gauche) {
			System.out.println("Erreur: vous avez  répondu de façon incohérente");
			return droite;
		} else if (droite == gauche) {
			return droite;			
		} else {
			// Détermine le milieu de l'intervalle
			int pivot = (gauche + droite) / 2;
			char rep;
			do {
				System.out.println("Le nombre est-il <, > ou = à " + pivot + " ?");
				rep = scanner.next().charAt(0);
			} while ((rep != '=') && (rep != '>') && (rep != '<'));

			switch (rep) {
			case '=':
				return pivot;
			case '<':
				return cherche(gauche, pivot-1);
			case '>':
				return cherche(pivot+1 , droite);
			default:
				return droite;
			}
		}
	}
}

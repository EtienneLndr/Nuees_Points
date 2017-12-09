#include <iostream>
#include "Pong.h"
#include "Constantes.h"
#include "save_datas.h"


int WIDTH_OF_WINDOW;
int HEIGHT_OF_WINDOW;
int RANDOM_VALUE;


int main(void) {
	srand(time(NULL));

	// Initialisation des constantes
	WIDTH_OF_WINDOW  = 600;
	HEIGHT_OF_WINDOW = 600;
	
	// Création du plateau
  	Pong pong("Nuees de Points", WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
	  
	// Lancement de l'exécution du programme
	int timeMax = pong.execute();
	  
	cout << "Temps d'exécution maximale: " << timeMax << endl;

	// Enregistrement du temps maximal d'exécution dans un fichier
	writeInFile("Temps d'exécution maximale: " + to_string(timeMax));
	
	return 0;
}
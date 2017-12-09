#include "Pong.h"
#include "Constantes.h"


#define NUMBER_OF_POINTS 100
#define RADIUS_OF_CIRCLE 75
#define RADIUS_OF_POINTS 2


using namespace std;


Pong::Pong(string n, int w, int h) : _name(n), _width(w), _height(h) {
	// Création de la fenêtre de jeu
	_win = new sf::RenderWindow(sf::VideoMode(_width, _height), _name);

	// Initialisation du pas de temps
	dt = 1;

	// Ajout du premier cercle
	for (int i = 0; i < NUMBER_OF_POINTS; i++) {
		addCercle(new Cercle(
			RADIUS_OF_POINTS + rand()%(_width - 2*RADIUS_OF_POINTS),
			RADIUS_OF_POINTS + rand()%(_height - 2*RADIUS_OF_POINTS),
			_width,
			_height,
			5 + rand()%251,
			5 + rand()%251,
			5 + rand()%251,
			RADIUS_OF_POINTS,
			dt + rand()%2));
	}

	// Création des lignes
	int red, green, blue;
	sf::VertexArray line(sf::LinesStrip, 2);	
	for (unsigned int i = 0; i < NUMBER_OF_POINTS; i++) {
		for (unsigned int j = 0; j < NUMBER_OF_POINTS; j++) {
			line[0].position = sf::Vector2f(cercle[i]->getX(), cercle[i]->getY());
			cercle[i]->getCouleur().getRVB(red, green, blue);
			line[0].color = sf::Color(red, green, blue);
		
			line[1].position = sf::Vector2f(cercle[j]->getX(), cercle[j]->getY());
			cercle[j]->getCouleur().getRVB(red, green, blue);
			line[0].color = sf::Color(red, green, blue);
		
			addVector(line);
		}
	}
}


Pong::~Pong(void) {
  	// Destruction des objets graphiques
	cout << "Destruction des objets graphiques" << endl;
	delete _win;
	delete mouse_circle;
	for (unsigned int i = 0; i < NUMBER_OF_POINTS; i++) {
  		delete cercle[i];
	}
}


void Pong::moveCirclesRandomly() {
	for (unsigned int i = 0; i < NUMBER_OF_POINTS; i++) {
		if (NULL != mouse_circle && cercle[i]->checkIfCollisionIsOk(mouse_circle)) {
			cout << "Collision" << endl;
			cercle[i]->collideAndBounce(mouse_circle);
		}
		
		cercle[i]->moveRandomly();
	}
}


void Pong::drawAll() {
	// On dessine tous les objets graphiques en appelant leur fonction de dessin
	_win->clear(sf::Color(0, 0, 0));

	if (mouse_circle != NULL)
		mouse_circle->dessine(_win);

	for (unsigned int i = 0; i < NUMBER_OF_POINTS; i++) {
		cercle[i]->dessine(_win);
	}

	for (unsigned int i = 0; i < vectors_to_draw.size(); i++) {
		_win->draw(vectors_to_draw[i]);
	}

	/*sf::VertexArray line(sf::LinesStrip, 2);
	line[0].position = sf::Vector2f(0, 30);
	line[1].position = sf::Vector2f(30, 30);

	_win->draw(line);

	line[0].position = sf::Vector2f(30, 0);
	line[1].position = sf::Vector2f(30, 30);

	_win->draw(line);*/
}


void Pong::updateAndAnimateVectors() {
	vectors_to_draw.clear();

	int pos1_x, pos1_y, pos2_x, pos2_y, distance;
	for (unsigned int i = 0; i < NUMBER_OF_POINTS; i++) {
		for (unsigned int j = 0; j < NUMBER_OF_POINTS; j++) {
			if (i != j) {
				pos1_x = cercle[i]->getX();
				pos1_y = cercle[i]->getY();
				pos2_x = cercle[j]->getX();
				pos2_y = cercle[j]->getY();
				distance = sqrt(pow(pos1_x - pos2_x, 2) + pow(pos1_y - pos2_y, 2));
				if (distance <= 2*RADIUS_OF_CIRCLE) {
					vectors[i*NUMBER_OF_POINTS + j][0].position = sf::Vector2f(pos1_x, pos1_y);
					vectors[i*NUMBER_OF_POINTS + j][1].position = sf::Vector2f(pos2_x, pos2_y);

					vectors_to_draw.push_back(vectors[i*NUMBER_OF_POINTS + j]);
				}
			}
		}
	}
}


void Pong::moveMouseCircle(sf::Vector2i globalPosition) {
	if (mouse_circle->getRadius() < RADIUS_OF_CIRCLE) 
		mouse_circle->setRadius(mouse_circle->getRadius() + 1);
	
	mouse_circle->setX(globalPosition.x);
	mouse_circle->setY(globalPosition.y);
}


int Pong::execute(void) { 
	/**
	 * Cette fonction est l'élément clé de notre programme. Une boucle while permet
	 * de lancer indéfiniment notre programme jusqu'à ce que l'utilisateur décide de mettre
	 * fin à la partie en fermCercle la fenêtre de jeu. Dans cette boucle while on fait appel
	 * à différentes fonctions permettCercle de mettre en place notre jeu. 
	 */
	drawAll();

	int timeMax = 0;
	
  	while (_win->isOpen()) {

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		
		// On déplace les fourmis
		if (!pause) {
			moveCirclesRandomly();
			updateAndAnimateVectors();
			drawAll();
		}
		
		_win->display();
		
    	sf::Event event;
    	if(_win->pollEvent(event)) {
      		switch (event.type) {
				// Fermeture de la fenêtre
      			case sf::Event::Closed:
             		_win->close();
					break;
				// Réacquisition du focus
				case sf::Event::GainedFocus:
					cout << "Focus regained" << endl;
					pause = false;
					break;
				// Perte du focus
				case sf::Event::LostFocus:
					cout << "Focus lost" << endl;
					pause = true;
					break;
             	// Si une touche du clavier est pressée:
        		case sf::Event::KeyPressed:
        			// Si c'est la touche 'echap' on met le jeu en pause
        			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        				// On met le jeu en pause --> plus aucun mouvement
        				if (!pause) pause = true;
        				else pause = false;
        			}
             		break;
             	// Si on clique avec la souris:
             	case sf::Event::MouseButtonPressed:
    				// Si c'est un clic gauche:
    				if (event.mouseButton.button == sf::Mouse::Right) {
        				/**
        				 * On teste si le clic est sur une forme à l'aide de la méthode 
        				 * cliqueSouris(int, int)
        				 */
    				} else if (event.mouseButton.button == sf::Mouse::Left && !mouseButtonPressed) {
						cout << "mouse left pressed" << endl;
						mouse_circle = new Cercle(
							event.mouseButton.x,
							event.mouseButton.y,
							_width,
							_height,
							0,
							0,
							0,
							1,
							dt);
						mouseButtonPressed = true;
					}
					break;
				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left && mouseButtonPressed) {
						cout << "mouse left released" << endl;
						mouseButtonPressed = false;
						delete mouse_circle;
						mouse_circle = NULL;
					}
        		default:
         			break;
      		}
		}

		if (mouseButtonPressed) {
			/**
			 * Récupération de la positon de la souris par rapport à la fenêtre
			 */
			sf::Vector2i globalPosition = sf::Mouse::getPosition(*_win);
			moveMouseCircle(globalPosition);
		}

		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		
		// Calcul de l'intervalle de temps
		auto duration = (int)duration_cast<microseconds>( t2 - t1 ).count();
		
		if (duration > timeMax) {
			timeMax = duration;
			cout << "Maximum time -> " << timeMax << endl;
		}
		
    	/**
    	 * On met le programme en pause pendCercle une petite durée car sinon celui-ci est trop rapide
		 * et il plante
    	 */
		usleep(10000);
	}

	return timeMax;
}
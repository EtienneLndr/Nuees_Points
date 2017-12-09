#include "Cercle.h"


int Cercle::mass = 1;


Cercle::Cercle(int _x, int _y, int l, int h, int r, int v, int b, int _radius, int _dt): Forme(_x, _y, l, h, Couleur(r, v, b)), radius(_radius), dt(_dt) {
	directionX = rand()%2 == 0 ? 1 : -1;
	directionY = rand()%2 == 0 ? 1 : -1;
}


Cercle::~Cercle() {
}


void Cercle::dessine(sf::RenderWindow *win) {
	int red, green, blue;
  	couleur.getRVB(red, green, blue);
  	sf::CircleShape shape(radius);
  	shape.setFillColor(sf::Color(red, green, blue));
  	shape.setPosition(x - radius, y - radius);
	win->draw(shape);
}

void Cercle::moveRandomly() {
	if (x + radius + dt > largeur || x - radius - dt < 0) {
		directionX *= -1;
	}
	if (y + radius + dt > hauteur || y - radius - dt < 0) {
		directionY *= -1;
	}

	x += directionX*dt;
	y += directionY*dt;
}

bool Cercle::checkIfCollisionIsOk(Cercle * cercle) {
	return (sqrt(pow(x - cercle->getX(), 2) + pow(y - cercle->getY(), 2)) 
				< radius + cercle->getRadius());
}


void Cercle::collideAndBounce(Cercle * cercle) {
	/*int collisionPointX = ((x * cercle->getRadius()) + (cercle->getX() * radius)) / (radius + cercle->getRadius());
	int collisionPointY = ((y * cercle->getRadius()) + (cercle->getY() * radius)) / (radius + cercle->getRadius());
	
	(void)collisionPointX;
	(void)collisionPointY;*/

	directionX = (directionX * (mass - cercle->getMass()) + (2 * cercle->getMass() * (-1 * directionX))) / (mass + cercle->getMass());
	directionY = (directionY * (mass - cercle->getMass()) + (2 * cercle->getMass() * (-1 * directionY))) / (mass + cercle->getMass());
}



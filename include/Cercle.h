#ifndef CERCLE_H
#define CERCLE_H
#include "Forme.h"
#include <vector>


class Cercle : public Forme {
	
	public:
		Cercle(int _x, int _y, int l, int h, int r, int v, int b, int _radius, int _dt);
		~Cercle();

		int getRadius();
		void setRadius(int r);
		int getMass();
		void setMass(int m);
		int getDt();
		void setDt(int d);

		void dessine(sf::RenderWindow *win);
		void moveRandomly();
		bool checkIfCollisionIsOk(Cercle * cercle);
		void collideAndBounce(Cercle * cercle);
		
	protected:
		int radius;
		int dt;
		int directionX, directionY;
		static int mass;
	
	};


inline int Cercle::getRadius() { return radius; }
inline void Cercle::setRadius(int r) { radius = r; }
inline int Cercle::getMass() { return mass; }
inline void Cercle::setMass(int m) { mass = m; }
inline int Cercle::getDt() { return dt; }
inline void Cercle::setDt(int d) { dt = d; }


#endif
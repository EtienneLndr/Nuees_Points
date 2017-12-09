#ifndef PONG_H
#define PONG_H
#include <vector>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <chrono>
#include "SFML/Graphics.hpp"
#include "Cercle.h"

using namespace std;
using namespace std::chrono;

class Case;

class Pong {
	
	public: 
		int execute();
		
		Pong(string n = "Window", int w = 400, int h = 400);
		~Pong();
		
		Cercle* getCercle(int i);
		void addCercle(Cercle * a);
		sf::VertexArray getVectorAt(unsigned int i);
		void addVector(sf::VertexArray vect);
		
	private:
		string _name;
    	int _width, _height;
    	sf::RenderWindow *_win;
		vector<Cercle*> cercle;
		Cercle * mouse_circle = NULL;
		vector<sf::VertexArray> vectors;
		vector<sf::VertexArray> vectors_to_draw;
		
		int limite;
		int dt 					= 1;
		bool pause 				= false;
		bool mouseButtonPressed = false;
		
		void moveCirclesRandomly();
		void drawAll();
		void updateAndAnimateVectors();
		void moveMouseCircle(sf::Vector2i globalPosition);
	
	};
		
		
inline Cercle* Pong::getCercle(int i) { return cercle[i]; }
inline void Pong::addCercle(Cercle * a) { cercle.push_back(a); }
inline sf::VertexArray Pong::getVectorAt(unsigned int i) { return vectors[i]; }
inline void Pong::addVector(sf::VertexArray vect) { vectors.push_back(vect); }


#endif
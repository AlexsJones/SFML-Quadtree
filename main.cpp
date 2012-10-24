// QuadtreeSimple.cpp : Demonstrates the use of Quadtree using SFML
//

#include "Quadtree.h"
#include "Object.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>

int main()
{
	using namespace std;

	sf::RenderWindow app( sf::VideoMode( 800, 600, 32 ), "Quadtree" );
	app.SetFramerateLimit( 60 );

	Quadtree quadtree( 0.0f, 0.0f, 800.0f, 600.0f, 0, 3 );


	vector<Object> objects;

	while( app.IsOpened() ) {
		sf::Event event;
		sf::Vector2f mousePosition = app.ConvertCoords(app.GetInput().GetMouseX(), app.GetInput().GetMouseY());
		while( app.GetEvent( event ) ) {
			if ( event.Type == sf::Event::KeyPressed ) {
				if ( event.Key.Code == sf::Key::Escape ) {
					app.Close();
				}
			}
			if ( event.Type == sf::Event::MouseButtonPressed ) {
				objects.push_back( Object( mousePosition.x, mousePosition.y, 32, 32 ) );
			}
		}
		app.Clear();

		for ( int n = 0; n < objects.size(); ++n ) {
			quadtree.AddObject( &objects[n] );
			objects[n].Draw( app );
		}
		quadtree.Draw( app );

		vector<Object*> returnObjects = quadtree.GetObjectsAt( mousePosition.x, mousePosition.y );
		cout << returnObjects.size() << endl;
		quadtree.Clear();

		app.Display();
	}

	return 0;
}
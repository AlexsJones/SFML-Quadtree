// QuadtreeSimple.cpp : Demonstrates the use of Quadtree using SFML
//

#include "quadtree.h"
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

	quadtree _quadtree( 0.0f, 0.0f, 800.0f, 600.0f, 0, 3 );
	vector<Object> objects;

	objects.push_back( Object( 0,0, 32, 32 ) );
	objects.push_back( Object( 100,100, 32, 32 ) );
	objects.push_back( Object( 350,350, 32, 32 ) );
	objects.push_back( Object( 500,500, 32, 32 ) );
	objects.push_back( Object( 500,510, 32, 32 ) );
	objects.push_back( Object( 500,520, 32, 32 ) );
	objects.push_back( Object( 500,525, 32, 32 ) );
	
	while( app.IsOpened() ) 
	{
		sf::Event event;
		sf::Vector2f mousePosition = app.ConvertCoords(app.GetInput().GetMouseX(), app.GetInput().GetMouseY());
		
		app.Clear();

		for ( int n = 0; n < objects.size(); ++n )
		{
			_quadtree.add_object( &objects[n] );
			objects[n].Draw( app );
		}
		while( app.GetEvent( event ) ) 
		{
			if ( event.Type == sf::Event::KeyPressed ) 
			{
				if ( event.Key.Code == sf::Key::Escape ) 
				{
				app.Close();
				}
			}
			if ( event.Type == sf::Event::MouseButtonPressed ) 
			{
				vector<Object*> returnObjects = _quadtree.get_objects_at( mousePosition.x, mousePosition.y );
	
				cout << returnObjects.size() << endl;
			}
		}
							
		_quadtree.clear();

		app.Display();
	}

	return 0;
}
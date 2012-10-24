#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/String.hpp>

using namespace std;

class Quadtree;
class Object;

class Quadtree {
public:
							Quadtree( float x, float y, float width, float height, int level, int maxLevel );

	void					AddObject( Object *object );
	vector<Object*>			GetObjectsAt( float x, float y );
	void					Clear();

	void					SetFont( const sf::Font &font );
	void					Draw( sf::RenderTarget &canvas );

private:
	float					x;
	float					y;
	float					width;
	float					height;
	int						level;
	int						maxLevel;
	vector<Object*>			objects;

	Quadtree *				parent;
	Quadtree *				NW;
	Quadtree *				NE;
	Quadtree *				SW;
	Quadtree *				SE;

	sf::Shape		                shape;
	sf::String				text;

	bool					Contains( Quadtree *child, Object *object );
};

#endif
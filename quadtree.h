#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/String.hpp>

using namespace std;

class quadtree;
class Object;

class quadtree {
public:
	quadtree( float x, float y, float width, float height, int level, int maxLevel );

	void	add_object( Object *object );
	vector<Object*>	get_objects_at( float x, float y );
	void	clear();
private:
	float	x;
	float	y;
	float	width;
	float	height;
	int		level;
	int		maxLevel;
	vector<Object*>	objects;

	quadtree *	parent;
	quadtree *	NW;
	quadtree *	NE;
	quadtree *	SW;
	quadtree *	SE;

	bool	contains( quadtree *child, Object *object );
};

#endif

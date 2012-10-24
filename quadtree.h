#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/String.hpp>

using namespace std;

class quadtree;
class treeobject;

class quadtree {
public:
	quadtree( float x, float y, float width, float height, int level, int maxLevel );

	void	add_object( treeobject *object );
	vector<treeobject*>	get_objects_at( float x, float y );
	void	clear();
private:
	float	x;
	float	y;
	float	width;
	float	height;
	int		level;
	int		maxLevel;
	vector<treeobject*>	objects;

	quadtree *	parent;
	quadtree *	NW;
	quadtree *	NE;
	quadtree *	SW;
	quadtree *	SE;

	bool	contains( quadtree *child, treeobject *object );
};

#endif

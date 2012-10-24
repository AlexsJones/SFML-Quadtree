#include "quadtree.h"
#include "treeobject.h"
#include <iostream>
#include <sstream>

using namespace std;

quadtree::quadtree( float _x, float _y, float _width, float _height, int _level, int _maxLevel ) :
	x		( _x ),
	y		( _y ),
	width	( _width ),
	height	( _height ),
	level	( _level ),
	maxLevel( _maxLevel )
{
	if ( level == maxLevel ) {
		return;
	}

	NW = new quadtree( x, y, width / 2.0f, height / 2.0f, level+1, maxLevel );
	NE = new quadtree( x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, maxLevel );
	SW = new quadtree( x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel );
	SE = new quadtree( x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel );
}

void quadtree::add_object( treeobject *object ) {
	if ( level == maxLevel ) {
		objects.push_back( object );
		return;
	}
	if ( contains( NW, object ) ) {
		NW->add_object( object ); return;
	} else if ( contains( NE, object ) ) {
		NE->add_object( object ); return;
	} else if ( contains( SW, object ) ) {
		SW->add_object( object ); return;
	} else if ( contains( SE, object ) ) {
		SE->add_object( object ); return;
	}
	if ( contains( this, object ) ) {
		objects.push_back( object );
	}
}

vector<treeobject*> quadtree::get_objects_at( float _x, float _y ) {
	if ( level == maxLevel ) {
		return objects;
	}
	
	vector<treeobject*> returnObjects, childReturnObjects;
	if ( !objects.empty() ) {
		returnObjects = objects;
	}
	if ( _x > x + width / 2.0f && _x < x + width ) {
		if ( _y > y + height / 2.0f && _y < y + height ) {
			childReturnObjects = SE->get_objects_at( _x, _y );
			returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );
			return returnObjects;
		} else if ( _y > y && _y <= y + height / 2.0f ) {
			childReturnObjects = NE->get_objects_at( _x, _y );
			returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );
			return returnObjects;
		}
	} else if ( _x > x && _x <= x + width / 2.0f ) {
		if ( _y > y + height / 2.0f && _y < y + height ) {
			childReturnObjects = SW->get_objects_at( _x, _y );
			returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );
			return returnObjects;
		} else if ( _y > y && _y <= y + height / 2.0f ) {
			childReturnObjects = NW->get_objects_at( _x, _y );
			returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );
			return returnObjects;
		}
	}
	return returnObjects;
}

void quadtree::clear() {
	if ( level == maxLevel ) {
		objects.clear();
		return;
	} else {
		NW->clear();
		NE->clear();
		SW->clear();
		SE->clear();
	}
	if ( !objects.empty() ) {
		objects.clear();
	}
}
bool quadtree::contains( quadtree *child, treeobject *object ) {
	return	 !( object->x < child->x ||
				object->y < child->y ||
				object->x > child->x + child->width  ||
				object->y > child->y + child->height ||
				object->x + object->width < child->x ||
				object->y + object->height < child->y ||
				object->x + object->width > child->x + child->width ||
				object->y + object->height > child->y + child->height );
}
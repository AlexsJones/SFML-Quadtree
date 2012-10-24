#include "Quadtree.h"
#include "Object.h"
#include <iostream>
#include <sstream>

using namespace std;

Quadtree::Quadtree( float _x, float _y, float _width, float _height, int _level, int _maxLevel ) :
	x		( _x ),
	y		( _y ),
	width	( _width ),
	height	( _height ),
	level	( _level ),
	maxLevel( _maxLevel )
{
	shape = sf::Shape::Rectangle ( x, y, x + width, y + height, sf::Color( 64, 128, 255 ),0.0f,sf::Color( 0, 0, 0, 0 ) );

	text.SetSize(12);
	text.SetPosition( x, y + level * 16 );

	if ( level == maxLevel ) {
		return;
	}

	NW = new Quadtree( x, y, width / 2.0f, height / 2.0f, level+1, maxLevel );
	NE = new Quadtree( x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, maxLevel );
	SW = new Quadtree( x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel );
	SE = new Quadtree( x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel );
}

void Quadtree::AddObject( Object *object ) {
	if ( level == maxLevel ) {
		objects.push_back( object );
		return;
	}
	if ( Contains( NW, object ) ) {
		NW->AddObject( object ); return;
	} else if ( Contains( NE, object ) ) {
		NE->AddObject( object ); return;
	} else if ( Contains( SW, object ) ) {
		SW->AddObject( object ); return;
	} else if ( Contains( SE, object ) ) {
		SE->AddObject( object ); return;
	}
	if ( Contains( this, object ) ) {
		objects.push_back( object );
	}
}

vector<Object*> Quadtree::GetObjectsAt( float _x, float _y ) {
	if ( level == maxLevel ) {
		return objects;
	}
	
	vector<Object*> returnObjects, childReturnObjects;
	if ( !objects.empty() ) {
		returnObjects = objects;
	}
	if ( _x > x + width / 2.0f && _x < x + width ) {
		if ( _y > y + height / 2.0f && _y < y + height ) {
			childReturnObjects = SE->GetObjectsAt( _x, _y );
			returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );
			return returnObjects;
		} else if ( _y > y && _y <= y + height / 2.0f ) {
			childReturnObjects = NE->GetObjectsAt( _x, _y );
			returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );
			return returnObjects;
		}
	} else if ( _x > x && _x <= x + width / 2.0f ) {
		if ( _y > y + height / 2.0f && _y < y + height ) {
			childReturnObjects = SW->GetObjectsAt( _x, _y );
			returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );
			return returnObjects;
		} else if ( _y > y && _y <= y + height / 2.0f ) {
			childReturnObjects = NW->GetObjectsAt( _x, _y );
			returnObjects.insert( returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end() );
			return returnObjects;
		}
	}
	return returnObjects;
}

void Quadtree::Clear() {
	if ( level == maxLevel ) {
		objects.clear();
		return;
	} else {
		NW->Clear();
		NE->Clear();
		SW->Clear();
		SE->Clear();
	}
	if ( !objects.empty() ) {
		objects.clear();
	}
}

void Quadtree::SetFont( const sf::Font &font ) {
	text.SetFont( font );
	if ( level != maxLevel ) {
		NW->SetFont( font );
		NE->SetFont( font );
		SW->SetFont( font );
		SE->SetFont( font );
	}
}

void Quadtree::Draw( sf::RenderTarget &canvas ) {
	stringstream ss;
	ss << objects.size();
	string numObjectsStr = ss.str();
	text.SetText( numObjectsStr );
	canvas.Draw( shape );
	canvas.Draw( text );
	if ( level != maxLevel ) {
		NW->Draw( canvas );
		NE->Draw( canvas );
		SW->Draw( canvas );
		SE->Draw( canvas );
	}
}

bool Quadtree::Contains( Quadtree *child, Object *object ) {
	return	 !( object->x < child->x ||
				object->y < child->y ||
				object->x > child->x + child->width  ||
				object->y > child->y + child->height ||
				object->x + object->width < child->x ||
				object->y + object->height < child->y ||
				object->x + object->width > child->x + child->width ||
				object->y + object->height > child->y + child->height );
}
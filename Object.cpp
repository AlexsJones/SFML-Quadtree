#include "Object.h"


Object::Object( float _x, float _y, float _width, float _height ) : 
	x		( _x ),
	y		( _y ),
	width	( _width ),
	height	( _height )
{
	shape = sf::Shape::Rectangle ( x, y, x + width, y + height, sf::Color( 32, 128, 255 ) );
}

void Object::Draw( sf::RenderTarget &canvas ) {
	canvas.Draw( shape );
}

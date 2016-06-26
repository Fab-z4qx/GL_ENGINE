#include "Entity.h"

namespace e3d {


Entity::Entity(const string& name, Mesh* meshPtr): _Mesh(meshPtr), MovableObject(name,e3d_entity) {
	_color = Vector4(255,255,255,1);
}

Entity::Entity(const string& name, Mesh* meshPtr, const Vector4& color): 
	_Mesh(meshPtr), _color(color), MovableObject(name,e3d_entity) {}

Entity::Entity(const string& name, Mesh* meshPtr, int red, int green, int blue): 
	_Mesh(meshPtr), MovableObject(name,e3d_entity) 
{
	_color.setX(red);
	_color.setY(green);
	_color.setZ(blue);
}

Entity::~Entity(void){
//On ne detruit pas le mesh ici puisqu'on peu associer un meme mesh à plusieurs entity
}

}
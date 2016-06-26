#pragma once

/* La classe Node permet de representer un noeud dans une scene */ 
/* C'est à dire d'y attacher un ou plusieurs object ainsi que d'autre node */
/* Ce qui permet d'appliquer une transformation à tout les object et sous noeuds qui li sont attaché */

#include <vector>
#include "MovableObject.h"

using namespace std;

namespace e3d{

class Node : public MovableObject
{
private:
	//static Node *_rootNode; //Noeuds principal ou sont attaché tout les object ou sous noeuds
	Node* _parentNode;
	std::vector<Node*> _childrenNode;
	vector<MovableObject*> _childrenObject;
	
	static Node* initRootNode();
public:
	/* Cree un rootNode */
	Node(const string& name);

	/* Cree un Node simple et l'attache a son noeud parent*/
	Node(Node* _ParentNode, const string& name);
	virtual ~Node();

	/* Met à jour la matrice associé à notre node */
	virtual void update(const Matrix& m);
	virtual void updateTrans(const Matrix& m);

	Node* getParentNode(void) const { return _parentNode; }
	void setParentNode(Node* parentNode) { if(NULL != _parentNode) parentNode->detachChildNode(this); _parentNode = parentNode; }

	void attachChildNode(Node* childNode);
	void detachChildNode(Node* childNode);

	void attachMovableObject(MovableObject* object);

	const size_t countChildNode() const     { return _childrenNode.size(); }
	const size_t countMovableObject() const { return _childrenObject.size(); }
	const bool IsRootNode(void) const { if(_parentNode == NULL){ return 1; } return 0; } //Renvoi 1 si c'est un parent 0 sinon

	Node* getChildNodeByName(const string& searchName);
	Node* getChildNodeAt(const int i) { return _childrenNode[i] ; }

	MovableObject* getMovableObjectAt(const int i) { return _childrenObject[i]; }

	// Transformations 
	void rotate(double angle, double x, double y, double z) { update(this->getRotate(angle,x,y,z)); }
	void rotateX(double angle) { update(this->getRotateX(angle)); }
	void rotateY(double angle) { update(this->getRotateY(angle)); }
	void rotateZ(double angle) { update(this->getRotateZ(angle)); }
	void translate(double x, double y, double z) { updateTrans(this->getTranslation(x,y,z)); }
	void scale(double x, double y, double z)	 { update(this->getScale(x,y,z)); }

};

}
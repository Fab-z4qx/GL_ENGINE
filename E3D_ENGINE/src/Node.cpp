#include "Node.h"

namespace e3d {

Node::Node(const string& name) : MovableObject(name,e3d_rootNode){
	_parentNode = NULL;
}

Node* Node::initRootNode(){
	return NULL;
}

Node::Node(Node* parentNode, const string& name): _parentNode(parentNode), MovableObject(name,e3d_node)
{
	parentNode->attachChildNode(this); //On attache l'object au noeud pere
}

Node::~Node(void)
{
    _parentNode = NULL;
	_childrenNode.clear();
	_childrenObject.clear();
}

void Node::update(const Matrix& m)
{
	this->setMat( this->getMat() * m );
} 

void Node::updateTrans(const Matrix& m)
{
	this->setMat(m.mult(this->getMat()));
} 


void Node::attachChildNode(Node* ChildNode)
{
    if(ChildNode != NULL)
    {
        if(ChildNode->getParentNode() != NULL) 
        {
            ChildNode->setParentNode(this); //alors on lui met this comme parent
        }
        _childrenNode.push_back(ChildNode); //On ajoute le node à notre vector
    }
}

void Node::detachChildNode(Node* ChildNode)
{
    if(ChildNode != NULL && !_childrenNode.empty())
    {
        for(size_t i = 0; i < _childrenNode.size(); ++i)
        {
            if(_childrenNode[i] == ChildNode)
            {
                _childrenNode.erase(_childrenNode.begin() + i);
                break; // break for loop
            }
        }
    }
}

void Node::attachMovableObject(MovableObject* object)
{
    if(object != NULL)
    {
		_childrenObject.push_back(object); //On ajoute le node à notre vector
    }
}

Node* Node::getChildNodeByName(const string& searchName)
{
    if(!_childrenNode.empty())
    {
        for(size_t i = 0; i < _childrenNode.size(); ++i)
        {
			if(_childrenNode[i]->getName() == searchName)
            {
                return _childrenNode[i];
            }
        }
    }
	return NULL;
}


}
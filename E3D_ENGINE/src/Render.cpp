#include "Render.h"

namespace e3d {

Render::Render(Camera* cam, Node* rootNode, string screenName , int renderModeSysteme, int width, int height) : _camera(cam), _renderMode(renderModeSysteme), _rootNode(rootNode)
{
#if(RENDER_SYS == 1) //On utilisent OpenCV
	_screen = new ScreenOpenCV(screenName,width,height,CV_8UC3);
#endif

#if(RENDER_SYS == 2) //On utilisent SFML
	_screen = new ScreenSFML(screenName,width,height,5);
#endif

    
#if(RENDER_SYS == 3) //On laisse le choix à l'utilisateur 
	if(renderModeSysteme == e3d_OpenCvRender){
		_screen = new ScreenOpenCV(screenName,width,height,CV_8UC3);
	}
	else if(renderModeSysteme == e3d_SFMLRender){
		_screen = new ScreenSFML(screenName,width,height,5);
	}
#endif
#if(RENDER_SYS == 4) //SFML OPENGL
    _screen = new ScreenGL(screenName,width,height,5);
#endif
}


Render::~Render(void)
{
	delete(_screen);
}

void Render::loop() //Exemple de boucle principal de rendu
{
	while(1)
	{
		clean();
		start();
		update();
	}
}

void Render::start() //Point d'entrée du render (se base sur le rootNode) 
{
	_aspectRatio = double(_screen->getWidth()) / double(_screen->getHeight()); //Maj du ratio si l'utilisateur à changé les dimentions de la fenetre
	_camera->getPerspective(_camera->getFov(), _aspectRatio, _camera->getNear(), _camera->getFar(), _projMat); //Maj de la matrice de projection 
	renderProcess(_rootNode,_rootNode->getMatIdentity()); //Calcule du rendu des pts à partir du noeuds Root
}

//Fonction de rendu principal 
// Elle permet de parcourir l'achitecture du RootNode de façon recursive
void Render::renderProcess(Node* nod, const Matrix& transformation)
{
	if( nod->countChildNode() != 0) //Si il y'a des sous noeuds
    {
		for(int i = 0; i < nod->countChildNode();++i) //On parcours tt les sous noeuds
        {
			renderProcess( nod->getChildNodeAt(i), transformation * nod->getMat() ); //On va appeler recursivement la fonction pour traiter les ss node
        }
    }
	if( nod->countMovableObject() > 0) //Si il n' y à pas de sous noeuds et des object
	{
		processToObject(nod,transformation * nod->getMat()); //on traite ses object directement	
	}
}

/* Permet de traiter les objets atachés à un Node */
 void Render::processToObject(Node* nod, const Matrix& transformation)
 {
	 if(nod->countMovableObject() != 0) //SI le noeuds contient des object
		{
			for (int i = 0; i < nod->countMovableObject(); i++) //On parcours tt les objets
			{
				if (dynamic_cast<Entity*>(nod->getMovableObjectAt(i)) != NULL) //SI c'est un object de type Entity
				{
					vector<Vector4> calc; //stock les pts projeté sur l'ecran 
					Entity *r_Entity = dynamic_cast<Entity*>(nod->getMovableObjectAt(i)); //on le cast en Entity
					if( r_Entity->isVisible() )
					{	
						RenderPoint(r_Entity,calc,transformation);
						RenderLigne(r_Entity,calc);
					}
				}
				else if (dynamic_cast<Label*>(nod->getMovableObjectAt(i)) != NULL)
				{
					Label *r_lab = dynamic_cast<Label*>(nod->getMovableObjectAt(i)); //on le cast en Entity
					if( r_lab->isVisible() )
					{	
						RenderLabel(r_lab,transformation);
					}
				}
			}
		}
 }

 /* Affiche les points d'un objet de type Entity */
 void Render::RenderPoint(Entity* r_Entity, vector<Vector4>& calc, const Matrix& transformation)
 {

	Vector4 r; //Pts transformé
	int red=(int)r_Entity->getColor().getX(), 
		blue=(int)r_Entity->getColor().getY(), 
		green=(int)r_Entity->getColor().getZ();

	for (int j = 0; j < r_Entity->getMesh()->getSize() ; j++) //On parcous tt les pts
	{
		r.setX(r_Entity->getPointX(j));
		r.setY(r_Entity->getPointY(j));
		r.setZ(r_Entity->getPointZ(j));
		r.setW(r_Entity->getPointW(j));

		r = transformation.mult(r_Entity->getMat()).mult(r); // = transformation * repaire * pts
		r = _projMat * (r - _camera->getPosition()); //Mat Projection * (vertex - camPosition)

		_screen->drawPoint(r.getX(),r.getY(),r.getX(),r.getY(), red,blue,green);
		calc.push_back(r); //on ajoute le pts projeté dans un tableau 
	} 
 }
  
 void inv(vector<Vector4>& calc, vector<Vector4>& invtab)
 {
	 for (int i = 0; i < calc.size(); i++)
	 {
		 Vector4 tmp;
		 tmp = calc[i];
		 invtab.push_back(tmp);
	 }
 }

 void Render::RenderLigne(Entity* r_Entity, vector<Vector4>& calc)
 {
	int r=(int)r_Entity->getColor().getX(), 
		g=(int)r_Entity->getColor().getY(), 
		b=(int)r_Entity->getColor().getZ();

	/*vector<Vector4> invtab;
	inv(calc,invtab);
	calc = invtab; */

	
	Polygone p; //polygone local
	double x1,y1, x2,y2; //Cordonées des pts à l'ecran
    for (int t = 0 ; t < r_Entity->getMesh()->getNbPolygone(); t++) //On parcours tt les polygones
	{
		p = r_Entity->getMesh()->getPolygoneAt(t);
		for (int k = 0; k < p.size(); k++) //On trace le polygone qui peu avoir un nombre de pts € [3;5]
		{
			if(k < p.size()-1)
			{
				x1 = ( calc[p.getPointAt(k)-1].getX() ); //On recup les pts aux indices indiqués
				y1 = ( calc[p.getPointAt(k)-1].getY() ); //On reutilise la valeurs des pts deja calculé en partant de la fin du tableau puisqu'ils sont inversés

				x2 = ( calc[p.getPointAt(k+1)-1].getX() ); 
				y2 = ( calc[p.getPointAt(k+1)-1].getY() );
				_screen->drawLine( x1, y1, x2, y2 , r,g,b); //on trace la ligne de x1,y1 vers x2,y2
			}
			else
			{
				x1 = ( calc[p.getPointAt(k)-1].getX() ); 
				y1 = ( calc[p.getPointAt(k)-1].getY() );

				x2 = ( calc[p.getPointAt(0)-1 ].getX() ); 
				y2 = ( calc[p.getPointAt(0)-1 ].getY() );
				_screen->drawLine( x1,y1, x2, y2 , r,g,b);
			} 
		}
	}
	/*
	Polygone p; //polygone local
	double x1,y1, x2,y2; //Cordonées des pts à l'ecran
    for (int t = 0 ; t < r_Entity->getMesh()->getNbPolygone(); t++) //On parcours tt les polygones
	{
		p = r_Entity->getMesh()->getPolygoneAt(t);
		for (int k = 0; k < p.size(); k++) //On trace le polygone qui peu avoir un nombre de pts € [3;5]
		{
			if(k < p.size()-1)
			{
				x1 = ( calc[calc.size()-1 - p.getPointAt(k)].getX() ); //On recup les pts aux indices indiqués
				y1 = ( calc[calc.size()-1 - p.getPointAt(k)].getY() ); //On reutilise la valeurs des pts deja calculé en partant de la fin du tableau puisqu'ils sont inversés

				x2 = ( calc[calc.size()-1 - p.getPointAt(k+1)].getX() );
				y2 = ( calc[calc.size()-1 - p.getPointAt(k+1)].getY() );
				_screen->drawLine( x1, y1, x2, y2 ,r,g,b); //on trace la ligne de x1,y1 vers x2,y2
			}
			else
			{
				x1 = ( calc[calc.size()-1 - p.getPointAt(k)].getX() );
				y1 = ( calc[calc.size()-1 - p.getPointAt(k)].getY() );

				x2 = ( calc[calc.size()-1 - p.getPointAt(0)].getX() ); 
				y2 = ( calc[calc.size()-1 - p.getPointAt(0)].getY() );
				_screen->drawLine( x1,y1, x2, y2 ,r,g,b);
			}
		}
	} */
 }

 /* Affichage d'un Label (texte) */
 void Render::RenderLabel(Label* lab, const Matrix& transformation)
 {	
	Vector4 r;
	r = transformation.mult(lab->getMat()).mult(r); // = transformation * repaire * pts
	r = _projMat * (r - _camera->getPosition()); //Mat Projection * (vertex - camPosition)
	_screen->drawLabel(lab->getLabel(), r.getX(), r.getY(), (int)lab->getColor().getX(), (int)lab->getColor().getY(), (int)lab->getColor().getZ());
 }

 }
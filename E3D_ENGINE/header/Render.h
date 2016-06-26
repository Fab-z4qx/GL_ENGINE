#pragma once

/* Classe Render */
/* Cette classe permet de faire les calcules de rendu d'une scene */
/* Elle se base sur un node, ce qu'on appel le NodeRoot */
/* Elle possede donc une pointeur sur la camera et l'écran pour recuperer la 
matrice de projection et ainsi afficher les points à l'écran */

#include "Config.h"
#include "Object.h"
#include "Camera.h"
#include "Screen.h"
#include "ScreenSFML.h"
#include "ScreenOpenCV.h"
#include "Node.h"
#include "Label.h"
#include "Entity.h"

#if(RENDER_SYS==1 || RENDER_SYS==3)
	const unsigned int e3d_OpenCvRender = 0;
#endif
#if(RENDER_SYS==2 || RENDER_SYS==3)
	const unsigned int e3d_SFMLRender = 1;
#endif

namespace e3d {
class Render
{
private:
	Camera *_camera;
	Screen *_screen;
	Node* _rootNode;
	Matrix _projMat; 
	double _aspectRatio;
	int _renderMode;

	/* Methode privé qui parcours les nodes et fait le rendu de la scene */
	void	renderProcess(Node* nod, const Matrix& transformation);
	void	processToObject(Node* nod, const Matrix& transformation);
	void	RenderPoint(Entity* r_Entity, vector<Vector4>& calc, const Matrix& transformation);
	void	RenderLigne(Entity* r_Entity, vector<Vector4>& calc);
	void	RenderLabel(Label* lab, const Matrix& transformation);

public:
	Render(Camera* cam, Node* rootNode, string screenName, int renderModeSysteme, int width=800, int height=800);
	~Render(void);

	void	loop(); //Exemple de boucle de rendu possible 
	void	start(); //Calcule le rendu des pts 
	void	clean() { _screen->clean(); }
	void	update() { _screen->update(); }
	
	Camera* getCamera() { return _camera; }
	void	setCamera(Camera* cam) {_camera = cam; }

	Node*	getRootNode() { return _rootNode; };
	void	setRootNode(Node* rootNode) { _rootNode = rootNode; }

	int		getRenderMode() { return _renderMode; }
	void	setRenderMode(int renderMode) { _renderMode = renderMode; } 
	
};

}
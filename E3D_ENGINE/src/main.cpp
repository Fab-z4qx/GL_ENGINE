#include <iostream>

#include "main.h"
#include <chrono>

using namespace std;
using namespace e3d;

void exemple()
{
	//Sphere s("myspehere",Vector4(0,0,0,1),20);
	Sphere s("mysphere",Vector4(0,0,0,0),50,20);
	Entity myen("Entity1",&s);

	Sphere s2("spehre2",Vector4(0,0,0,1),4,25.0,25.0);
	Entity myen2("Entity2",&s2);

	Sphere s3("spdzqehre2",Vector4(0,10,0,1),5,30.0,30.0);
	Entity myen3("Entitdy2",&s3);

	Sphere s4("spdzqehre2",Vector4(0,0,0,1),10,10,10);
	cout << s4 << endl;
	Entity myen4("Entitdy2",&s4);

	Sphere s5("spdzqehre2",Vector4(0,0,0,1),10,1);
	Entity myen5("Entitdy2",&s5);

	Cube cu("cube",Vector4(0,0,0,1),50,50,50);
	Entity cube("Encube",&cu);

	Node n("rootNode");	
	n.attachMovableObject(&cube);
	n.translate(20,-50,0);
	myen2.translate(-10,0,0);

	ObjLoader loader;
	Mesh *m = loader.load("cartoon","sandal.obj");
	Entity en6("cartoone",m);
	en6.translate(40,0,0);
	en6.setColor(150,150,255);

	cube.rotateX(PI/6);
	cube.rotateY(PI/6);
	en6.scale(7,7,7);

	//Label l("labeltest","test");
	//l.translate(50,0,0);
	//l.setColor(0,255,255);

	Node n2(&n,"subnode"); //attache automatiquement le nouveau noeuds n2 à n
	n2.attachMovableObject(&myen3);

	Node n3(&n2,"subnode2");
	n3.attachMovableObject(&myen4);

	Node n4(&n,"subNode3");
	n4.attachMovableObject(&myen5);
	n4.translate(-20,20,0);

	n.translate(20,-15,0); 
	myen.translate(20,0,0);
	myen5.translate(100,0,0);
	myen5.rotateX(PI/6);

	n.attachMovableObject(&en6);
//	n.attachMovableObject(&l);

	Vector4 camPos(-25,+25,0,1); //position de la cam
	double fov = 10;
	double neaR = 0.1, faR = 25;

	Camera cam("Mycam",camPos,fov,neaR,faR);
	Render r(&cam,&n,"Experiment",e3d_SFMLRender); 

	en6.rotateX(PI/6);
	
	int frames = 0;
	auto start = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> diff;
	while(1)
	{
		r.clean(); //On efface l'image
		for (int i = 0; i < 100000; i++) {
			n.rotateY(PI / 8000);
			en6.rotateX(PI / 2500);
		}
		r.start(); //On fais le rendu à partir du RootNode
		r.update(); //On met à jour l'image

		diff = std::chrono::system_clock::now() - start;
		if (diff.count() > 1000) {
			std::cout << "Frame : " << frames << std::endl;
			std::cout << diff.count() << std::endl;
			std::cout << "FPS : " << (1000.0*frames) / diff.count() << std::endl;
			start = std::chrono::system_clock::now();
			frames = 0;
		}
		frames++;
	}	

	Object::cleanPool();
	
}

int main(void)
{
	exemple();
    system("PAUSE");
    
    return 0;
}


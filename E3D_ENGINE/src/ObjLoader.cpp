#include "ObjLoader.h"

namespace e3d {

ObjLoader::ObjLoader() 
{
	
}


ObjLoader::~ObjLoader(void)
{

}

string doubleSlash(string s)
{
    //Remplace "//" par "/1/".
    string s1="";
    for(unsigned int i=0;i<s.size();i++)
    {
        if(i<s.size()-1&&s[i]=='/'&&s[i+1]=='/')
        {
            s1+="/1/";
            i++;
        }
        else
            s1+=s[i];
    }
    return s1;
}

string remplacerSlash(string s)
{
    //Remplace les '/' par des espaces.
    string ret="";
    for(unsigned int i=0;i<s.size();i++)
    {
        if(s[i]=='/')
            ret+=' ';
        else
            ret+=s[i];
    }
    return ret;
}

vector<string> splitSpace(string s)
{
    //Eclate une chaîne au niveau de ses espaces.
    vector<string> ret;
    string s1="";
    for(unsigned int i=0;i<s.size();i++)
    {
        if(s[i]==' '||i==s.size()-1)
        {
            if(i==s.size()-1)
                s1+=s[i];
            ret.push_back(s1);
            s1="";
        }
        else
            s1+=s[i];
    }
    return ret;
}

double* vector2float(vector<double>& tab)
{
    double* t=NULL;
    t=(double*)malloc(tab.size()*sizeof(double));
    if(t==NULL||tab.empty())
    {
        double *t1=(double*)malloc(sizeof(double)*3);
        for(int i=0;i<3;i++)
            t1[i]=0.;
        return t1;
    }

    for(unsigned int i=0;i<tab.size();i++)
        t[i]=tab[i];
    return t;
}

string get_directory(string s)
{
    string s1="",s2="";
    for(unsigned int i=0;i<s.size();i++)
    {
        if(s[i]=='/'||s[i]=='\\')
        {
            s1+=s2+"/";
            s2="";
        }
        else
            s2+=s[i];
    }
    return s1;
}
/*! Parse separator. */
const char* parseSep(const char*& token)
{
    size_t sep = strspn(token, " \t");
    if (!sep) throw std::runtime_error("separator expected");
    return token+=sep;
}

/*! Read float from a string. */
float getFloat(const char*& token) 
{
    token += strspn(token, " \t");
    float n = (float)atof(token);
    token += strcspn(token, " \t\r");
    return n;
}

/*! Read Vec2f from a string. */
Vector4 getVec2f(const char*& token) 
{
    float x = getFloat(token);
    float y = getFloat(token);
	return Vector4(x,y,0,1);
}

/*! Read Vec3f from a string. */
Vector4 getVec3f(const char*& token) 
{
    float x = getFloat(token);
    float y = getFloat(token);
    float z = getFloat(token);
	return Vector4(x, y, z,1);
}

/*! Determine if character is a separator. */
bool isSep(const char c) 
{
    return (c == ' ') || (c == '\t');
}



Vertex ObjLoader::getInt3(const char*& token)
{
    Vertex v(-1);
    v.v = fix_v(atoi(token));
    token += strcspn(token, "/ \t\r");
    if (token[0] != '/') 
		return(v);
	token++;
    
    // it is i//n
    if (token[0] == '/') 
	{
        token++;
        v.vn = fix_vn(atoi(token));
        token += strcspn(token, " \t\r");
        return(v);
    }
    
    // it is i/t/n or i/t
    v.vt = fix_vt(atoi(token));
    token += strcspn(token, "/ \t\r");
    if (token[0] != '/') return(v);
		token++;
    
    // it is i/t/n
    v.vn = fix_vn(atoi(token));
    token += strcspn(token, " \t\r");

return(v);
}

const char* parseSepOpt(const char*& token) {
    return token+=strspn(token, " \t");
}

Mesh* ObjLoader::load(const string& name, const string& filename)
{
	/* Cree un object de type Mesh*/ 
	/* On s'occupe pour l'instant que des vertex et des _polygones */
	_m = new Mesh(name);

	ifstream f(filename.c_str(), ios::in);
	string line, curname="";

	std::ifstream ifs;
    std::string path = filename;
    try {
        ifs.open(filename);
        if (ifs.fail()) throw std::runtime_error("can't open file " + std::string(filename));
 
		//std::shared_ptr<Material> defaultMaterial(new Material);
       // curMaterial = defaultMaterial;
 
        char line[1024]; 
        while (ifs.peek() != EOF)
        {
            ifs.getline(line, sizeof(line), '\n');
            const char* token = line + strspn(line, " \t"); // ignore space and tabs
 
            if (token[0] == 0) continue;
            if (token[0] == 'v' && isSep(token[1])) 
			{ 
				_m->addVertex(getVec3f(token += 2)); 
			}
            if (!strncmp(token, "vn",  2) && isSep(token[2])) 
			{
				normal.push_back(getVec3f(token += 3));
			}
            if (!strncmp(token, "vt",  2) && isSep(token[2])) 
			{ 
				texture.push_back(getVec2f(token += 3)); 
			}
            if (token[0] == 'f' && isSep(token[1])) 
			{
				string line(token);
				line=doubleSlash(line); //On remplace "//" par "/1/" dans toute la ligne
				line=remplacerSlash(line); //On remplace les '/' par des espaces, ex : pour "f 1/2/3 4/5/6 7/8/9" on obtiendra "f 1 2 3 4 5 6 7 8 9"
				vector<string> termes=splitSpace(line.substr(2)); //On éclate la chaîne en ses espaces (le substr permet d'enlever "f ")

                if(termes.size()==3 || termes.size()==4) //On aurait très bien pu mettre i<ndonnees mais je veux vraiment limiter à 3 ou 4
                {
                    _m->addPolygone(Polygone(atoi(termes[0].c_str()),atoi(termes[1].c_str()),atoi(termes[2].c_str())));
                }
                if(termes.size()==9) //S'il n'y a que 3 sommets on duplique le dernier pour faire un quad ayant l'apparence d'un triangle
                {
                   _m->addPolygone(Polygone(atoi(termes[0].c_str()),atoi(termes[3].c_str()),atoi(termes[6].c_str())));
                }
			}
            /*! use material 
            if (!strncmp(token, "usemtl", 6) && isSep(token[6]))
            {
                flushFaceGroup();
                std::string name(parseSep(token += 6));
                if (materials.find(name) == materials.end()) curMaterial = defaultMaterial;
                else curMaterial = materials[name];
                continue;
            } */
             
            /* load material library 
            if (!strncmp(token, "mtllib", 6) && isSep(token[6])) 
			{
               // loadMTL(path + "/" + std::string(parseSep(token += 6)));
                continue;
            } */
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    ifs.close();

return _m;
}


void ObjLoader::charger_mtl(string nom)
{
	/*
    bool d_dabord=false;// Si l'opacité est ecrite avant la couleur
    std::string temp ;//variable utile
	std::string temp2 ;//variable utile

    ifstream fichier(nom.c_str(),ios::in);
    string curname="";
    if(fichier)
    {
        string ligne="";
        while(getline(fichier,ligne))
        {
            while(ligne[0]=='\t') ligne = ligne.substr(1);// Cas ou les tabulations sont utilisées
            if(ligne[0]=='n') //nouveau materiau
                curname=ligne.substr(7);

            else if(ligne[0]=='K'&&ligne[1]=='d') //couleur
            {
                vector<string> termes=splitSpace(ligne.substr(3));
                materiaux.push_back(new Material((float)strtod(termes[0].c_str(),NULL),(float)strtod(termes[1].c_str(),NULL),(float)strtod(termes[2].c_str(),NULL),curname));
               if(d_dabord)
				   materiaux[materiaux.size()-1]->getColor().setX(strtod(temp.c_str(),NULL));
            }
            else if(ligne[0]=='m'&&ligne[5]=='d')//map_Kd (texture)
            {
                if(ligne[9]==' ') ligne = "map_Kd "+ligne.substr(31);
                string f=get_directory(nom)+ligne.substr(7);
              //  texture=loadTexture(f.c_str());
            }
            else if(ligne[0]=='d') //opacité
            {
                string n=temp=ligne.substr(2);
                if(!materiaux.size())d_dabord = true ;

                if(!d_dabord)
					materiaux[materiaux.size()-1]->getColor().setX(strtod(n.c_str(),NULL));

            }
        }
        fichier.close();
    }
    else
    {
        fprintf(stderr,"Erreur lors de la lecture de %s...",nom.c_str());
        exit(EXIT_FAILURE);
    }*/
}
             
}
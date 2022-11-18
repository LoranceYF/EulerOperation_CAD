#ifndef MODEL
#define MODEL

#include"vec3f.h"
#include<vector>

using std::vector;

typedef int Id;

class WrokSpace;
class Solid;
class Face;
class Loop;
class HalfEdge;
class Vertex;
class Edge;
/*
class WorkSpace {
public:
	vector<Solid*> sList;
};
*/

class Solid {
public:
	/*
	Solid() : sno(-1),sWorkSpace(nullptr) {}
	Solid(WorkSpace* ws) :sWorkSpace(ws), sno(ws->sList.size()) {
		ws->sList.push_back(this);
	}
	Id sno;
	*/
	vector<Face*> Sfaces;
	vector<Vertex*> Svertexs;
	//WorkSpace *sWorkSpace;

	int removeF(const Id &fid);	//失败返回-1
	void show();
	void clear();
};

class Face
{
public:
	Face() : fSolid(nullptr), fno(-1) {}
	Face(Solid* s) : fSolid(s), fno(s->Sfaces.size()) {
		fSolid->Sfaces.push_back(this);
	}
	Id fno;
	Solid *fSolid;
	vector<Loop*> Floop;

	HalfEdge *fhel(const Id &vst);	//在面里的所有环中，寻找以vst为起点的半边
	HalfEdge *fhel2(const Id &vst,const Id &vdst);	//在面里的所有环中，寻找以vst为起点，vdst为终点的半边
	void show();
};

class Loop
{
public:
	Loop() : lFace(nullptr), Lhe(nullptr), in(false) {}
	Loop(Face* f) :lFace(f), Lhe(nullptr), in(false) {
		f->Floop.push_back(this);
	}
	Face *lFace;
	HalfEdge *Lhe;
	bool in;

	HalfEdge *fhe(const Id &vst);
	HalfEdge *fhe2(const Id &vst,const Id &vdst);
	void renewLoop();	//刷新环内每条半边，使其指向自己
	void show();
};

class HalfEdge
{
public:
	HalfEdge() : heLoop(nullptr), pre(nullptr), nxt(nullptr), edge(nullptr), stv(nullptr), endv(nullptr) {}
	HalfEdge(Loop* l) : heLoop(l), pre(nullptr), nxt(nullptr), edge(nullptr), stv(nullptr), endv(nullptr) {
		l->Lhe = this;
	}
	Loop *heLoop;
	Edge *edge;
	Vertex *stv, *endv;

	HalfEdge *pre, *nxt;
	HalfEdge* mate();
};

class Edge
{
public:
	Edge() :/* preve(nullptr), nexte(nullptr),*/ he1(nullptr), he2(nullptr) {}
	//Edge *preve, *nexte;
	HalfEdge *he1, *he2;
};

class Vertex
{
public:
	Vertex() :vno(-1), vcoord(vec3f(0, 0, 0)), vHe(nullptr) {}
	Vertex(Solid *s, const vec3f &v) :vno(s->Svertexs.size()), vcoord(v), vHe(nullptr) {
		s->Svertexs.push_back(this);
	}
	Id vno;
	HalfEdge *vHe;	//记录以该结点为起始点，最新建立的一条半边。用于控制在复杂环路内，mef构造新换的走向
	Solid *vSolid;
	vec3f vcoord;
};

#endif // !MODEL





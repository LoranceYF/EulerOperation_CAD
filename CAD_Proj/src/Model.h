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

	int removeF(const Id &fid);	//ʧ�ܷ���-1
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

	HalfEdge *fhel(const Id &vst);	//����������л��У�Ѱ����vstΪ���İ��
	HalfEdge *fhel2(const Id &vst,const Id &vdst);	//����������л��У�Ѱ����vstΪ��㣬vdstΪ�յ�İ��
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
	void renewLoop();	//ˢ�»���ÿ����ߣ�ʹ��ָ���Լ�
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
	HalfEdge *vHe;	//��¼�Ըý��Ϊ��ʼ�㣬���½�����һ����ߡ����ڿ����ڸ��ӻ�·�ڣ�mef�����»�������
	Solid *vSolid;
	vec3f vcoord;
};

#endif // !MODEL





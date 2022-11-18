#include"Model.h"

Solid *mvfs(const vec3f &_vcoord) {
	Solid *s0 = new Solid();

	Face *f0 = new Face(s0);
	Vertex *v0 = new Vertex(s0, _vcoord);

	return s0;
}

void _mev(Face *&f0, Loop *&lp0, HalfEdge *&he, Vertex *&vst, Vertex *&vdst) {
	if (!lp0) {
		Loop *lp = new Loop(f0);
		lp0 = lp;
	}
	HalfEdge *nhe1 = new HalfEdge(lp0);
	HalfEdge *nhe2 = new HalfEdge(lp0);
	Edge *ne = new Edge();

	ne->he1 = nhe1;
	ne->he2 = nhe2;

	nhe1->edge = ne;
	nhe2->edge = ne;

	nhe1->stv = vst;
	nhe1->endv = vdst;
	vst->vHe = nhe1;

	nhe2->stv = vdst;
	nhe2->endv = vst;
	vdst->vHe = nhe2;

	nhe1->nxt = nhe2;
	nhe2->pre = nhe1;

	lp0->Lhe = nhe1;

	if (he) {
		nhe1->pre = he->pre;
		he->pre->nxt = nhe1;
		nhe2->nxt = he;
		he->pre = nhe2;
	}
	else {
		nhe2->nxt = nhe1;
		nhe1->pre = nhe2;
	}

	return;
}

Id mev(Solid *&s,const Id &fid,const Id &vst, const vec3f &_vcoord) {
	Face *f0;
	if (s->Sfaces.size() <= fid || !(f0 = s->Sfaces[fid])) {
		printf("cannot find face %d\n", fid);
		return -1;
	}

	Vertex *v0;
	if (s->Svertexs.size() <= vst || !(v0 = s->Svertexs[vst])) {
		printf("cannot find vertex %d\n", vst);
		return -1;
	}

	Loop *lp0(nullptr);
	HalfEdge *he0(nullptr);

	if (!f0->Floop.empty()) {
		he0 = v0->vHe;
		if (!he0 || he0->heLoop->lFace != f0) {
			he0 = f0->fhel(vst);
			if (!he0) {
				printf("cannot find vertex %d in face %d\n", vst, fid);
				return -1;
			}
		}
		lp0 = he0->heLoop;
	}

	/*
		if (!f0->Floop.empty()) {
			he0 = f0->fhel(vst);
			if (!he0) {
				printf("cannot find vertex %d in face %d\n", vst, f);
				return 1;
			}
			lp0 = he0->heLoop;
	;	}
	*/
	Vertex *v1 = new Vertex(s, _vcoord);

	_mev(f0, lp0, he0, v0, v1);

	return v1->vno;
}

void _mef(Loop *&lp0, Vertex *&v1, Vertex *&v2, HalfEdge *&he1, HalfEdge *&he2, Loop *&nLoop) {
	Edge *ne = new Edge();
	HalfEdge *nhe1 = new HalfEdge(lp0);
	HalfEdge *nhe2 = new HalfEdge(nLoop);

	ne->he1 = nhe1;
	ne->he2 = nhe2;

	nhe1->edge = ne;
	nhe2->edge = ne;

	nhe1->stv = v1;
	nhe1->endv = v2;
	nhe2->stv = v2;
	nhe2->endv = v1;

	nhe1->pre = he1->pre;
	nhe1->nxt = he2;
	nhe2->pre = he2->pre;
	nhe2->nxt = he1;

	he1->pre->nxt = nhe1;
	he1->pre = nhe2;
	he2->pre->nxt = nhe2;
	he2->pre = nhe1;

	lp0->renewLoop();
	nLoop->renewLoop();

	return;
}

//vst,vdst点选取的不同会导致新面与旧面所分开得到的环路不同
Id mef(Solid *&s,const Id &fid,const Id &vst,const Id &vdst) {
	Face *f0;
	if (s->Sfaces.size() <= fid || !(f0 = s->Sfaces[fid])) {
		printf("cannot find face %d\n", fid);
		return -1;
	}

	Vertex *v1;
	if (s->Svertexs.size() <= vst || !(v1 = s->Svertexs[vst])) {
		printf("cannot find vertex %d\n", vst);
		return -1;
	}

	Vertex *v2;
	if (s->Svertexs.size() <= vdst || !(v2 = s->Svertexs[vdst])) {
		printf("cannot find vertex %d\n", vdst);
		return -1;
	}

	Loop *lp0(nullptr);
	HalfEdge *he1(nullptr);
	HalfEdge *he2(nullptr);

	//如果顶点指向边在面内，则不用查找，否则在所选面内查找一个新的半边（如果进行了查找操作则不能保证新环走向）
	he1 = (v1->vHe->heLoop->lFace == f0) ? v1->vHe : f0->fhel(vst);
	he2 = (v2->vHe->heLoop->lFace == f0) ? v2->vHe : f0->fhel(vdst);

	lp0 = he1->heLoop;
	if (lp0 != he2->heLoop) {
		printf("cannot find loop with vertex %d and vertex %d\n", vst, vdst);
		return -1;
	}

	Face *nFace = new Face(s);
	Loop *nLoop = new Loop(nFace);

	_mef(lp0, v1, v2, he1, he2, nLoop);

	return nFace->fno;
}

void _kemr(Face *f0, HalfEdge *he) {
	Loop *lp = he->heLoop;
	Loop *nlp;
	HalfEdge *mhe = he->mate();

	he->endv->vHe = he->nxt;
	he->stv->vHe = mhe->nxt;

	he->pre->nxt = mhe->nxt;
	mhe->nxt->pre = he->pre;

	mhe->pre->nxt = he->nxt;
	he->nxt->pre = mhe->pre;

	nlp = new Loop(f0);
	nlp->Lhe = mhe->nxt;
	nlp->renewLoop();
	nlp->in = true;	//构造内环，其中环的选取与he的选择有关

	lp->Lhe = he->nxt;

	delete he->edge;
	delete he;
	delete mhe;

	return;
}

//vid1所处的环会被分入内环，vid2则会被分入外环
int kemr(Solid *&s,const Id &fid,const Id &vid1,const Id &vid2) {
	Face *f0;
	if (s->Sfaces.size() <= fid || !(f0 = s->Sfaces[fid])) {
		printf("cannot find face %d\n", fid);
		return -1;
	}

	Vertex *v1;
	if (s->Svertexs.size() <= vid1 || !(v1 = s->Svertexs[vid1])) {
		printf("cannot find vertex %d\n", vid1);
		return -1;
	}

	Vertex *v2;
	if (s->Svertexs.size() <= vid2 || !(v2 = s->Svertexs[vid2])) {
		printf("cannot find vertex %d\n", vid2);
		return -1;
	}

	HalfEdge *he = f0->fhel2(vid1, vid2);
	if (!he) {
		printf("cannot find edge with vertex %d and vertex %d\n", vid1, vid2);
		return -1;
	}

	_kemr(f0, he);

	return 0;
}

void _kmfrh(Face *&f1, Face *&f2) {
	for (Loop *lp : f2->Floop) {
		lp->in = true;
		lp->lFace = f1;
		f1->Floop.emplace_back(lp);
	}
	f2->Floop.clear();
	return;
}

//将f2并入f1,即f2的所有环转换为f1的内环
int kfmrh(Solid *&s,const Id &fid1,const Id &fid2) {
	Face *f1;
	if (s->Sfaces.size() <= fid1 || !(f1 = s->Sfaces[fid1])) {
		printf("cannot find face %d\n", fid1);
		return -1;
	}

	Face *f2;
	if (s->Sfaces.size() <= fid2 || !(f2 = s->Sfaces[fid2])) {
		printf("cannot find face %d\n", fid2);
		return -1;
	}

	_kmfrh(f1, f2);

	return(s->removeF(fid2));
}

//对单独一个环进行扫掠建模
void _buildloop(Solid *&s, Loop *&lp,const vec3f &_vec) {
	Loop *revlp = lp->Lhe->mate()->heLoop;	//得到当前loop的反向loop
	HalfEdge *he = lp->Lhe;
	Vertex *nv;
	Id v1, v2, vst;
	Id fid(revlp->lFace->fno);

	nv = he->stv;
	vst = v1 = mev(s, fid, nv->vno, nv->vcoord + _vec);

	he = he->pre;
	do {
		nv = he->stv;
		v2 = mev(s, fid, nv->vno, nv->vcoord + _vec);
		mef(s, fid, v1, v2);	//v1,v2的选取顺序可以保证fid始终为所需要的面
		v1 = v2;
		he = he->pre;
	} while (he != lp->Lhe);

	v2 = vst;

	mef(s, fid, v1, v2);

	return;
}

//对一个合法的平面进行扫掠操作
int sweep(Solid *&s,const Id &fid,const vec3f &_vec) {
	Face *f;
	if (s->Sfaces.size() <= fid || !(f = s->Sfaces[fid])) {
		printf("cannot find face %d\n", fid);
		return -1;
	}

	Loop *outer(nullptr);
	vector<Loop*> inner;

	for (Loop *lp : f->Floop) {
		if (lp->in) {
			inner.emplace_back(lp);
		}
		else {
			if (!outer) {
				outer = lp;
			}
			else {
				printf("found mutiple outer loops in face %d\n", fid);
				return -1;
			}
		}
	}

	Id outerFid = outer->Lhe->mate()->heLoop->lFace->fno;
	_buildloop(s, outer, _vec);

	for (Loop *ilp : inner) {
		Id innerFid = ilp->Lhe->mate()->heLoop->lFace->fno;
		_buildloop(s, ilp, _vec);
		kfmrh(s, outerFid, innerFid);
	}

	return 0;
}
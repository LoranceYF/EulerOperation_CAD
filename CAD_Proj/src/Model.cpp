#include"Model.h"
/*
Face *Solid::fface(Id f) {
	Face *tmpf = this->Sfaces;

	if (tmpf) {
		if (tmpf->fno != f) {
			do
			{
				tmpf = tmpf->nextf;
			} while (tmpf != this->Sfaces && tmpf->fno != f);
		}
	}
	else {
		return nullptr;
	}
	return tmpf->fno == f ? tmpf : nullptr;
}
*/

int Solid::removeF(const Id &fid) {
	Face *f = Sfaces[fid];
	if (f->Floop.empty()) {
		delete f;
		Sfaces.erase(Sfaces.begin() + fid);
		for (size_t i = fid; i < Sfaces.size(); ++i) {
			Sfaces[i]->fno = i;
		}
	}
	else {
		printf("face %d is not empty!\n", fid);
		return -1;
	}
	return 0;
}

void Solid::clear() {};

HalfEdge *Face::fhel(const Id &vst) {
	HalfEdge *he(nullptr);
	for (Loop *tmpL : Floop) {
		he = tmpL->fhe(vst);
		if (he) break;
	}

	return he;
}

void Solid::show() {
	printf("---------------\n");
	printf("Vertex num:%d\n", Svertexs.size());
	printf("Face num:%d\n", Sfaces.size());
	printf("---Vertexs info---\n");
	int cnt = -1;
	for (Vertex *v : Svertexs) {
		if (++cnt > 2) {
			printf("\n");
			cnt = 0;
		}
		printf("Vertex %d:(%.2lf,%.2lf,%.2lf)\t", v->vno, v->vcoord.x, v->vcoord.y, v->vcoord.z);
	}
	printf("\n---Faces info---\n");
	for (Face *f : Sfaces) {
		f->show();
	}
	return;
}

HalfEdge *Face::fhel2(const Id &vst,const Id &vdst) {
	HalfEdge *he(nullptr);
	for (Loop *tmpL : Floop) {
		he = tmpL->fhe2(vst, vdst);
		if (he) break;
	}

	return he;
}

void Face::show() {
	printf("Face %d contains %d loops:\n", fno, Floop.size());
	for (Loop *lp : Floop) {
		printf("\t");
		lp->show();
	}
	return;
}

HalfEdge *Loop::fhe(const Id &vst) {
	HalfEdge *ret(nullptr);

	if (Lhe) {
		if (Lhe->stv->vno == vst) {
			ret = Lhe;
		}
		else {
			ret = Lhe->nxt;
			while (Lhe != ret && ret->stv->vno != vst) {
				ret = ret->nxt;
			}
			ret = (ret == Lhe ? nullptr : ret);
		}
	}
	return ret;
}

HalfEdge *Loop::fhe2(const Id &vst,const Id &vdst) {
	HalfEdge *ret(nullptr);

	if (Lhe) {
		if (Lhe->stv->vno == vst && Lhe->endv->vno == vdst) {
			ret = Lhe;
		}
		else {
			ret = Lhe->nxt;
			while (Lhe != ret && (ret->stv->vno != vst || ret->endv->vno != vdst)) {
				ret = ret->nxt;
			}
			ret = (ret == Lhe ? nullptr : ret);
		}
	}
	return ret;
}

HalfEdge *HalfEdge::mate() {
	return this != edge->he1 ? edge->he1 : edge->he2;
}

void Loop::renewLoop() {
	HalfEdge *tmp = Lhe;
	do {
		tmp->heLoop = this;
		tmp = tmp->nxt;
	} while (tmp != Lhe);
	return;
}

void Loop::show() {
	HalfEdge *he = Lhe;
	if (!he) {
		printf("empty loop\n");
		return;
	}
	if (in) {
		printf("inner:");
	}
	else {
		printf("outer;");
	}

	/*
	printf("%d", he->endv->vno);
	do {
		printf("->%d", he->stv->vno);
		he = he->pre;
	} while (he != Lhe);
	*/

	printf("%d", he->stv->vno);
	do {
		printf("->%d", he->endv->vno);
		he = he->nxt;
	} while (he != Lhe);

	printf("\n");

	return;
}
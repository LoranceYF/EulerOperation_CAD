#include <GL/glut.h>

#include"Display.h"

GLuint Display(Solid *&s)
{
	GLuint id = glGenLists(1);  // create a display list
	if (!id) return id;          // failed to create a list, return 0

	GLUtesselator *tess = gluNewTess(); // create a tessellator
	if (!tess) return 0;  // failed to create tessellation object, return 0

	// register callback functions
	gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK *)())tessBeginCB);
	gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK *)())tessEndCB);
	gluTessCallback(tess, GLU_TESS_ERROR, (void (CALLBACK *)())tessErrorCB);
	gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK *)())tessVertexCB);

	glNewList(id, GL_COMPILE);
	glColor3f(0.5, 1, 1);
	for (Face *f : s->Sfaces) {
		gluTessBeginPolygon(tess, 0);
		for (Loop *lp : f->Floop) {
			gluTessBeginContour(tess);
			HalfEdge *he = lp->Lhe;
			do {
				he = he->nxt;
				gluTessVertex(tess, he->stv->vcoord, he->stv->vcoord);
			} while (he != lp->Lhe);
			gluTessEndContour(tess);
		}
		gluTessEndPolygon(tess);
	}
	glEndList();

	gluDeleteTess(tess);        // delete after tessellation

	// DEBUG //
	// print out actual GL calls that are performed
	cout << endl;
	cout << "Draw Solid\n";
	cout << "===============\n";
	cout << ss.str().c_str() << endl;
	ss.str("");                     // clear string buffer

	return id;      // return handle ID of a display list
}
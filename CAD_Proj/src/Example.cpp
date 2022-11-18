#include"Op.h"

Solid *CreateModel1() {
	Solid *s = mvfs(vec3f(0, 0, 0));

	mev(s, 0, 0, vec3f(4, 0, 0));
	mev(s, 0, 1, vec3f(4, 4, 0));
	mev(s, 0, 2, vec3f(0, 4, 0));

	mef(s, 0, 3, 0);

	mev(s, 1, 0, vec3f(1, 1, 0));
	mev(s, 1, 4, vec3f(1, 3, 0));
	mev(s, 1, 5, vec3f(3, 3, 0));
	mev(s, 1, 6, vec3f(3, 1, 0));

	mef(s, 1, 4, 7);

	kemr(s, 1, 4, 0);

	sweep(s, 1, vec3f(0, 0, 1));

	return s;
}

Solid *CreateModel2() {
	Solid *s = mvfs(vec3f(0, 3, 0));

	mev(s, 0, 0, vec3f(2, 2, 0));
	mev(s, 0, 1, vec3f(2, -2, 0));
	mev(s, 0, 2, vec3f(0, -3, 0));
	mev(s, 0, 3, vec3f(-2, -2, 0));
	mev(s, 0, 4, vec3f(-2, 2, 0));

	mef(s, 0, 5, 0);
	//此时有两个面，面0朝下，面1朝上

	mev(s, 0, 0, vec3f(0, 2, 0));
	mev(s, 0, 6, vec3f(1, 1, 0));
	mev(s, 0, 7, vec3f(1, 0, 0));
	mev(s, 0, 8, vec3f(-1, 0, 0));
	mev(s, 0, 9, vec3f(-1, 1, 0));

	mef(s, 0, 6, 10);
	
	kemr(s, 0, 6, 0);
	//此时面0带有一个内环，面1为大环面，朝上；面2为小环面，朝下

	mev(s, 0, 3, vec3f(0, -2, 0));
	mev(s, 0, 11, vec3f(-1, -1, 0));
	mev(s, 0, 12, vec3f(1, -1, 0));
	
	mef(s, 0, 11, 13);

	kemr(s, 0, 11, 3);

	sweep(s, 0, vec3f(0, 0, 1));

	return s;
}


Solid *CreateModel3() {
	Solid *s = mvfs(vec3f(0, 3, 0));

	mev(s, 0, 0, vec3f(2, 2, 0));
	mev(s, 0, 1, vec3f(2, -2, 0));
	mev(s, 0, 2, vec3f(0, -3, 0));
	mev(s, 0, 3, vec3f(-2, -2, 0));
	mev(s, 0, 4, vec3f(-2, 2, 0));

	mef(s, 0, 5, 0);
	//此时有两个面，面0朝下，面1朝上

	mev(s, 0, 0, vec3f(0, 2, 0));
	mev(s, 0, 6, vec3f(1, 1, 0));
	mev(s, 0, 7, vec3f(1, 0, 0));
	mev(s, 0, 8, vec3f(-1, 0, 0));
	mev(s, 0, 9, vec3f(-1, 1, 0));

	mef(s, 0, 6, 10);

	kemr(s, 0, 6, 0);
	//此时面0带有一个内环，面1为大环面，朝上；面2为小环面，朝下

	mev(s, 0, 3, vec3f(0, -2, 0));
	mev(s, 0, 11, vec3f(-1, -1, 0));
	mev(s, 0, 12, vec3f(1, -1, 0));

	mef(s, 0, 11, 13);

	kemr(s, 0, 11, 3);

	sweep(s, 0, vec3f(0, -2.0f, 1.0f));

	return s;
}
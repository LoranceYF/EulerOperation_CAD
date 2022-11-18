#ifndef OP
#define OP

#include"Model.h"

Solid *mvfs(const vec3f &_vcoord);
Id mev(Solid *&s, const Id &fid, const Id &vst, const vec3f &_vcoord);	//返回新点的Id
Id mef(Solid *&s, const Id &fid, const Id &vst, const Id &vdst);	//返回新面的Id
int kemr(Solid *&s, const Id &fid, const Id &vst, const Id &vdst);	//失败返回-1
int kfmrh(Solid *&s, const Id &fid1, const Id &fid2);	//将f2并入f1，失败返回-1
int sweep(Solid *&s, const Id &fid, const vec3f &_vec);
#endif // !OP
#ifndef OP
#define OP

#include"Model.h"

Solid *mvfs(const vec3f &_vcoord);
Id mev(Solid *&s, const Id &fid, const Id &vst, const vec3f &_vcoord);	//�����µ��Id
Id mef(Solid *&s, const Id &fid, const Id &vst, const Id &vdst);	//���������Id
int kemr(Solid *&s, const Id &fid, const Id &vst, const Id &vdst);	//ʧ�ܷ���-1
int kfmrh(Solid *&s, const Id &fid1, const Id &fid2);	//��f2����f1��ʧ�ܷ���-1
int sweep(Solid *&s, const Id &fid, const vec3f &_vec);
#endif // !OP
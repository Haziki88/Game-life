#pragma once
#include"../Base/Base.h"
#include"fmfmap.h"

//�����`�b�v�ԍ�
#define NULL_TIP 0
#define MAP_TIP_SIZE 16
#define MAP_WIDTH 128
#define MAP_HEIGHT 128
class Map : public Base, CFmfMap {
private:
	CImage m_map_tip[2];
	CImage m_backGround;
public:
	Map(int nextArea, const CVector2D& nextplayerpos);
	~Map();
	void Draw();
	//�w����W�̃`�b�v�ԍ����擾
	int GetTip(const CVector2D& pos ,int* tx = nullptr, int* ty = nullptr);
	//�w���A�w��s�̃}�b�v�`�b�v���擾
	int GetTip(int x, int y);
	//�}�b�v�`�b�v�Ƃ̓����蔻��
	int CollisionMap(const CVector2D& pos);
	int CollisionMap(const CVector2D& pos, const CRect& rect, CVector2D* rev_pos);
};
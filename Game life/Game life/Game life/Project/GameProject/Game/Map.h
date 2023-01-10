#pragma once
#include"../Base/Base.h"
#include"fmfmap.h"

//透明チップ番号
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
	//指定座標のチップ番号を取得
	int GetTip(const CVector2D& pos ,int* tx = nullptr, int* ty = nullptr);
	//指定列、指定行のマップチップを取得
	int GetTip(int x, int y);
	//マップチップとの当たり判定
	int CollisionMap(const CVector2D& pos);
	int CollisionMap(const CVector2D& pos, const CRect& rect, CVector2D* rev_pos);
};
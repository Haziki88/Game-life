#pragma once
#include"Map.h"
class Dijkstra :public Base{
public:
	struct CELL {
		int x;
		int y;
	};
private:
	unsigned char m_score[MAP_HEIGHT][MAP_WIDTH];
	int m_path_size;
	CELL m_goal;
	static const unsigned int m_max_value = 255;
	CELL m_path[m_max_value];
	bool _FindShorttestPath(Map*map,int x,int y,unsigned char score);
public:
	Dijkstra();
	~Dijkstra();
	bool FindShortestPath(Map* map, const CVector2D& start, const CVector2D& goal);
	int GetPathSize() {
		return m_path_size;
	}
	CVector2D GetPathPoint(unsigned char idx) {
		return CVector2D(m_path[idx].x * MAP_TIP_SIZE + MAP_TIP_SIZE / 2,
			m_path[idx].y * MAP_TIP_SIZE + MAP_TIP_SIZE / 2);
	}
	void Draw();
};
#include "Dijkstra.h"


Dijkstra::Dijkstra()
:Base(eType_Dijkstra)
{
	m_path_size = 0;
	memset(m_score, m_max_value, sizeof(m_score));
}

Dijkstra::~Dijkstra()
{

}

bool Dijkstra::_FindShorttestPath(Map* map, int x, int y, unsigned char score)
{
	//壁なら調べない
	if (map->GetTip(x, y) < 125) return false;
	//既に最短距離の経路があれば調べない
	if (m_score[y][x] <= score) return false;
	//距離更新
	m_score[y][x] = score;
	//目的地
	if (x == m_goal.x && y == m_goal.y) {
		//移動経路更新
		m_path[score] = { x,y };
		//距離更新
		m_path_size = score + 1;
		return true;
	}

	//目的への経路か
	bool ret = false;

	//次の調べる位置　←↑→↓
	int next_x[4] = { -1,0,1,0 };
	int next_y[4] = { 0,-1,0,1 };
	//次は上下左右を調べる
	for (int i = 0; i < 4; i++) {
		int xx = x + next_x[i];
		int yy = y + next_y[i];
		//再帰的に呼び出して経路探索
		bool find = _FindShorttestPath(map, xx, yy, score + 1);
		//目的地に届く経路なら
		if (find) {
			//移動経路更新
			m_path[score] = { x,y };
			ret = true;
		}
	}
	return ret;
}

bool Dijkstra::FindShortestPath(Map* map,const CVector2D& start, const CVector2D& goal)
{
	//開始地点、目的地の座標をマップデータ上での行と列に変換
	int start_x = start.x / MAP_TIP_SIZE;
	if (start_x < 0 || start_x >= MAP_WIDTH) return false;
	int start_y = start.y / MAP_TIP_SIZE;
	if (start_y < 0 || start_y >= MAP_HEIGHT) return false;
	int goal_x = goal.x / MAP_TIP_SIZE;
	if (goal_x < 0 || goal_x >= MAP_WIDTH) return false;
	int goal_y = goal.y / MAP_TIP_SIZE;
	if (goal_y < 0 || goal_y >= MAP_HEIGHT) return false;

	//距離データリセット
	memset(m_score, m_max_value, sizeof(m_score));
	//目的地設定
	m_goal = { goal_x,goal_y };
	//経路開始地点は自分の位置
	m_path[0] = { start_x,start_y };
	m_path_size = 0;
	//再帰的に呼び出して経路探索
	_FindShorttestPath(map, start_x, start_y, 1);

	//パスの数が更新されていれば、目的への経路がm_pathへ格納されている
	return (m_path_size>0) ? true:false;
}
void Dijkstra::Draw()
{
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (m_score[i][j] < 255)
				FONT_T()->Draw(MAP_TIP_SIZE / 2 + MAP_TIP_SIZE * j-m_scroll.x, MAP_TIP_SIZE / 2 + MAP_TIP_SIZE * i-m_scroll.y,
					1, 0, 0, "%d", m_score[i][j]);
		}
	}
}
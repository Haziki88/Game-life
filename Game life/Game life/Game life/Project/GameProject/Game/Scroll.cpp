#include "Scroll.h"
Scroll::Scroll(const CVector2D& screen_size) :Base(eType_Scroll), m_player(nullptr) {
	m_screen_size = screen_size;
	m_scale = 0.7;
}

void Scroll::Draw() {
	//プレイヤーが居なければ
	if (!m_player) {
		//プレイヤーを探索
		m_player = Base::FindObject(eType_Player);
	}
	else {
		//プレイヤーが削除されそうなら
		if (m_player->m_kill)
			//ポインタを解除
			m_player = nullptr;
	}
	if (HOLD(CInput::eUp))
		m_scale = max(0.7f, m_scale - 0.01f);
	if (HOLD(CInput::eDown))
		m_scale = min(1.5f, m_scale + 0.01f);
	CVector2D draw_size = m_screen_size * m_scale;

	//----①拡大縮小：画面左上が原点
	//スクロール値設定
	//if (m_player) {
		//m_scroll.x = m_player->m_pos.x - 600;
		//m_scroll.y = m_player->m_pos.y - 500;

	//}
	//ゲーム内解像度変更
	//CCamera::GetCamera()->SetSize(draw_size.x, draw_size.y);
	//----------------------------



	//-----②拡大縮小：画面中心が原点2
	if (m_player) {
		m_scroll.x = m_player->m_pos.x;
		m_scroll.y = m_player->m_pos.y - 200;
	}
	//ゲーム内解像度変更
	CCamera::GetCamera()->SetSize(draw_size.x, draw_size.y);
	//画面中心が原点になる2D用投影行列
	//※行列は2年のゲーム数学で習うため、今回はこのまま使用するのみ
	CCamera::GetCamera()->SetProjectionMatrix2D(CMatrix(
		2.0f / draw_size.x, 0.0f, 0.0f, 0.0f,
		0.0f, -2.0f / draw_size.y, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f));

	//--------------------------------
}
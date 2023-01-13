#include "Player.h"
#include "AnimData.h"
#include "Field.h"
#include "Slash.h"
#include "Effect.h"
#include"Map.h"
#include"Child.h"
#include"AreaChange.h"
Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	//画像複製
	m_img = COPY_RESOURCE("Knight", CImage);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos_old=m_pos = p;
	//中心位置設定
	m_img.SetCenter(44, 54);
	//矩形設定
	m_rect = CRect(-9, -28, 9, 0);
	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground=true;
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_damage_no = -1;
	//
	m_hp = 100;
	m_rad = 32.0f;
	m_path_idx = 0;

}
Player::~Player()
{

}
void Player::StateIdle()
{
	//移動量
	const float move_speed = 4;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 12;

	CVector2D mousePos = (CInput::GetMousePoint() + m_scroll-CVector2D(640,150))*m_scale;
	if (mousePos.x > m_pos.x) {
		m_flip = false;
	}
	else if(mousePos.x<m_pos.x) {
		m_flip = true;
	}
	//移動
	
		if (PUSH(CInput::eMouseL)) {
			if (Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Field))) {
				m_path.FindShortestPath(m,m_pos, mousePos);
				
				m_path_idx = 0;
			}
		}
	
		
	if (m_path_idx < m_path.GetPathSize()) {
		CVector2D vec = m_path.GetPathPoint(m_path_idx) - m_pos;
		if (vec.Length() > 8) {
			m_ang = atan2(vec.x, vec.y);
			CVector2D dir(sin(m_ang), cos(m_ang));
			m_pos += dir * move_speed;
			move_flag = true;
		}
		else {
			m_path_idx++;
		}
	}
	
	//ジャンプ
	/*if (m_is_ground && PUSH(CInput::eButton2)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
	}*/

	//攻撃
		//攻撃状態へ移行

	//攻撃
	if (PUSH(CInput::eMouseR)) {
		//攻撃状態へ移行
		m_state = eState_Attack;
		m_attack_no++;
	}

	//ジャンプ中なら
	if (!m_is_ground) {
		/*if (m_vec.y < 0)
			//上昇アニメーション
			m_img.ChangeAnimation(eAnimJumpUp, false);
		else
			//下降アニメーション
			m_img.ChangeAnimation(eAnimJumpDown, false);*/
	}
	//移動中なら
	else
	{
		if (move_flag) {
			//走るアニメーション
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			//待機アニメーション
			m_img.ChangeAnimation(eAnimIdle);
		}

	}


}
void Player::StateAttack()
{
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack01, false);
	//2番目のパターンなら
	//if (m_img.GetIndex() == 2) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-32, -16), m_flip, eType_Player_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(32, -16), m_flip, eType_Player_Attack, m_attack_no));
		}
	//}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Idle;
	}
}


void Player::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Player::StateDown()
{
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		m_kill = true;
	}
}
void Player::Update() {
	m_pos_old = m_pos;
	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
		//攻撃状態
	case eState_Attack:
		StateAttack();
		break;
		//ダメージ状態
	case eState_Damage:
		StateDamage();
		break;
		//ダウン状態
	case eState_Down:
		StateDown();
		break;
	}
	//落ちていたら落下中状態へ移行
	//if (m_is_ground && m_vec.y > GRAVITY * 4)
		//m_is_ground = false;
	//重力による落下
	//m_vec.y += GRAVITY;
	//m_pos += m_vec;


	//アニメーション更新
	m_img.UpdateAnimation();

	//スクロール設定
	/*m_scroll.x = m_pos.x - 1280 / 2;
	m_scroll.y = m_pos.y - 500;*/

	if (!m_enable_area_change && !m_hit_area_change)
		m_enable_area_change = true;
	m_hit_area_change = false;
}

void Player::Draw() {
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//m_path.Draw();
	if (m_path.GetPathSize() > 0) {
		Utility::DrawCircle(GetScreenPos(m_path.GetPathPoint(m_path.GetPathSize() - 1)), 16, CVector4D(1, 0, 1, 1));
	}
	Utility::DrawCircle(GetScreenPos(m_pos), 16, CVector4D(1, 0, 0, 1));
	//描画
	m_img.Draw();
	//DrawRect();
}
void Player::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_AreaChange:
		if (Base::CollisionRect(this, b)) {
			//エリアチェンジに触れている
			m_hit_area_change = true;
			//エリアチェンジ可能なら
			if (m_enable_area_change) {
				if (AreaChange* a = dynamic_cast<AreaChange*>(b)) {
					//マップとエリアチェンジオブジェクトを削除
					KillByType(eType_Field);
					KillByType(eType_AreaChange);
					//次のマップを生成
					Base::Add(new Map(a->m_nextArea, a->m_nextplayerpos));
					//エリアチェンジ一時不許可
					m_enable_area_change = false;
				}
			}
		}

		break;
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			CVector2D v;
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect,&v);
			if (t != NULL_TIP)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect,&v);
			if (t != NULL_TIP)
				m_pos.y = m_pos_old.y;
		}
		break;
	case eType_Child:
		if (Base::CollisionCircle(this, b)) {
			if (Child* c = dynamic_cast<Child*>(b)) {
				if (!c->m_parent) {
					c->m_parent = this;
					m_childs.push_back(c);
				}
			}
		}
		/*if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y));
			if (t != 0)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y));
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;*/
		//ゴール判定
	/*case eType_Goal:
		if (Base::CollisionRect(this, b)) {
			SetKill();
		}
		break;*/
		//攻撃エフェクトとの判定
	case eType_Enemy_Attack:
		//Slash型へキャスト、型変換できたら
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				//同じ攻撃の連続ダメージ防止
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;

				}
				//Base::Add(new Effect("Effect_Blood",
					//m_pos + CVector2D(0, -64), m_flip));

				//Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -64), m_flip));
			}
		}
		break;
		
		//Field型へキャスト、型変換できたら
		/*if (Field* f = dynamic_cast<Field*>(b)) {
			//地面より下にいったら
			if (m_pos.y > f->GetGroundY()) {
				//地面の高さに戻す
				m_pos.y = f->GetGroundY();
				//落下速度リセット
				m_vec.y = 0;
				//接地フラグON
				m_is_ground = true;
			}
		}
		break;*/
	}

}

void Player::EraseChild(Child* c)
{
	//リストから子を検索
	auto it = std::find(m_childs.begin(), m_childs.end(), c);
	//子　親を解除
	(*it)->m_parent = nullptr;
	m_childs.erase(it);
}

void Player::EraseAllChild()
{
	//先頭から末尾までのループ(削除するたびitが変わるので、it++はしない)
	for (auto it = m_childs.begin(); it != m_childs.end();/*it++*/) {
		//	子　親を解除
		(*it)->m_parent = nullptr;
		//親　子をリストから外す
		it = m_childs.erase(it);
	}
}





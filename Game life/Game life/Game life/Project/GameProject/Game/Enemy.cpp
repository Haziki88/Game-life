#include "Enemy.h"
#include "AnimData.h"
#include "Field.h"
#include "Slash.h"
#include "Effect.h"
#include"Map.h"
#include"Player.h"

Enemy::Enemy(const CVector2D& p, bool flip) :
	Base(eType_Enemy) {
	//画像複製
	m_img = COPY_RESOURCE("Enemysukebase", CImage);

	//m_img.Load("Image/Enemy.png", enemy_anim_data, 256, 256);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_next_pos=m_pos_old=m_pos = p;
	//中心位置設定
	m_img.SetCenter(32, 64);
	//当たり判定用矩形設定
	m_rect = CRect(-16, -32, 16, 0);
	//反転フラグ
	m_flip = flip;
	m_cnt = 0;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = true;
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_attack_no = -1;
	m_viewLength = 150.0f;
	m_viewAngle = DtoR(45.0f);
	m_isChase = false;
	m_moveDir = CVector2D::left;
	m_path_idx = 1;

}
Enemy::~Enemy()
{
}
bool Enemy::IsFoundPlayer() const
{
	Base* p = Base:: FindObject(eType_Player);
	Player* player = dynamic_cast<Player*>(p);
	CVector2D forward = GetForward();
	CVector2D playervec = player->GetPos() - m_pos;
	float angle = CVector2D::Dot(
		forward.GetNormalize(),
		playervec.GetNormalize()
	);
	if (angle < cosf(m_viewAngle)) {
		return false;
	}
	if (playervec.Length() > m_viewLength) {
		return false;
	}
	return true;
}
void Enemy::StateIdle()
{
	//移動量
	const float move_speed = 4;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 12;

	Base* player = Base::FindObject(eType_Player);
	m_isChase = IsFoundPlayer();
	/*if (m_isChase) {
		if(player){
			//左移動
			if (player->m_pos.x < m_pos.x - 32) {
				//移動量を設定
				m_pos.x += -move_speed;
				//反転フラグ
				m_flip = true;
				move_flag = true;
			}
			else
				//右移動
				if (player->m_pos.x > m_pos.x + 32) {
					//移動量を設定
					m_pos.x += move_speed;
					//反転フラグ
					m_flip = false;
					move_flag = true;
				}
				else
					if (player->m_pos.y > m_pos.y + 32) {
						m_pos.y += +move_speed;
						move_flag = true;
					}
					else
						if (player->m_pos.y < m_pos.y - 32) {
						m_pos.y += -move_speed;
						move_flag = true;
						}
						else {
								//攻撃状態へ移行
						m_state = eState_Attack;
						m_attack_no++;
					}
		}
		
	}*/
	//if (m_isChase) {
	//if (--m_count <= 0) {
	if (player) {
		if (m_isChase) {
			m_target_point = player->m_pos+CVector2D(16,0);
				if (Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Field))) {
					m_path.FindShortestPath(m, m_pos , m_target_point);
					m_path_idx = 2;
				}
				if (m_path_idx < m_path.GetPathSize()) {
					CVector2D vec = m_path.GetPathPoint(m_path_idx) - m_pos ;
					if (vec.Length() > 8) {
						m_ang = atan2(vec.x, vec.y);
						CVector2D dir(sin(m_ang), cos(m_ang));
						m_pos += dir * move_speed;
						move_flag = true;
					}
				else {
						m_path_idx++;

				}
					if (player->m_pos.x > m_pos.x - 32 && player->m_pos.x < m_pos.x + 32
						&& player->m_pos.y < m_pos.y + 32 && player->m_pos.y > m_pos.y - 32) {
						m_state = eState_Attack;
						m_attack_no++;
					}
			}
		}
		
			if (--m_count <= 0) {
				m_next_pos = CVector2D((rand()%9*MAP_TIP_SIZE)+60,(rand()%MAP_HEIGHT*MAP_TIP_SIZE)+130);
				if (Map* m = dynamic_cast<Map*>(Base::FindObject(eType_Field))) {
					m_path.FindShortestPath(m, m_pos,m_next_pos );
					m_path_idx = 3;
					m_count = 600;
				
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
	
		
	}
	
		
	//}
	
	
	


	

	if (!m_is_ground) {
		if (m_vec.y < 0)
			//上昇アニメーション
			m_img.ChangeAnimation(eAnimJumpUp, false);
		else
			//下降アニメーション
			m_img.ChangeAnimation(eAnimJumpDown, false);
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
	/*if (--m_cnt <= 0) {
		m_cnt = rand() % 120 + 180;
		m_state = eState_Wait;
	}*/

}
void Enemy::StateWait() {
	//待機アニメーション
	m_img.ChangeAnimation(eAnimIdle);
	if (--m_cnt <= 0) {
		m_cnt = rand() % 120 + 180;
		m_state = eState_Idle;
	}
}
void Enemy::StateAttack()
{
	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack01, false);
	//3番目のパターンなら
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			Base::Add(new Slash(m_pos + CVector2D(-32, -16), m_flip, eType_Enemy_Attack, m_attack_no));
		}
		else {
			Base::Add(new Slash(m_pos + CVector2D(32, -16), m_flip, eType_Enemy_Attack, m_attack_no));
		}
	}
	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {
		//通常状態へ移行
		m_state = eState_Wait;
	}

}
void Enemy::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Wait;
	}
}
void Enemy::StateDown()
{
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		//Base::Add(new Effect("Effect_Smoke",
			//m_pos + CVector2D(0, 0), m_flip));

		m_kill = true;
	}
}
void Enemy::Update() {
	m_pos_old = m_pos;
	switch (m_state) {
		//通常状態
	case eState_Wait:
		StateWait();
		break;
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
//	m_scroll.x = m_pos.x - 1280 / 2;

}

void Enemy::Draw() {
	float alpha = 0.5f;
	CVector4D color(0.0f, 1.0f, 0.0f, alpha);
	float angle = atan2f(m_moveDir.y, m_moveDir.x);
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//m_path.Draw();
	Utility::DrawCircle(GetScreenPos(m_pos), 16, CVector4D(1, 0, 0, 1));
	//描画
	m_img.Draw();
	//当たり判定矩形の表示
	//DrawRect();
}
void Enemy::Collision(Base* b)
{
	switch (b->m_type) {
	//攻撃エフェクトとの判定
	case eType_Player_Attack:
		//Slash型へキャスト、型変換できたら
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				Base* player = Base::FindObject(eType_Player);
				Player* p = dynamic_cast<Player*>(player);
				//同じ攻撃の連続ダメージ防止
				m_damage_no = s->GetAttackNo();
				m_hp -= p->damage();
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;

				}
				//Base::Add(new Effect("Effect_Blood",
					//m_pos + CVector2D(0, -128), m_flip));

				//Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -64), m_flip));
			}
		}
		break;
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			CVector2D v;
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect,&v);
			if (t != 0)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect,&v);
			if (t != 0)
				m_pos.y = m_pos_old.y;
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





#include "Game.h"
#include"Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"
#include"UI.h"
#include"Child.h"
#include"Scroll.h"
#include"Canvas.h"
#include "../Title/Title.h"

Game::Game() :Base(eType_Scene)
{
	Base::Add(new Map(1, CVector2D(70, 100)));
	Base::Add(new UI());
	
	


}

Game::~Game()
{
	//全てのオブジェクトを破棄
	Base::KillAll();
	//タイトルシーンへ
	//Base::Add(new Title());
}

void Game::Update()
{
	//ゴールが無ければゲームシーン終了
	/*if (!Base::FindObject(eType_Goal)) {
		SetKill();
	}*/

	//プレイヤー死亡　ボタン１でゲームシーン終了
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		m_kill = true;
	}
}


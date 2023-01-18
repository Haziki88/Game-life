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
#include"../Gameclear/Gameclear.h"
#include"../Gameover/Gameover.h"

Game::Game() :Base(eType_Scene)
{
	Base::Add(new Map(1, CVector2D(70, 100)));
	Base::Add(new UI());
	Base::Add(new Scroll(CVector2D(GL::window_width, GL::window_height)));
	Base::Add(new Canvas(CVector2D(GL::window_width, GL::window_height)));
	


}

Game::~Game()
{
	//全てのオブジェクトを破棄
	Base::KillAll();
	//タイトルシーンへ
	
	if (clear_flag == true) {
		Base::Add(new Gameclear());
	}
	else  {
		Base::Add(new Gameover());
	}
	//Base::Add(new Title());
}

void Game::Update()
{
	//ゴールが無ければゲームシーン終了
	/*if (!Base::FindObject(eType_Goal)) {
		SetKill();
	}*/

	//プレイヤー死亡　ボタン１でゲームシーン終了
	if (!Base::FindObject(eType_Player)) {
		m_kill = true;
	}
}


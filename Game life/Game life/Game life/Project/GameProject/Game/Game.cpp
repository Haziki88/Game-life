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
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�^�C�g���V�[����
	
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
	//�S�[����������΃Q�[���V�[���I��
	/*if (!Base::FindObject(eType_Goal)) {
		SetKill();
	}*/

	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player)) {
		m_kill = true;
	}
}


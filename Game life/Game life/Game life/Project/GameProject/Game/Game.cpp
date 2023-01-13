#include "Game.h"
#include"Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"
#include"UI.h"
#include"Child.h"
#include "../Title/Title.h"

Game::Game() :Base(eType_Scene)
{
	Base::Add(new Map(1, CVector2D(300, 200)));
	Base::Add(new UI());
	Base::Add(new Player(CVector2D(300, 200), false));
	Base::Add(new Enemy(CVector2D(400, 300), true));
	Base::Add(new Child(CVector2D(600, 200)));


}

Game::~Game()
{
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�^�C�g���V�[����
	//Base::Add(new Title());
}

void Game::Update()
{
	//�S�[����������΃Q�[���V�[���I��
	/*if (!Base::FindObject(eType_Goal)) {
		SetKill();
	}*/

	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		m_kill = true;
	}
}


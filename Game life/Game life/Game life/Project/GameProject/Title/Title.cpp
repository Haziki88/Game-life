#include "Title.h"
#include "../Game/Game.h"
Title::Title():Base(eType_Scene),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
{
	m_img = COPY_RESOURCE("Title",CImage);
}

Title::~Title()
{
	//タイトル破棄時にゲームシーンへ移行
	Base::Add(new Game());
}

void Title::Update()
{
	//ボタン１でタイトル破棄
	if (PUSH(CInput::eButton1)) {
		m_kill = true;
	}
}

void Title::Draw()
{
	m_img.Draw();
	//文字表示
	m_title_text.Draw(64, 256, 0, 0, 0, "Title");
	m_title_text.Draw(64, 512, 0, 0, 0, "Push Z");
}

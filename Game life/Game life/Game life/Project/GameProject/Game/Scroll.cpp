#include "Scroll.h"
Scroll::Scroll(const CVector2D& screen_size) :Base(eType_Scroll), m_player(nullptr) {
	m_screen_size = screen_size;
	m_scale = 0.7;
}

void Scroll::Draw() {
	//�v���C���[�����Ȃ����
	if (!m_player) {
		//�v���C���[��T��
		m_player = Base::FindObject(eType_Player);
	}
	else {
		//�v���C���[���폜���ꂻ���Ȃ�
		if (m_player->m_kill)
			//�|�C���^������
			m_player = nullptr;
	}
	if (HOLD(CInput::eUp))
		m_scale = max(0.7f, m_scale - 0.01f);
	if (HOLD(CInput::eDown))
		m_scale = min(1.5f, m_scale + 0.01f);
	CVector2D draw_size = m_screen_size * m_scale;

	//----�@�g��k���F��ʍ��オ���_
	//�X�N���[���l�ݒ�
	//if (m_player) {
		//m_scroll.x = m_player->m_pos.x - 600;
		//m_scroll.y = m_player->m_pos.y - 500;

	//}
	//�Q�[�����𑜓x�ύX
	//CCamera::GetCamera()->SetSize(draw_size.x, draw_size.y);
	//----------------------------



	//-----�A�g��k���F��ʒ��S�����_2
	if (m_player) {
		m_scroll.x = m_player->m_pos.x;
		m_scroll.y = m_player->m_pos.y - 200;
	}
	//�Q�[�����𑜓x�ύX
	CCamera::GetCamera()->SetSize(draw_size.x, draw_size.y);
	//��ʒ��S�����_�ɂȂ�2D�p���e�s��
	//���s���2�N�̃Q�[�����w�ŏK�����߁A����͂��̂܂܎g�p����̂�
	CCamera::GetCamera()->SetProjectionMatrix2D(CMatrix(
		2.0f / draw_size.x, 0.0f, 0.0f, 0.0f,
		0.0f, -2.0f / draw_size.y, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f));

	//--------------------------------
}
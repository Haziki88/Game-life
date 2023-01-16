#pragma once
#include <GLLibrary.h>
enum {
	eType_Scroll,
	eType_Field,
	eType_Player,
	eType_Enemy,
	eType_Bullet,
	eType_Goal,
	eType_Player_Attack,
	eType_Enemy_Attack,
	eType_Effect,
	eType_Dijkstra,
	eType_Parent,
	eType_Child,
	eType_AreaChange,
	eType_Canvas,
	eType_UI,
	eType_Scene,
};


#define GRAVITY (9.8f/20)
class Base {
public:

	//�I�u�W�F�N�g�̎��
	int m_type;
	//���W�f�[�^
	CVector2D m_pos;
	CVector2D m_pos_old;
	//��]�l
	float m_ang;
	//���a
	float m_rad;
	//�ړ��x�N�g��
	CVector2D m_vec;
	//�폜�t���O
	bool m_kill;
	//�I�u�W�F�N�g�̃��X�g
	static std::list<Base*> m_list;
	//��`
	CRect	m_rect;	

	//�X�N���[���l
	static CVector2D m_scroll;
	static float m_scale;

public:
	static CVector2D GetScreenPos(const CVector2D& pos);
	//type �I�u�W�F�N�g�̎��
	Base(int type);
	virtual ~Base();
	virtual void Update();
	virtual void Draw();
	virtual void Collision(Base* b);
	//�폜�t���OON
	void SetKill() { m_kill = true; }
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void ResetPos(const CVector2D& pos) {
		m_pos = m_pos_old = pos;
	}
	//�S�ẴI�u�W�F�N�g�̍X�V
	static void UpdateAll();
	//�S�ẴI�u�W�F�N�g�̕`��
	static void DrawAll();
	//�S�ẴI�u�W�F�N�g�̓����蔻�茟��
	static void CollisionAll();
	//�폜�`�F�b�N
	static void CheckKillAll();
	//�I�u�W�F�N�g�̒ǉ�
	static void Add(Base* b);
	static void KillAll();
	/// <summary>
	/// �w�肵����ނ̃I�u�W�F�N�g���폜
	/// </summary>
	/// <param name="type">�I�u�W�F�N�g�̎��</param>
	static void KillByType(int type);
	//�~���m�̏Փ�
	static bool CollisionCircle(Base* b1, Base* b2);
	//��`���m�̔���
	static bool CollisionRect(Base* b1, Base* b2);
	/// ��`�̕\��
	void DrawRect();

	static Base* FindObject(int type);
	static std::list<Base*> FindObjects(int type);

};


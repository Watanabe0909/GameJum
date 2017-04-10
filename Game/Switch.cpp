//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Switch.cpp
//!
//! @brief  �X�C�b�`�̃\�[�X�t�@�C��
//!
//! @date   2017/04/09		
//!
//! @author �n粐^�l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//�w�b�_�t�@�C���̃C���N���[�h
#include "Switch.h"

//----------------------------------------------------------------------
//! @brief �R���X�g���N�^
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
Switch::Switch(int pos_x, int pos_y)
{
	m_handle  = new Texture(L"Resources\\Images\\switch.png");
	m_grp_x = 0;
	m_grp_y = 0;
	m_grp_w = M_SWTICH_GRP;
	m_grp_h = M_SWTICH_GRP;
	m_pos_x = pos_x;
	m_pos_y = pos_y;
	m_state = false;
}

//----------------------------------------------------------------------
//! @brief �f�X�g���N�^
//!
//----------------------------------------------------------------------
Switch::~Switch()
{
	delete m_handle;
	m_handle = nullptr;
}

//----------------------------------------------------------------------
//! @brief �X�C�b�`�̃I���I�t�̐؂�ւ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Switch::Swtiching()
{
	m_grp_x = M_SWTICH_GRP;
}

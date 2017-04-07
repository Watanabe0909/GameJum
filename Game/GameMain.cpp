//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2016/11/04		
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#define _GAMEMAIN_
#include "Player.h"
#include "GameMain.h"
#include "GameBase.h"
#include "GamePlay.h"
#include "GameTitle.h"
#include "GameClear.h"
#include "GameOver.h"
#include "GameLogo.h"
#include "Box.h"
#include <ctime>
using namespace DirectX::SimpleMath;
using namespace DirectX;

// �v���g�^�C�v�錾 ====================================================

// �O���[�o���ϐ��̒�` ====================================================

Texture *g_BlockImage;
Texture *g_grpBack;
Texture *g_grpResult;
Texture *g_grpOver;
Texture *g_grpTitle;
GameBase* base;
int g_time;
int g_highscore;

// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeGame(void)
{
	base =new Logo();
	g_NextScene = g_scene;
}




//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateGame(void)
{
	//��
	ADX2Le::Update();

	//�V�[���Ǘ�
	if (g_NextScene != g_scene)
	{
		g_scene = g_NextScene;
		delete base;
		g_init = 0;


		//�V�[�����Ƃ̌Ăяo��
		switch (g_scene)
		{
		case LOGO:
			base = new Logo();
			break;

		case TITLE:
			base = new Title();
			break;

		case PLAY:
			base = new Play();
			break;

		case CLEAR:
			base = new Clear();
			break;

		case OVER:
			base = new Over();
			break;
		}
	}

	g_key_old = g_key_code;
	base->Update();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderGame(void)
{

	base->Render();
	
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	ADX2Le::Finalize();
	
	delete base;
	delete g_grpBack;
	delete g_grpResult;
	delete g_grpTitle;
}



//----------------------------------------------------------------------
//! @brief �e�N�X�`���̕`��
//!
//! @param[in] xy���W�C�摜�̎n�_xy, �摜�̑傫��wh, �e�N�X�`��
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawRectTexture(int pos_x, int pos_y, int tex_x, int tex_y, int tex_w, int tex_h, Texture* handle)
{
	//rect = { leftupX, leftupY, rightdownX, rightdownY };
	RECT rect = { tex_x, tex_y, tex_x + tex_w, tex_y + tex_h };

	//Draw(�e�N�X�`��, �ꏊ , �傫��, �F����, ��](���W�A��), ��]����Ƃ��̒��S���W , �g��{��)
	g_spriteBatch->Draw(handle->m_pTexture, Vector2((float)pos_x, (float)pos_y), &rect, 
							Colors::White, 0.0f, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
}






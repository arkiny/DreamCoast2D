#include "stdafx.h"
#include "sGameOverScreen.h"
#include "cD2DRenderer.h"

sGameOverScreen::sGameOverScreen()
{
}


sGameOverScreen::~sGameOverScreen()
{
}

sGameOverScreen::sGameOverScreen(cGameManager* cg){
	m_pGameManager = cg;
}

void sGameOverScreen::Render(cD2DRenderer& renderer){
	/// �ؽ�Ʈ ���
	// ���� ���� ������ �ɸ´� �������ͽ��� ������
	// �ش� ���� ����� ������ �ɷ� ����
	wchar_t* wszText_ = new wchar_t[20];
	swprintf(wszText_, 20, L"Game Over");
	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

	D2D1_RECT_F layoutRect = D2D1::RectF(
		500.0f, 300.0f, 600.0f, 400.0f
		);

	renderer.GetRenderTarget()->DrawTextW(
		wszText_,
		cTextLength_,
		renderer.GetTextFormat(),
		layoutRect,
		renderer.GetBrush());
}
void sGameOverScreen::Update(float delta){
	m_accumtime += delta;
	// �װ� 5�� ������ ���� ����
	// ����� �̷��� ó��
	if (m_accumtime > 5.0f){
		::PostQuitMessage(NULL);
	}
}

void sGameOverScreen::OnInit(cD2DRenderer& renderer){
}

void sGameOverScreen::OnExit(){

}
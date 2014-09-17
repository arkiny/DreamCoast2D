#pragma once

class cD2DRenderer;
class VECTOR2D;
class uSprite;

class mIObject
{
public:
	virtual ~mIObject();

	virtual void onInit(cD2DRenderer& renderer) = 0;
	virtual void onUpdate(float fdeltatime) = 0;

	// object�� �⺻������ �������� �Ұ��� ������ �ֱ� ������
	// ������ ������ �̷������ ���� ��ӹ޾� �������̵� �� �ʿ� ����
	// ���� ���� Ŭ�������� �ǽ� ����
	virtual void onRender(cD2DRenderer& renderer);

protected:
	// �⺻������ ����������� ������ ���� ������
	// POINT�� �� ��� LONG ������ ��ȯ�� �Ͼ�� ������ �������꿡 ������ �����.
	VECTOR2D* _posVector;			// ��ġ
	uSprite* m_spriteAtlas;			// ��������Ʈ ����
	ID2D1Bitmap* m_ipD2DBitmap;		// ��������Ʈ ����
};


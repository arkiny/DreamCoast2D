#pragma once

class cD2DRenderer;

class VECTOR2D;

class uiInterface
{
public:
	uiInterface();
	uiInterface(float x, float y);
	virtual ~uiInterface();
public:
	virtual void OnInit(cD2DRenderer&) = 0;
	virtual void Update(float) = 0;
	virtual void Render(cD2DRenderer&) = 0;	

	VECTOR2D* getPos(){ return m_vpos; }
	void setPos(VECTOR2D* in);
	void setPos(float x, float y);

//todo: ���� ���콺�� �̿��ؼ� �����������̽��� �ű�� ���� �ּ��߰�
private:
	VECTOR2D* m_vpos;
};


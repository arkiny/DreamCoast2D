#pragma once

class cD2DRenderer;

class uiInterface
{
public:
	uiInterface();
	~uiInterface();
public:
	virtual void OnInit(cD2DRenderer&) = 0;
	virtual void Update(float) = 0;
	virtual void Render(cD2DRenderer&) = 0;	

//todo: ���� ���콺�� �̿��ؼ� �����������̽��� �ű�� ���� �ּ��߰�
//private:
//	VECTOR2D* pos;
};


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

//todo: 차후 마우스를 이용해서 유저인터페이스를 옮기기 위해 주석추가
//private:
//	VECTOR2D* pos;
};


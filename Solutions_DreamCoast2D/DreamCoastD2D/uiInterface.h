#pragma once

class cD2DRenderer;

class uiInterface
{
public:
	uiInterface();
	~uiInterface();
public:
	virtual void Render(cD2DRenderer&) = 0;
	virtual void Update(float) = 0;
	virtual void OnInit(cD2DRenderer&) = 0;
};


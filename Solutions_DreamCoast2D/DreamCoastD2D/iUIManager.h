#pragma once
class cD2DRenderer;
class iUIManager
{
public:
	iUIManager();
	virtual ~iUIManager();

	void Render(cD2DRenderer&) = 0;
	void Update(float);
	void OnInit(cD2DRenderer&);
public:

};


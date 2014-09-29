#pragma once
#include <vector>

class uiInterface;
class cD2DRenderer;
class mIObject;
class wTileMap;

// UI Screen has UI interface classes.
// Using as a layer of the game screen
// therefore, ui layer is not a screen 
// -> does not hierarchy screen class
class InGameUI 
{
public:
	InGameUI();
	InGameUI(mIObject*, wTileMap*);
	~InGameUI();
	void Render(cD2DRenderer&);
	void Update(float);
	void OnInit(cD2DRenderer&);
private:
	//bool config[]; 
	//���� ��Ʈ�ѿ��� Ű �Է¿� ���� UI����� ���� �״��Ѵ�.
	std::vector<uiInterface*> m_pInterface;
};


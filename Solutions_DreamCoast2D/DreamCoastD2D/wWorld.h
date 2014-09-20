#pragma once
#include "cD2DRenderer.h"

class coControl;
class mPlayer;
class wTileMap;

class wWorld
{
public:
	wWorld();
	~wWorld();

	void Render(cD2DRenderer&);
	void Update(float deltaTime);
	void OnInit(cD2DRenderer&, coControl*);

private:
	// player init�� world���� ������, �� ������ m_Map���� �����͸� �޾Ƽ� �ǽ�
	mPlayer* m_Player;
	wTileMap* m_Map;

	// World���� ���������� �������ְ�, �÷��̾� Ŭ������ �����͸� �̾Ƽ� �����ֱ�� �����ϴ� �ɷ�
	// FSM�� �̿��ϸ�, �������� ������ �̿��Ҽ� ������ ����. World�� �Ʒ��� ���� �����͸� �ְ�
	// �ʿ��Ѱ͸��� ���ƾ��� ������ �ʰ���
	// vector<wTileMap*> MapList;
};


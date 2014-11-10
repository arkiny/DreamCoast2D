#pragma once
#include "cD2DRenderer.h"

class coControl;
class mPlayer;
class wTileMap;
class cResourceManager;

class wWorld
{
public:
	wWorld();
	~wWorld();

	void Render();
	void RenderEdit();
	void Update(float deltaTime);
	void OnInit(int mapnumber);

	mPlayer* getPlayer(){ return m_Player; }
	wTileMap* getMap() { return m_Map; }
	bool isGameOver(); 
private:
	// player init�� world���� ������, �� ������ m_Map���� �����͸� �޾Ƽ� �ǽ�
	mPlayer* m_Player;
	wTileMap* m_Map;

	// getter�� setter������ �ϸ� player class�� map�� ��ȣ�ۿ��� ���⼭ ������ ���� �� ������..
	// ������ �� �����ִ� ����, ���� ��ȣ �ۿ��� ��� �ؾ����� �ǹ�
	// ���Ϳ� �÷��̾� ��ġ�� �޾ƿͼ� ���⼭ ó���� �Ҽ� �ִ°� ������ ������
	// ���� �����Ŀ� ������� ���� ������ �ʿ��ҵ�.
	// player�� m_Map���� player �����͸� �����ϰ�, getter�� setter�� �̿��ؼ�
	// worldŬ�������� ó���ϴ� �ɷ�..? �ƴϸ� �ִ��� wTileMap ��ü�� worldmap�̳� �ٸ������Ƿ�
	// �� �ȿ��� ��� ó���ϴ� �ɷ�? �׷� ��Ʈ�� ���ڸ� ��� �޾ƿ;� �ϴ°ǰ�?

	// World���� ���������� �������ְ�, �÷��̾� Ŭ������ �����͸� �̾Ƽ� �����ֱ�� �����ϴ� �ɷ�
	// FSM�� �̿��ϸ�, �������� ������ �̿��Ҽ� ������ ����. World�� �Ʒ��� ���� �����͸� �ְ�
	// �ʿ��Ѱ͸��� ���ƾ��� ������ �ʰ���
	// vector<wTileMap*> MapList;
};


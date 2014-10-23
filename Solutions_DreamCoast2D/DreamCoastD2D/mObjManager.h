#pragma once
#include "IMapObject.h"
#include <list>

class wTileMap;

class mObjManager
{
public:
	mObjManager();
	~mObjManager();
	void update(float);
	void render();

	void pushToObjectlist(IMapObject* Object);
	void deletefromObjectlistByTileCoordinate(float x, float y, wTileMap* map);

private:
	// Ÿ�� ������ŭ �� �ڸ�(����)�� �����
	// �ű⼭ ��ǥ�� ���ؼ� �� ��ǥ�� �ڸ��� �ٲٰų�
	// Ȥ�� ������ ���鼭 �����ϹǷ�

	std::vector<IMapObject*> m_qMapObject;
};


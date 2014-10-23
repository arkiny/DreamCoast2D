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
	// 타일 갯수만큼 빈 자리(벡터)로 만들고
	// 거기서 좌표를 구해서 그 좌표의 자리를 바꾸거나
	// 혹은 어차피 돌면서 렌더하므로

	std::vector<IMapObject*> m_qMapObject;
};


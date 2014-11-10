#pragma once
#include <vector>
#include "IGObject.h"
#include "IMapObject.h"

// 휘발성으로 넣어서?
// 렌더만 여기서 하는 걸로?
// 업데이트는 월드에서
// 렌더는 각 타일에서
// 이 클래스는 일종의 렌더 도우미 겸 컨테이너

class uCamera;
class VECTOR2D;
class uSprite;
class mNetworkObject;
class mNetworkMob;

struct ID2D1Bitmap;

class uTile
{
public:
	uTile();
	uTile(int type, uCamera* const in);
	~uTile();

	void setCam(uCamera* const in){ m_Cam = in; }

	void addObject(ICharacter* in);
	void addMapObject(IMapObject* in);
	void addNetObject(mNetworkObject* in);
	void addNetMobObject(mNetworkMob* in);

	void deleteAllObject();
	void setType(int in){ _type = in; }
	int getType(){ return _type; }
	std::vector<ICharacter*> getTileObjects(){ return m_vObjects; }

	void renderTile(float x, float y, 
		uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap);

	void renderTileEdit(float x, float y,
		uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap);

	void renderObject(float x, float y);

	void renderMapObject(float x, float y);

	void renderNetObject(float x, float y);

	void renderNetMobObject(float x, float y);
	
	void onHit(float dmg);
private:
	int _type;	
	uCamera* m_Cam;
	std::vector<ICharacter*> m_vObjects;
	std::vector<IMapObject*> m_qMapObject;
	std::vector<mNetworkObject*> m_qNetworkObject;
	std::vector<mNetworkMob*> m_qNetMobObject;

	void hRender(VECTOR2D tilePos,
		uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap);
};
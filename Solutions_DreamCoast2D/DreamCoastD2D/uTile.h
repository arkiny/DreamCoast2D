#pragma once
#include <vector>

// 휘발성으로 넣어서?
// 렌더만 여기서 하는 걸로?
// 업데이트는 월드에서
// 렌더는 각 타일에서
// 이 클래스는 일종의 렌더 도우미 겸 컨테이너

class mIObject;
class cD2DRenderer;
class uCamera;
class VECTOR2D;
class uSprite;
struct ID2D1Bitmap;

class uTile
{
public:
	uTile();
	uTile(int type, uCamera* const in);
	~uTile();

	void setCam(uCamera* const in){ m_Cam = in; }

	void addObject(mIObject* in);
	void deleteAllObject();
	void setType(int in){ _type = in; }
	int getType(){ return _type; }
	std::vector<mIObject*> getTileObjects(){ return m_vObjects; }

	void renderTile(float x, float y, cD2DRenderer& renderer, 
		uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap);
	
	void onHit(float dmg);
private:
	int _type;	
	uCamera* m_Cam;
	std::vector<mIObject*> m_vObjects;

	void hRender(cD2DRenderer& renderer, VECTOR2D tilePos,
		uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap);
};
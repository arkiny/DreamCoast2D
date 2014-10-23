#pragma once
#include <vector>
#include "IGObject.h"
#include "IMapObject.h"

// �ֹ߼����� �־?
// ������ ���⼭ �ϴ� �ɷ�?
// ������Ʈ�� ���忡��
// ������ �� Ÿ�Ͽ���
// �� Ŭ������ ������ ���� ����� �� �����̳�

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

	void addObject(ICharacter* in);
	void addMapObject(IMapObject* in);

	void deleteAllObject();
	void setType(int in){ _type = in; }
	int getType(){ return _type; }
	std::vector<ICharacter*> getTileObjects(){ return m_vObjects; }

	void renderTile(float x, float y, 
		uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap);

	void renderMapObject(float x, float y);
	
	void onHit(float dmg);
private:
	int _type;	
	uCamera* m_Cam;
	std::vector<ICharacter*> m_vObjects;
	std::vector<IMapObject*> m_qMapObject;

	void hRender(VECTOR2D tilePos,
		uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap);
};
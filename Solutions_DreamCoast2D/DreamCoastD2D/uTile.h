#pragma once
#include <vector>

// �ֹ߼����� �־?
// ������ ���⼭ �ϴ� �ɷ�?
// ������Ʈ�� ���忡��
// ������ �� Ÿ�Ͽ���
// �� Ŭ������ ������ ���� ����� �� �����̳�

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

	void renderTile(float x, float y, cD2DRenderer& renderer, 
		uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap);
	
private:
	int _type;	
	uCamera* m_Cam;
	std::vector<mIObject*> objects;

	void hRender(cD2DRenderer& renderer, VECTOR2D tilePos,
		uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap);
};
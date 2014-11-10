#pragma once
// GFX ���̾�
// ��ǥ�� �̺�Ʈ�� �޾Ƽ�
// �ش� ��ǥ�� �׷��� ����Ʈ�� �ѷ��ش�
// �ش� �̺�Ʈ���� queue�� �����ϸ�
// �̾Ƽ� ó���ϰ�, �ش� �̺�Ʈ ����ÿ�
// Ǫ������ �ʰ� �״�� �����Ѵ�.
// mGFX ���̾�� GameUI�� �ƴ�, World�� �����ϸ�
// �ش� �̺�Ʈ �߻���, �� ĳ���Ͱ� �ݹ��ؿͼ� �ش� �̺�Ʈ�� add�Ѵ�.
#include <queue>
#include "Singleton.h"
#include "IEffect.h"

class mGFX : public Singleton<mGFX>
{
public:
	mGFX();
	~mGFX();
	void update(float);
	void render();
	void pushToEventQueue(IEffect* effect);
private:
	std::queue<IEffect*> m_qEffects;
};


#pragma once

class mMonster;
class uSprite;

// aiState�� ������ �����Ǹ�, �÷��̾� ������Ʈ�� ������Ʈ �ӽ����� ġȯ
class aiState
{
public:
	aiState(){}
	virtual ~aiState(){}
public:
	//��������
	virtual void enter(mMonster* pmon) = 0;
	//��������
	virtual void execute(mMonster* pmon) = 0;
	//���� ��Ż
	virtual void exit(mMonster* pmon) = 0;
protected:
	uSprite* m_sprite;
};



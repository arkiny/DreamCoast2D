#pragma once

class mMonster;

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
};

class aiStateIdle : public aiState{
private:
	void enter(mMonster* pmon);
	void execute(mMonster* pmon);
	void exit(mMonster* pmon);
};

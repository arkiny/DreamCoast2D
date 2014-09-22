#pragma once

class mMonster;

// aiState가 괜찮게 설정되면, 플레이어 오브젝트도 스테이트 머신으로 치환
class aiState
{
public:
	aiState();
	virtual ~aiState();
public:
	virtual void enter(mMonster* pmon) = 0;
	virtual void execute(mMonster* pmon) = 0;
	virtual void exit(mMonster* pmon) = 0;
};

class aiStateIdle : public aiState{
private:
	void enter(mMonster* pmon);
	void execute(mMonster* pmon);
	void exit(mMonster* pmon);
};

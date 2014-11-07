#pragma once

#include "mCharacter.h"
#include "IInventory.h"
#include "DB_Skill_Area_List.h"
//#include "IItem.h"

#include <queue>
#include <map>


#define BELT_MAX 3

// ��Ʈ ����Ű, A, S, D�� ���� ü��, ����, Ư��
enum BELTSHORTCUT{KEY_A, KEY_S, KEY_D};

class uSprite;
class mItem;
class piState;

// Statemachine�� �̿����� ���� ä�� �����ϴ�
// player object
// ���� ��Ȳ�� ���� statemachine������ ��ȭ
class mPlayer : public mCharacter, public IPlayable
{
public:
	mPlayer();
	~mPlayer();
	void onInit();
	void onUpdate(float fdeltatime);
	void onRender();
	void onRender(bool);
	
	// StatController
	void getHit(float dmg);

	// graphic control
	void setAlpha(float in){ m_alpha = in; }
	float getAlpha(){ return m_alpha; }

	// StateInitializer
	// void onIdle();

	bool isDeadComplete() { return m_deadcomp; }

	void setRealPos(float x, float y);
	//virtual void setDrawPos(float x, float y);

	// inventory control
	//void addToInventory();
	//void removeFromInventory(int ID);
	//void useItem(int index);
	
	//std::map<int, mItem*> getInventory(){ return m_vInventory; }
	//virtual void addToInventory(mItem*);
	//virtual void removeFromInventory(int ID);

	void setBelt(int index, int id){ m_aBelt[index] = id; }
	int getBelt(int index){ return m_aBelt[index]; }
	IInventory* getInventory() { return m_Inventory; }
	void setAttackPower(float in) { m_default_attackPower = in; }
	float getAttackPower() { return m_default_attackPower; }
	float getAttackSpeed() { return m_attackSpeed; }

	//
	void changeStatus(piState* nextState);
	int getMoveDir(){ return m_MoveDir; }
	int getSeeDir(){ return  m_SeeDir; }
	int getState(){ return m_State; }
	void setState(int in){ m_State = (OBJECTSTATE)in; }
	void setMoveDir(int in) { m_MoveDir = (DIRECTION)in; }
	void setSeeDir(int in) { m_SeeDir = (DIRECTION)in; }
	//


	// Ű���� �Է¿� ���� ������
	// Helper methods -> ���Ϳ��Ե� �ʿ��Ұ�� object�� �̵�
	void onMove(float deltaTime);
	void onAttack(float deltaTime);
	void onHit(float fdeltatime);
	void onDead(float);
	// skill �� ��ų Ŀ�ǵ忡 ���� statemachine���� ó��?
	void onCasting(float);

	//tile dmg ó��
	void dmgToTile(float delta, float attackpower);
	void dmgToArea(float delta, float attackpower, int AreaType);

	//
	void effectToArea(float delta, int effectType, int AreaType);
	void effectToTile(float delta, int effectType);

private:
	piState* m_playerState;	
		
	DIRECTION m_SeeDir; // ���� �ִ� ����
	DIRECTION m_MoveDir;
	OBJECTSTATE m_State;	

	// rendering alpha parameter control
	float m_alpha = 1.0f;
	
	// ���� ����, ���� ������ �߰�, ĳ���� �߰��� ���� ��ȭ
	float m_default_attackPower = 10.0f;
	float m_attackSpeed = 2.0f;
	float m_attackaccumtime = 0.0f;

	// onhit delay time
	float m_onhitMaxtime = 0.5f;
	float m_onhitAccumtime = 0.0f;

	// fade out time
	float m_deadFadeOutTime = 0.0f;

	bool m_deadcomp = false;


	/// Skill���� ����
	// ��ų ĳ���� ����
	std::vector<int*> m_SkillList; 

	float m_castaccumtime = 0.0f;
	
	std::queue<int> m_qKeyInput;
	void putKeyIntoQueue();

	// ��ų ĳ���ýÿ� Updateüũ�� ���� ����
	int m_castingSkill = 99;
	
	// ����Լ���, ��ų�� ������ ���ϱ� ���� �Լ�
	bool skillCompare(std::queue<int> &keyinput, int* skillArray, int index);
	
	// ��ų�� ���� �ٸ� ȿ���� ������� �Լ�
	void skillEffect(int skilltype);	
	
	// player�� inventory�� ������ ������, 
	// ��Ʈ����UI���� ó���ؾ��Ѵ�.
	// �׽�Ʈ������ Init���� �־����
	// ���Ŀ� UI���� �����ϴ� ����� ���� ó��
	//std::map<int, mItem*> m_vInventory;
	// IItem ����Ű�� a, s, d
	int m_aBelt[BELT_MAX];
	IInventory* m_Inventory;

	// ���� ������
	// default 10000
	int m_nGold = 10000;
	bool m_bEndbehavior = false;	
};


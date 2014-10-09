// 
enum ITEM_TYPE
{ 
	ITEM_EQUIPMENT,		// effect to static stat
	ITEM_CONSUME,		// effect to current stat
	ITEM_TYPE_MAX
};

enum ITEM_EFFECT_ID
{ 
	ITEM_POTION_HEALTH_SMALL,	// potion effect
	ITEM_POTION_HEALTH_BIG,		// potion effect
	ITEM_CONSUME_MAX
};

typedef struct Effect
{
	float HP;
	float MP;
	float Defense;
	float MoveSpeed;
}EFFECT, *LPEFFECT;

class mCharacter;

// ������ �ϳ��ϳ��� ��ư
// �������� �ϳ��� �����ͷθ� �����ϰ� ������ �ʿ�� ����
// ������ �ʿ䰡 ���涧�� UI�ν� ��µǾ�����
__interface IItem{
	// Ÿ�� ������
	virtual void setType(int type);
	virtual int getType();

	// ��ưó�� ���ýÿ� ��Ƽ���ս÷� ����
	//virtual void setActivate();
	//virtual void setSelected();
	
	// ����
	virtual void itemOnEffect(mCharacter*);
};


// �κ��丮 UI
__interface IItemInventory {
	// ���콺�� ��� �ű涧
	virtual void update(float);
	virtual void render();
	
	// �߰��� ������� ������ �߰�
	virtual void addToInventroy(IItem* item);
	virtual void removeFromInventory(int Iterator);
	
	// ���� ������ ���� ����
	virtual void changeOrder(int from, int to);

	// Ű����� �����϶� �̵���
	virtual void setCursor(int in);
	virtual int getCursor();

	// Ȱ��ȭ�� ������Ʈ �޾ƿͼ� ����
	virtual void setActivate();
	virtual void setSelected();
};

// UI_inventory ���� ���
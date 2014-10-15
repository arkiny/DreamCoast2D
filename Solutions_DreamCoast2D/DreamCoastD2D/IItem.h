#pragma once
#include "IGObject.h"
#include "cResourceID.h"

#define NULLITEM 6553526



__interface MovableItem{
	virtual bool isMoving();
	virtual void setMoving(bool in);

	virtual void saveOldPos(float x, float y);
	virtual POINTFLOAT getOldcur();
	virtual POINTFLOAT getGap();
	virtual void moveTo(float x, float y);

	virtual bool isInside(float x, float y);
};

// 아이템 하나하나가 버튼
// 아이템은 하나의 데이터로만 존재하고 렌더할 필요는 없다
// 렌더할 필요가 생길때는 UI로써 출력되었을때
__interface IItem : public MovableItem{
	// 타입 수정시
	virtual void setType(int type, int id);
	virtual int getType();

	// 버튼처럼 선택시와 액티베잇시로 나눔
	//virtual void setActivate();
	//virtual void setSelected();

	virtual void Init();
	virtual void Render();
	virtual void Update(float);
	
	// 사용시
	virtual void itemOnEffect(ICharacter*);
	virtual void setEffect(EFFECT);
	virtual void setEffect(float, float, float, float, float, float);

	virtual void setAmount(int);
	virtual int getAmount();
	virtual int getID();
	virtual void setID(int in);

	virtual void setPos(float, float);
	virtual VECTOR2D* getPos();

	virtual bool isSelected();
	virtual bool isActivated();
	virtual void setSelected(bool in);
	virtual void setActivated(bool in);
};


// 인벤토리 UI
__interface IItemInventory {
	// 마우스로 들어 옮길때
	virtual void Init();
	virtual void update(float);
	virtual void render();
	
	// 추가된 순서대로 아이템 추가
	virtual void addToInventroy(IItem* item);
	virtual void removeFromInventory(int Iterator);
	
	// 차후 구현할 순서 변경
	virtual void changeOrder(int from, int to);

	// 키보드로 움직일때 이동용
	virtual void setCursor(int in);
	virtual int getCursor();

	// 활성화시 업데이트 받아와서 렌더
	virtual void setActivate();
	virtual void setSelected();
};

// UI_inventory 따로 출력
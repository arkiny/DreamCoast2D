#pragma once


class VECTOR2D;

class uiInterface
{
public:
	uiInterface();
	uiInterface(float x, float y);
	virtual ~uiInterface();
public:
	virtual void OnInit() = 0;
	virtual void Update(float) = 0;
	virtual void Render() = 0;	

	VECTOR2D* getPos(){ return m_vpos; }
	void setPos(VECTOR2D* in);
	void setPos(float x, float y);

//todo: 차후 마우스를 이용해서 유저인터페이스를 옮기기 위해 주석추가
private:
	VECTOR2D* m_vpos;
};


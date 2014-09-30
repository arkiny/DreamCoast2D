#pragma once

class coControl;
class cD2DRenderer;
class cGameManager;

class sIScreen
{
public:
	sIScreen();
	sIScreen(cGameManager*);
	virtual ~sIScreen();
	
	virtual void OnInit(cD2DRenderer&) = 0;
	virtual void Update(float) = 0;
	virtual void Render(cD2DRenderer&) = 0;
	virtual void OnExit() = 0;

	void setControl(coControl* in){ m_pControl = in; }
	coControl* getControl(){ return m_pControl; }

private:
	coControl* m_pControl;

protected:
	// ���� ��ũ�� ��ȯ�� ���� �ݹ��� ������
	cGameManager* m_pGameManager;
};
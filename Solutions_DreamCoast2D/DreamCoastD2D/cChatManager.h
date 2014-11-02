#pragma once

#include <queue>
#include "cIChatMgr.h"
#include "Singleton.h"

class cChatManager : public cIChatMgr, public Singleton<cChatManager>
{
public:
	cChatManager();
	~cChatManager();
	virtual void Render();
	virtual void Update(float deltaTime);
	virtual void OnInit();
	virtual void addToChatLog(std::string add) { m_qChat.push(add);	}
	virtual void setVisible(bool in){ m_bVisible = in; }

	bool getVisibleStatus(){ return m_bVisible; }
private:
	std::queue<std::string> m_qChat;
	bool m_bVisible = true;
};


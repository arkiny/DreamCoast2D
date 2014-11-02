#pragma once
#include <string>
class cIChatMgr
{
public:
	cIChatMgr();
	~cIChatMgr();
	virtual void Render() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void OnInit() = 0;
	virtual void addToChatLog(std::string add) = 0;
	virtual void setVisible(bool in) = 0;
};


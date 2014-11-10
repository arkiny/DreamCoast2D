#pragma once

enum MESSAGETYPE_ID{
	PLAYER_ID_ENTRY,
	PLAYER_ID_UPDATE,
	PLAYER_ID_LOGOUT,
	MOB_ID_ENTRY,
	MOB_ID_UPDATE,
	MOB_ID_LOGOUT
};

enum MESSAGE_MOB_TYPE{
	NMOB_NOT_MOB,
	NMOB_PASSIVE_PORING,
	NMOB_ACTIVE_PORING,
	NMOB_BAPO
};

struct movePacket{
	int msgtype;
	int id;
	int mob_type;
	int state;
	int direction;
	int seedir;
	float px;
	float py;
	float speed;
};

#include "stdafx.h"
#include <vector>
#include "mPlayer.h"
#include "VECTOR2D.h"
#include "wTileMap.h"
#include "uSprite.h"
#include "uTile.h"
#include "mGFX.h"
#include "mEffect.h"

// �Ϲ� ��Ÿ�
void mPlayer::dmgToTile(float delta, float dmg){
	//bool attacktrigger = false;
	m_attackaccumtime += delta;
	VECTOR2D currentTile = m_pTileMap->getTileCoordinates(*_realVector);
	float fx, fy;

	if (m_attackaccumtime > FRAMERATE * 2.5f){
		//attacktrigger = true;
		m_attackaccumtime = 0.0f;
		if (m_SeeDir == LEFTDOWN){
			fx = currentTile.x + 1.0f;
			fy = currentTile.y;
		}
		else if (m_SeeDir == LEFTUP){
			fx = currentTile.x;
			fy = currentTile.y - 1.0f;
		}
		else if (m_SeeDir == RIGHTDOWN){
			fx = currentTile.x;
			fy = currentTile.y + 1.0f;
		}
		else if (m_SeeDir == RIGHTUP){
			fx = currentTile.x - 1.0f;;
			fy = currentTile.y;
		}
		else {}
		// ���� Ÿ�ϳ��� ���� �������� �����Ƿ�...
		m_pTileMap->getTile(currentTile.x, currentTile.y)->onHit(dmg);
		m_pTileMap->getTile(fx, fy)->onHit(dmg);
	}
}



// TODO: ������ ������� �޾ƿñ ���� ���
void mPlayer::dmgToArea(float delta, float dmg, int AreaType){
	//bool attacktrigger = false;
	m_attackaccumtime += delta;
	VECTOR2D currentTile = m_pTileMap->getTileCoordinates(*_realVector);
	// ���� struct, class or �����迭ȭ�ؼ� ���� �޾ƿ��� �ɷ�
	int dir;
	switch (m_SeeDir)
	{
	case LEFTDOWN:
		dir = 0;
		break;
	case LEFTUP:
		dir = 1;
		break;
	case RIGHTDOWN:
		dir = 2;
		break;
	case RIGHTUP:
		dir = 3;
		break;
	default:
		dir = 99;
		break;
	}

	// �̰� �����̳�ȭ �ؾ� �ϴµ�...
	std::queue < std::pair<float, float> > skillArea;
	
	switch (AreaType)
	{
	case AREA_TYPE1:
		for (std::pair<float, float> x : Area_Type1[dir]){
			skillArea.push(x);
		}
		break;
	default:
		// do nothing. will not be happend by events
		break;
	}		
	std::queue <std::pair<float, float>> skillCoord;
	if (m_attackaccumtime > FRAMERATE * 2.5f){
		//attacktrigger = true;
		m_attackaccumtime = 0.0f;
		std::pair < float, float > adder;
		while (!skillArea.empty()){
			adder = skillArea.front();
			if (currentTile.x + adder.first < m_pTileMap->getMapLimit().x &&
				currentTile.x + adder.second < m_pTileMap->getMapLimit().y&&
				currentTile.x + adder.first >= 0 &&
				currentTile.y + adder.second >= 0){
				skillCoord.push({ currentTile.x + adder.first, currentTile.y + adder.second });
			}
			skillArea.pop();
		}				
			
		// ���� Ÿ�ϳ��� ���� �������� �����Ƿ�...
		// ���� �� �ڸ����� Ÿ�� onHIT�迭�� ����. 
		m_pTileMap->getTile(currentTile.x, currentTile.y)->onHit(dmg);
		while (!skillCoord.empty()){
			m_pTileMap->getTile(skillCoord.front().first, skillCoord.front().second)->onHit(dmg);
			skillCoord.pop();
		}
	}
}

void mPlayer::effectToArea(float delta, int effectType, int AreaType){
	//bool attacktrigger = false;
	//m_attackaccumtime += delta;
	
	VECTOR2D iso;
	VECTOR2D currentTile = m_pTileMap->getTileCoordinates(*_realVector);

	// ���� struct, class or �����迭ȭ�ؼ� ���� �޾ƿ��� �ɷ�
	int dir;
	switch (m_SeeDir)
	{
	case LEFTDOWN:
		dir = 0;
		break;
	case LEFTUP:
		dir = 1;
		break;
	case RIGHTDOWN:
		dir = 2;
		break;
	case RIGHTUP:
		dir = 3;
		break;
	default:
		dir = 99;
		break;
	}

	// �̰� �����̳�ȭ �ؾ� �ϴµ�...
	std::queue < std::pair<float, float> > skillArea;

	switch (AreaType)
	{
	case AREA_TYPE1:
		for (std::pair<float, float> x : Area_Type1[dir]){
			skillArea.push(x);
		}
		break;
	default:
		// do nothing. will not be happend by events
		break;
	}
	std::queue <std::pair<float, float>> skillCoord;
	//if (m_attackaccumtime > FRAMERATE * 2.5f){
	//	//attacktrigger = true;
	//	m_attackaccumtime = 0.0f;
		std::pair < float, float > adder;
		while (!skillArea.empty()){
			adder = skillArea.front();
			if (currentTile.x + adder.first < m_pTileMap->getMapLimit().x &&
				currentTile.x + adder.second < m_pTileMap->getMapLimit().y&&
				currentTile.x + adder.first >= 0 &&
				currentTile.y + adder.second >= 0){
				skillCoord.push({ currentTile.x + adder.first, currentTile.y + adder.second });
			}
			skillArea.pop();
		}

		// ���� Ÿ�ϳ��� ���� �������� �����Ƿ�...
		// ���� �� �ڸ����� Ÿ�� onHIT�迭�� ����. 
		//m_pTileMap->getTile(currentTile.x, currentTile.y)->onHit(dmg);
		float x, y;
		VECTOR2D in;
		while (!skillCoord.empty()){
			iso.x = skillCoord.front().second;
			iso.y = skillCoord.front().first; 
			x = iso.x*m_pTileMap->getRectTileWidth();
			y = iso.y*m_pTileMap->getRectTileHeight();
			in = VECTOR2D(x, y);
			iso = m_pTileMap->twoDtoISO(in);
			::mGFX::GetInstance().pushToEventQueue(new mEffect(1, 0, new VECTOR2D(iso.x, iso.y), m_Cam));			
			//::mGFX::GetInstance().pushToEventQueue(new mEffect(1, 0, new VECTOR2D(in.x, in.y), m_Cam));
			skillCoord.pop();
		}
	//}
}

void mPlayer::effectToTile(float delta, int effectType){
	//bool attacktrigger = false;
	//m_attackaccumtime += delta;
	VECTOR2D currentTile = m_pTileMap->getTileCoordinates(*_realVector);
	VECTOR2D iso;

	//if (m_attackaccumtime > FRAMERATE * 2.5f){
	//	//attacktrigger = true;
	//	m_attackaccumtime = 0.0f;
		if (m_SeeDir == LEFTUP){
			iso.x = currentTile.y - 1.0f;
			iso.y = currentTile.x;
		}
		else if (m_SeeDir == LEFTDOWN){
			iso.x = currentTile.y;
			iso.y = currentTile.x + 1.0f;
		}
		else if (m_SeeDir == RIGHTDOWN){
			iso.x = currentTile.y + 1.0f;
			iso.y = currentTile.x;
		}
		else if (m_SeeDir == RIGHTUP){
			iso.x = currentTile.y;
			iso.y = currentTile.x - 1.0f;
		}
		else {}
		// ���� Ÿ�ϳ��� ���� �������� �����Ƿ�...
		float x = iso.x*m_pTileMap->getRectTileWidth();
		float y = iso.y*m_pTileMap->getRectTileHeight();
		VECTOR2D in(x, y);
		iso = m_pTileMap->twoDtoISO(in);
		::mGFX::GetInstance().pushToEventQueue(new mEffect(1, 0, new VECTOR2D(iso.x, iso.y), m_Cam));
	//}
}
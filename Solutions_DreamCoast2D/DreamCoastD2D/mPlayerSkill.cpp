#include "stdafx.h"
#include <vector>
#include "mPlayer.h"
#include "VECTOR2D.h"
#include "wTileMap.h"
#include "uSprite.h"
#include "uTile.h"


// 일반 사거리
void mPlayer::dmgToTile(float delta, float dmg){
	//bool attacktrigger = false;
	m_attackaccumtime += delta;
	VECTOR2D currentTile = m_pTileMap->getTileCoordinates(*_realVector);
	float fx, fy;

	if (m_attackaccumtime > FRAMERATE * 2.0f){
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
		// 같은 타일내에 겹쳐 있을수도 있으므로...
		m_pTileMap->getTile(currentTile.x, currentTile.y)->onHit(dmg);
		m_pTileMap->getTile(fx, fy)->onHit(dmg);
	}
}



// TODO: 범위를 어떤식으로 받아올까에 대한 고민
void mPlayer::dmgToArea(float delta, float dmg, int AreaType){
	//bool attacktrigger = false;
	m_attackaccumtime += delta;
	VECTOR2D currentTile = m_pTileMap->getTileCoordinates(*_realVector);
	// 차후 struct, class or 동적배열화해서 범위 받아오는 걸로
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

	// 이걸 컨테이너화 해야 하는데...
	std::queue < std::pair<float, float> > skillArea;
	
	switch (AreaType)
	{
	case AREA_TYPE1:
		for (std::pair<float, float> x : Area_Type1[dir]){
			skillArea.push(x);
		}
		break;
	default:

		break;
	}		
	std::queue <std::pair<float, float>> skillCoord;
	if (m_attackaccumtime > FRAMERATE * 2.0f){
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
			
		// 같은 타일내에 겹쳐 있을수도 있으므로...
		// 차후 이 자리에는 타일 onHIT계열이 들어간다. 
		m_pTileMap->getTile(currentTile.x, currentTile.y)->onHit(dmg);
		while (!skillCoord.empty()){
			m_pTileMap->getTile(skillCoord.front().first, skillCoord.front().second)->onHit(dmg);
			skillCoord.pop();
		}
	}
}
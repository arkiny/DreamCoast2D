#include "stdafx.h"
#include <stdio.h>
#include <queue>
#include <vector>
#include "uFileControl.h"
#include "wWorld.h"
#include "mPlayer.h"
#include "mMonster.h"
#include "wTileMap.h"
#include "VECTOR2D.h"

struct DATA{
	float player_x;
	float player_y;
	int map_height;
	int map_width;
	int mapinfo[625];
	int monsterNum;
	float monster_x[100];
	float monster_y[100];
};

uFileControl::uFileControl(wWorld* worldMap)
{
	m_pWorld = worldMap;
}


uFileControl::~uFileControl()
{
	m_pWorld = nullptr;
}

void uFileControl::SaveToFile(int num){
	char fileName[128];
	sprintf(fileName, "map%d.txt", num);

	//char fileName[] = "map1.dat";
	FILE* f;
	if ((f = fopen(fileName, "wb")) == NULL)	{
		MessageBox(NULL, L"File Open Failed!!", L"Error", MB_OK);
		return;
	}
	//float player_x;
	//float player_y;

	//// 맵사이즈
	//int height;
	//int width;
	DATA savechunk;

	/*std::queue<int> mapinfo;
	std::queue<std::pair<float, float>> mobpos;*/

	//플레이어 시작 위치
	savechunk.player_x = m_pWorld->getPlayer()->getRealPos()->x;
	savechunk.player_y = m_pWorld->getPlayer()->getRealPos()->y;

	// 맵사이즈
	savechunk.map_height = static_cast<int>(m_pWorld->getMap()->getMapLimit().y);
	savechunk.map_width = static_cast<int>(m_pWorld->getMap()->getMapLimit().x);
	//std::queue<int> mapinfo;
		
	// 맵 타일 정보
	int save = 0;
	for (int j = 0; j < savechunk.map_height; j++){
		for (int i = 0; i < savechunk.map_width; i++){
			savechunk.mapinfo[save] = m_pWorld->getMap()->getMapinfo(i, j);
			save++;
		}
	}

	//std::queue<VECTOR2D> mobpos;
	VECTOR2D mobpt(0.0f, 0.0f);
	savechunk.monsterNum = m_pWorld->getMap()->getMobList()->size();
	for (int i = 0; i < savechunk.monsterNum; i++){
		mobpt = m_pWorld->getMap()->getTileCoordinates(*(m_pWorld->getMap()->getMobList()->at(i)->getDrawPos()));
		//mobpos.push(std::pair<float, float>(mobpt.x, mobpt.y));
		savechunk.monster_x[i] = mobpt.x;
		savechunk.monster_y[i] = mobpt.y;
		//mobpos.pop();
	}
	
	/*fprintf(f, "%f ", player_x);
	fprintf(f, "%f\n", player_y);
	fprintf(f, "%d ", height);
	fprintf(f, "%d\n", width);

	fprintf(f, "%d\n", mapinfo.size());

	while (!mapinfo.empty()){
		fprintf(f, "%d", mapinfo.front());		
		mapinfo.pop();
	}	
	fprintf(f, "\n");

	while (!mobpos.empty()){
		fprintf(f, "%f", mobpos.front().first);
		fprintf(f, "%f", mobpos.front().second);
		fprintf(f, "\n");
		mobpos.pop();
	}	*/

	//fputs();

	fwrite(&savechunk, sizeof(savechunk), 1, f);
	fclose(f);
	MessageBox(NULL, L"저장되었습니다.", L"파일저장", MB_OK);
}

void uFileControl::LoadFromFile(int num, wWorld* to){
	char fileName[128];
	sprintf(fileName, "map%d.txt", num);
	//char fileName[] = "map1.dat";
	FILE* f;
	if ((f = fopen(fileName, "rb")) == NULL)	{
		MessageBox(NULL, L"File Open Failed!!", L"Error", MB_OK);
		return;
	}
	
	//float player_x ;
	//float player_y ;

	//// 맵사이즈
	//int height ;
	//int width ;
	//std::queue<int> mapinfo;
	//VECTOR2D mobpt(0.0f, 0.0f);

	//std::queue<int> mapinfo;
	//while (true){
	//	if (buff == EOF) break;
	//	
	//}

	DATA loadchunk;
	fread(&loadchunk, sizeof(loadchunk), 1, f);
	fclose(f);
	//to = m_pWorld;
	//float x = a.mobpos.front().first;
	//MessageBox(NULL, L"파일이 로드 되었습니다.", L"파일 로드", MB_OK);

	to->getPlayer()->setRealPos(loadchunk.player_x, loadchunk.player_y);

	to->getMap()->setSize(loadchunk.map_width, loadchunk.map_height);
	int load = 0;
	for (int j = 0; j < loadchunk.map_height; j++){
		for (int i = 0; i < loadchunk.map_width; i++){
			to->getMap()->setTile(i, j, loadchunk.mapinfo[load]);
			load++;
		}
	}

	VECTOR2D mobpt(0.0f, 0.0f);
	
	for (int i = 0; i < loadchunk.monsterNum; i++){
		//mobpt = m_pWorld->getMap()->getTileCoordinates(*(m_pWorld->getMap()->getMobList()->at(i)->getDrawPos()));
		//mobpos.push(std::pair<float, float>(mobpt.x, mobpt.y));
		/*loadchunk.monster_x[i] = mobpt.x;
		loadchunk.monster_y[i] = mobpt.y;*/
		to->getMap()->addMonsterTotile(loadchunk.monster_x[i], loadchunk.monster_y[i]);
		//mobpos.pop();
	}
}
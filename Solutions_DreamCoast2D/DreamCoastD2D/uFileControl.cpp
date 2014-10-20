#include "stdafx.h"
#include "uFileControl.h"
#include "wWorld.h"
#include <iostream>


uFileControl::uFileControl(wWorld* worldMap)
{
	m_pWorld = worldMap;
}


uFileControl::~uFileControl()
{
}

void uFileControl::SaveToFile(int num){
	char fileName[128];
	sprintf(fileName, "map%d.txt", num);

	//char fileName[] = "map1.dat";
	FILE* f;
	if ((f = fopen(fileName, "w")) == NULL)	{
		MessageBox(NULL, L"File Open Failed!!", L"Error", MB_OK);
		return;
	}

	wWorld a = *m_pWorld;

	fwrite(&a, sizeof(a), 1, f);
	fclose(f);
	MessageBox(NULL, L"저장되었습니다.", L"파일저장", MB_OK);
}

void uFileControl::LoadFromFile(int num, wWorld* to){
	char fileName[128];
	sprintf(fileName, "map%d.txt", num);
	//char fileName[] = "map1.dat";
	FILE* f;
	if ((f = fopen(fileName, "r")) == NULL)	{
		MessageBox(NULL, L"File Open Failed!!", L"Error", MB_OK);
		return;
	}
	fread(m_pWorld, sizeof(*m_pWorld), 1, f);
	fclose(f);
	to = m_pWorld;
	MessageBox(NULL, L"파일이 로드 되었습니다.", L"파일 로드", MB_OK);
}
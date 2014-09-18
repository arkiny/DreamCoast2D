DreamCoast2D
============
Game DreamCoast2D Portfolio Project based on Direct2D


09182014 목표 및 노트
- TileMap Draw
- Ordering
- Picking (For문 말고, 해당 좌표를 받으면 좌표를 IsoMetric 타일 좌표화 하여 확인하기)
- Class를 이용해서 데이터 베이스화(해당 데이터베이스는 확대축소를 편하게 하기 위해, STL을 이용한다.)
- 플레이char가 해당 타일에 있을 때 해당 타일 색입히기

* 기술 노트
- 각 타일이 렌더될때, 해당 타일에 캐릭터 정보가 있을때, 해당 오브젝트도 같이 렌더한다.
- ?? 맵이 매번 렌더될때마다 렌더 될텐데, 배경으로 따로 렌더하면서, 
	맵 정보 변경시만 렌더할수 있게 할순 없을까?

09172014 목표
 - Player(object 이동)
 - Vector 이용 이동
 - Pivot 처리하고 해당 유틸 클래스로 리팩터
 - Sprite 부분은 다른 오브젝트에서 사용하므로 Util클래스로 애드할 것)

 clear

09162014 DreamCoastD2D Project Start (ver 09162014)
 - Basic Framework and Test Bed coded
 - 가장 원초적인 프레임워크 코딩을 통해, 차후 캐릭터 모델링등을 테스트할 테스트 베드로 이용한다. 

DreamCoast2D
============
Game DreamCoast2D Portfolio Project based on Direct2D
============

09212014 새벽 작업 결산
- World class 분리 (차후 GameScreen에서 투영)
- TileOrdering Test

해야할것
- 이동불가 처리
- 캐릭터 및 Object 타일링
 -- 가설 : 현재 타일을 깔때 같이 렌더하는 방식은 스프라이트가 잘리는 현상이 일어나므로,
            타일은 먼저 깔고, 캐릭터를 깐뒤에, 해당 타일에 Tree등의 오브젝트를 겹까는 형식으로 실시
			(이렇게 하면 차후 옵션으로 나무삭제등의 옵션을 추가할수 있을 것으로 보인다)

============

09192014 오후 작업 시작
- Sprite Pivot 조정 Clear
- 첫 맵 생성시 설정에 맞게 크기 조절 및 데이터 로딩
- 플레이어 및 오브젝트 오더링 실시 -> 타일 렌더시, 해당 오브젝트가 그 좌표에 있을시에 렌더한다.
- 각 타일별로 데이터 저장하여 이동 못하게 충돌할 것

============

09192014 새벽 작업 종료 및 결산
- Ordering
- Picking (For문 말고, 해당 좌표를 받으면 좌표를 IsoMetric 타일 좌표화 하여 확인하기)
- 플레이char가 해당 타일에 있을 때 해당 타일 색입히기
이상 완료

해야할 것
- Class를 이용해서 데이터 베이스화(해당 데이터베이스는 확대축소를 편하게 하기 위해, STL을 이용한다.)
- 시간이 남을 경우 Pivot 조절 (현재 피봇은 무조건 스프라이트의 가장 밑, 가운데지만, 자연스러운 피벗 조절이 필요할듯)
- 해당 타일을 렌더할때 해당 오브젝트의 색을 변형시키는 함수가 있나?

============

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
	
============

09172014 목표
 - Player(object 이동)
 - Vector 이용 이동
 - Pivot 처리하고 해당 유틸 클래스로 리팩터
 - Sprite 부분은 다른 오브젝트에서 사용하므로 Util클래스로 애드할 것)

 clear

09162014 DreamCoastD2D Project Start (ver 09162014)
 - Basic Framework and Test Bed coded
 - 가장 원초적인 프레임워크 코딩을 통해, 차후 캐릭터 모델링등을 테스트할 테스트 베드로 이용한다. 

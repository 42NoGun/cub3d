# cub3d

## 스케치
- 텍스쳐가 없는 벽면 레이케스트
1. parse map
  - 파일에서 게임 실행에 필요한 정보를 읽어 들여서 적절한 자료구조에 정보를 저장
2. initialize data
  - map file에서 필요한 정보를 구조체에 담는다
  - ex) 플레이어 정보, 텍스쳐 정보 등등
3. launch game
   1) raycast
   - 현재 플레이어가 바라보는 방향을 기준으로 ray를 발사하여 벽을 찾아 내야 한다.
   - 벽을 찾는데는 DDA알고리즘을 사용한다.
   - 찾아낸 벽과 현재 플레이어 위치 사이의 거리를 구한다.
   - 구한 거리를 가지고 실제 화면에 얼마 만큼의 길이로 수직선을 그릴지 판단한다.
   - 화면에 수직선을 그린다.
   - 해당 과정을 화면의 전체 x값(수직선의 위치)에 대해 반복 한다.
   
   2) 이미지 출력
   - 수직선을 하나의 이미지로 만들고 화면에 이미지를 출력한다.

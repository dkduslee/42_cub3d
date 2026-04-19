# 🎮 cub3D 프로젝트 계획서

> 팀원: [login1], [login2] | 기간: 4주 (1달) | 언어: C

---

## 📁 디렉토리 구조

```
cub3D/
├── Makefile
├── README.md
├── includes/
│   ├── cub3d.h          # 메인 헤더 (구조체, 매크로, 함수 프로토타입)
│   └── keys.h           # 키코드 정의
├── srcs/
│   ├── main.c           # 진입점, 초기화, mlx_loop
│   ├── parse/
│   │   ├── parse.c      # .cub 파일 파싱 진입점
│   │   ├── parse_map.c  # 맵 파싱 및 유효성 검사
│   │   ├── parse_texture.c  # NO/SO/WE/EA 텍스처 경로 파싱
│   │   └── parse_color.c    # F/C 색상 파싱
│   ├── render/
│   │   ├── render.c     # 렌더링 루프 (매 프레임)
│   │   ├── raycasting.c # DDA 알고리즘 핵심 로직
│   │   ├── texture.c    # 벽 텍스처 매핑
│   │   └── draw.c       # mlx_put_pixel, 천장/바닥 색상 칠하기
│   ├── player/
│   │   ├── move.c       # W/A/S/D 이동 처리
│   │   └── rotate.c     # 좌우 화살표 회전 처리
│   ├── event/
│   │   └── hooks.c      # ESC, X버튼, 키 입력 이벤트 연결
│   └── utils/
│       ├── error.c      # 에러 메시지 출력 및 종료
│       ├── free.c       # 모든 메모리 해제
│       └── utils.c      # 공통 유틸 함수 (ft_split 등)
├── textures/            # 벽 텍스처 이미지 (xpm 파일)
│   ├── north.xpm
│   ├── south.xpm
│   ├── east.xpm
│   └── west.xpm
└── maps/                # 테스트용 .cub 맵 파일
    ├── valid.cub
    └── invalid_*.cub    # 에러 케이스 테스트용
```

---

## 🏗️ 핵심 구조체 설계

```c
/* 텍스처 이미지 */
typedef struct s_img {
    void    *img_ptr;
    char    *addr;
    int     bits_per_pixel;
    int     line_len;
    int     endian;
    int     width;
    int     height;
}   t_img;

/* 플레이어 */
typedef struct s_player {
    double  pos_x;      // 위치
    double  pos_y;
    double  dir_x;      // 방향 벡터
    double  dir_y;
    double  plane_x;    // 카메라 평면 벡터
    double  plane_y;
}   t_player;

/* 맵 정보 */
typedef struct s_map {
    char    **grid;     // 2D 맵 배열
    int     rows;
    int     cols;
    char    *no_path;   // 텍스처 경로
    char    *so_path;
    char    *we_path;
    char    *ea_path;
    int     floor_color;    // 0xRRGGBB
    int     ceiling_color;
}   t_map;

/* 메인 게임 구조체 */
typedef struct s_game {
    void        *mlx;
    void        *win;
    t_img       screen;     // 화면 버퍼 이미지
    t_img       textures[4]; // 0:N 1:S 2:E 3:W
    t_player    player;
    t_map       map;
}   t_game;
```

---

## 📐 레이캐스팅 알고리즘 흐름

```
매 프레임마다:
┌─────────────────────────────────────┐
│  화면 가로 픽셀(x = 0 ~ WIDTH-1) 순회  │
│                                     │
│  1. 카메라 좌표 계산                  │
│     camera_x = 2 * x / WIDTH - 1   │
│                                     │
│  2. 레이 방향 벡터 계산               │
│     ray_dir = dir + plane * camera_x│
│                                     │
│  3. DDA 알고리즘으로 벽 충돌 탐지     │
│     (delta_dist, side_dist 계산)    │
│                                     │
│  4. 벽까지의 거리(perp_wall_dist) 계산│
│                                     │
│  5. 그릴 벽 높이 계산                │
│     line_height = HEIGHT / dist     │
│                                     │
│  6. 텍스처 좌표 계산 후 픽셀 그리기   │
└─────────────────────────────────────┘
```

**참고 자료:** [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) (필독!)

---

## 📅 4주 개발 일정

### 역할 분담

| 파트 | 담당 | 설명 |
|------|------|------|
| 파싱 전체 | 팀원 A | .cub 파일 읽기, 맵/텍스처/색상 파싱, 유효성 검사 |
| 레이캐스팅 + 렌더링 | 팀원 B | DDA 알고리즘, 텍스처 매핑, 화면 출력 |
| 플레이어 이동/회전 | 팀원 B | 키 입력 처리, 충돌 없는 이동 |
| mlx 세팅, 이벤트 | 공동 | 윈도우, 훅 연결, 종료 처리 |
| 에러/메모리 관리 | 공동 | free, error 함수 |

---

### 1주차 — 기반 세팅 & 파싱

**목표: 프로그램이 .cub 파일을 읽고 구조체에 저장할 수 있어야 한다.**

- [ ] 프로젝트 디렉토리 구조 세팅, Makefile 작성
- [ ] 공통 헤더 (`cub3d.h`) 설계 — 구조체 확정
- [ ] mlx 초기화 및 빈 윈도우 띄우기 (Hello World 수준)
- [ ] .cub 파일 읽기 (get_next_line 활용)
- [ ] NO/SO/WE/EA 텍스처 경로 파싱
- [ ] F/C 색상 파싱 (R,G,B → int 변환)
- [ ] 맵 파싱 (2D 배열로 저장)
- [ ] 맵 유효성 검사: 벽으로 둘러싸임 여부, 플레이어 위치 1개, 허용 문자만 존재
- [ ] 에러 시 `"Error\n" + 메시지` 출력 후 종료

---

### 2주차 — 레이캐스팅 & 기본 렌더링

**목표: 흑백이라도 좋으니 3D 벽이 화면에 보여야 한다.**

- [ ] 플레이어 초기 pos, dir, plane 벡터 계산 (N/S/E/W 방향에 따라)
- [ ] 카메라 평면, 레이 방향 벡터 계산
- [ ] DDA 알고리즘 구현 (벽 충돌 감지)
- [ ] 벽까지 수직 거리 계산, 어안렌즈 왜곡 제거
- [ ] 벽 높이 계산 후 선 그리기 (단색)
- [ ] 천장 / 바닥 단색으로 채우기
- [ ] mlx image buffer (`mlx_get_data_addr`) 활용 픽셀 직접 쓰기

---

### 3주차 — 텍스처 매핑 & 이동/회전

**목표: 텍스처가 입혀진 완성된 뷰와 자유로운 이동이 가능해야 한다.**

- [ ] xpm 텍스처 로딩 (`mlx_xpm_file_to_image`)
- [ ] 벽 히트 면(N/S/E/W)에 따른 텍스처 선택
- [ ] 텍스처 X좌표 (wallX) 계산
- [ ] 텍스처 Y좌표 (step별 texPos) 계산 후 픽셀 샘플링
- [ ] W/A/S/D 이동 구현 (방향 벡터 기반)
- [ ] 좌우 화살표 회전 구현 (회전 행렬 적용)
- [ ] ESC, 윈도우 X 버튼 종료 처리
- [ ] 전체 메모리 누수 점검 (valgrind)

---

### 4주차 — 완성 & 테스트 & (보너스)

**목표: 완성도 높이기, 예외 처리 강화, 선택적으로 보너스 구현**

- [ ] 다양한 맵으로 엣지 케이스 테스트
- [ ] 비정상 입력 전체 에러 처리 점검
- [ ] 코드 Norm 검사 (norminette)
- [ ] README.md 작성
- [ ] 여유 있으면 보너스:
  - [ ] 벽 충돌 처리 (Wall collision)
  - [ ] 마우스로 시점 회전
  - [ ] 미니맵

---

## ⚠️ 주요 주의사항

1. **맵은 반드시 벽(1)으로 둘러싸여야 함** — flood fill 또는 경계 검사로 검증
2. **플레이어는 정확히 1명** — N, S, E, W 중 하나만 존재
3. **맵은 .cub 파일에서 항상 마지막에 위치**
4. **공백(space)도 맵의 유효한 구성 요소** — 공백 안으로 이동 시 에러
5. **모든 힙 메모리 해제 필수** — valgrind로 반드시 확인
6. **Norm 위반 시 0점** — 함수당 25줄, 파일당 5개 함수 등 규칙 준수
7. **보너스는 mandatory가 완벽할 때만 채점됨**

---

## 🔗 핵심 참고 자료

| 자료 | 링크 |
|------|------|
| Lode's Raycasting Tutorial (필독) | https://lodev.org/cgtutor/raycasting.html |
| miniLibX 공식 문서 | https://harm-smits.github.io/42docs/libs/minilibx |
| DDA 알고리즘 설명 | https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm) |
| 원본 게임 플레이 | http://users.atw.hu/wolf3d/ |

---

## ✅ 완료 기준 체크리스트

- [ ] `make` 시 경고 없이 컴파일
- [ ] 유효한 .cub 파일로 실행 시 3D 뷰 정상 출력
- [ ] W/A/S/D 이동, 화살표 회전 동작
- [ ] N/S/E/W 벽마다 다른 텍스처 출력
- [ ] 천장/바닥 색상 정상 출력
- [ ] ESC 및 X버튼 정상 종료
- [ ] 잘못된 맵 입력 시 `Error\n` + 메시지 출력
- [ ] valgrind 메모리 누수 없음
- [ ] norminette 통과

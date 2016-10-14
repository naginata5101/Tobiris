#include <Mikan.h>
#include <time.h>
#include <direct.h>

#define WIDHT 640
#define HEIGHT 480

#define UP 0	//"â°"Ç∆åìóp
#define RIGHT 1	//"èc"Ç∆åìóp
#define DOWN 2
#define LEFT 3

#define TITLE 0
#define STAGE_SELECT 1
#define EXPLANATION 2
#define PUZZLE_GAME 10
#define ENDLESS_GAME 11
#define BATTLE_GAME 12
#define EDITOR 100

#define T_I 0
#define T_S 1
#define T_Z 2
#define T_J 3
#define T_L 4
#define T_O 5
#define T_T 6

const int ChipSize = 20;
const int BlockHei = 20 + 2;
const int BlockWid = 10 + 2;

const int StageMax = 10;
const int TetriMax = 50;

const int LimitTime = 300;
const int StartTime = 60;
const int ChainTime = 10 * 60;
const int SecondX = WIDHT - ( 2 + 10 ) * ChipSize;

struct tetrimino
{
	int x[ TetriMax ];
	int y[ TetriMax ];

	int t[ TetriMax ];
	int dir[ TetriMax ];
	int ori[ TetriMax ];
	int time[ TetriMax ];
};
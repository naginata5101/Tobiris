#include "common.h"


int mode = 0;
int selection;
int timer;
//背景のブロック達
int back[ HEIGHT / ChipSize ][ WIDHT / ChipSize ];

int cursorX, cursorY;
//カーソルの種類（テトリミノ(true)orポインタ(false)）
bool cursorT;
int choice = 0;
int direction = UP;
int EndTime;
bool menu = false;
struct tetrimino tetri;

int StageNum;
int UsedTet[ 7 ];
int LimitTet[ 7 ];
bool fail, clear, timeUP;

int SlideTime;
int score;
int HighScore = 0;
//連続数=N,連続の種類=T
int comboN, comboT, comboP, comboTime;
bool DidMove = false;

//バトルでの勝者（引き分けは0）
int winner;

int cursorX2, cursorY2;
bool cursorT2;
int choice2 = 0;
int selection2 = 0;
int direction2 = 0;
int SlideTime2;
int score2;
int comboN2, comboT2, comboP2, comboTime2;
bool DidMove2 = false;
struct tetrimino tetri2;




//パズルモードで直前に飛ばしたテトリミノが元にいた座標
int LastBlockX[ 4 ] = { -100, -100, -100, -100 };
int	LastBlockY[ 4 ] = { -100, -100, -100, -100 };





void Set_Back( int back[ HEIGHT / ChipSize ][ WIDHT / ChipSize ] );
void Draw_BackGround( int back[ HEIGHT / ChipSize ][ WIDHT / ChipSize ] );

void Chenge_CursorType( bool *cursorT, bool *cursorT2 );

void Move_Title( int *selection );
void Choice_Title( int block[ BlockHei ][ BlockWid ], int block2[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], struct tetrimino *tet, struct tetrimino *tet2,
	int *mode, int *selection, int *selection2, int *choice, int *choice2, int *direction, int *direction2, int *timer, int *cursorX, int *cursorX2, int *cursorY, int *cursorY2,
	int *EndTime, int *score, int *score2, int *comboN, int *comboN2, int *comboT, int *comboT2, int *comboP, int *comboP2, int *comboTime, int *comboTime2, int *winner, bool *menu );
void Move_StageSelecte( int *selection );
void Choice_StageSelecte( const int stage[ StageMax ][ BlockHei ][ BlockWid ], int block[ BlockHei ][ BlockWid ], int stocks[ StageMax ][ 7 ], int UsedTet[ 7 ], int LimitTet [ 7 ],
	struct tetrimino *tet, int *mode, int *selection, int *timer, int *StageNum, int *cursorX, int *cursorY, int *choice, int *direction, int *EndTime, bool *menu, bool *timeUP, bool *clear, bool *fail );
void Move_Explanation( int *mode, int *selection );


void Silhouette_Cursor_Change( int PadNum, int *choice, int *direction );
void Silhouette_Cursor_Move( int PadNum, int *x, int *y, int choice, int direction );
bool Silhouette_Make_Tetrimino( int PadNum, int block[ BlockHei ][ BlockWid ], int LimitTet[ 7 ], int UsedTet[ 7 ], int LastBlockX[ 4 ], int LastBlockY[ 4 ],
	struct tetrimino *tet, int choice, int direction, int timer, int x, int y, int StageNum, int mode );

bool Pointer_Cursor_Move( int PadNum, int block[ BlockHei ][ BlockWid ], int *x, int *y );
void Pointer_Choice_Block( int PadNum, int block[ BlockHei ][ BlockWid ], int x, int y, int *choice, bool DidMove );
bool Pointer_Make_Tetrimino( int block[ BlockHei ][ BlockWid ], int LimitTet[ 7 ], int UsedTet[ 7 ], int LastBlockX[ 4 ], int LastBlockY[ 4 ],
	struct tetrimino *tet, int *choice, int mode, int StageNum );


void Puzzle_Move_Tetrimino( struct tetrimino *tet, int timer );
void Puzzle_TimeUP( int timer, int *EndTime, bool *timeUP );
void Puzzle_Menu( int PadNum, int block[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], int LastBlockX[ 4 ], int LastBlockY[ 4 ],
	struct tetrimino *tet, int *mode, int *selection, int *choice, bool *menu, bool cursorT );
void Puzzle_Check_End( int block[ BlockHei ][ BlockWid ], bool *fail, bool *clear, int timer, int *EndTime );
void Puzzle_GameOver( int PadNum, struct tetrimino *tet, int *mode, int timer, int EndTime, bool clear, bool *menu );
	
void Update_HighScore( bool endless, int *score, int *HighScore, int timer, int EndTime );

void Endless_Move_Tetrimino( int block[ BlockHei ][ BlockWid ], struct tetrimino *tet, int timer );
void Endless_Move_Blocks( int PadNum, int block[ BlockHei ][ BlockWid ], int timer, int *SlideTime, int *EndTime, int *cursorX, int *cursorY, int *score, int *winner );
void Endless_Count_Score( struct tetrimino *tet, int *score, int *comboN, int *comboT, int *comboP, int *conboTime, int timer );
void Endless_Menu( int PadNum, int *mode, int *selection, bool *menu );
void Endless_GameOver( int PadNum, int *mode, int *score, int *comboP, int *comboTime, int timer, int EndTime, bool *menu );

void Battle_Count_Score( struct tetrimino *tet, int *score, int *comboN, int *comboT, int *comboP, int *comboTime, int timer,
	int block2[ BlockHei ][ BlockWid ], int *cursorY2 );


void Draw_BlockBack();
void Draw_Title( int selection, bool cursorT, bool cursorT2 );
void Draw_StageSelection( int selection );
void Draw_Thumbnail( const int stage[ StageMax ][ BlockHei ][ BlockWid ], int selection );
void Draw_Explanation( int selection );


void Draw_Block( int block[ BlockHei ][ BlockWid ] );
void Draw_Tetrimino( struct tetrimino tet );

void Draw_Silhouette_Cursor( int x, int y, int choice, int dirction );
void Draw_Puzzle_Tetrinimos( int LimitTet[ 7 ], int UsedTet[ 7 ], int StageNum, int choice, bool cursorT );
void Draw_Puzzle_Menu( int selection );
void Draw_Limit_Time( int timer, int EndTime );
void Draw_Puzzle_End( int timer, int EndTime, bool menu, bool timeUP, bool clear, bool fail );

void Draw_Pointer_Cursor( int x, int y );
void Draw_Endless_PlayTime( int timer, int EndTime );
void Draw_Endless_Score( int score, int comboN, int comboT, int comboP, int conboTime, int timer );
void Draw_Endless_Menu( int selection );
void Draw_Endless_End( int timer, int EndTime, int score, int HighScore, bool menu );

void Draw_Battle_BlockBack();
void Draw_Battle_Block( int block[ BlockHei ][ BlockWid ], int block2[ BlockHei ][ BlockWid ] );
void Draw_Battle_Tetrimino( struct tetrimino tet, struct tetrimino tet2 );
void Draw_Battle_Cursor( int x, int y, int x2, int y2, bool t, bool t2, int choice, int choice2, int direction, int direction2 );
void Draw_Battle_PlayTime( int timer, int EndTime );
void Draw_Battle_Score( int timer, int score, int score2, int comboN, int comboN2, int comboT, int comboT2,
	int comboP, int comboP2, int comboTime, int comboTime2 );
void Draw_Battle_Menu( int selection, int selection2 );
void Draw_Battle_End( int timer, int EndTime, int score, int score2, int HighScore, bool menu, int winner );



void Editor_Make_Tetrimino( int block[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], struct tetrimino *tet,
	int *mode, int choice, int *selection, int direction, int x, int y, bool *menu );
void Draw_Editor_Tetrinimos( int UsedTet[ 7 ], int choice );
void Draw_Editor_Menu( int selection );




int stocks[ StageMax ][ 7 ] =
{
	//全てに余裕(1ずつ)有り
	{ 4, 5, 5, 4, 5, 4, 5 },
	{ 5, 5, 5, 5, 5, 5, 5 },
	{ 4, 4, 5, 3, 3, 2, 4 },
	{ 3, 3, 4, 5, 4, 3, 6 },
	//一部に余裕有り
		//I,O,T
	{ 4, 4, 4, 4, 4, 4, 4,},
		//S,Z,J,L
	{ 0, 7, 7, 7, 7, 0, 0 },
	//余裕Zero
	{ 3, 3, 3, 3, 3, 3, 3 },
	{ 4, 4, 4, 3, 3, 3, 4 },
	{ 4, 4, 4, 4, 4, 4, 4 },
	{ 8, 6, 8, 7, 6, 7, 8 }
};


int block[ BlockHei ][ BlockWid ] =
{
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
};

int block2[ BlockHei ][ BlockWid ] =
{
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
};


const int stage[ StageMax ][ BlockHei ][ BlockWid ] =
{
	{
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
	},
	{
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  1,  0,  0,  0,  1,  1,  0, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
	},
	{
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0, -1 },
		{ -1,  1,  0,  0,  0,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  0,  1,  0,  0,  0,  1,  0, -1 },
		{ -1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  0, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1, -1 },
		{ -1,  0,  1,  1,  0,  1,  1,  1,  1,  0,  1, -1 },
		{ -1,  1,  1,  0,  0,  1,  1,  0,  1,  0,  1, -1 },
		{ -1,  0,  1,  1,  1,  1,  0,  1,  1,  1,  1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
	},
	{
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0, -1 },
		{ -1,  0,  0,  1,  0,  1,  1,  1,  1,  0,  0, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1, -1 },
		{ -1,  1,  1,  1,  0,  1,  1,  0,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  0,  1,  1,  1,  0,  0,  1,  1,  0, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  0,  1,  0,  0,  1,  0,  0,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  0,  0,  1,  1,  1,  1,  0,  1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
	},
	{
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  1,  0,  0,  0,  0,  1,  1,  0,  1, -1 },
		{ -1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  0,  1,  1,  1,  1,  0,  1, -1 },
		{ -1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  0, -1 },
		{ -1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  1, -1 },
		{ -1,  1,  1,  1,  0,  1,  1,  1,  1,  0,  1, -1 },
		{ -1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	},
	{
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  1,  1,  1,  0,  0,  1,  1,  1,  0,  0, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	},
	{
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0, -1 },
		{ -1,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0, -1 },
		{ -1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  1,  1,  1,  1,  1,  1,  0,  0,  0, -1 },
		{ -1,  0,  0,  1,  0,  1,  1,  1,  1,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1, -1 },
		{ -1,  0,  1,  1,  1,  1,  1,  1,  0,  1,  0, -1 },
		{ -1,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  1,  1,  0,  0,  1,  1,  1,  1,  1,  0, -1 },
		{ -1,  1,  0,  0,  0,  0,  1,  0,  1,  1,  1, -1 },
		{ -1,  1,  0,  0,  0,  1,  1,  1,  1,  0,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1, -1 },
		{ -1,  0,  1,  1,  0,  1,  1,  1,  1,  1,  1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	},
	{
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0, -1 },
		{ -1,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0, -1 },
		{ -1,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0, -1 },
		{ -1,  1,  1,  1,  0,  0,  0,  0,  1,  1,  1, -1 },
		{ -1,  0,  1,  1,  0,  1,  1,  0,  1,  1,  0, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  0,  1,  1,  1,  1,  0,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  0,  0,  1,  0,  0,  0,  0,  1,  0,  0, -1 },
		{ -1,  1,  0,  1,  1,  0,  0,  1,  1,  0,  1, -1 },
		{ -1,  1,  0,  1,  0,  1,  1,  0,  1,  0,  1, -1 },
		{ -1,  1,  1,  1,  0,  1,  1,  0,  1,  1,  1, -1 },
		{ -1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  0, -1 },
		{ -1,  1,  1,  1,  1,  0,  0,  1,  1,  1,  1, -1 },
		{ -1,  1,  0,  0,  1,  1,  1,  1,  0,  0,  1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	},
	{
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,},
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
		{ -1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0, -1 },
		{ -1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  0, -1 },
		{ -1,  1,  1,  0,  0,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  0, -1 },
		{ -1,  0,  1,  0,  1,  1,  1,  1,  0,  1,  1, -1 },
		{ -1,  0,  1,  0,  0,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  0,  1,  1,  1,  0,  1, -1 },
		{ -1,  0,  1,  1,  0,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1, -1 },
		{ -1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  0,  0,  1,  0,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1, -1 },
		{ -1,  1,  0,  1,  1,  0,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  0, -1 },
		{ -1,  0,  1,  1,  1,  1,  0,  0,  1,  1,  0, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	},
	{
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	}
};
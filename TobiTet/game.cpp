#include "common.h"


//ゲーム開始の準備===================================================
//背景のブロックの配置
void Set_Back( int back[ HEIGHT / ChipSize ][ WIDHT / ChipSize ] )
{
	for( int i = 0; i < HEIGHT / ChipSize; i ++ )
	{
		for( int j = 0; j < WIDHT / ChipSize; j ++ )
		{
			back[ i ][ j ] = rand() % 8;
		}
	}
}

//カーソル配置
void Put_Cursor( int block[ BlockHei ][ BlockWid ], int *x, int *y )
{
	for( int i = 0; i < BlockHei; i++ )
	{
		for( int j = 0; j < BlockWid; j ++)
		{
			if( block[ i ][ j ] == 1 )
			{
				*x = j;
				//誤射を防ぐために、1段上に置く。
				*y = i - 1;
				return;
			}
		}
	}
}

//そのテトリミノが宙に浮いていないかの判定（設置していたらtrue）
bool Tetrimino_Stand_Ground( int block[ BlockHei ][ BlockWid ], int x, int y, int t, int d )
{
	//I
	if( t == T_I &&
		( d == UP ||
		  d == DOWN ) &&
		( block[ y + 1 ][ x - 1 ] != 0 ||
		  block[ y + 1 ][ x ] != 0 ||
		  block[ y + 1 ][ x + 1 ] != 0 ||
		  block[ y + 1 ][ x + 2 ] != 0 ) )
	{
		return true;
	}
	if( t == T_I &&
		( d == RIGHT ||
		  d == LEFT ) &&
		block[ y + 3 ][ x ] != 0 )
	{
		return true;
	}

	//S
	if( t == T_S &&
		( d == UP ||
		  d == DOWN ) &&
		( block[ y + 2 ][ x - 1 ] != 0 ||
		  block[ y + 2 ][ x ] != 0 ||
		  block[ y + 1 ][ x + 1 ] != 0 ) )
	{
		return true;
	}
	if( t == T_S &&
		( d == RIGHT ||
		  d == LEFT ) &&
		( block[ y + 1 ][ x ] != 0 ||
		  block[ y + 2 ][ x + 1 ] != 0 ) )
	{
		return true;
	}

	//Z
	if( t == T_Z &&
		( d == UP ||
		  d == DOWN ) &&
		( block[ y + 1 ][ x - 1 ] != 0 ||
		  block[ y + 2 ][ x ] != 0 ||
		  block[ y + 2 ][ x + 1 ] != 0 ) )
	{
		return true;
	}
	if( t == T_Z &&
		( d == RIGHT ||
		  d == LEFT ) &&
		( block[ y + 2 ][ x - 1 ] != 0 ||
		  block[ y + 1 ][ x ] != 0 ) )
	{
		return true;
	}

	//J
	if( t == T_J &&
		d == UP &&
		( block[ y + 1 ][ x - 1 ] != 0 ||
		  block[ y + 1 ][ x ] != 0 ||
		  block[ y + 1 ][ x + 1 ] != 0 ) )
	{
		return true;
	}
	if( t == T_J &&
		d == RIGHT &&
		( block[ y + 2 ][ x ] != 0 ||
		  block[ y ][ x + 1 ] != 0 ) )
	{
		return true;
	}
	if( t == T_J &&
		d == DOWN &&
		( block[ y + 1 ][ x - 1 ] != 0 ||
		  block[ y + 1 ][ x ] != 0 ||
		  block[ y + 2 ][ x + 1 ] != 0 ) )
	{
		return true;
	}
	if( t == T_J &&
		d == LEFT &&
		( block[ y + 2 ][ x - 1 ] != 0 ||
		  block[ y + 2 ][ x ] != 0 ) )
	{
		return true;
	}

	//L
	if( t == T_L &&
		d == UP &&
		( block[ y + 1 ][ x - 1 ] != 0 ||
		  block[ y + 1 ][ x ] != 0 ||
		  block[ y + 1 ][ x + 1 ] != 0 ) )
	{
		return true;
	}
	if( t == T_L &&
		d == RIGHT &&
		( block[ y + 2 ][ x ] != 0 ||
		  block[ y + 2 ][ x + 1 ] != 0 ) )
	{
		return true;
	}
	if( t == T_L &&
		d == DOWN &&
		( block[ y + 2 ][ x - 1 ] != 0 ||
		  block[ y + 1 ][ x ] != 0 ||
		  block[ y + 1 ][ x + 1 ] != 0 ) )
	{
		return true;
	}
	if( t == T_L &&
		d == LEFT &&
		( block[ y ][ x - 1 ] != 0 ||
		  block[ y + 2 ][ x ] != 0 ) )
	{
		return true;
	}

	//O
	if( t == T_O &&
		( block[ y + 2 ][ x ] != 0 ||
		  block[ y + 2 ][ x + 1 ] != 0 ) )
	{
		return true;
	}

	//T
	if( t == T_T &&
		d == UP &&
		( block[ y + 1 ][ x - 1 ] != 0 ||
		  block[ y + 1 ][ x ] != 0 ||
		  block[ y + 1 ][ x + 1 ] != 0 ) )
	{
		return true;
	}
	if( t == T_T &&
		d == RIGHT &&
		( block[ y + 2 ][ x ] != 0 ||
		  block[ y + 1 ][ x + 1 ] != 0 ) )
	{
		return true;
	}
	if( t == T_T &&
		d == DOWN &&
		( block[ y + 1 ][ x - 1 ] != 0 ||
		  block[ y + 2 ][ x ] != 0 ||
		  block[ y + 1 ][ x + 1 ] != 0 ) )
	{
		return true;
	}
	if( t == T_T &&
		d == LEFT &&
		( block[ y + 1 ][ x - 1 ] != 0 ||
		  block[ y + 2 ][ x ] != 0 ) )
	{
		return true;
	}

	return false;
}

//ランダムステージを作る
void Random_Make_Stage( int block[ BlockHei ][ BlockWid ], int LimitTet[ 7 ] )
{
	//そのテトリミノのx,type,directionの変数
	int x, t, d;

	//初期化
	for( int i = 1; i < BlockHei - 1; i ++ )
	{
		for( int j = 1; j < BlockWid - 1; j ++ )
		{
			block[ i ][ j ] = 0;
		}
	}
	for( int i = 0; i < 7; i ++ )
	{
		LimitTet[ i ] = 0;
	}

	//テトリミノの配置に20回だけ挑戦する。
	for( int i = 0; i < 20; i ++ )
	{
		x = rand() % ( BlockWid - 2 ) + 1;
		t = rand() % 7;
		d = rand() % 4;
		//X座標の修正------------
		//I型
		if( t == T_I &&
			( d == UP ||
			d == DOWN ) )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1;
			}
			if( x > BlockWid - 2 - 2 )
			{
				x = BlockWid - 2 - 2;
			}
		}
		else if( t == T_I &&
			( d == RIGHT ||
			d == LEFT ) )
		{
			if( x < 1 )
			{
				x = 1;
			}
			if( x > BlockWid - 2 )
			{
				x = BlockWid - 2;
			}
		}

		//S型
		else if( t == T_S &&
			( d == UP ||
			d == DOWN ) )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1 ;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}
		else if( t == T_S &&
			( d == RIGHT ||
			d == LEFT ) )
		{
			if( x < 1 )
			{
				x = 1;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}

		//Z型
		else if( t == T_Z &&
			( d == UP ||
			d == DOWN ) )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}
		else if( t == T_Z &&
			( d == RIGHT ||
			d == LEFT ) )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1;
			}
			if( x > BlockWid - 2 )
			{
				x = BlockWid - 2;
			}
		}

		//J型
		else if( t == T_J &&
			d == UP )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}
		else if( t == T_J &&
			d == RIGHT )
		{
			if( x < 1 )
			{
				x = 1;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}
		else if( t == T_J &&
			d == DOWN )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}
		else if( t == T_J &&
			d == LEFT )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1;
			}
			if( x > BlockWid - 2 )
			{
				x = BlockWid - 2;
			}
		}

		//L型
		else if( t == T_L &&
			d == UP )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}
		else if( t == T_L &&
			d == RIGHT )
		{
			if( x < 1 )
			{
				x = 1;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}
		else if( t == T_L &&
			d == DOWN )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}
		else if( t == T_L &&
			d == LEFT )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1;
			}
			if( x > BlockWid - 2 )
			{
				x = BlockWid - 2;
			}
		}

		//O型
		else if( t == T_O )
		{
			if( x < 1 )
			{
				x = 1;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}

		//T型
		else if( t == T_T &&
			d == UP )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}
		else if( t == T_T &&
			d == RIGHT )
		{
			if( x < 1 )
			{
				x = 1;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}
		else if( t == T_T &&
			d == DOWN )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1;
			}
			if( x > BlockWid - 2 - 1 )
			{
				x = BlockWid - 2 - 1;
			}
		}
		else if( t == T_T &&
			d == LEFT )
		{
			if( x < 1 + 1 )
			{
				x = 1 + 1;
			}
			if( x > BlockWid - 2 )
			{
				x = BlockWid - 2;
			}
		}

		//Y座標の決定
		for( int y = 1; y < BlockHei - 1; y ++ )
		{
			if( Tetrimino_Stand_Ground( block, x, y, t, d ) == true &&
				!( t == T_I && ( d == RIGHT || d == LEFT ) && y == 1 ) &&
				!( t == T_S && ( d == UP || d == DOWN ) && y == 1 ) &&
				!( t == T_Z && ( d == UP || d == DOWN ) && y == 1 ) &&
				!( t == T_J && y == 0) &&
				!( t == T_L && y == 0) &&
				!( t == T_T && d != DOWN && y == 1 ) )
			{
				bool puted = false;
				//実際にブロックを置く。---------
				//I型
				if( puted == false &&
					t == T_I &&
					( d == UP ||
					d == DOWN ) )
				{
					if( block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y ][ x + 2 ] != 1 )
					{
						block[ y ][ x - 1 ] = 1;
						block[ y ][ x ] = 1;
						block[ y ][ x + 1 ] = 1;
						block[ y ][ x + 2 ] = 1;

						puted = true;
					}
				}
				if( puted == false &&
					t == T_I &&
					( d == RIGHT ||
					d == LEFT ) )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x ] != 1 &&
						block[ y + 2 ][ x ] != 1 )
					{ 
						block[ y - 1 ][ x ] = 1;
						block[ y ][ x ] = 1;
						block[ y + 1 ][ x ] = 1;
						block[ y + 2 ][ x ] = 1;

						puted = true;
					}
				}

				//S型
				if( puted == false &&
					t == T_S &&
					( d == UP ||
					d == DOWN ) )
				{
					if( block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y + 1 ][ x - 1 ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						block[ y ][ x ] = 1;
						block[ y ][ x + 1 ] = 1;
						block[ y + 1 ][ x - 1 ] = 1;
						block[ y + 1 ][ x ] = 1;

						puted = true;
					}
				}
				if( puted == false &&
					t == T_S &&
					( d == RIGHT ||
					d == LEFT ) )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x + 1 ] != 1 )
					{
						block[ y - 1 ][ x ] = 1;
						block[ y ][ x + 1 ] = 1;
						block[ y ][ x ] = 1;
						block[ y + 1 ][ x + 1 ] = 1;

						puted = true;
					}
				}

				//Z型
				if( puted == false &&
					t == T_Z &&
					( d == UP ||
					d == DOWN ) )
				{
					if( block[ y ][ x ] != 1 &&
						block[ y ][ x - 1 ] != 1 &&
						block[ y + 1 ][ x ] != 1 &&
						block[ y + 1 ][ x + 1 ] != 1 )
					{
						block[ y ][ x ] = 1;
						block[ y ][ x - 1 ] = 1;
						block[ y + 1 ][ x ] = 1;
						block[ y + 1 ][ x + 1 ] = 1;

						puted = true;
					}
				}
				if( puted == false &&
					t == T_Z &&
					( d == RIGHT ||
					d == LEFT ) )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x - 1 ] != 1 )
					{
						block[ y - 1 ][ x ] = 1;
						block[ y ][ x - 1 ] = 1;
						block[ y ][ x ] = 1;
						block[ y + 1 ][ x - 1 ] = 1;

						puted = true;
					}
				}

				//J型
				if( puted == false &&
					t == T_J &&
					d == UP )
				{
					if( block[ y - 1 ][ x - 1 ] != 1 &&
						block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 )
					{
						block[ y - 1 ][ x - 1 ] = 1;
						block[ y ][ x - 1 ] = 1;
						block[ y ][ x ] = 1;
						block[ y ][ x + 1 ] = 1;

						puted = true;
					}
				}
				if( puted == false &&
					t == T_J &&
					d == RIGHT )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y - 1 ][ x + 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						block[ y - 1 ][ x ] = 1;
						block[ y - 1 ][ x + 1 ] = 1;
						block[ y ][ x ] = 1;
						block[ y + 1 ][ x ] = 1;

						puted = true;
					}
				}
				if( puted == false &&
					t == T_J &&
					d == DOWN )
				{
					if( block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y + 1 ][ x + 1 ] != 1 )
					{
						block[ y ][ x - 1 ] = 1;
						block[ y ][ x ] = 1;
						block[ y ][ x + 1 ] = 1;
						block[ y + 1 ][ x + 1 ] = 1;

						puted = true;
					}
				}
				if( puted == false &&
					t == T_J &&
					d == LEFT )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x - 1 ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						block[ y - 1 ][ x ] = 1;
						block[ y ][ x ] = 1;
						block[ y + 1 ][ x - 1 ] = 1;
						block[ y + 1 ][ x ] = 1;

						puted = true;
					}
				}

				//L型
				if( puted == false &&
					t == T_L &&
					d == UP )
				{
					if( block[ y - 1 ][ x + 1 ] != 1 &&
						block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 )
					{
						block[ y - 1 ][ x + 1 ] = 1;
						block[ y ][ x - 1 ] = 1;
						block[ y ][ x ] = 1;
						block[ y ][ x + 1 ] = 1;

						puted = true;
					}
				}
				if( puted == false &&
					t == T_L &&
					d == RIGHT )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x ] != 1 &&
						block[ y + 1 ][ x + 1 ] != 1 )
					{
						block[ y - 1 ][ x ] = 1;
						block[ y ][ x ] = 1;
						block[ y + 1 ][ x ] = 1;
						block[ y + 1 ][ x + 1 ] = 1;

						puted = true;
					}
				}
				if( puted == false &&
					t == T_L &&
					d == DOWN )
				{
					if( block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y + 1 ][ x - 1 ] != 1 )
					{
						block[ y ][ x - 1 ] = 1;
						block[ y ][ x ] = 1;
						block[ y ][ x + 1 ] = 1;
						block[ y + 1 ][ x - 1 ] = 1;

						puted = true;
					}
				}
				if( puted == false &&
					t == T_L &&
					d == LEFT )
				{
					if( block[ y - 1 ][ x - 1 ] != 1 &&
						block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						block[ y - 1 ][ x - 1 ] = 1;
						block[ y - 1 ][ x ] = 1;
						block[ y ][ x ] = 1;
						block[ y + 1 ][ x ] = 1;

						puted = true;
					}
				}

				//O型
				if( puted == false &&
					t == T_O )
				{
					if( block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y + 1 ][ x ] != 1 &&
						block[ y + 1 ][ x + 1 ] != 1 )
					{
						block[ y ][ x ] = 1;
						block[ y ][ x + 1 ] = 1;
						block[ y + 1 ][ x ] = 1;
						block[ y + 1 ][ x + 1 ] = 1;

						puted = true;
					}
				}

				//T型
				if( puted == false &&
					t == T_T &&
					d == UP )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x -1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 )
					{
						block[ y - 1 ][ x ] = 1;
						block[ y ][ x -1 ] = 1;
						block[ y ][ x ] = 1;
						block[ y ][ x + 1 ] = 1;

						puted = true;
					}
				}
				if( puted == false &&
					t == T_T &&
					d == RIGHT )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						block[ y - 1 ][ x ] = 1;
						block[ y ][ x ] = 1;
						block[ y ][ x + 1 ] = 1;
						block[ y + 1 ][ x ] = 1;

						puted = true;
					}
				}
				if( puted == false &&
					t == T_T &&
					d == DOWN )
				{
					if( block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						block[ y ][ x - 1 ] = 1;
						block[ y ][ x ] = 1;
						block[ y ][ x + 1 ] = 1;
						block[ y + 1 ][ x ] = 1;

						puted = true;
					}
				}
				if( puted == false &&
					t == T_T &&
					d == LEFT )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						block[ y - 1 ][ x ] = 1;
						block[ y ][ x - 1 ] = 1;
						block[ y ][ x ] = 1;
						block[ y + 1 ][ x ] = 1;

						puted = true;
					}
				}


				if( puted == true)
				{
					LimitTet[ t ] += 1;
					break;
				}
			}
		}
	}
	//全てのテトリミノの制限に+1
	for( int i = 0; i < 7; i ++ )
	{
		LimitTet[ i ] += 1;
	}
}

void Puzzle_Stady_Game( const int stage[ StageMax ][ BlockHei ][ BlockWid ], int block[ BlockHei ][ BlockWid ], int stocks[ StageMax ][ 7 ], int UsedTet[ 7 ], int LimitTet[ 7 ], struct tetrimino *tet,
	int *selection, int *StageNum, int *timer, int *cursorX, int *cursorY, int *choice, int *direction, int *EndTime, bool *menu, bool *timeUP, bool *clear, bool *fail )
{
	//ブロック配置
	if( *selection < 10 )
	{
		*StageNum = *selection;

		for( int i = 0; i < StageMax; i ++ )
		{
			if( *StageNum == i )
			{
				for( int j = 0; j < 7; j ++ )
				{
					LimitTet[ j ] = stocks[ i ][ j ];
				}

				for( int j = 0; j < BlockHei; j ++ )
				{
					for( int k = 0; k < BlockWid; k ++ )
					{
						block[ j ][ k ] = stage[ i ][ j ][ k ];
					}
				}
			}
		}
	}
	//オリジナルステージ
	else if( *selection == 10 )
	{
		FILE *fp;

		fp = fopen( "stage/stage.txt", "r" );
		if( fp == NULL )
		{
			exit( 1 );
		}
		for( int i = 0; i < BlockHei; i ++ )
		{
			fscanf( fp, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d" ,&block[ i ][ 0 ], &block[ i ][ 1 ], 
				&block[ i ][ 2 ], &block[ i ][ 3 ], &block[ i ][ 4 ], &block[ i ][ 5 ], &block[ i ][ 6 ], 
				&block[ i ][ 7 ], &block[ i ][ 8 ], &block[ i ][ 9 ], &block[ i ][ 10 ], &block[ i ][ 11 ] );
		}
		fclose( fp );

		fp = fopen( "stage/tetrimino.txt", "r" );
		if( fp == NULL )
		{
			exit( 1 );
		}
		fscanf( fp, "%d, %d, %d, %d, %d, %d, %d",
			&LimitTet[ 0 ], &LimitTet[ 1 ], &LimitTet[ 2 ], &LimitTet[ 3 ], &LimitTet[ 4 ], &LimitTet[ 5 ], &LimitTet[ 6 ] );
		fclose( fp );

		//テトリミノに余裕を
		for( int i = 0; i < 7; i ++ )
		{
			LimitTet[ i ] += 1;
		}
	}
	//ランダムステージ
	else if( *selection == 11 )
	{
		Random_Make_Stage( block, LimitTet );
	}



	for( int i = 0; i < TetriMax; i ++ )
	{
		tet->x[ i ] = -100;
		tet->y[ i ] = 1000;
	}

	for( int i = 0; i < 7; i ++ )
	{
		UsedTet[ i ] = 0;
	}

	Put_Cursor( block, cursorX, cursorY );

	*timer = 0;
	*selection = 0;
	*choice = 0;
	*direction = 0;

	*EndTime = -100;
	*menu = false;

	*timeUP = false;
	*clear = false;
	*fail = false;

	//曲再生
	MikanSound->Play( 1, true );
}

void Endless_Stady_Game( int block[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], struct tetrimino *tet, int *selection, int *choice, int *direction,
	int *timer,	int *cursorX, int *cursorY, int *EndTime, int *score, int *comboN, int *comboT, int *comboP, int *comboTime, bool *menu )
{
	//ブロックの初期化
	for( int i = 1; i < BlockHei - 1; i ++ )
	{
		for( int j = 1; j < BlockWid - 1; j ++ )
		{
			block[ i ][ j ] = 0;
		}
	}
	for( int i = 0; i < 7; i ++ )
	{
		UsedTet[ i ] = 0;
	}

	
	//カーソル配置
	*cursorX = *cursorY = -1;


	*timer = 0;
	*selection = 0;
	*choice = 0;
	*direction = 0;

	*EndTime = -100;
	*menu = false;

	*score = 0;
	*comboN = 0;
	*comboT = -1;
	*comboP = 0;
	*comboTime = 0;

	for( int i = 0; i < TetriMax; i ++ )
	{
		tet->x[ i ] = -100;
		tet->y[ i ] = 1000;
	}


	//曲再生
	MikanSound->Play( 0, true );
}

void Battle_Stady_Game( int block[ BlockHei ][ BlockWid ], int block2[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], struct tetrimino *tet, struct tetrimino *tet2, int *selection, int *selection2,
	int *choice, int *choice2,	int *timer,	int *cursorX, int *cursorX2, int *cursorY, int *cursorY2, int *EndTime, int *score, int *score2, int *direction, int *direction2,
	int *comboN2, int *comboN, int *comboT, int *comboT2, int *comboP, int *comboP2, int *comboTime, int *comboTime2, int *winner, bool *menu )
{
	//ブロックの初期化
	for( int i = 1; i < BlockHei - 1; i ++ )
	{
		for( int j = 1; j < BlockWid - 1; j ++ )
		{
			block[ i ][ j ] = 0;
			block2[ i ][ j ] = 0;
		}
	}
	for( int i = 0; i < 7; i ++ )
	{
		UsedTet[ i ] = 0;
	}


	*timer = 0;

	//カーソル配置
	*cursorX = *cursorY = -1;
	*cursorX2 = *cursorY2 = -1;
	*selection = 0;
	*selection2 = 0;
	*choice = 0;
	*choice2 = 0;
	*direction = 0;
	*direction2 = 0;

	*EndTime = -100;
	*menu = false;
	*winner = -1;

	*score = 0;
	*score2 = 0;
	*comboN = 0;
	*comboN2 = 0;
	*comboT = -1;
	*comboT2 = -1;
	*comboP = 0;
	*comboP2 = 0;
	*comboTime = 0;
	*comboTime2 = 0;

	for( int i = 0; i < TetriMax; i ++ )
	{
		tet->x[ i ] = -100;
		tet2->x[ i ] = -100;
		tet->y[ i ] = 1000;
		tet2->y[ i ] = 1000;
	}


	//曲再生
	MikanSound->Play( 0, true );
}

void Editor_Stady_Game( int block[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], struct tetrimino *tet,
	int *choice, int *selection, int *direction, int *x, int *y, bool *menu )
{
	for( int i = 1; i < BlockHei - 1; i ++ )
	{
		for( int j = 1; j < BlockWid - 1; j ++ )
		{
			block[ i ][ j ] = 0;
		}
	}

	for( int i = 0; i < TetriMax; i ++ )
	{
		tet->x[ i ] = -100;
		tet->y[ i ] = 1000;
	}

	for( int i = 0; i < 7; i ++ )
	{
		UsedTet[ i ] = 0;
	}

	//カーソル配置
	*x = 1;
	*y = BlockHei - 1;
	*choice = 0;
	*selection = 0;
	*direction = 0;

	*menu = false;


	//曲再生
	MikanSound->Play( 1, true );
}



//タイトル等=======================================================
//1,2Pのカーソルタイプの選択
void Chenge_CursorType( bool *cursorT, bool *cursorT2 )
{
	if( MikanInput->GetKeyNum( K_D ) == 1 ||
		MikanInput->GetPadNum( 0, PAD_G ) == 1 )
	{
		*cursorT = true;
		MikanSound->Play( 11, false );
	}
	if( MikanInput->GetKeyNum( K_C ) == 1  ||
		MikanInput->GetPadNum( 0, PAD_H ) == 1)
	{
		*cursorT = false;
		MikanSound->Play( 11, false );
	}

	if( MikanInput->GetKeyNum( K_D ) == 1 ||
		MikanInput->GetPadNum( 1, PAD_G ) == 1 )
	{
		*cursorT2 = true;
		MikanSound->Play( 11, false );
	}
	if( MikanInput->GetKeyNum( K_C ) == 1  ||
		MikanInput->GetPadNum( 1, PAD_H ) == 1)
	{
		*cursorT2 = false;
		MikanSound->Play( 11, false );
	}
}

void Move_Title( int *selection )
{
	if( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
		MikanInput->GetPadNum( 0, PAD_UP ) % 10 == 1 )
	{
		if( *selection > 0 )
		{
			*selection -= 1;
		}
		else
		{
			*selection = 5;
		}
		MikanSound->Play( 10, false );
	}
	if( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
		MikanInput->GetPadNum( 0, PAD_DOWN ) % 10 == 1 )
	{
		if( *selection < 5 )
		{
			*selection += 1;
		}
		else
		{
			*selection = 0;
		}
		MikanSound->Play( 10, false );
	}
	//例外処理
	if( *selection < 0 )
	{
		*selection = 0;
	}
	if( * selection > 5 )
	{
		*selection = 5;
	}

	//曲停止
	MikanSound->Stop( 0 );
	MikanSound->Stop( 1 );
}

void Choice_Title( int block[ BlockHei ][ BlockWid ], int block2[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], struct tetrimino *tet, struct tetrimino *tet2,
	int *mode, int *selection, int *selection2, int *choice, int *choice2, int *direction, int *direction2, int *timer, int *cursorX, int *cursorX2, int *cursorY, int *cursorY2,
	int *EndTime, int *score, int *score2, int *comboN, int *comboN2, int *comboT, int *comboT2, int *comboP, int *comboP2, int *comboTime, int *comboTime2, int *winner, bool *menu )
{
	//ステージセレクトの処理との兼ね合いで"== 3"にしておく。
	if( MikanInput->GetKeyNum( K_Z ) == 3 ||
		MikanInput->GetPadNum( 0, PAD_B ) == 3 )
	{
		if( *selection == 0 )
		{
			*mode = STAGE_SELECT;
		}
		else if( *selection == 1 )
		{
			*mode = ENDLESS_GAME;
			Endless_Stady_Game( block, UsedTet, tet, selection, choice, direction, timer, cursorX, cursorY, EndTime, score, comboN, comboT, comboP, comboTime, menu );
		}
		else if( *selection == 2 )
		{
			*mode = BATTLE_GAME;
			Battle_Stady_Game( block, block2, UsedTet, tet, tet2, selection, selection2, choice, choice2, timer,
				cursorX, cursorX2, cursorY, cursorY2, EndTime, score, score2, direction, direction2, comboN, comboN2, comboT, comboT2,
				comboP, comboP2, comboTime, comboTime2, winner, menu );
		}
		else if( *selection == 3 )
		{
			*mode = EDITOR;
			Editor_Stady_Game( block, UsedTet, tet, choice, selection, direction, cursorX, cursorY, menu );
		}
		else if( *selection == 4 )
		{
			*mode = EXPLANATION;
			*choice = 0;
		}
		else if( *selection == 5 )
		{
			*mode = -1;
		}

		*selection = 0;

		MikanSound->Play( 12, false );
	}
}

void Move_StageSelecte( int *selection )
{
	//上下移動
	if( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
		MikanInput->GetPadNum( 0, PAD_UP ) % 10 == 1 )
	{
		if( *selection == 10 )
		{
			*selection = 11;
		}
		else if( *selection == 11 )
		{
			*selection = 10;
		}
		else if( *selection > 0 &&
			*selection != 5 )
		{
			*selection -= 1;
		}
		else
		{
			*selection += 4;
		}
		MikanSound->Play( 10, false );
	}
	if( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
		MikanInput->GetPadNum( 0, PAD_DOWN ) % 10 == 1 )
	{
		if( *selection == 10 )
		{
			*selection = 11;
		}
		else if( *selection == 11 )
		{
			*selection = 10;
		}
		else if( *selection < StageMax + 2 - 1 &&
			*selection != 4 &&
			*selection != 9 )
		{
			*selection += 1;
		}
		else
		{
			*selection -= 4;
		}
		MikanSound->Play( 10, false );
	}

	//左右移動
	if( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
		MikanInput->GetPadNum( 0, PAD_RIGHT ) % 10 == 1 )
	{
		if( *selection < 5 )
		{
			*selection += 5;
		}
		else if( *selection >= 5 &&
			*selection < 8 )
		{
			*selection = 10;
		}
		else if( *selection >= 8 &&
			*selection < 10 )
		{
			*selection = 11;
		}
		else if( *selection == 10 )
		{
			*selection = 1;
		}
		else if( *selection == 11 )
		{
			*selection = 3;
		}
		MikanSound->Play( 10, false );
	}
	if( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
		MikanInput->GetPadNum( 0, PAD_LEFT ) % 10 == 1)
	{
		if( *selection < 3 )
		{
			*selection = 10;
		}
		else if( *selection >= 3 &&
			*selection < 5 )
		{
			*selection = 11;
		}
		else if( *selection >= 5 &&
			*selection < 10 )
		{
			*selection -= 5;
		}
		else if( *selection == 10 )
		{
			*selection = 6;
		}
		else if( *selection == 11 )
		{
			*selection = 8;
		}
		MikanSound->Play( 10, false );
	}

	//例外処理
	if( *selection < 0 )
	{
		*selection = 0;
	}
	if( * selection > StageMax + 2 - 1 )
	{
		*selection = StageMax + 2 - 1;
	}
}

void Choice_StageSelecte( const int stage[ StageMax ][ BlockHei ][ BlockWid ], int block[ BlockHei ][ BlockWid ], int stocks[ StageMax ][ 7 ], int UsedTet[ 7 ], int LimitTet [ 7 ], struct tetrimino *tet,
	int *mode, int *selection, int *timer, int *StageNum, int *cursorX, int *cursorY, int *choice, int *direction, int *EndTime, bool *menu, bool *timeUP, bool *clear, bool *fail )
{
	if( MikanInput->GetKeyNum( K_Z ) == 2 ||
		MikanInput->GetPadNum( 0, PAD_B ) == 2 )
	{
		*mode = PUZZLE_GAME;
		Puzzle_Stady_Game( stage, block, stocks, UsedTet, LimitTet, tet, selection, StageNum, timer, cursorX, cursorY, choice, direction, EndTime, menu, timeUP, clear, fail );
	
		MikanSound->Play( 12, false );
	}

	if( MikanInput->GetKeyNum( K_X ) == 1 ||
		MikanInput->GetPadNum( 0, PAD_C ) == 1 )
	{
		*selection = 0;
		*mode = TITLE;

		MikanSound->Play( 13, false );
	}
}

void Move_Explanation( int *mode, int *selection )
{
	if( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
		MikanInput->GetPadNum( 0, PAD_RIGHT ) % 10 == 1 )
	{
		if( *selection < 2 )
		{
			*selection += 1;
		}
		else
		{
			*selection = 0;
		}
		MikanSound->Play( 10, false );
	}
	if( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
		MikanInput->GetPadNum( 0, PAD_LEFT ) % 10 == 1 )
	{
		if( *selection > 0 )
		{
			*selection -= 1;
		}
		else
		{
			*selection = 2;
		}
		MikanSound->Play( 10, false );
	}
	//例外処理
	if( *selection < 0 )
	{
		*selection = 0;
	}
	if( *selection > 2 )
	{
		*selection = 2;
	}
	
	//Z,Xキーでタイトルに
	//　3==兼ね合い
	if( ( MikanInput->GetKeyNum( K_Z ) == 3 ||
		  MikanInput->GetPadNum( 0, PAD_B ) == 3 ) ||
		( MikanInput->GetKeyNum( K_X ) == 3 ||
		  MikanInput->GetPadNum( 0, PAD_C ) == 3 ) )
	{
		*mode = TITLE;
		MikanSound->Play( 13, false );
	}
}


//以下、ゲームモード=================================================
//選んだブロック達の上部が空いているか否かの判定関数
//true==上が空いている、false==空いていない
bool Puzzle_Blocks_Upper( int block[ BlockHei ][ BlockWid ] )
{
	for( int i = 0; i < BlockHei; i ++ )
	{
		for( int j = 0; j < BlockWid; j ++ )
		{
			if( block[ i ][ j ] == 2 )
			{
				for( int k = i; k > 0; k -- )
				{
					if( block[ k ][ j ] == 1 )//上のブロックが空でも選択中でも無かったら
					{
						return false;//false返す。
					}
				}
			}
		}
	}

	return true;
}

//選択中のブロックの1つ上が空いているか否か
bool Endless_Blocks_Upper( int block[ BlockHei ][ BlockWid ] )
{
	for( int i = 0; i < BlockHei; i ++ )
	{
		for( int j = 0; j < BlockWid; j ++ )
		{
			if( block[ i ][ j ] == 2 &&
				//1つ上が非選択のブロックならば
				block[ i - 1 ][ j ] == 1 )
			{
				return false;
			}
		}
	}

	return true;
}


//カーソルのテトリミノと向きの変更
void Silhouette_Cursor_Change( int PadNum, int *choice, int *direction )
{
	//Dキー（L1）で前のテトリミノに
	if( MikanInput->GetKeyNum( K_D ) % 10 == 1 ||
		MikanInput->GetPadNum( PadNum, PAD_G ) % 10 == 1 )
	{
		if( *choice > T_I )
		{
			*choice -= 1;
			MikanSound->Play( 11, false );
		}
		else if( *choice <= T_I )
		{
			*choice = T_T;
			MikanSound->Play( 11, false );
		}
	}
	//Cキー（R1）で次のテトリミノに
	else if( MikanInput->GetKeyNum( K_C ) % 10 == 1 ||
		MikanInput->GetPadNum( PadNum, PAD_H ) % 10 == 1 )
	{
		if( *choice < T_T )
		{
			*choice += 1;
			MikanSound->Play( 11, false );
		}
		else if( *choice >= T_T )
		{
			*choice = T_I;
			MikanSound->Play( 11, false );
		}
	}

	//Sキーが押されたら向きを変更する。
	if( MikanInput->GetKeyNum( K_X ) % 10 == 1 ||
		MikanInput->GetPadNum( PadNum, PAD_C ) % 10 == 1 )
	{
		if( *direction < LEFT )
		{
			*direction += 1;
			MikanSound->Play( 11, false );
		}
		else if( *direction >= LEFT )
		{
			*direction = UP;
			MikanSound->Play( 11, false );
		}
	}
}

//カーソルの移動関数
void Silhouette_Cursor_Move( int PadNum, int *x, int *y, int choice, int direction )
{
	//I型
	if( choice == T_I &&
		( direction == UP ||
		direction == DOWN ) )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
				MikanSound->Play( 10, false );
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 )
			{
				*y += 1;
				MikanSound->Play( 10, false );
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
				MikanSound->Play( 10, false );
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 2 )
			{
				*x += 1;
				MikanSound->Play( 10, false );
			}
		}

		if( *y < 1 )
		{
			*y = 1;
		}
		if( *y > BlockHei - 2 )
		{
			*y = BlockHei - 2;
		}
		if( *x < 1 + 1 )
		{
			*x = 1 + 1;
		}
		if( *x > BlockWid - 2 - 2 )
		{
			*x = BlockWid - 2 - 2;
		}
	}
	else if( choice == T_I &&
		( direction == RIGHT ||
		direction == LEFT ) )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 2 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 )
			{
				*x += 1;
			}
		}

		if( *y < 1 + 1 )
		{
			*y = 1 + 1;
		}
		if( *y > BlockHei - 2 - 2 )
		{
			*y = BlockHei - 2 - 2;
		}
		if( *x < 1 )
		{
			*x = 1;
		}
		if( *x > BlockWid - 2 )
		{
			*x = BlockWid - 2;
		}
	}

	//S型
	else if( choice == T_S &&
		( direction == UP ||
		direction == DOWN ) )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 )
		{
			*y = 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 + 1  )
		{
			*x = 1 + 1 ;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}
	else if( choice == T_S &&
		( direction == RIGHT ||
		direction == LEFT ) )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 + 1 )
		{
			*y = 1 + 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 )
		{
			*x = 1;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}

	//Z型
	else if( choice == T_Z &&
		( direction == UP ||
		direction == DOWN ) )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 )
		{
			*y = 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 + 1 )
		{
			*x = 1 + 1;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}
	else if( choice == T_Z &&
		( direction == RIGHT ||
		direction == LEFT ) )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 )
			{
				*x += 1;
			}
		}

		if( *y < 1 + 1 )
		{
			*y = 1 + 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 + 1 )
		{
			*x = 1 + 1;
		}
		if( *x > BlockWid - 2 )
		{
			*x = BlockWid - 2;
		}
	}

	//J型
	else if( choice == T_J &&
		direction == UP )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 + 1 )
		{
			*y = 1 + 1;
		}
		if( *y > BlockHei - 2 )
		{
			*y = BlockHei - 2;
		}
		if( *x < 1 + 1 )
		{
			*x = 1 + 1;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}
	else if( choice == T_J &&
		direction == RIGHT )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 + 1 )
		{
			*y = 1 + 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 )
		{
			*x = 1;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}
	else if( choice == T_J &&
		direction == DOWN )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 )
		{
			*y = 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 + 1 )
		{
			*x = 1 + 1;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}
	else if( choice == T_J &&
		direction == LEFT )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 )
			{
				*x += 1;
			}
		}

		if( *y < 1 + 1 )
		{
			*y = 1 + 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 + 1 )
		{
			*x = 1 + 1;
		}
		if( *x > BlockWid - 2 )
		{
			*x = BlockWid - 2;
		}
	}

	//L型
	else if( choice == T_L &&
		direction == UP )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 + 1 )
		{
			*y = 1 + 1;
		}
		if( *y > BlockHei - 2 )
		{
			*y = BlockHei - 2;
		}
		if( *x < 1 + 1 )
		{
			*x = 1 + 1;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}
	else if( choice == T_L &&
		direction == RIGHT )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 + 1 )
		{
			*y = 1 + 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 )
		{
			*x = 1;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}
	else if( choice == T_L &&
		direction == DOWN )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 )
		{
			*y = 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 + 1 )
		{
			*x = 1 + 1;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}
	else if( choice == T_L &&
		direction == LEFT )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 )
			{
				*x += 1;
			}
		}

		if( *y < 1 + 1 )
		{
			*y = 1 + 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 + 1 )
		{
			*x = 1 + 1;
		}
		if( *x > BlockWid - 2 )
		{
			*x = BlockWid - 2;
		}
	}

	//O型
	else if( choice == T_O )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 )
		{
			*y = 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 )
		{
			*x = 1;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}

	//T型
	else if( choice == T_T &&
		direction == UP )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 + 1 )
		{
			*y = 1 + 1;
		}
		if( *y > BlockHei - 2 )
		{
			*y = BlockHei - 2;
		}
		if( *x < 1 + 1 )
		{
			*x = 1 + 1;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}
	else if( choice == T_T &&
		direction == RIGHT )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 + 1 )
		{
			*y = 1 + 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 )
		{
			*x = 1;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}
	else if( choice == T_T &&
		direction == DOWN )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 - 1 )
			{
				*x += 1;
			}
		}

		if( *y < 1 )
		{
			*y = 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 + 1 )
		{
			*x = 1 + 1;
		}
		if( *x > BlockWid - 2 - 1 )
		{
			*x = BlockWid - 2 - 1;
		}
	}
	else if( choice == T_T &&
		direction == LEFT )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//上
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//下
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//左
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//右
			if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
				*x < BlockWid - 2 )
			{
				*x += 1;
			}
		}

		if( *y < 1 + 1 )
		{
			*y = 1 + 1;
		}
		if( *y > BlockHei - 2 - 1 )
		{
			*y = BlockHei - 2 - 1;
		}
		if( *x < 1 + 1 )
		{
			*x = 1 + 1;
		}
		if( *x > BlockWid - 2 )
		{
			*x = BlockWid - 2;
		}
	}
}

//テトリミノの生成、及び選択ブロックの消去
//テトリミノを実際に作れたらtrue
bool Silhouette_Make_Tetrimino( int PadNum, int block[ BlockHei ][ BlockWid ], int LimitTet[ 7 ], int UsedTet[ 7 ], int LastBlockX[ 4 ], int LastBlockY[ 4 ],
	struct tetrimino *tet, int choice, int direction, int timer, int x, int y, int StageNum, int mode )
{
	if( MikanInput->GetKeyNum( K_Z ) % 10 == 1 ||
		MikanInput->GetPadNum( PadNum, PAD_B ) % 10 == 1 )
	{
		//いずれかのテトリミノが当てはまったか否かの判定変数
		bool find = false;
		//選ばれたテトリミノの種類を記憶する。
		//実際に使われたテトリミノの個数を記録するために必要。
		int ChoicedTet;

		for( int i = 0; i < TetriMax; i ++)
		{
			if( tet->x[ i ] < 0 )//未使用の（＝tet.xがマイナスの）テトリミノを探す
			{
				//I型
				if( find == false &&
					choice == T_I &&
					( direction == UP ||
					  direction == DOWN ) &&
					UsedTet[ T_I ] < LimitTet[ T_I ] )
				{
					if( block[ y ][ x - 1 ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y ][ x + 1 ] == 1 &&
						block[ y ][ x + 2 ] == 1 )
					{
						tet->t[ i ] = T_I;
						tet->dir[ i ] = UP;
						
						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y ][ x + 2 ] = 2;

						ChoicedTet = T_I;
						find = true;
					}
				}
				if( find == false &&
					choice == T_I &&
					( direction == RIGHT ||
					direction == LEFT ) &&
					UsedTet[ T_I ] < LimitTet[ T_I ] )
				{
					if( block[ y - 1 ][ x ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y + 1 ][ x ] == 1 &&
						block[ y + 2 ][ x ] == 1 )
					{ 
						tet->t[ i ] = T_I;
						tet->dir[ i ] = RIGHT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x ] = 2;
						block[ y + 2 ][ x ] = 2;

						ChoicedTet = T_I;
						find = true;
					}
				}

				//S型
				if( find == false &&
					choice == T_S &&
					( direction == UP ||
					direction == DOWN ) &&
					UsedTet[ T_S ] < LimitTet[ T_S ] )
				{
					if( block[ y ][ x ] == 1 &&
						block[ y ][ x + 1 ] == 1 &&
						block[ y + 1 ][ x - 1 ] == 1 &&
						block[ y + 1 ][ x ] == 1 )
					{
						tet->t[ i ] = T_S;
						tet->dir[ i ] = UP;

						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y + 1 ][ x - 1 ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_S;
						find = true;
					}
				}
				if( find == false &&
					choice == T_S &&
					( direction == RIGHT ||
					  direction == LEFT ) &&
					UsedTet[ T_S ] < LimitTet[ T_S ] )
				{
					if( block[ y - 1 ][ x ] == 1 &&
						block[ y ][ x + 1 ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y + 1 ][ x + 1 ] == 1 )
					{
						tet->t[ i ] = T_S;
						tet->dir[ i ] = RIGHT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x + 1 ] = 2;

						ChoicedTet = T_S;
						find = true;
					}
				}

				//Z型
				if( find == false &&
					choice == T_Z &&
					( direction == UP ||
					direction == DOWN ) &&
					UsedTet[ T_Z ] < LimitTet[ T_Z ] )
				{
					if( block[ y ][ x ] == 1 &&
						block[ y ][ x - 1 ] == 1 &&
						block[ y + 1 ][ x ] == 1 &&
						block[ y + 1 ][ x + 1 ] == 1 )
					{
						tet->t[ i ] = T_Z;
						tet->dir[ i ] = UP;

						block[ y ][ x ] = 2;
						block[ y ][ x - 1 ] = 2;
						block[ y + 1 ][ x ] = 2;
						block[ y + 1 ][ x + 1 ] = 2;

						ChoicedTet = T_Z;
						find = true;
					}
				}
				if( find == false &&
					choice == T_Z &&
					( direction == RIGHT ||
					direction == LEFT ) )
				{
					if( block[ y - 1 ][ x ] == 1 &&
						block[ y ][ x - 1 ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y + 1 ][ x - 1 ] == 1 &&
					UsedTet[ T_Z ] < LimitTet[ T_Z ] )
					{
						tet->t[ i ] = T_Z;
						tet->dir[ i ] = RIGHT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x - 1 ] = 2;

						ChoicedTet = T_Z;
						find = true;
					}
				}

				//J型
				if( find == false &&
					choice == T_J &&
					direction == UP &&
					UsedTet[ T_J ] < LimitTet[ T_J ] )
				{
					if( block[ y - 1 ][ x - 1 ] == 1 &&
						block[ y ][ x - 1 ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y ][ x + 1 ] == 1 )
					{
						tet->t[ i ] = T_J;
						tet->dir[ i ] = UP;

						block[ y - 1 ][ x - 1 ] = 2;
						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;

						ChoicedTet = T_J;
						find = true;
					}
				}
				if( find == false &&
					choice == T_J &&
					direction == RIGHT &&
					UsedTet[ T_J ] < LimitTet[ T_J ] )
				{
					if( block[ y - 1 ][ x ] == 1 &&
						block[ y - 1 ][ x + 1 ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y + 1 ][ x ] == 1 )
					{
						tet->t[ i ] = T_J;
						tet->dir[ i ] = RIGHT;

						block[ y - 1 ][ x ] = 2;
						block[ y - 1 ][ x + 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_J;
						find = true;
					}
				}
				if( find == false &&
					choice == T_J &&
					direction == DOWN &&
					UsedTet[ T_J ] < LimitTet[ T_J ] )
				{
					if( block[ y ][ x - 1 ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y ][ x + 1 ] == 1 &&
						block[ y + 1 ][ x + 1 ] == 1 )
					{
						tet->t[ i ] = T_J;
						tet->dir[ i ] = DOWN;

						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y + 1 ][ x + 1 ] = 2;

						ChoicedTet = T_J;
						find = true;
					}
				}
				if( find == false &&
					choice == T_J &&
					direction == LEFT &&
					UsedTet[ T_J ] < LimitTet[ T_J ] )
				{
					if( block[ y - 1 ][ x ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y + 1 ][ x - 1 ] == 1 &&
						block[ y + 1 ][ x ] == 1 )
					{
						tet->t[ i ] = T_J;
						tet->dir[ i ] = LEFT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x - 1 ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_J;
						find = true;
					}
				}

				//L型
				if( find == false &&
					choice == T_L &&
					direction == UP &&
					UsedTet[ T_L ] < LimitTet[ T_L ] )
				{
					if( block[ y - 1 ][ x + 1 ] == 1 &&
						block[ y ][ x - 1 ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y ][ x + 1 ] == 1 )
					{
						tet->t[ i ] = T_L;
						tet->dir[ i ] = UP;

						block[ y - 1 ][ x + 1 ] = 2;
						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;

						ChoicedTet = T_L;
						find = true;
					}
				}
				if( find == false &&
					choice == T_L &&
					direction == RIGHT &&
					UsedTet[ T_L ] < LimitTet[ T_L ] )
				{
					if( block[ y - 1 ][ x ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y + 1 ][ x ] == 1 &&
						block[ y + 1 ][ x + 1 ] == 1 )
					{
						tet->t[ i ] = T_L;
						tet->dir[ i ] = RIGHT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x ] = 2;
						block[ y + 1 ][ x + 1 ] = 2;

						ChoicedTet = T_L;
						find = true;
					}
				}
				if( find == false &&
					choice == T_L &&
					direction == DOWN &&
					UsedTet[ T_L ] < LimitTet[ T_L ] )
				{
					if( block[ y ][ x - 1 ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y ][ x + 1 ] == 1 &&
						block[ y + 1 ][ x - 1 ] == 1 )
					{
						tet->t[ i ] = T_L;
						tet->dir[ i ] = DOWN;

						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y + 1 ][ x - 1 ] = 2;

						ChoicedTet = T_L;
						find = true;
					}
				}
				if( find == false &&
					choice == T_L &&
					direction == LEFT &&
					UsedTet[ T_L ] < LimitTet[ T_L ] )
				{
					if( block[ y - 1 ][ x - 1 ] == 1 &&
						block[ y - 1 ][ x ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y + 1 ][ x ] == 1 )
					{
						tet->t[ i ] = T_L;
						tet->dir[ i ] = LEFT;

						block[ y - 1 ][ x - 1 ] = 2;
						block[ y - 1 ][ x ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_L;
						find = true;
					}
				}

				//O型
				if( find == false &&
					choice == T_O &&
					UsedTet[ T_O ] < LimitTet[ T_O ] )
				{
					if( block[ y ][ x ] == 1 &&
						block[ y ][ x + 1 ] == 1 &&
						block[ y + 1 ][ x ] == 1 &&
						block[ y + 1 ][ x + 1 ] == 1 )
					{
						tet->t[ i ] = T_O;
						tet->dir[ i ] = UP;

						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y + 1 ][ x ] = 2;
						block[ y + 1 ][ x + 1 ] = 2;

						ChoicedTet = T_O;
						find = true;
					}
				}

				//T型
				if( find == false &&
					choice == T_T &&
					direction == UP &&
					UsedTet[ T_T ] < LimitTet[ T_T ] )
				{
					if( block[ y - 1 ][ x ] == 1 &&
						block[ y ][ x -1 ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y ][ x + 1 ] == 1 )
					{
						tet->t[ i ] = T_T;
						tet->dir[ i ] = UP;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x -1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;

						ChoicedTet = T_T;
						find = true;
					}
				}
				if( find == false &&
					choice == T_T &&
					direction == RIGHT &&
					UsedTet[ T_T ] < LimitTet[ T_T ] )
				{
					if( block[ y - 1 ][ x ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y ][ x + 1 ] == 1 &&
						block[ y + 1 ][ x ] == 1 )
					{
						tet->t[ i ] = T_T;
						tet->dir[ i ] = RIGHT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_T;
						find = true;
					}
				}
				if( find == false &&
					choice == T_T &&
					direction == DOWN &&
					UsedTet[ T_T ] < LimitTet[ T_T ] )
				{
					if( block[ y ][ x - 1 ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y ][ x + 1 ] == 1 &&
						block[ y + 1 ][ x ] == 1 )
					{
						tet->t[ i ] = T_T;
						tet->dir[ i ] = DOWN;

						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_T;
						find = true;
					}
				}
				if( find == false &&
					choice == T_T &&
					direction == LEFT &&
					UsedTet[ T_T ] < LimitTet[ T_T ] )
				{
					if( block[ y - 1 ][ x ] == 1 &&
						block[ y ][ x - 1 ] == 1 &&
						block[ y ][ x ] == 1 &&
						block[ y + 1 ][ x ] == 1 )
					{
						tet->t[ i ] = T_T;
						tet->dir[ i ] = LEFT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_T;
						find = true;
					}
				}


				//選択中のテトリミノに適したブロックの配置だった場合
				if( find == true )
				{
					//全ての"LastBlock"を未使用にする（場外に出す）。
					for( int k = 0; k < 4; k ++ )
					{
						LastBlockX[ k ] = -100;
						LastBlockY[ k ] = -100;
					}

					//上が空いていればテトリミノの生成＋ブロック消去
					if( ( mode == PUZZLE_GAME &&
						  Puzzle_Blocks_Upper( block ) == true ) ||
						( ( mode == ENDLESS_GAME ||
						    mode == BATTLE_GAME ) &&
						Endless_Blocks_Upper( block ) == true ) )
					{
						for( int j = 0; j < BlockHei; j ++ )
						{
							for( int k = 0; k < BlockWid; k ++ )
							{
								if( block[ j ][ k ] == 2 )
								{
									block[ j ][ k ] = 0;

									//最後に消したブロックの座標を未使用の（場外にある）"LastBlock"に記憶する。
									for( int l = 0; l < 4; l ++ )
									{
										if( LastBlockX[ l ] < 0 )
										{
											LastBlockX[ l ] = k;
											break;
										}
									}
									for( int l = 0; l < 4; l ++ )
									{
										if( LastBlockY[ l ] < 0 )
										{
											LastBlockY[ l ] = j;
											break;
										}
									}
								}
							}
						}

						tet->x[ i ] = x;
						tet->y[ i ] = y;

						tet->ori[ i ] = y;
						tet->time[ i ] = timer;

						//パズルモードでは使用したテトリミノを記録する。
						if( mode == PUZZLE_GAME )
						{
							UsedTet[ ChoicedTet ] += 1;
						}

						MikanSound->Play( 14, false );

						return true;

					}
					//空いていなければ失敗
					else
					{
						for( int j = 0; j < BlockHei; j ++ )
						{
							for( int k = 0; k < BlockWid; k ++ )
							{
								if( block[ j ][ k ] == 2 )
								{
									block[ j ][ k ] = 1;
								}
							}
						}
					}
				}
				break;
			}
		}
		MikanSound->Play( 15, false );
	}

	return false;
}


//カーソルの移動関数
bool Pointer_Cursor_Move( int PadNum, int block[ BlockHei ][ BlockWid ], int *x, int *y )
{
	//実際にカーソルが動いたか否かの判定 -> DidMove
	bool DidMove = false;

	//上
	if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
		*y > 1 )
	{
		*y -= 1;
		DidMove = true;
		MikanSound->Play( 10, false );
	}
	//下
	if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
		*y < BlockHei - 2 )
	{
		*y += 1;
		DidMove = true;
		MikanSound->Play( 10, false );
	}
	//左
	if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
		*x > 1 )
	{
		*x -= 1;
		DidMove = true;
		MikanSound->Play( 10, false );
	}
	//右
	if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
		*x < BlockWid - 2 )
	{
		*x += 1;
		DidMove = true;
		MikanSound->Play( 10, false );
	}

	//例外処理
	if( *y == 0 )
	{
		*y = 1;
	}
	if( *y == BlockHei )
	{
		*y = BlockHei - 1;
	}
	if( *x == 0 )
	{
		*x = 1;
	}
	if( *x == BlockWid - 1 )
	{
		*x = BlockWid - 2;
	}

	return DidMove;
}

//ブロック選択の解除
void Pointer_Remove_Choice( int block[ BlockHei ][ BlockWid ] )
{
	for( int i = 0; i < BlockHei; i ++ )
	{
		for( int j = 0; j < BlockWid; j ++ )
		{
			if( block[ i ][ j ] == 2 )
			{
				block[ i ][ j ] = 1;//選択解除
			}
		}
	}
}

//ブロックの選択・非選択の関数
void Pointer_Choice_Block( int PadNum, int block[ BlockHei ][ BlockWid ], int x, int y, int *choice, bool DidMove )
{
	//隣接する「選択中のブロック」の数を調べ、2つ以上ならば選択を解除できないようにする。
	int count = 0;

	if( block[ y - 1 ][ x ] == 2 )
	{
		count ++;
	}
	if( block[ y + 1 ][ x ] == 2 )
	{
		count ++;
	}
	if( block[ y ][ x - 1 ] == 2 )
	{
		count ++;
	}
	if( block[ y ][ x + 1 ] == 2 )
	{
		count ++;
	}

	if( MikanInput->GetKeyNum( K_Z ) == 1 ||	//Zキーが押されたか
		MikanInput->GetPadNum( PadNum, PAD_B ) == 1 ||
		DidMove == true )						//移動したタイミングで判定する。
	{
		if( MikanInput->GetKeyNum( K_Z ) > 0 ||	//Zキーが押されており、
			MikanInput->GetPadNum( PadNum, PAD_B ) > 0 )
		{
			if( block[ y ][ x ] == 1 &&			//非選択中のブロック上で
				( *choice <= 0 ||				//何処も選択していないか
				  block[ y - 1 ][ x ] == 2 ||		//選択中のブロックに隣接していたら
				  block[ y + 1 ][ x ] == 2 ||
				  block[ y ][ x - 1 ] == 2 ||
				  block[ y ][ x + 1 ] == 2 ) )
			{
				block[ y ][ x ] = 2;			//そのブロックを選択し、
				*choice += 1;					//選択数を増加させる。
				MikanSound->Play( 12, false );
			}
			else if( block[ y ][ x ] == 2 &&
				count <= 1 )					//それ以外で、選択中のブロックの上で
			{
				block[ y ][ x ] = 1;			//そのブロックの選択を解き、
				*choice -= 1;					//選択数を減少させる。
				MikanSound->Play( 13, false );
			}
		}
	}

	//Xキーが押された場合、全ての選択を解除する。
	if( MikanInput->GetKeyNum( K_X ) == 1 ||
		MikanInput->GetPadNum( PadNum, PAD_C ) == 1 )
	{
		*choice = 0;

		Pointer_Remove_Choice( block );
		MikanSound->Play( 13, false );
	}
}

//テトリミノの生成、及び選択ブロックの消去
bool Pointer_Make_Tetrimino( int block[ BlockHei ][ BlockWid ], int LimitTet[ 7 ], int UsedTet[ 7 ], int LastBlockX[ 4 ], int LastBlockY[ 4 ],
	struct tetrimino *tet, int *choice, int mode, int StageNum )
{
	//いずれかのテトリミノが当てはまったか否かの判定変数
	bool maked = false;

	if( *choice >= 4 )
	{
		*choice = 0;

		if( ( mode == PUZZLE_GAME &&
			  Puzzle_Blocks_Upper( block ) == true ) ||
			( ( mode == ENDLESS_GAME ||
				mode == BATTLE_GAME ) &&
			  Endless_Blocks_Upper( block ) == true ) )
		{
			for( int n = 0; n < TetriMax; n ++)
			{
				if( tet->x[ n ] < 0 )//未使用の（＝tet.xがマイナスの）テトリミノを探す
				{
					//I型
					if( maked == false  &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_I ] < LimitTet[ T_I ] ) )
					{
						for( int i = 0; i < BlockHei; i ++ )//横ver
						{
							for( int j = 1; j < BlockWid - 2; j ++ )
							{
								if( block[ i ][ j - 1 ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i ][ j + 1 ] == 2 &&
									block[ i ][ j + 2 ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_I;
									tet->dir[ n ] = UP;
									tet->ori[ n ] = i;

									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_I ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					if( maked == false  &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_I ] < LimitTet[ T_I ] ) )
					{
						for( int i = 1; i < BlockHei - 2; i ++ )//縦ver
						{
							for( int j = 0; j < BlockWid; j ++ )
							{
								if( block[ i - 1 ][ j ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i + 1 ][ j ] == 2 &&
									block[ i + 2 ][ j ] == 2 )
								{ 
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_I;
									tet->dir[ n ] = RIGHT;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_I ] += 1;
									}

									maked = true;
								}
							}
						}
					}

					//S型
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_S ] < LimitTet[ T_S ] ) )
					{
						for( int i = 0; i < BlockHei - 1; i ++ )//横ver
						{
							for( int j = 1; j < BlockWid - 1; j ++ )
							{
								if( block[ i ][ j ] == 2 &&
									block[ i ][ j + 1 ] == 2 &&
									block[ i + 1 ][ j - 1 ] == 2 &&
									block[ i + 1 ][ j ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_S;
									tet->dir[ n ] = UP;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_S ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_S ] < LimitTet[ T_S ] ) )
					{
						for( int i = 1; i < BlockHei - 1; i ++ )//縦ver
						{
							for( int j = 1; j < BlockWid; j ++ )
							{
								if( block[ i - 1 ][ j ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i ][ j + 1 ] == 2 &&
									block[ i + 1 ][ j + 1 ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_S;
									tet->dir[ n ] = RIGHT;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_S ] += 1;
									}

									maked = true;
								}
							}
						}
					}

					//Z型
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_Z ] < LimitTet[ T_Z ] ) )
					{
						for( int i = 0; i < BlockHei - 1; i ++ )//横ver
						{
							for( int j = 1; j < BlockWid - 1; j ++ )
							{
								if( block[ i ][ j - 1 ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i + 1 ][ j ] == 2 &&
									block[ i + 1 ][ j + 1 ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_Z;
									tet->dir[ n ] = UP;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_Z ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_Z ] < LimitTet[ T_Z ] ) )
					{
						for( int i = 1; i < BlockHei - 1; i ++ )//縦ver
						{
							for( int j = 0; j < BlockWid - 1; j ++ )
							{
								if( block[ i - 1 ][ j ] == 2 &&
									block[ i ][ j - 1 ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i + 1 ][ j - 1 ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_Z;
									tet->dir[ n ] = RIGHT;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_Z ] += 1;
									}

									maked = true;
								}
							}
						}
					}

					//J型
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_J ] < LimitTet[ T_J ] ) )
					{
						for( int i = 1; i < BlockHei; i ++ )//上ver
						{
							for( int j = 1; j < BlockWid - 1; j ++ )
							{
								if( block[ i - 1 ][ j - 1 ] == 2 &&
									block[ i ][ j - 1 ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i ][ j + 1 ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_J;
									tet->dir[ n ] = UP;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_J ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_J ] < LimitTet[ T_J ] ) )
					{
						for( int i = 1; i < BlockHei - 1; i ++ )//右ver
						{
							for( int j = 0; j < BlockWid - 1; j ++ )
							{
								if( block[ i - 1 ][ j ] == 2 &&
									block[ i - 1 ][ j + 1 ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i + 1 ][ j ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_J;
									tet->dir[ n ] = RIGHT;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_J ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_J ] < LimitTet[ T_J ] ) )
					{
						for( int i = 0; i < BlockHei - 1; i ++ )//下ver
						{
							for( int j = 1; j < BlockWid - 1; j ++ )
							{
								if( block[ i ][ j - 1 ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i ][ j + 1 ] == 2 &&
									block[ i + 1 ][ j + 1 ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_J;
									tet->dir[ n ] = DOWN;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_J ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_J ] < LimitTet[ T_J ] ) )
					{
						for( int i = 1; i < BlockHei - 1; i ++ )//左ver
						{
							for( int j = 1; j < BlockWid; j ++ )
							{
								if( block[ i - 1 ][ j ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i + 1 ][ j - 1 ] == 2 &&
									block[ i + 1 ][ j ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_J;
									tet->dir[ n ] = LEFT;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_J ] += 1;
									}

									maked = true;
								}
							}
						}
					}

					//L型
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_L ] < LimitTet[ T_L ] ) )
					{
						for( int i = 1; i < BlockHei; i ++ )//上ver
						{
							for( int j = 1; j < BlockWid - 1; j ++ )
							{
								if( block[ i - 1 ][ j + 1 ] == 2 &&
									block[ i ][ j - 1 ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i ][ j + 1 ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_L;
									tet->dir[ n ] = UP;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_L ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_L ] < LimitTet[ T_L ] ) )
					{
						for( int i = 1; i < BlockHei - 1; i ++ )//右ver
						{
							for( int j = 0; j < BlockWid - 1; j ++ )
							{
								if( block[ i - 1 ][ j ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i + 1 ][ j ] == 2 &&
									block[ i + 1 ][ j + 1 ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_L;
									tet->dir[ n ] = RIGHT;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_L ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_L ] < LimitTet[ T_L ] ) )
					{
						for( int i = 0; i < BlockHei - 1; i ++ )//下ver
						{
							for( int j = 1; j < BlockWid - 1; j ++ )
							{
								if( block[ i ][ j - 1 ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i ][ j + 1 ] == 2 &&
									block[ i + 1 ][ j - 1 ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_L;
									tet->dir[ n ] = DOWN;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_L ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_L ] < LimitTet[ T_L ] ) )
					{
						for( int i = 1; i < BlockHei - 1; i ++ )//左ver
						{
							for( int j = 1; j < BlockWid; j ++ )
							{
								if( block[ i - 1 ][ j - 1 ] == 2 &&
									block[ i - 1 ][ j ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i + 1 ][ j ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_L;
									tet->dir[ n ] = LEFT;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_L ] += 1;
									}

									maked = true;
								}
							}
						}
					}

					//O型
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_O ] < LimitTet[ T_O ] ) )
					{
						for( int i = 0; i < BlockHei - 1; i ++ )
						{
							for( int j = 0; j < BlockWid - 1; j ++ )
							{
								if( block[ i ][ j ] == 2 &&
									block[ i ][ j + 1 ] == 2 &&
									block[ i + 1 ][ j ] == 2 &&
									block[ i + 1 ][ j + 1 ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_O;
									tet->dir[ n ] = UP;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_O ] += 1;
									}

									maked = true;
								}
							}
						}
					}

					//T型
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_T ] < LimitTet[ T_T ] ) )
					{
						for( int i = 1; i < BlockHei; i ++ )//上ver
						{
							for( int j = 1; j < BlockWid - 1; j ++ )
							{
								if( block[ i - 1 ][ j ] == 2 &&
									block[ i ][ j -1 ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i ][ j + 1 ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_T;
									tet->dir[ n ] = UP;
									tet->ori[ n ] = i;
									
									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_T ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_T ] < LimitTet[ T_T ] ) )
					{
						for( int i = 1; i < BlockHei - 1; i ++ )//右ver
						{
							for( int j = 0; j < BlockWid - 1; j ++ )
							{
								if( block[ i - 1 ][ j ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i ][ j + 1 ] == 2 &&
									block[ i + 1 ][ j ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_T;
									tet->dir[ n ] = RIGHT;
									tet->ori[ n ] = i;

									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_T ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_T ] < LimitTet[ T_T ] ) )
					{
						for( int i = 0; i < BlockHei - 1; i ++ )//下ver
						{
							for( int j = 1; j < BlockWid - 1; j ++ )
							{
								if( block[ i ][ j - 1 ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i ][ j + 1 ] == 2 &&
									block[ i + 1 ][ j ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_T;
									tet->dir[ n ] = DOWN;
									tet->ori[ n ] = i;

									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_T ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_T ] < LimitTet[ T_T ] ) )
					{
						for( int i = 1; i < BlockHei - 1; i ++ )//左ver
						{
							for( int j = 1; j < BlockWid; j ++ )
							{
								if( block[ i - 1 ][ j ] == 2 &&
									block[ i ][ j - 1 ] == 2 &&
									block[ i ][ j ] == 2 &&
									block[ i + 1 ][ j ] == 2 )
								{
									tet->x[ n ] = j;
									tet->y[ n ] = i;

									tet->t[ n ] = T_T;
									tet->dir[ n ] = LEFT;
									tet->ori[ n ] = i;

									if( mode == PUZZLE_GAME )
									{
										UsedTet[ T_T ] += 1;
									}

									maked = true;
								}
							}
						}
					}
					break;
				}
			}

			if( maked == true )
			{
				//全ての"LastBlock"を未使用にする（場外に出す）。
				for( int k = 0; k < 4; k ++ )
				{
					LastBlockX[ k ] = -100;
					LastBlockY[ k ] = -100;
				}

				for( int i = 0; i < BlockHei; i ++ )
				{
					for( int j = 0; j < BlockWid; j ++ )
					{
						if( block[ i ][ j ] == 2 )
						{
							//選択中のブロックを消去する。
							block[ i ][ j ] = 0;

							//最後に消したブロックの座標を未使用の（場外にある）"LastBlock"に記憶する。
							for( int k = 0; k < 4; k ++ )
							{
								if( LastBlockX[ k ] < 0 )
								{
									LastBlockX[ k ] = j;
									break;
								}
							}
							for( int k = 0; k < 4; k ++ )
							{
								if( LastBlockY[ k ] < 0 )
								{
									LastBlockY[ k ] = i;
									break;
								}
							}

							MikanSound->Play( 14, false );
						}
					}
				}
			}
			//選択が不正であった場合には選択解除
			else
			{
				for( int i = 0; i < BlockHei; i ++ )
				{
					for( int j = 0; j < BlockWid; j ++ )
					{
						if( block[ i ][ j ] == 2 )
						{
							block[ i ][ j ] = 1;
						}
					}
				}
				MikanSound->Play( 15, false );
			}
		}
		else
		{
			Pointer_Remove_Choice( block );
			MikanSound->Play( 13, false );
		}
	}

	return maked;
}



//以下、パズルモード-------------------------------------------------
//テトリミノの移動
void Puzzle_Move_Tetrimino( struct tetrimino *tet, int timer )
{
	for( int i = 0; i < TetriMax; i ++ )
	{
		if( ( timer - tet->time[ i ] ) % 5 == 0 &&
			tet->y[ i ] >= -ChipSize &&
			tet->x[ i ] > 0 )
		{
			tet->y[ i ] --;
		}
	}
};

//制限時間制御関数
void Puzzle_TimeUP( int timer, int *EndTime, bool *timeUP )
{
	if( timer / 60 > LimitTime )
	{
		*EndTime = timer;
		*timeUP = true;
	}
}

//テトリミノを戻す「一手戻す」関数
void Puzzle_Return_Tetrimino( int block[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], int LastBlockX[ 4 ], int LastBlockY[ 4 ], struct tetrimino *tet, int *choice, bool cursorT )
{
	//連続で戻せないようにする。（最大連続1回）
	if( LastBlockX[ 0 ] > 0 )
	{
		//ブロックを復元するし、LastBlockX,Yを使用済み状態にする。
		for( int i = 0; i < 4; i ++ )
		{
			block[ LastBlockY[ i ] ][ LastBlockX[ i ] ] = 1;

			LastBlockX[ i ] = -100;
			LastBlockY[ i ] = -100;
		}
		for( int i = TetriMax - 1; i >= 0; i -- )
		{
			if( tet->x[ i ] >= 0 )
			{
				//直前に作られてたテトリミノを場外に出し、未使用状態に。
				tet->x[ i ] = -100;
				tet->y[ i ] = 1000;

				//テトリミノの使用回数を-1する。
				UsedTet[ tet->t[ i ] ] -= 1;

				break;
			}
		}
	}

	//カーソルがポインタタイプのための処理->選択を解除させる
	if( cursorT == false )
	{
		*choice = 0;
		for( int i = 1; i < BlockHei - 1; i ++ )
		{
			for( int j = 1; j < BlockWid - 1; j ++ )
			{
				if( block[ i ][ j ] == 2 )
				{
					block[ i ][ j ] = 1;
				}
			}
		}
	}
}

//メニュー画面での処理関数
void Puzzle_Menu( int PadNum, int block[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], int LastBlockX[ 4 ], int LastBlockY[ 4 ],
	struct tetrimino *tet, int *mode, int *selection, int *choice, bool *menu, bool cursorT )
{
	//Aキーでメニュー画面へ
	if( ( MikanInput->GetKeyNum( K_A ) == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_A ) == 1 ) &&
		  *menu == false )
	{
		*menu = true;
		MikanSound->Play( 12, false );
	}

	if( *menu == true )
	{
		//移動処理
		if( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
			MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1)
		{
			if( *selection > 0 )
			{
				*selection -= 1;
			}
			else
			{
				*selection = 2;
			}
			MikanSound->Play( 10, false );
		}
		if( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
			MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 )
		{
			if( *selection < 2 )
			{
				*selection += 1;
			}
			else
			{
				*selection = 0;
			}
			MikanSound->Play( 10, false );
		}

		//選択処理
		//タイトルの処理との兼ね合いで"== 3"にしておく。
		if( MikanInput->GetKeyNum( K_Z ) == 3 ||
			MikanInput->GetPadNum( PadNum, PAD_B ) == 3 )
		{
			if( *selection == 0 )
			{
				//特に無し
			}
			if( *selection == 1 )
			{
				Puzzle_Return_Tetrimino( block, UsedTet, LastBlockX, LastBlockY, tet, choice, cursorT );
			}
			if( *selection == 2 )
			{
				*mode = TITLE;
			}

			*selection = 0;
			*menu = false;

			MikanSound->Play( 12, false );
		}
		if( MikanInput->GetKeyNum( K_X ) == 1 ||
			MikanInput->GetPadNum( PadNum, PAD_C ) == 1 )
		{
			*selection = 0;
			*menu = false;

			MikanSound->Play( 13, false );
		}
	}
}

//「詰み」やクリアの判定
void Puzzle_Check_End( int block[ BlockHei ][ BlockWid ], bool *fail, bool *clear, int timer, int *EndTime )
{
	//「詰み」判定
	//連続数の記録
	int count;
	for( int i = 1; i < BlockHei - 1; i ++ )
	{
		for( int j = 1; j < BlockWid; j ++ )
		{
			count = 0;
			//カウント処理
			if( block[ i ][ j ] == 1 )
			{
				count += 1;

				//上
				if( block[ i - 1 ][ j ] == 1 )
				{
					count += 1;

					//上右
					if( block[ i - 1 ][ j + 1 ] == 1 )
					{
						count += 1;

						//上右右
						if( block[ i - 1 ][ j + 1 + 1 ] == 1 )
						{
							count += 1;
						}
						//上右上
						if( block[ i - 1 - 1 ][ j + 1 ] == 1 )
						{
							count += 1;
						}
					}
					//上上
					if( block[ i - 1 - 1 ][ j ] == 1 )
					{
						count += 1;

						//上上右
						if( block[ i - 1 - 1 ][ j + 1 ] == 1 )
						{
							count += 1;
						}
						//上上上
						if( block[ i - 1 - 1 - 1 ][ j ] == 1 )
						{
							count += 1;
						}
						//上上左
						if( block[ i - 1 - 1 ][ j - 1 ] == 1 )
						{
							count += 1;
						}
					}
					//上左
					if( block[ i - 1 ][ j - 1 ] == 1 )
					{
						count += 1;

						//上左上
						if( block[ i - 1 - 1 ][ j - 1 ] == 1 )
						{
							count += 1;
						}
						//上左左
						if( block[ i - 1 ][ j - 1 - 1 ] == 1 )
						{
							count += 1;
						}
					}
				}
				//右
				if( block[ i ][ j + 1 ] == 1 )
				{
					count += 1;

					//右上
					if( block[ i - 1 ][ j + 1 ] == 1 )
					{
						count += 1;

						//右上上
						if( block[ i - 1 - 1 ][ j + 1 ] == 1 )
						{
							count += 1;
						}
						//右上右
						if( block[ i - 1 ][ j + 1 + 1 ] == 1 )
						{
							count += 1;
						}
					}
					//右右
					if( block[ i ][ j + 1 + 1 ] == 1 )
					{
						count += 1;

						//右右上
						if( block[ i - 1 ][ j + 1 + 1 ] == 1 )
						{
							count += 1;
						}
						//右右右
						if( block[ i ][ j + 1 + 1 + 1 ] == 1 )
						{
							count += 1;
						}
						//右右下
						if( block[ i + 1 ][ j + 1 + 1 ] == 1 )
						{
							count += 1;
						}
					}
					//右下
					if( block[ i + 1 ][ j + 1 ] == 1 )
					{
						count += 1;

						//右下右
						if( block[ i + 1 ][ j + 1 + 1 ] == 1 )
						{
							count += 1;
						}
						//右下下
						if( block[ i + 1 + 1 ][ j + 1 ] == 1 )
						{
							count += 1;
						}
					}
				}
				//下
				if( block[ i + 1 ][ j ] == 1 )
				{
					count += 1;

					//下下
					if( block[ i + 1 + 1 ][ j ] == 1 )
					{
						count += 1;

						//下下右
						if( block[ i + 1 + 1 ][ j + 1 ] == 1 )
						{
							count += 1;
						}
						//下下下
						if( block[ i + 1 + 1 + 1 ][ j ] == 1 )
						{
							count += 1;
						}
						//下下左
						if( block[ i + 1 + 1 ][ j - 1 ] == 1 )
						{
							count += 1;
						}
					}
					//下右
					if( block[ i + 1 ][ j + 1 ] == 1 )
					{
						count += 1;

						//下右下
						if( block[ i + 1 + 1 ][ j + 1 ] == 1 )
						{
							count += 1;
						}
						//下右右
						if( block[ i + 1 ][ j + 1 + 1 ] == 1 )
						{
							count += 1;
						}
					}
					//下左
					if( block[ i + 1 ][ j - 1 ] == 1 )
					{
						count += 1;

						//下左下
						if( block[ i + 1 + 1 ][ j - 1 ] == 1 )
						{
							count += 1;
						}
						//下左左
						if( block[ i + 1 ][ j - 1 - 1 ] == 1 )
						{
							count += 1;
						}
					}
				}
				//左
				if( block[ i ][ j - 1 ] == 1 )
				{
					count += 1;

					//左上
					if( block[ i - 1 ][ j - 1 ] == 1 )
					{
						count += 1;

						//左上上
						if( block[ i - 1 - 1 ][ j - 1 ] == 1 )
						{
							count += 1;
						}
						//左上左
						if( block[ i - 1 ][ j - 1 - 1 ] == 1 )
						{
							count += 1;
						}
					}
					//左下
					if( block[ i + 1 ][ j - 1 ] == 1 )
					{
						count += 1;

						//左下下
						if( block[ i + 1 + 1 ][ j - 1 ] == 1 )
						{
							count += 1;
						}
						//左下左
						if( block[ i + 1 ][ j - 1 - 1 ] == 1 )
						{
							count += 1;
						}
					}
					//左左
					if( block[ i ][ j - 1 - 1 ] == 1 )
					{
						count += 1;

						//左左上
						if( block[ i - 1 ][ j - 1 - 1 ] == 1 )
						{
							count += 1;
						}
						//左左下
						if( block[ i + 1 ][ j - 1 - 1 ] == 1 )
						{
							count += 1;
						}
						//左左左
						if( block[ i ][ j - 1 - 1 - 1 ] == 1 )
						{
							count += 1;
						}
					}
				}

				if( count < 4 )
				{
					*fail = true;
					*EndTime = timer;
				}
			}
		}
	}


	//クリアしたかの判定
	bool DidClear = true;
	for( int i = 1; i < BlockHei - 1; i ++ )
	{
		for( int j = 1; j < BlockWid; j ++ )
		{
			if( block[ i ][ j ] == 1 )
			{
				DidClear = false;
			}
		}
	}
	if( DidClear == true )
	{
		*clear = true;
		*EndTime = timer;
	}
}

//ゲーム終了時の処理
void Puzzle_GameOver( int PadNum, struct tetrimino *tet, int *mode, int timer, int EndTime, bool clear, bool *menu )
{
	if( timer == EndTime + 1 )
	{
		if( clear == true )
		{
			MikanSound->Play( 16, false );
		}
		else
		{
			MikanSound->Play( 17, false );
		}
		//曲停止
		MikanSound->Stop( 0 );
		MikanSound->Stop( 1 );
	}

	if( clear == true )
	{
		if( timer % 10 == 0 )
		{
			for( int i = TetriMax - 1; i >= 0; i -- )
			{
				if( tet->x[ i ] >= 0 &&
					tet->y[ i ] <= 0 )
				{
					tet->y[ i ] = 1;
					break;
				}
			}
		}
		for( int i = TetriMax - 1; i >= 0; i -- )
		{
			if( tet->x[ i ] >= 0 &&
				tet->y[ i ] >= 0 &&
				tet->y[ i ] < tet->ori[ i ] )
			{
				tet->y[ i ] += 1;
			}
		}
	}

	if( timer - EndTime >= 250 &&
		( MikanInput->GetKeyNum( K_X ) == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_C ) == 1 ) )
	{
		*mode = TITLE;
		//*mode = -1;
		MikanSound->Play( 12, false );
	}

	//クリア後250フレームで背景を描画する。
	if( timer - EndTime == 250 )
	{
		*menu = true;
	}

	//タイトルへ
	if( timer - EndTime >= 250 &&
		( MikanInput->GetKeyNum( K_Z ) == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_B ) ) )
	{
		if( *menu == false )
		{
			*menu = true;
		}
		else
		{
			*menu = false;
		}
		MikanSound->Play( 11, false );
	}
}



//以下、エンドレスモード---------------------------------------------
//テトリミノの移動、及び停止
void Endless_Move_Tetrimino( int block[ BlockHei ][ BlockWid ], struct tetrimino *tet, int timer )
{
	//探索が完了したか否か
	bool find;

	for( int i = 0; i < TetriMax; i ++ )
	{
		if( ( timer - tet->time[ i ] ) % 5 == 0 &&
			tet->y[ i ] >= -2 &&
			tet->x[ i ] > 0  )
		{
			find = false;

			//画面上部に来ていない状態ならば
			if( tet->y[ i ] > 1 )
			{
				//I型
				if( find == false &&
					tet->t[ i ] == T_I &&
					( tet->dir[ i ] == UP ||
					tet->dir[ i ] == DOWN ) &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 2 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 2 ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_I &&
					( tet->dir[ i ] == RIGHT ||
					tet->dir[ i ] == LEFT ) &&
					//以上の条件のテトリミノの時、上がブロックならば
					block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 2 ][ tet->x[ i ]  ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				//S型
				if( find == false &&
					tet->t[ i ] == T_S &&
					( tet->dir[ i ] == UP ||
					tet->dir[ i ] == DOWN ) &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ||
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_S &&
					( tet->dir[ i ] == RIGHT ||
					tet->dir[ i ] == LEFT ) &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] + 1 ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				//Z型
				if( find == false &&
					tet->t[ i ] == T_Z &&
					( tet->dir[ i ] == UP ||
					tet->dir[ i ] == DOWN ) &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] + 1 ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_Z &&
					( tet->dir[ i ] == RIGHT ||
					tet->dir[ i ] == LEFT ) &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] - 1 ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				//J型
				if( find == false &&
					tet->t[ i ] == T_J &&
					tet->dir[ i ] == UP &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_J &&
					tet->dir[ i ] == RIGHT &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 2 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_J &&
					tet->dir[ i ] == DOWN &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] + 1 ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_J &&
					tet->dir[ i ] == LEFT &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				//L型
				if( find == false &&
					tet->t[ i ] == T_L &&
					tet->dir[ i ] == UP &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] + 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_L &&
					tet->dir[ i ] == RIGHT &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] + 1 ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_L &&
					tet->dir[ i ] == DOWN &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] - 1 ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_L &&
					tet->dir[ i ] == LEFT &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				//O型
				if( find == false &&
					tet->t[ i ] == T_O &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] + 1 ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				//T型
				if( find == false &&
					tet->t[ i ] == T_T &&
					tet->dir[ i ] == UP &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_T &&
					tet->dir[ i ] == RIGHT &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_T &&
					tet->dir[ i ] == DOWN &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_T &&
					tet->dir[ i ] == LEFT &&
					//以上の条件のテトリミノの時、上がブロックならば
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ) )
				{
					//テトリミノのマスにブロックを配置して
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//該当するテトリミノを未使用にする（場外へ）
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
			}


			//上記以外ならば上へ移動させる
			if( find == false )
			{
				tet->y[ i ] --;
			}
		}
	}
};

//せり出すブロックの生成
void Endless_Make_Blocks( int block[ BlockHei ][ BlockWid ] )
{
	for( int i = 1; i < BlockWid - 1; i ++ )
	{
		if( rand()  % 10 < 2 )
		{
			block[ BlockHei - 2 ][ i ] = 0;
		}
		else
		{
			block[ BlockHei - 2 ][ i ] = 1;
		}
	}
}
//ブロックのスライド
//生成できたらtrue
bool Endless_Slide_Blocks( int block[ BlockHei ][ BlockWid ], int *cursorY )
{
	for( int i = 1; i < BlockHei - 1; i ++ )
	{
		for( int j = 1; j < BlockWid - 1; j ++ )
		{
			//最上部までブロックが詰まっていないことを確認する
			if( i == 1 &&
				block[ i ][ j ] >= 1 )
			{
				return false;
			}

			block[ i - 1 ][ j ] = block[ i ][ j ];
		}
	}
	Endless_Make_Blocks( block );
	*cursorY -= 1;

	MikanSound->Play( 20, false );
	return true;
}
//エンドレスモードでのブロックの挙動、及びカーソル配置やブロックに合わせた動き。+終了判定
void Endless_Move_Blocks( int PadNum, int block[ BlockHei ][ BlockWid ], int timer, int *SlideTime, int *EndTime,
	int *cursorX, int *cursorY, int *score, int *winner )
{
	//ゲーム中にSキーでスライド
	if( ( MikanInput->GetKeyNum( K_S ) == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_D ) == 1 ) &&
		timer >= StartTime &&
		*EndTime < 0 )
	{
		if( Endless_Slide_Blocks( block, cursorY ) == true )
		{
			*score += 300;
		}
	}

	//開始前に下から10段のブロックをせり出させる。
	//1分== "timer / 60 / 60"
	if( timer >= 10 &&
		timer < StartTime &&
		timer % 5 == 0 )
	{
		Endless_Slide_Blocks( block, cursorY );
	}
	//カーソルの配置
	else if( timer == StartTime )
	{
		Put_Cursor( block, cursorX, cursorY );
		*SlideTime = 0;

		MikanSound->Play( 18, false );
	}

	else if( timer > StartTime &&
		( timer - StartTime ) / 60 / 20 < 10 &&
		( timer - *SlideTime ) / 60 > 10 - ( timer - StartTime ) / 60 / 20 )
	{
		if( Endless_Slide_Blocks( block, cursorY ) == false )
		{
			*EndTime = timer;
		
			if( PadNum == 0 )
			{
				*winner = 2;;
			}
			else
			{
				//両方とも敗者->引き分け
				if( *winner == 2 )
				{
					*winner = 0;
				}
				else
				{
					*winner = 1;
				}
			}
		}
		else
		{
			*SlideTime = timer;
		}
	}

	else if( ( timer - StartTime ) / 60 / 20 >= 10 &&
		( timer - StartTime ) % 60 == 0 &&
		  Endless_Slide_Blocks( block, cursorY ) == false )
	{
		*EndTime = timer;

		if( PadNum == 0 )
		{
			*winner = 2;;
		}
		else
		{
			//両方とも敗者->引き分け
			if( *winner == 2 )
			{
				*winner = 0;
			}
			else
			{
				*winner = 1;
			}
		}
	}
}

//スコアの処理、及びテトリミノの消去
void Endless_Count_Score( struct tetrimino *tet, int *score, int *comboN, int *comboT, int *comboP, int *comboTime, int timer )
{
	int addscore = 0;

	for( int i = 0; i < TetriMax; i ++ )
	{
		if( tet->x[ i ] >= 0 &&
			tet->y[ i ] < -1 )
		{
			//基本得点:I&O=50,J&L&T=100,S&Z=150点
			if( tet->t[ i ] == T_I ||
				tet->t[ i ] == T_O )
			{
				addscore = 1;
			}
			else if( tet->t[ i ] == T_T )
			{
				addscore = 2;
			}
			else if( tet->t[ i ] == T_J ||
				tet->t[ i ] == T_L )
			{
				addscore = 3;
			}
			else if( tet->t[ i ] == T_S ||
				tet->t[ i ] == T_Z )
			{
				addscore = 4;
			}

			//連続の記録
			//コンボが途切れた場合
			if( tet->t[ i ] != *comboT )
			{
				*comboN = 0;
				*comboT = tet->t[ i ];

				*score += *comboP;
				*comboP = 0;
			}
			*comboTime = timer;
			*comboN += 1;

			//連続消去でボーナスN*N/2点
			*comboP += 10 * ( addscore * *comboN * *comboN + addscore * *comboN * 3 ) / 4;

			//テトリミノの初期化
			tet->x[ i ] = -100;
			tet->y[ i ] = 1000;
		}
	}

	//コンボ時間が切れた場合
	if( timer - *comboTime > ChainTime )
	{
		*score += *comboP;
		*comboP = 0;

		*comboN = 0;
		*comboT = -1;
	}
}

//メニュー画面での処理関数
void Endless_Menu( int PadNum, int *mode, int *selection, bool *menu )
{
	//Aキーでメニュー画面へ
	if( ( MikanInput->GetKeyNum( K_A ) == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_A ) == 1 ) &&
		  *menu == false )
	{
		*menu = true;
		MikanSound->Play( 12, false );
	}

	if( *menu == true )
	{
		//移動処理
		if( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
			MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 )
		{
			if( *selection > 0 )
			{
				*selection -= 1;
			}
			else
			{
				*selection = 1;
			}
			MikanSound->Play( 10, false );
		}
		if( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
			MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 )
		{
			if( *selection < 1 )
			{
				*selection += 1;
			}
			else
			{
				*selection = 0;
			}
			MikanSound->Play( 10, false );
		}

		//選択処理
		//タイトルの処理との兼ね合いで"== 3"にしておく。
		if( MikanInput->GetKeyNum( K_Z ) == 3 ||
			MikanInput->GetPadNum( PadNum, PAD_B ) == 3 )
		{
			if( *selection == 0 )
			{
				//特に無し
			}
			if( *selection == 1 )
			{
				*mode = TITLE;
			}

			*selection = 0;
			*menu = false;

			MikanSound->Play( 12, false );
		}
		if( MikanInput->GetKeyNum( K_X ) == 1 ||
			MikanInput->GetPadNum( PadNum, PAD_C ) == 1 )
		{
			*selection = 0;
			*menu = false;

			MikanSound->Play( 13, false );
		}
	}
}

//ゲーム終了後の処理
void Endless_GameOver( int PadNum, int *mode, int *score, int *comboP, int *comboTime, int timer, int EndTime, bool *menu )
{
	if( timer == EndTime + 1 )
	{
		*score += *comboP;
		*comboP = 0;
		*comboTime = 0;

		MikanSound->Play( 19, false );
		//曲停止
		MikanSound->Stop( 0 );
		MikanSound->Stop( 1 );
	}

	if( timer - EndTime >= 100 &&
		( MikanInput->GetKeyNum( K_X ) == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_C ) == 1 ) )
	{
		*mode = TITLE;
		//*mode = -1;
		MikanSound->Play( 12, false );
	}

	//クリア後250フレームで背景を描画する。
	if( timer - EndTime == 100 &&
		PadNum == 0 )
	{
		*menu = true;
	}
	if( timer - EndTime >= 100 &&
		( MikanInput->GetKeyNum( K_Z ) == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_B ) == 1 ) )
	{
		if( !( MikanInput->GetKeyNum( K_Z ) == 1 &&
			PadNum == 1 ) )
		{
			if( *menu == false )
			{
				*menu = true;
			}
			else
			{
				*menu = false;
			}
			MikanSound->Play( 12, false );
		}
	}
}

//ハイスコアの更新
void Update_HighScore( bool endless, int *score, int *HighScore, int timer, int EndTime )
{
	int AnotherScore;

	//処理の兼ね合いで+2
	if( EndTime + 2 == timer )
	{
		FILE *fp;

		fp = fopen( "stage/score.txt", "r" );
		if( fp == NULL )
		{
			exit( 1 );
		}

		if( endless == true )
		{
			fscanf( fp, "%d, %d", HighScore, &AnotherScore );
		}
		else
		{
			fscanf( fp, "%d, %d", &AnotherScore, HighScore );
		}

		fclose( fp );


		if( *score > *HighScore )
		{
			*HighScore = *score;

			fp = fopen( "stage/score.txt", "w" );
			if( fp == NULL )
			{
				exit( 1 );
			}

			if( endless == true )
			{
				fprintf( fp, "%d, %d", *HighScore, AnotherScore );
			}
			else
			{
				fprintf( fp, "%d, %d", AnotherScore, *HighScore );
			}

			fclose( fp );
		}
	}
}



//以下、バトルモード---------------------------------------------
//コンボスコアに応じて相手のブロックを押し上げる
void Battle_Attack( int block2[ BlockHei ][ BlockWid ], int *cursorY2, int comboP )
{
	for( int i = 0; i < comboP / 1000; i ++ )
	{
		Endless_Slide_Blocks( block2, cursorY2 );
	}
}

//スコアの処理
void Battle_Count_Score( struct tetrimino *tet, int *score, int *comboN, int *comboT, int *comboP, int *comboTime, int timer,
	int block2[ BlockHei ][ BlockWid ], int *cursorY2 )
	//block2,cursorY2はそれぞれ相手のものを入れる
{
	int addscore = 0;

	for( int i = 0; i < TetriMax; i ++ )
	{
		if( tet->x[ i ] >= 0 &&
			tet->y[ i ] < -1 )
		{
			//基本得点:I&O=50,J&L&T=100,S&Z=150点
			if( tet->t[ i ] == T_I ||
				tet->t[ i ] == T_O )
			{
				addscore = 1;
			}
			if( tet->t[ i ] == T_J ||
				tet->t[ i ] == T_L ||
				tet->t[ i ] == T_T )
			{
				addscore = 2;
			}
			if( tet->t[ i ] == T_S ||
				tet->t[ i ] == T_Z )
			{
				addscore = 3;
			}

			//連続の記録
			//コンボが途切れた場合
			if( tet->t[ i ] != *comboT )
			{
				Battle_Attack( block2, cursorY2, *comboP );

				*comboN = 0;
				*comboT = tet->t[ i ];

				*score += *comboP;
				*comboP = 0;
			}
			*comboTime = timer;
			*comboN += 1;

			//連続消去でボーナスN*N/2点
			*comboP += 10 * ( addscore * *comboN * *comboN + addscore * *comboN * 3 ) / 4;

			//テトリミノの初期化
			tet->x[ i ] = -100;
			tet->y[ i ] = 1000;
		}
	}

	//コンボ時間が切れた場合
	if( timer - *comboTime > ChainTime )
	{
		Battle_Attack( block2, cursorY2, *comboP );

		*score += *comboP;
		*comboP = 0;

		*comboN = 0;
		*comboT = -1;
	}
}



//エディタ-----------------------------------------------------------
void Editor_Make_Tetrimino( int block[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], struct tetrimino *tet,
	int *mode, int choice, int *selection, int direction, int x, int y, bool *menu )
{
	if( ( MikanInput->GetKeyNum( K_Z ) % 10 == 1 ||
		 MikanInput->GetPadNum( 0, PAD_B ) % 10 == 1 ) &&
		 *menu == false )
	{
		//いずれかのテトリミノが当てはまったか否かの判定変数
		bool find = false;
		//選ばれたテトリミノの種類を記憶する。
		//実際に使われたテトリミノの個数を記録するために必要。
		int ChoicedTet;

		for( int i = 0; i < TetriMax; i ++)
		{
			if( tet->x[ i ] < 0 )//未使用の（＝tet.xがマイナスの）テトリミノを探す
			{
				//I型
				if( find == false &&
					choice == T_I &&
					( direction == UP ||
					direction == DOWN ) )
				{
					if( block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y ][ x + 2 ] != 1 )
					{
						tet->t[ i ] = T_I;
						tet->dir[ i ] = UP;
						
						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y ][ x + 2 ] = 2;

						ChoicedTet = T_I;
						find = true;
					}
				}
				if( find == false &&
					choice == T_I &&
					( direction == RIGHT ||
					direction == LEFT ) )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x ] != 1 &&
						block[ y + 2 ][ x ] != 1 )
					{ 
						tet->t[ i ] = T_I;
						tet->dir[ i ] = RIGHT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x ] = 2;
						block[ y + 2 ][ x ] = 2;

						ChoicedTet = T_I;
						find = true;
					}
				}

				//S型
				if( find == false &&
					choice == T_S &&
					( direction == UP ||
					direction == DOWN ) )
				{
					if( block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y + 1 ][ x - 1 ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						tet->t[ i ] = T_S;
						tet->dir[ i ] = UP;

						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y + 1 ][ x - 1 ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_S;
						find = true;
					}
				}
				if( find == false &&
					choice == T_S &&
					( direction == RIGHT ||
					  direction == LEFT ) )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x + 1 ] != 1 )
					{
						tet->t[ i ] = T_S;
						tet->dir[ i ] = RIGHT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x + 1 ] = 2;

						ChoicedTet = T_S;
						find = true;
					}
				}

				//Z型
				if( find == false &&
					choice == T_Z &&
					( direction == UP ||
					direction == DOWN ) )
				{
					if( block[ y ][ x ] != 1 &&
						block[ y ][ x - 1 ] != 1 &&
						block[ y + 1 ][ x ] != 1 &&
						block[ y + 1 ][ x + 1 ] != 1 )
					{
						tet->t[ i ] = T_Z;
						tet->dir[ i ] = UP;

						block[ y ][ x ] = 2;
						block[ y ][ x - 1 ] = 2;
						block[ y + 1 ][ x ] = 2;
						block[ y + 1 ][ x + 1 ] = 2;

						ChoicedTet = T_Z;
						find = true;
					}
				}
				if( find == false &&
					choice == T_Z &&
					( direction == RIGHT ||
					direction == LEFT ) )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x - 1 ] != 1 )
					{
						tet->t[ i ] = T_Z;
						tet->dir[ i ] = RIGHT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x - 1 ] = 2;

						ChoicedTet = T_Z;
						find = true;
					}
				}

				//J型
				if( find == false &&
					choice == T_J &&
					direction == UP )
				{
					if( block[ y - 1 ][ x - 1 ] != 1 &&
						block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 )
					{
						tet->t[ i ] = T_J;
						tet->dir[ i ] = UP;

						block[ y - 1 ][ x - 1 ] = 2;
						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;

						ChoicedTet = T_J;
						find = true;
					}
				}
				if( find == false &&
					choice == T_J &&
					direction == RIGHT )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y - 1 ][ x + 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						tet->t[ i ] = T_J;
						tet->dir[ i ] = RIGHT;

						block[ y - 1 ][ x ] = 2;
						block[ y - 1 ][ x + 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_J;
						find = true;
					}
				}
				if( find == false &&
					choice == T_J &&
					direction == DOWN )
				{
					if( block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y + 1 ][ x + 1 ] != 1 )
					{
						tet->t[ i ] = T_J;
						tet->dir[ i ] = DOWN;

						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y + 1 ][ x + 1 ] = 2;

						ChoicedTet = T_J;
						find = true;
					}
				}
				if( find == false &&
					choice == T_J &&
					direction == LEFT )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x - 1 ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						tet->t[ i ] = T_J;
						tet->dir[ i ] = LEFT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x - 1 ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_J;
						find = true;
					}
				}

				//L型
				if( find == false &&
					choice == T_L &&
					direction == UP )
				{
					if( block[ y - 1 ][ x + 1 ] != 1 &&
						block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 )
					{
						tet->t[ i ] = T_L;
						tet->dir[ i ] = UP;

						block[ y - 1 ][ x + 1 ] = 2;
						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;

						ChoicedTet = T_L;
						find = true;
					}
				}
				if( find == false &&
					choice == T_L &&
					direction == RIGHT )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x ] != 1 &&
						block[ y + 1 ][ x + 1 ] != 1 )
					{
						tet->t[ i ] = T_L;
						tet->dir[ i ] = RIGHT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x ] = 2;
						block[ y + 1 ][ x + 1 ] = 2;

						ChoicedTet = T_L;
						find = true;
					}
				}
				if( find == false &&
					choice == T_L &&
					direction == DOWN )
				{
					if( block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y + 1 ][ x - 1 ] != 1 )
					{
						tet->t[ i ] = T_L;
						tet->dir[ i ] = DOWN;

						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y + 1 ][ x - 1 ] = 2;

						ChoicedTet = T_L;
						find = true;
					}
				}
				if( find == false &&
					choice == T_L &&
					direction == LEFT )
				{
					if( block[ y - 1 ][ x - 1 ] != 1 &&
						block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						tet->t[ i ] = T_L;
						tet->dir[ i ] = LEFT;

						block[ y - 1 ][ x - 1 ] = 2;
						block[ y - 1 ][ x ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_L;
						find = true;
					}
				}

				//O型
				if( find == false &&
					choice == T_O )
				{
					if( block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y + 1 ][ x ] != 1 &&
						block[ y + 1 ][ x + 1 ] != 1 )
					{
						tet->t[ i ] = T_O;
						tet->dir[ i ] = UP;

						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y + 1 ][ x ] = 2;
						block[ y + 1 ][ x + 1 ] = 2;

						ChoicedTet = T_O;
						find = true;
					}
				}

				//T型
				if( find == false &&
					choice == T_T &&
					direction == UP )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x -1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 )
					{
						tet->t[ i ] = T_T;
						tet->dir[ i ] = UP;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x -1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;

						ChoicedTet = T_T;
						find = true;
					}
				}
				if( find == false &&
					choice == T_T &&
					direction == RIGHT )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						tet->t[ i ] = T_T;
						tet->dir[ i ] = RIGHT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_T;
						find = true;
					}
				}
				if( find == false &&
					choice == T_T &&
					direction == DOWN )
				{
					if( block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y ][ x + 1 ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						tet->t[ i ] = T_T;
						tet->dir[ i ] = DOWN;

						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y ][ x + 1 ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_T;
						find = true;
					}
				}
				if( find == false &&
					choice == T_T &&
					direction == LEFT )
				{
					if( block[ y - 1 ][ x ] != 1 &&
						block[ y ][ x - 1 ] != 1 &&
						block[ y ][ x ] != 1 &&
						block[ y + 1 ][ x ] != 1 )
					{
						tet->t[ i ] = T_T;
						tet->dir[ i ] = LEFT;

						block[ y - 1 ][ x ] = 2;
						block[ y ][ x - 1 ] = 2;
						block[ y ][ x ] = 2;
						block[ y + 1 ][ x ] = 2;

						ChoicedTet = T_T;
						find = true;
					}
				}


				//テトリミノの配置が可能ならば
				if( find == true &&
					Tetrimino_Stand_Ground( block, x, y, choice, direction ) == true )
				{
					for( int j = 0; j < BlockHei; j ++ )
					{
						for( int k = 0; k < BlockWid; k ++ )
						{
							if( block[ j ][ k ] == 2 )
							{
								block[ j ][ k ] = 1;

								tet->x[ i ] = x;
								tet->y[ i ] = y;
							}
						}
					}

					//使用したテトリミノを記録する。
					UsedTet[ ChoicedTet ] += 1;

					MikanSound->Play( 14, false );
				}
				//配置不可能ならば選択解除
				else
				{
					for( int j = 0; j < BlockHei; j ++ )
					{
						for( int k = 0; k < BlockWid; k ++ )
						{
							if( block[ j ][ k ] == 2 )
							{
								block[ j ][ k ] = 0;
							}
						}
					}
					MikanSound->Play( 15, false );
				}

				break;
			}
		}
	}



	//Aキーでメニュー画面へ
	if( ( MikanInput->GetKeyNum( K_A ) == 1 ||
		  MikanInput->GetPadNum( 0, PAD_A ) == 1 ) &&
		  *menu == false )
	{
		*menu = true;
		MikanSound->Play( 12, false );
	}

	//メニューの処理
	if( *menu )
	{
		if( MikanInput->GetKeyNum( K_UP ) == 1 ||
			MikanInput->GetPadNum( 0, PAD_UP ) == 1 )
		{
			if( *selection > 0 )
			{
				*selection -= 1;
			}
			else
			{
				*selection = 4;
			}
			MikanSound->Play( 10, false );
		}
		if( MikanInput->GetKeyNum( K_DOWN ) == 1 ||
			MikanInput->GetPadNum( 0, PAD_DOWN ) == 1 )
		{
			if( *selection < 4 )
			{
				*selection += 1;
			}
			else
			{
				*selection = 0;
			}
			MikanSound->Play( 10, false );
		}
		//例外処理
		if( *selection < 0 )
		{
			*selection = 0;
		}
		else if( *selection > 4 )
		{
			*selection = 4;
		}

		if( MikanInput->GetKeyNum( K_Z ) == 3 ||
			MikanInput->GetPadNum( 0, PAD_B ) == 3 )
		{
			if( *selection == 0 )
			{
				//特になし
				MikanSound->Play( 12, false );
			}

			//リセット
			else if( *selection == 1 )
			{
				for( int i = 0; i < TetriMax; i ++ )
				{
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				for( int i = 0; i < 7; i ++ )
				{
					UsedTet[ i ] = 0;
				}

				for( int i = 1; i < BlockHei - 1; i ++ )
				{
					for( int j = 1; j < BlockWid - 1; j ++)
					{
						block[ i ][ j ] = 0;
					}
				}
				MikanSound->Play( 20, false );
			}

			//セーブ！！！
			else if( *selection == 2 )
			{
				_mkdir( "stage" );

				FILE *fp;

				//ステージ上のブロックの状態
				fp = fopen( "stage/stage.txt", "w" );
				if( fp == NULL )
				{
					exit( 1 );
				}

				for( int i = 0; i < BlockHei; i ++ )
				{
					for( int j = 0; j < BlockWid - 1; j ++ )
					{
						fprintf( fp, "%d, ", block[ i ][ j ] );
					}
					fprintf( fp, "%d\n", block[ i ][ BlockWid - 1 ] );
				}
				fclose( fp );


				//使用したテトリミノの種類と数、及び種類・向き・座標
				fp = fopen( "stage/tetrimino.txt", "w" );
				if( fp == NULL )
				{
					exit( 1 );
				}

				//1行目
				for( int i = 0; i < 7 - 1; i ++ )
				{
					fprintf( fp, "%d, ", UsedTet[ i ] );
				}
				fprintf( fp, "%d\n", UsedTet[ 6 ] );
				//それ以降
				for( int i = 0; i < TetriMax; i ++ )
				{
					if( tet->x[ i ] > 0 )
					{
						fprintf( fp, "%d, %d, %d, %d\n", tet->x[ i ], tet->y[ i ], tet->t[ i ], tet->dir[ i ] );
					}
				}

				fclose( fp );

				MikanSound->Play( 14, false );
			}

			//ロード！！！！！
			else if( *selection == 3 )
			{
				FILE *fp;

				fp = fopen( "stage/stage.txt", "r" );
				if( fp == NULL )
				{
					exit( 1 );
				}
				for( int i = 0; i < BlockHei; i ++ )
				{
					fscanf( fp, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d" ,&block[ i ][ 0 ], &block[ i ][ 1 ], 
						&block[ i ][ 2 ], &block[ i ][ 3 ], &block[ i ][ 4 ], &block[ i ][ 5 ], &block[ i ][ 6 ], 
						&block[ i ][ 7 ], &block[ i ][ 8 ], &block[ i ][ 9 ], &block[ i ][ 10 ], &block[ i ][ 11 ] );
				}
				fclose( fp );

				//
				fp = fopen( "stage/tetrimino.txt", "r" );
				if( fp == NULL )
				{
					exit( 1 );
				}
				//1行目
				fscanf( fp, "%d, %d, %d, %d, %d, %d, %d",
					&UsedTet[ 0 ], &UsedTet[ 1 ], &UsedTet[ 2 ], &UsedTet[ 3 ], &UsedTet[ 4 ], &UsedTet[ 5 ], &UsedTet[ 6 ] );
				//それ以降
				for( int x, y, t, d, i = 0;
					fscanf( fp, "%d, %d, %d, %d", &x, &y, &t, &d ) != EOF;
					i ++ )
				{
					tet->x[ i ] = x;
					tet->y[ i ] = y;
					tet->t[ i ] = t;
					tet->dir[ i ] = d;
				}
				fclose( fp );

				MikanSound->Play( 14, false );
			}

			//タイトルへ
			else if( *selection == 4 )
			{
				*mode = TITLE;
				MikanSound->Play( 12, false );
			}

			//簡易的な初期化
			*menu = false;
			*selection = 0;
		}

		if( MikanInput->GetKeyNum( K_X ) == 1 ||
			MikanInput->GetPadNum( 0, PAD_C ) == 1 )
		{
			*selection = 0;
			*menu = false;

			MikanSound->Play( 13, false );
		}
	}
}
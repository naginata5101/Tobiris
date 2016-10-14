#include "common.h"


//�Q�[���J�n�̏���===================================================
//�w�i�̃u���b�N�̔z�u
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

//�J�[�\���z�u
void Put_Cursor( int block[ BlockHei ][ BlockWid ], int *x, int *y )
{
	for( int i = 0; i < BlockHei; i++ )
	{
		for( int j = 0; j < BlockWid; j ++)
		{
			if( block[ i ][ j ] == 1 )
			{
				*x = j;
				//��˂�h�����߂ɁA1�i��ɒu���B
				*y = i - 1;
				return;
			}
		}
	}
}

//���̃e�g���~�m�����ɕ����Ă��Ȃ����̔���i�ݒu���Ă�����true�j
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

//�����_���X�e�[�W�����
void Random_Make_Stage( int block[ BlockHei ][ BlockWid ], int LimitTet[ 7 ] )
{
	//���̃e�g���~�m��x,type,direction�̕ϐ�
	int x, t, d;

	//������
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

	//�e�g���~�m�̔z�u��20�񂾂����킷��B
	for( int i = 0; i < 20; i ++ )
	{
		x = rand() % ( BlockWid - 2 ) + 1;
		t = rand() % 7;
		d = rand() % 4;
		//X���W�̏C��------------
		//I�^
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

		//S�^
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

		//Z�^
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

		//J�^
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

		//L�^
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

		//O�^
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

		//T�^
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

		//Y���W�̌���
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
				//���ۂɃu���b�N��u���B---------
				//I�^
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

				//S�^
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

				//Z�^
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

				//J�^
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

				//L�^
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

				//O�^
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

				//T�^
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
	//�S�Ẵe�g���~�m�̐�����+1
	for( int i = 0; i < 7; i ++ )
	{
		LimitTet[ i ] += 1;
	}
}

void Puzzle_Stady_Game( const int stage[ StageMax ][ BlockHei ][ BlockWid ], int block[ BlockHei ][ BlockWid ], int stocks[ StageMax ][ 7 ], int UsedTet[ 7 ], int LimitTet[ 7 ], struct tetrimino *tet,
	int *selection, int *StageNum, int *timer, int *cursorX, int *cursorY, int *choice, int *direction, int *EndTime, bool *menu, bool *timeUP, bool *clear, bool *fail )
{
	//�u���b�N�z�u
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
	//�I���W�i���X�e�[�W
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

		//�e�g���~�m�ɗ]�T��
		for( int i = 0; i < 7; i ++ )
		{
			LimitTet[ i ] += 1;
		}
	}
	//�����_���X�e�[�W
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

	//�ȍĐ�
	MikanSound->Play( 1, true );
}

void Endless_Stady_Game( int block[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], struct tetrimino *tet, int *selection, int *choice, int *direction,
	int *timer,	int *cursorX, int *cursorY, int *EndTime, int *score, int *comboN, int *comboT, int *comboP, int *comboTime, bool *menu )
{
	//�u���b�N�̏�����
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

	
	//�J�[�\���z�u
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


	//�ȍĐ�
	MikanSound->Play( 0, true );
}

void Battle_Stady_Game( int block[ BlockHei ][ BlockWid ], int block2[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], struct tetrimino *tet, struct tetrimino *tet2, int *selection, int *selection2,
	int *choice, int *choice2,	int *timer,	int *cursorX, int *cursorX2, int *cursorY, int *cursorY2, int *EndTime, int *score, int *score2, int *direction, int *direction2,
	int *comboN2, int *comboN, int *comboT, int *comboT2, int *comboP, int *comboP2, int *comboTime, int *comboTime2, int *winner, bool *menu )
{
	//�u���b�N�̏�����
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

	//�J�[�\���z�u
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


	//�ȍĐ�
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

	//�J�[�\���z�u
	*x = 1;
	*y = BlockHei - 1;
	*choice = 0;
	*selection = 0;
	*direction = 0;

	*menu = false;


	//�ȍĐ�
	MikanSound->Play( 1, true );
}



//�^�C�g����=======================================================
//1,2P�̃J�[�\���^�C�v�̑I��
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
	//��O����
	if( *selection < 0 )
	{
		*selection = 0;
	}
	if( * selection > 5 )
	{
		*selection = 5;
	}

	//�Ȓ�~
	MikanSound->Stop( 0 );
	MikanSound->Stop( 1 );
}

void Choice_Title( int block[ BlockHei ][ BlockWid ], int block2[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], struct tetrimino *tet, struct tetrimino *tet2,
	int *mode, int *selection, int *selection2, int *choice, int *choice2, int *direction, int *direction2, int *timer, int *cursorX, int *cursorX2, int *cursorY, int *cursorY2,
	int *EndTime, int *score, int *score2, int *comboN, int *comboN2, int *comboT, int *comboT2, int *comboP, int *comboP2, int *comboTime, int *comboTime2, int *winner, bool *menu )
{
	//�X�e�[�W�Z���N�g�̏����Ƃ̌��ˍ�����"== 3"�ɂ��Ă����B
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
	//�㉺�ړ�
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

	//���E�ړ�
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

	//��O����
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
	//��O����
	if( *selection < 0 )
	{
		*selection = 0;
	}
	if( *selection > 2 )
	{
		*selection = 2;
	}
	
	//Z,X�L�[�Ń^�C�g����
	//�@3==���ˍ���
	if( ( MikanInput->GetKeyNum( K_Z ) == 3 ||
		  MikanInput->GetPadNum( 0, PAD_B ) == 3 ) ||
		( MikanInput->GetKeyNum( K_X ) == 3 ||
		  MikanInput->GetPadNum( 0, PAD_C ) == 3 ) )
	{
		*mode = TITLE;
		MikanSound->Play( 13, false );
	}
}


//�ȉ��A�Q�[�����[�h=================================================
//�I�񂾃u���b�N�B�̏㕔���󂢂Ă��邩�ۂ��̔���֐�
//true==�オ�󂢂Ă���Afalse==�󂢂Ă��Ȃ�
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
					if( block[ k ][ j ] == 1 )//��̃u���b�N����ł��I�𒆂ł�����������
					{
						return false;//false�Ԃ��B
					}
				}
			}
		}
	}

	return true;
}

//�I�𒆂̃u���b�N��1�オ�󂢂Ă��邩�ۂ�
bool Endless_Blocks_Upper( int block[ BlockHei ][ BlockWid ] )
{
	for( int i = 0; i < BlockHei; i ++ )
	{
		for( int j = 0; j < BlockWid; j ++ )
		{
			if( block[ i ][ j ] == 2 &&
				//1�オ��I���̃u���b�N�Ȃ��
				block[ i - 1 ][ j ] == 1 )
			{
				return false;
			}
		}
	}

	return true;
}


//�J�[�\���̃e�g���~�m�ƌ����̕ύX
void Silhouette_Cursor_Change( int PadNum, int *choice, int *direction )
{
	//D�L�[�iL1�j�őO�̃e�g���~�m��
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
	//C�L�[�iR1�j�Ŏ��̃e�g���~�m��
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

	//S�L�[�������ꂽ�������ύX����B
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

//�J�[�\���̈ړ��֐�
void Silhouette_Cursor_Move( int PadNum, int *x, int *y, int choice, int direction )
{
	//I�^
	if( choice == T_I &&
		( direction == UP ||
		direction == DOWN ) )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
				MikanSound->Play( 10, false );
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 )
			{
				*y += 1;
				MikanSound->Play( 10, false );
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
				MikanSound->Play( 10, false );
			}
			//�E
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
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 2 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 )
			{
				*x -= 1;
			}
			//�E
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

	//S�^
	else if( choice == T_S &&
		( direction == UP ||
		direction == DOWN ) )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//�E
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
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 )
			{
				*x -= 1;
			}
			//�E
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

	//Z�^
	else if( choice == T_Z &&
		( direction == UP ||
		direction == DOWN ) )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//�E
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
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//�E
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

	//J�^
	else if( choice == T_J &&
		direction == UP )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//�E
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
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 )
			{
				*x -= 1;
			}
			//�E
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
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//�E
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
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//�E
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

	//L�^
	else if( choice == T_L &&
		direction == UP )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//�E
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
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 )
			{
				*x -= 1;
			}
			//�E
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
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//�E
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
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//�E
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

	//O�^
	else if( choice == T_O )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 )
			{
				*x -= 1;
			}
			//�E
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

	//T�^
	else if( choice == T_T &&
		direction == UP )
	{
		if( ( MikanInput->GetKeyNum( K_X ) <= 0 &&
			  MikanInput->GetKeyNum( K_A ) <= 0 ) &&
			( MikanInput->GetPadNum( PadNum, PAD_C ) <= 0 &&
			  MikanInput->GetPadNum( PadNum, PAD_A ) <= 0 ) )
		{
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//�E
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
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 )
			{
				*x -= 1;
			}
			//�E
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
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//�E
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
			//��
			if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
				*y > 1 + 1 )
			{
				*y -= 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
				*y < BlockHei - 2 - 1 )
			{
				*y += 1;
			}
			//��
			if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
				  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
				*x > 1 + 1 )
			{
				*x -= 1;
			}
			//�E
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

//�e�g���~�m�̐����A�y�ёI���u���b�N�̏���
//�e�g���~�m�����ۂɍ�ꂽ��true
bool Silhouette_Make_Tetrimino( int PadNum, int block[ BlockHei ][ BlockWid ], int LimitTet[ 7 ], int UsedTet[ 7 ], int LastBlockX[ 4 ], int LastBlockY[ 4 ],
	struct tetrimino *tet, int choice, int direction, int timer, int x, int y, int StageNum, int mode )
{
	if( MikanInput->GetKeyNum( K_Z ) % 10 == 1 ||
		MikanInput->GetPadNum( PadNum, PAD_B ) % 10 == 1 )
	{
		//�����ꂩ�̃e�g���~�m�����Ă͂܂������ۂ��̔���ϐ�
		bool find = false;
		//�I�΂ꂽ�e�g���~�m�̎�ނ��L������B
		//���ۂɎg��ꂽ�e�g���~�m�̌����L�^���邽�߂ɕK�v�B
		int ChoicedTet;

		for( int i = 0; i < TetriMax; i ++)
		{
			if( tet->x[ i ] < 0 )//���g�p�́i��tet.x���}�C�i�X�́j�e�g���~�m��T��
			{
				//I�^
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

				//S�^
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

				//Z�^
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

				//J�^
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

				//L�^
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

				//O�^
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

				//T�^
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


				//�I�𒆂̃e�g���~�m�ɓK�����u���b�N�̔z�u�������ꍇ
				if( find == true )
				{
					//�S�Ă�"LastBlock"�𖢎g�p�ɂ���i��O�ɏo���j�B
					for( int k = 0; k < 4; k ++ )
					{
						LastBlockX[ k ] = -100;
						LastBlockY[ k ] = -100;
					}

					//�オ�󂢂Ă���΃e�g���~�m�̐����{�u���b�N����
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

									//�Ō�ɏ������u���b�N�̍��W�𖢎g�p�́i��O�ɂ���j"LastBlock"�ɋL������B
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

						//�p�Y�����[�h�ł͎g�p�����e�g���~�m���L�^����B
						if( mode == PUZZLE_GAME )
						{
							UsedTet[ ChoicedTet ] += 1;
						}

						MikanSound->Play( 14, false );

						return true;

					}
					//�󂢂Ă��Ȃ���Ύ��s
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


//�J�[�\���̈ړ��֐�
bool Pointer_Cursor_Move( int PadNum, int block[ BlockHei ][ BlockWid ], int *x, int *y )
{
	//���ۂɃJ�[�\�������������ۂ��̔��� -> DidMove
	bool DidMove = false;

	//��
	if( ( MikanInput->GetKeyNum( K_UP ) % 10 == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_UP ) % 10 == 1 ) &&
		*y > 1 )
	{
		*y -= 1;
		DidMove = true;
		MikanSound->Play( 10, false );
	}
	//��
	if( ( MikanInput->GetKeyNum( K_DOWN ) % 10 == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_DOWN ) % 10 == 1 ) &&
		*y < BlockHei - 2 )
	{
		*y += 1;
		DidMove = true;
		MikanSound->Play( 10, false );
	}
	//��
	if( ( MikanInput->GetKeyNum( K_LEFT ) % 10 == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_LEFT ) % 10 == 1 ) &&
		*x > 1 )
	{
		*x -= 1;
		DidMove = true;
		MikanSound->Play( 10, false );
	}
	//�E
	if( ( MikanInput->GetKeyNum( K_RIGHT ) % 10 == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_RIGHT ) % 10 == 1 ) &&
		*x < BlockWid - 2 )
	{
		*x += 1;
		DidMove = true;
		MikanSound->Play( 10, false );
	}

	//��O����
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

//�u���b�N�I���̉���
void Pointer_Remove_Choice( int block[ BlockHei ][ BlockWid ] )
{
	for( int i = 0; i < BlockHei; i ++ )
	{
		for( int j = 0; j < BlockWid; j ++ )
		{
			if( block[ i ][ j ] == 2 )
			{
				block[ i ][ j ] = 1;//�I������
			}
		}
	}
}

//�u���b�N�̑I���E��I���̊֐�
void Pointer_Choice_Block( int PadNum, int block[ BlockHei ][ BlockWid ], int x, int y, int *choice, bool DidMove )
{
	//�אڂ���u�I�𒆂̃u���b�N�v�̐��𒲂ׁA2�ȏ�Ȃ�ΑI���������ł��Ȃ��悤�ɂ���B
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

	if( MikanInput->GetKeyNum( K_Z ) == 1 ||	//Z�L�[�������ꂽ��
		MikanInput->GetPadNum( PadNum, PAD_B ) == 1 ||
		DidMove == true )						//�ړ������^�C�~���O�Ŕ��肷��B
	{
		if( MikanInput->GetKeyNum( K_Z ) > 0 ||	//Z�L�[��������Ă���A
			MikanInput->GetPadNum( PadNum, PAD_B ) > 0 )
		{
			if( block[ y ][ x ] == 1 &&			//��I�𒆂̃u���b�N���
				( *choice <= 0 ||				//�������I�����Ă��Ȃ���
				  block[ y - 1 ][ x ] == 2 ||		//�I�𒆂̃u���b�N�ɗאڂ��Ă�����
				  block[ y + 1 ][ x ] == 2 ||
				  block[ y ][ x - 1 ] == 2 ||
				  block[ y ][ x + 1 ] == 2 ) )
			{
				block[ y ][ x ] = 2;			//���̃u���b�N��I�����A
				*choice += 1;					//�I�𐔂𑝉�������B
				MikanSound->Play( 12, false );
			}
			else if( block[ y ][ x ] == 2 &&
				count <= 1 )					//����ȊO�ŁA�I�𒆂̃u���b�N�̏��
			{
				block[ y ][ x ] = 1;			//���̃u���b�N�̑I���������A
				*choice -= 1;					//�I�𐔂�����������B
				MikanSound->Play( 13, false );
			}
		}
	}

	//X�L�[�������ꂽ�ꍇ�A�S�Ă̑I������������B
	if( MikanInput->GetKeyNum( K_X ) == 1 ||
		MikanInput->GetPadNum( PadNum, PAD_C ) == 1 )
	{
		*choice = 0;

		Pointer_Remove_Choice( block );
		MikanSound->Play( 13, false );
	}
}

//�e�g���~�m�̐����A�y�ёI���u���b�N�̏���
bool Pointer_Make_Tetrimino( int block[ BlockHei ][ BlockWid ], int LimitTet[ 7 ], int UsedTet[ 7 ], int LastBlockX[ 4 ], int LastBlockY[ 4 ],
	struct tetrimino *tet, int *choice, int mode, int StageNum )
{
	//�����ꂩ�̃e�g���~�m�����Ă͂܂������ۂ��̔���ϐ�
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
				if( tet->x[ n ] < 0 )//���g�p�́i��tet.x���}�C�i�X�́j�e�g���~�m��T��
				{
					//I�^
					if( maked == false  &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_I ] < LimitTet[ T_I ] ) )
					{
						for( int i = 0; i < BlockHei; i ++ )//��ver
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
						for( int i = 1; i < BlockHei - 2; i ++ )//�cver
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

					//S�^
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_S ] < LimitTet[ T_S ] ) )
					{
						for( int i = 0; i < BlockHei - 1; i ++ )//��ver
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
						for( int i = 1; i < BlockHei - 1; i ++ )//�cver
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

					//Z�^
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_Z ] < LimitTet[ T_Z ] ) )
					{
						for( int i = 0; i < BlockHei - 1; i ++ )//��ver
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
						for( int i = 1; i < BlockHei - 1; i ++ )//�cver
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

					//J�^
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_J ] < LimitTet[ T_J ] ) )
					{
						for( int i = 1; i < BlockHei; i ++ )//��ver
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
						for( int i = 1; i < BlockHei - 1; i ++ )//�Ever
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
						for( int i = 0; i < BlockHei - 1; i ++ )//��ver
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
						for( int i = 1; i < BlockHei - 1; i ++ )//��ver
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

					//L�^
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_L ] < LimitTet[ T_L ] ) )
					{
						for( int i = 1; i < BlockHei; i ++ )//��ver
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
						for( int i = 1; i < BlockHei - 1; i ++ )//�Ever
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
						for( int i = 0; i < BlockHei - 1; i ++ )//��ver
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
						for( int i = 1; i < BlockHei - 1; i ++ )//��ver
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

					//O�^
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

					//T�^
					if( maked == false &&
						( mode != PUZZLE_GAME ||
						  UsedTet[ T_T ] < LimitTet[ T_T ] ) )
					{
						for( int i = 1; i < BlockHei; i ++ )//��ver
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
						for( int i = 1; i < BlockHei - 1; i ++ )//�Ever
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
						for( int i = 0; i < BlockHei - 1; i ++ )//��ver
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
						for( int i = 1; i < BlockHei - 1; i ++ )//��ver
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
				//�S�Ă�"LastBlock"�𖢎g�p�ɂ���i��O�ɏo���j�B
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
							//�I�𒆂̃u���b�N����������B
							block[ i ][ j ] = 0;

							//�Ō�ɏ������u���b�N�̍��W�𖢎g�p�́i��O�ɂ���j"LastBlock"�ɋL������B
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
			//�I�����s���ł������ꍇ�ɂ͑I������
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



//�ȉ��A�p�Y�����[�h-------------------------------------------------
//�e�g���~�m�̈ړ�
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

//�������Ԑ���֐�
void Puzzle_TimeUP( int timer, int *EndTime, bool *timeUP )
{
	if( timer / 60 > LimitTime )
	{
		*EndTime = timer;
		*timeUP = true;
	}
}

//�e�g���~�m��߂��u���߂��v�֐�
void Puzzle_Return_Tetrimino( int block[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], int LastBlockX[ 4 ], int LastBlockY[ 4 ], struct tetrimino *tet, int *choice, bool cursorT )
{
	//�A���Ŗ߂��Ȃ��悤�ɂ���B�i�ő�A��1��j
	if( LastBlockX[ 0 ] > 0 )
	{
		//�u���b�N�𕜌����邵�ALastBlockX,Y���g�p�ςݏ�Ԃɂ���B
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
				//���O�ɍ���Ă��e�g���~�m����O�ɏo���A���g�p��ԂɁB
				tet->x[ i ] = -100;
				tet->y[ i ] = 1000;

				//�e�g���~�m�̎g�p�񐔂�-1����B
				UsedTet[ tet->t[ i ] ] -= 1;

				break;
			}
		}
	}

	//�J�[�\�����|�C���^�^�C�v�̂��߂̏���->�I��������������
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

//���j���[��ʂł̏����֐�
void Puzzle_Menu( int PadNum, int block[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], int LastBlockX[ 4 ], int LastBlockY[ 4 ],
	struct tetrimino *tet, int *mode, int *selection, int *choice, bool *menu, bool cursorT )
{
	//A�L�[�Ń��j���[��ʂ�
	if( ( MikanInput->GetKeyNum( K_A ) == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_A ) == 1 ) &&
		  *menu == false )
	{
		*menu = true;
		MikanSound->Play( 12, false );
	}

	if( *menu == true )
	{
		//�ړ�����
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

		//�I������
		//�^�C�g���̏����Ƃ̌��ˍ�����"== 3"�ɂ��Ă����B
		if( MikanInput->GetKeyNum( K_Z ) == 3 ||
			MikanInput->GetPadNum( PadNum, PAD_B ) == 3 )
		{
			if( *selection == 0 )
			{
				//���ɖ���
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

//�u�l�݁v��N���A�̔���
void Puzzle_Check_End( int block[ BlockHei ][ BlockWid ], bool *fail, bool *clear, int timer, int *EndTime )
{
	//�u�l�݁v����
	//�A�����̋L�^
	int count;
	for( int i = 1; i < BlockHei - 1; i ++ )
	{
		for( int j = 1; j < BlockWid; j ++ )
		{
			count = 0;
			//�J�E���g����
			if( block[ i ][ j ] == 1 )
			{
				count += 1;

				//��
				if( block[ i - 1 ][ j ] == 1 )
				{
					count += 1;

					//��E
					if( block[ i - 1 ][ j + 1 ] == 1 )
					{
						count += 1;

						//��E�E
						if( block[ i - 1 ][ j + 1 + 1 ] == 1 )
						{
							count += 1;
						}
						//��E��
						if( block[ i - 1 - 1 ][ j + 1 ] == 1 )
						{
							count += 1;
						}
					}
					//���
					if( block[ i - 1 - 1 ][ j ] == 1 )
					{
						count += 1;

						//���E
						if( block[ i - 1 - 1 ][ j + 1 ] == 1 )
						{
							count += 1;
						}
						//����
						if( block[ i - 1 - 1 - 1 ][ j ] == 1 )
						{
							count += 1;
						}
						//��㍶
						if( block[ i - 1 - 1 ][ j - 1 ] == 1 )
						{
							count += 1;
						}
					}
					//�㍶
					if( block[ i - 1 ][ j - 1 ] == 1 )
					{
						count += 1;

						//�㍶��
						if( block[ i - 1 - 1 ][ j - 1 ] == 1 )
						{
							count += 1;
						}
						//�㍶��
						if( block[ i - 1 ][ j - 1 - 1 ] == 1 )
						{
							count += 1;
						}
					}
				}
				//�E
				if( block[ i ][ j + 1 ] == 1 )
				{
					count += 1;

					//�E��
					if( block[ i - 1 ][ j + 1 ] == 1 )
					{
						count += 1;

						//�E���
						if( block[ i - 1 - 1 ][ j + 1 ] == 1 )
						{
							count += 1;
						}
						//�E��E
						if( block[ i - 1 ][ j + 1 + 1 ] == 1 )
						{
							count += 1;
						}
					}
					//�E�E
					if( block[ i ][ j + 1 + 1 ] == 1 )
					{
						count += 1;

						//�E�E��
						if( block[ i - 1 ][ j + 1 + 1 ] == 1 )
						{
							count += 1;
						}
						//�E�E�E
						if( block[ i ][ j + 1 + 1 + 1 ] == 1 )
						{
							count += 1;
						}
						//�E�E��
						if( block[ i + 1 ][ j + 1 + 1 ] == 1 )
						{
							count += 1;
						}
					}
					//�E��
					if( block[ i + 1 ][ j + 1 ] == 1 )
					{
						count += 1;

						//�E���E
						if( block[ i + 1 ][ j + 1 + 1 ] == 1 )
						{
							count += 1;
						}
						//�E����
						if( block[ i + 1 + 1 ][ j + 1 ] == 1 )
						{
							count += 1;
						}
					}
				}
				//��
				if( block[ i + 1 ][ j ] == 1 )
				{
					count += 1;

					//����
					if( block[ i + 1 + 1 ][ j ] == 1 )
					{
						count += 1;

						//�����E
						if( block[ i + 1 + 1 ][ j + 1 ] == 1 )
						{
							count += 1;
						}
						//������
						if( block[ i + 1 + 1 + 1 ][ j ] == 1 )
						{
							count += 1;
						}
						//������
						if( block[ i + 1 + 1 ][ j - 1 ] == 1 )
						{
							count += 1;
						}
					}
					//���E
					if( block[ i + 1 ][ j + 1 ] == 1 )
					{
						count += 1;

						//���E��
						if( block[ i + 1 + 1 ][ j + 1 ] == 1 )
						{
							count += 1;
						}
						//���E�E
						if( block[ i + 1 ][ j + 1 + 1 ] == 1 )
						{
							count += 1;
						}
					}
					//����
					if( block[ i + 1 ][ j - 1 ] == 1 )
					{
						count += 1;

						//������
						if( block[ i + 1 + 1 ][ j - 1 ] == 1 )
						{
							count += 1;
						}
						//������
						if( block[ i + 1 ][ j - 1 - 1 ] == 1 )
						{
							count += 1;
						}
					}
				}
				//��
				if( block[ i ][ j - 1 ] == 1 )
				{
					count += 1;

					//����
					if( block[ i - 1 ][ j - 1 ] == 1 )
					{
						count += 1;

						//�����
						if( block[ i - 1 - 1 ][ j - 1 ] == 1 )
						{
							count += 1;
						}
						//���㍶
						if( block[ i - 1 ][ j - 1 - 1 ] == 1 )
						{
							count += 1;
						}
					}
					//����
					if( block[ i + 1 ][ j - 1 ] == 1 )
					{
						count += 1;

						//������
						if( block[ i + 1 + 1 ][ j - 1 ] == 1 )
						{
							count += 1;
						}
						//������
						if( block[ i + 1 ][ j - 1 - 1 ] == 1 )
						{
							count += 1;
						}
					}
					//����
					if( block[ i ][ j - 1 - 1 ] == 1 )
					{
						count += 1;

						//������
						if( block[ i - 1 ][ j - 1 - 1 ] == 1 )
						{
							count += 1;
						}
						//������
						if( block[ i + 1 ][ j - 1 - 1 ] == 1 )
						{
							count += 1;
						}
						//������
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


	//�N���A�������̔���
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

//�Q�[���I�����̏���
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
		//�Ȓ�~
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

	//�N���A��250�t���[���Ŕw�i��`�悷��B
	if( timer - EndTime == 250 )
	{
		*menu = true;
	}

	//�^�C�g����
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



//�ȉ��A�G���h���X���[�h---------------------------------------------
//�e�g���~�m�̈ړ��A�y�ђ�~
void Endless_Move_Tetrimino( int block[ BlockHei ][ BlockWid ], struct tetrimino *tet, int timer )
{
	//�T���������������ۂ�
	bool find;

	for( int i = 0; i < TetriMax; i ++ )
	{
		if( ( timer - tet->time[ i ] ) % 5 == 0 &&
			tet->y[ i ] >= -2 &&
			tet->x[ i ] > 0  )
		{
			find = false;

			//��ʏ㕔�ɗ��Ă��Ȃ���ԂȂ��
			if( tet->y[ i ] > 1 )
			{
				//I�^
				if( find == false &&
					tet->t[ i ] == T_I &&
					( tet->dir[ i ] == UP ||
					tet->dir[ i ] == DOWN ) &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 2 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 2 ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_I &&
					( tet->dir[ i ] == RIGHT ||
					tet->dir[ i ] == LEFT ) &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 2 ][ tet->x[ i ]  ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				//S�^
				if( find == false &&
					tet->t[ i ] == T_S &&
					( tet->dir[ i ] == UP ||
					tet->dir[ i ] == DOWN ) &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ||
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_S &&
					( tet->dir[ i ] == RIGHT ||
					tet->dir[ i ] == LEFT ) &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] + 1 ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				//Z�^
				if( find == false &&
					tet->t[ i ] == T_Z &&
					( tet->dir[ i ] == UP ||
					tet->dir[ i ] == DOWN ) &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] + 1 ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_Z &&
					( tet->dir[ i ] == RIGHT ||
					tet->dir[ i ] == LEFT ) &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] - 1 ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				//J�^
				if( find == false &&
					tet->t[ i ] == T_J &&
					tet->dir[ i ] == UP &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_J &&
					tet->dir[ i ] == RIGHT &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 2 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_J &&
					tet->dir[ i ] == DOWN &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] + 1 ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_J &&
					tet->dir[ i ] == LEFT &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				//L�^
				if( find == false &&
					tet->t[ i ] == T_L &&
					tet->dir[ i ] == UP &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] + 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_L &&
					tet->dir[ i ] == RIGHT &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] + 1 ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_L &&
					tet->dir[ i ] == DOWN &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] - 1 ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_L &&
					tet->dir[ i ] == LEFT &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				//O�^
				if( find == false &&
					tet->t[ i ] == T_O &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] + 1 ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}

				//T�^
				if( find == false &&
					tet->t[ i ] == T_T &&
					tet->dir[ i ] == UP &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_T &&
					tet->dir[ i ] == RIGHT &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_T &&
					tet->dir[ i ] == DOWN &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] + 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] + 1 ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
				if( find == false &&
					tet->t[ i ] == T_T &&
					tet->dir[ i ] == LEFT &&
					//�ȏ�̏����̃e�g���~�m�̎��A�オ�u���b�N�Ȃ��
					( block[ tet->y[ i ] - 2 ][ tet->x[ i ] ] == 1 ||
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] - 1 ] == 1 ) )
				{
					//�e�g���~�m�̃}�X�Ƀu���b�N��z�u����
					block[ tet->y[ i ] - 1 ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] - 1 ] = 1;
					block[ tet->y[ i ] ][ tet->x[ i ] ] = 1;
					block[ tet->y[ i ] + 1 ][ tet->x[ i ] ] = 1;

					//�Y������e�g���~�m�𖢎g�p�ɂ���i��O�ցj
					tet->x[ i ] = -100;
					tet->y[ i ] = 1000;
				}
			}


			//��L�ȊO�Ȃ�Ώ�ֈړ�������
			if( find == false )
			{
				tet->y[ i ] --;
			}
		}
	}
};

//����o���u���b�N�̐���
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
//�u���b�N�̃X���C�h
//�����ł�����true
bool Endless_Slide_Blocks( int block[ BlockHei ][ BlockWid ], int *cursorY )
{
	for( int i = 1; i < BlockHei - 1; i ++ )
	{
		for( int j = 1; j < BlockWid - 1; j ++ )
		{
			//�ŏ㕔�܂Ńu���b�N���l�܂��Ă��Ȃ����Ƃ��m�F����
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
//�G���h���X���[�h�ł̃u���b�N�̋����A�y�уJ�[�\���z�u��u���b�N�ɍ��킹�������B+�I������
void Endless_Move_Blocks( int PadNum, int block[ BlockHei ][ BlockWid ], int timer, int *SlideTime, int *EndTime,
	int *cursorX, int *cursorY, int *score, int *winner )
{
	//�Q�[������S�L�[�ŃX���C�h
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

	//�J�n�O�ɉ�����10�i�̃u���b�N������o������B
	//1��== "timer / 60 / 60"
	if( timer >= 10 &&
		timer < StartTime &&
		timer % 5 == 0 )
	{
		Endless_Slide_Blocks( block, cursorY );
	}
	//�J�[�\���̔z�u
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
				//�����Ƃ��s��->��������
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
			//�����Ƃ��s��->��������
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

//�X�R�A�̏����A�y�уe�g���~�m�̏���
void Endless_Count_Score( struct tetrimino *tet, int *score, int *comboN, int *comboT, int *comboP, int *comboTime, int timer )
{
	int addscore = 0;

	for( int i = 0; i < TetriMax; i ++ )
	{
		if( tet->x[ i ] >= 0 &&
			tet->y[ i ] < -1 )
		{
			//��{���_:I&O=50,J&L&T=100,S&Z=150�_
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

			//�A���̋L�^
			//�R���{���r�؂ꂽ�ꍇ
			if( tet->t[ i ] != *comboT )
			{
				*comboN = 0;
				*comboT = tet->t[ i ];

				*score += *comboP;
				*comboP = 0;
			}
			*comboTime = timer;
			*comboN += 1;

			//�A�������Ń{�[�i�XN*N/2�_
			*comboP += 10 * ( addscore * *comboN * *comboN + addscore * *comboN * 3 ) / 4;

			//�e�g���~�m�̏�����
			tet->x[ i ] = -100;
			tet->y[ i ] = 1000;
		}
	}

	//�R���{���Ԃ��؂ꂽ�ꍇ
	if( timer - *comboTime > ChainTime )
	{
		*score += *comboP;
		*comboP = 0;

		*comboN = 0;
		*comboT = -1;
	}
}

//���j���[��ʂł̏����֐�
void Endless_Menu( int PadNum, int *mode, int *selection, bool *menu )
{
	//A�L�[�Ń��j���[��ʂ�
	if( ( MikanInput->GetKeyNum( K_A ) == 1 ||
		  MikanInput->GetPadNum( PadNum, PAD_A ) == 1 ) &&
		  *menu == false )
	{
		*menu = true;
		MikanSound->Play( 12, false );
	}

	if( *menu == true )
	{
		//�ړ�����
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

		//�I������
		//�^�C�g���̏����Ƃ̌��ˍ�����"== 3"�ɂ��Ă����B
		if( MikanInput->GetKeyNum( K_Z ) == 3 ||
			MikanInput->GetPadNum( PadNum, PAD_B ) == 3 )
		{
			if( *selection == 0 )
			{
				//���ɖ���
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

//�Q�[���I����̏���
void Endless_GameOver( int PadNum, int *mode, int *score, int *comboP, int *comboTime, int timer, int EndTime, bool *menu )
{
	if( timer == EndTime + 1 )
	{
		*score += *comboP;
		*comboP = 0;
		*comboTime = 0;

		MikanSound->Play( 19, false );
		//�Ȓ�~
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

	//�N���A��250�t���[���Ŕw�i��`�悷��B
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

//�n�C�X�R�A�̍X�V
void Update_HighScore( bool endless, int *score, int *HighScore, int timer, int EndTime )
{
	int AnotherScore;

	//�����̌��ˍ�����+2
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



//�ȉ��A�o�g�����[�h---------------------------------------------
//�R���{�X�R�A�ɉ����đ���̃u���b�N�������グ��
void Battle_Attack( int block2[ BlockHei ][ BlockWid ], int *cursorY2, int comboP )
{
	for( int i = 0; i < comboP / 1000; i ++ )
	{
		Endless_Slide_Blocks( block2, cursorY2 );
	}
}

//�X�R�A�̏���
void Battle_Count_Score( struct tetrimino *tet, int *score, int *comboN, int *comboT, int *comboP, int *comboTime, int timer,
	int block2[ BlockHei ][ BlockWid ], int *cursorY2 )
	//block2,cursorY2�͂��ꂼ�ꑊ��̂��̂�����
{
	int addscore = 0;

	for( int i = 0; i < TetriMax; i ++ )
	{
		if( tet->x[ i ] >= 0 &&
			tet->y[ i ] < -1 )
		{
			//��{���_:I&O=50,J&L&T=100,S&Z=150�_
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

			//�A���̋L�^
			//�R���{���r�؂ꂽ�ꍇ
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

			//�A�������Ń{�[�i�XN*N/2�_
			*comboP += 10 * ( addscore * *comboN * *comboN + addscore * *comboN * 3 ) / 4;

			//�e�g���~�m�̏�����
			tet->x[ i ] = -100;
			tet->y[ i ] = 1000;
		}
	}

	//�R���{���Ԃ��؂ꂽ�ꍇ
	if( timer - *comboTime > ChainTime )
	{
		Battle_Attack( block2, cursorY2, *comboP );

		*score += *comboP;
		*comboP = 0;

		*comboN = 0;
		*comboT = -1;
	}
}



//�G�f�B�^-----------------------------------------------------------
void Editor_Make_Tetrimino( int block[ BlockHei ][ BlockWid ], int UsedTet[ 7 ], struct tetrimino *tet,
	int *mode, int choice, int *selection, int direction, int x, int y, bool *menu )
{
	if( ( MikanInput->GetKeyNum( K_Z ) % 10 == 1 ||
		 MikanInput->GetPadNum( 0, PAD_B ) % 10 == 1 ) &&
		 *menu == false )
	{
		//�����ꂩ�̃e�g���~�m�����Ă͂܂������ۂ��̔���ϐ�
		bool find = false;
		//�I�΂ꂽ�e�g���~�m�̎�ނ��L������B
		//���ۂɎg��ꂽ�e�g���~�m�̌����L�^���邽�߂ɕK�v�B
		int ChoicedTet;

		for( int i = 0; i < TetriMax; i ++)
		{
			if( tet->x[ i ] < 0 )//���g�p�́i��tet.x���}�C�i�X�́j�e�g���~�m��T��
			{
				//I�^
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

				//S�^
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

				//Z�^
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

				//J�^
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

				//L�^
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

				//O�^
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

				//T�^
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


				//�e�g���~�m�̔z�u���\�Ȃ��
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

					//�g�p�����e�g���~�m���L�^����B
					UsedTet[ ChoicedTet ] += 1;

					MikanSound->Play( 14, false );
				}
				//�z�u�s�\�Ȃ�ΑI������
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



	//A�L�[�Ń��j���[��ʂ�
	if( ( MikanInput->GetKeyNum( K_A ) == 1 ||
		  MikanInput->GetPadNum( 0, PAD_A ) == 1 ) &&
		  *menu == false )
	{
		*menu = true;
		MikanSound->Play( 12, false );
	}

	//���j���[�̏���
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
		//��O����
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
				//���ɂȂ�
				MikanSound->Play( 12, false );
			}

			//���Z�b�g
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

			//�Z�[�u�I�I�I
			else if( *selection == 2 )
			{
				_mkdir( "stage" );

				FILE *fp;

				//�X�e�[�W��̃u���b�N�̏��
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


				//�g�p�����e�g���~�m�̎�ނƐ��A�y�ю�ށE�����E���W
				fp = fopen( "stage/tetrimino.txt", "w" );
				if( fp == NULL )
				{
					exit( 1 );
				}

				//1�s��
				for( int i = 0; i < 7 - 1; i ++ )
				{
					fprintf( fp, "%d, ", UsedTet[ i ] );
				}
				fprintf( fp, "%d\n", UsedTet[ 6 ] );
				//����ȍ~
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

			//���[�h�I�I�I�I�I
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
				//1�s��
				fscanf( fp, "%d, %d, %d, %d, %d, %d, %d",
					&UsedTet[ 0 ], &UsedTet[ 1 ], &UsedTet[ 2 ], &UsedTet[ 3 ], &UsedTet[ 4 ], &UsedTet[ 5 ], &UsedTet[ 6 ] );
				//����ȍ~
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

			//�^�C�g����
			else if( *selection == 4 )
			{
				*mode = TITLE;
				MikanSound->Play( 12, false );
			}

			//�ȈՓI�ȏ�����
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
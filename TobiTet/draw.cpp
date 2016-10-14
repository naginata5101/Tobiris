#include "common.h"


//�ȉ��A���ʏ���====================================================
void Draw_BackGround( int back[ HEIGHT / ChipSize ][ WIDHT / ChipSize ] )
{
	for( int i = 0; i < HEIGHT / ChipSize; i ++ )
	{
		for( int j = 0; j < WIDHT / ChipSize; j ++ )
		{
			MikanDraw->DrawTexture( 0, j * ChipSize, i * ChipSize, back[ i ][ j ] * ChipSize, 4 * 4 * ChipSize, ChipSize, ChipSize );
		}
	}
	MikanDraw->DrawBox( 0, 0, WIDHT, HEIGHT, 0x7F000000 );
}


//�ȉ��A�^�C�g����ʂ̏���==========================================
void Draw_Title( int selection, bool cursorT, bool cursorT2 )
{
	MikanDraw->DrawBox( ( WIDHT - 128 * 4 ) / 2, 0, 128 * 4, 32 * 4 + 20 * 2, 0xFF000000 );
	MikanDraw->DrawBox( ( WIDHT - 30 * 8 ) / 2, 32 * 4 + 20 * 2, 30 * 8, HEIGHT - 32 * 4 - 20 * 2, 0xFF000000 );

	MikanDraw->DrawBox( 0, 0, 50, HEIGHT, 0xFFFFFFFF );
	MikanDraw->DrawBox( WIDHT - 50, 0, 50, HEIGHT, 0xFFFFFFFF );

	MikanDraw->DrawTextureScaling( 3, ( WIDHT - 128 * 4 ) / 2, 20, 0, 0, 128, 32, 4 );

	if( selection == 0 )
	{
		MikanDraw->Printf( 1, ( WIDHT - 6 * 30 ) / 2, 200 - 10 / 2, "�p�Y�����[�h" );
	}
	else
	{
		MikanDraw->Printf( 2, ( WIDHT - 6 * 20 ) / 2, 200, "�p�Y�����[�h" );
	}
	if( selection == 1 )
	{
		MikanDraw->Printf( 1, ( WIDHT - 8 * 30 ) / 2, 250 - 10 / 2, "�G���h���X���[�h" );
	}
	else
	{
		MikanDraw->Printf( 2, ( WIDHT - 8 * 20 ) / 2, 250, "�G���h���X���[�h" );
	}
	if( selection == 2 )
	{
		MikanDraw->Printf( 1, ( WIDHT - 6 * 30 ) / 2, 300 - 10 / 2, "�o�g�����[�h" );
	}
	else
	{
		MikanDraw->Printf( 2, ( WIDHT - 6 * 20 ) / 2, 300, "�o�g�����[�h" );
	}
	if( selection == 3 )
	{
		MikanDraw->Printf( 1, ( WIDHT - 7 * 30 ) / 2, 350 - 10 / 2, "�G�f�B�^���[�h" );
	}
	else
	{
		MikanDraw->Printf( 2, ( WIDHT - 7 * 20 ) / 2, 350, "�G�f�B�^���[�h" );
	}
	if( selection == 4 )
	{
		MikanDraw->Printf( 1, ( WIDHT - 5 * 30 ) / 2, 400 - 10 / 2, "�Q�[������" );
	}
	else
	{
		MikanDraw->Printf( 2, ( WIDHT - 5 * 20 ) / 2, 400, "�Q�[������" );
	}
	if( selection == 5 )
	{
		MikanDraw->Printf( 1, ( WIDHT - 5 * 30 ) / 2, 450 - 10 / 2, "�Q�[���I��" );
	}
	else
	{
		MikanDraw->Printf( 2, ( WIDHT - 5 * 20 ) / 2, 450, "�Q�[���I��" );
	}

	//�J�[�\���^�C�v�̕`��
	if( cursorT == true )
	{
		MikanDraw->Printf( 8, 0, 0, "1P\n�V\n��\n�G\n�b\n�g\n��\n�b\n�h" );
	}
	else
	{
		MikanDraw->Printf( 9, 0, 0, "1P\n�|\n�C\n��\n�^\n�b\n��\n�b\n�h" );
	}
	if( cursorT2 == true )
	{
		MikanDraw->Printf( 8, WIDHT - 50, 0, "2P\n�V\n��\n�G\n�b\n�g\n��\n�b\n�h" );
	}
	else
	{
		MikanDraw->Printf( 9, WIDHT - 50, 0, "2P\n�|\n�C\n��\n�^\n�b\n��\n�b\n�h" );
	}
}

void Draw_StageSelection( int selection )
{
	MikanDraw->DrawBox( ( WIDHT - 8 * 50 ) / 2, 40, 8 * 50, 50, 0xFF000000 );
	MikanDraw->DrawBox( 60 - ( 10 / 2 * 3 ), 150 - ( 10 / 2 ), 120 * 2 + ( 30 / 2 * 8 ), 50 * 4 + 30, 0xFF000000 );

	MikanDraw->Printf( 3, ( WIDHT - 8 * 50 ) / 2, 40, "�X�e�[�W�Z���N�g" );

	for( int i = 0; i < StageMax; i ++ )
	{
		if( i < 5 )
		{
			if( selection == i )
			{
				MikanDraw->Printf( 1, 60 - ( 10 / 2 * 3 ), 150 + ( i * 50 ) - ( 10 / 2 ), "stage%d", i + 1 );
			}
			else
			{
				MikanDraw->Printf( 2, 60, 150 + ( i * 50 ), "stage%d", i + 1 );
			}
		}
		else if ( i < 10 )
		{
			if( selection == i )
			{
				MikanDraw->Printf( 1, 180 - ( 10 / 2 * 3 ), 150 + ( ( i - 5 ) * 50 ) - ( 10 / 2 ), "stage%d", i + 1 );
			}
			else
			{
				MikanDraw->Printf( 2, 180, 150 + ( ( i - 5 ) * 50 ), "stage%d", i + 1 );
			}
		}
	}

	if( selection == 10 )
	{
		MikanDraw->Printf( 1, 300 - ( 10 / 2 * 3 ), 150 + 50 - 10 / 2, "original\nstage" );
	}
	else
	{
		MikanDraw->Printf( 2, 300, 150 + 50, "original\nstage" );
	}
	if( selection == 11 )
	{
		MikanDraw->Printf( 1, 300 - ( 10 / 2 * 3 ), 150 + 50 * 3 - 10 / 2, "random\nstage" );
	}
	else
	{
		MikanDraw->Printf( 2, 300, 150 + 50 * 3, "random\nstage" );
	}
}

void Draw_Thumbnail( const int stage[ StageMax ][ BlockHei ][ BlockWid ], int selection )
{
	MikanDraw->DrawBox( WIDHT - BlockWid * ChipSize / 2 - 60, 150, BlockWid * 10, BlockHei * 10, 0xFF000000 );

	for( int i = 0; i < StageMax; i ++ )
	{
		if( selection == i )
		{
			MikanDraw->DrawBox( 460 + 10, 150 + 10, ( BlockWid - 2 ) * 10, ( BlockHei - 2 ) * 10, 0xFFFFFFFF );
			for( int j = 0; j < BlockHei; j ++ )
			{
				for( int k = 0; k < BlockWid; k ++ )
				{
					if( stage[ i ][ j ][ k ] == 1 )
					{
						MikanDraw->DrawTexture( 0, ( k * ChipSize / 2 ) + 460, j * ChipSize / 2 + 150,
							10 * ChipSize, 4 * 4 * ChipSize, ChipSize / 2, ChipSize / 2 );
					}
				}
			}
			break;
		}
		else
		{
			MikanDraw->DrawBox( 460 + 10, 150 + 10, ( BlockWid - 2 ) * 10, ( BlockHei - 2 ) * 10, 0xFF7F7F7F );
		}
	}
}

void Draw_Explanation( int selection )
{
	if( selection == 0 )
	{
		MikanDraw->Printf( 1, 0, 100,
			"�y�Q�[���T�v�z\n"
			"�@�{��́u��΂����n�p�Y���Q�[���v�ł��B\n"
			"�@�ɗ��܂��Ă���e�g���X�u���b�N��\n"
			"�@�e��e�g���~�m�i�e�g���X�ň���\n"
			"�@4�̃u���b�N���q�������z�j�ɓ��Ă͂߁A\n"
			"�@��ʏ㕔�ɔ�΂��Ă��܂��ĉ������B" );
	}
	else if( selection == 1 )
	{
		MikanDraw->Printf( 6, 0, 0,
			"�y���[�h�����z\n"
			"�E�p�Y�����[�h\n"
			"�@�E�ɕ\������鐧�����Ńe�g���~�m�����A\n"
			"�@�������ԓ��ɑS�Ẵu���b�N���΂��ĉ������B\n"
			"�@�X�e�[�W�ɂ���āA�e�g���~�m�̐�����\n"
			"�@�]�T���L�����薳�������肵�܂��B\n"
			"�@���̃��[�h�ł́A�㕔�����S�ɋ󂢂Ă��Ȃ����\n"
			"�@�e�g���~�m����邱�Ƃ͂ł��܂���B\n"
			"\n"
			"�E�G���h���X���[�h\n"
			"�@�����ɏo�ė���u���b�N���΂��܂���A\n"
			"�@�����_��ڎw���ĉ������B\n"
			"�@�����e�g���~�m��A�����ď�����\n"
			"�@�R���{�̓_���������A����`�̃e�g���~�m�̕���\n"
			"�@������_���������ł��B\n"
			"�@���̃��[�h�ł́A�㕔�Ɍ��Ԃ�����΃e�g���~�m��\n"
			"�@��邱�Ƃ��ł��A�o�����e�g���~�m��\n"
			"�@�u���b�N�ɂԂ��������_�Œ�~���܂��B" );
	}
	else if( selection == 2 )
	{
		MikanDraw->Printf( 6, 0, 0,
			"�y���[�h�����z\n"
			"�E�o�g�����[�h\n"
			"�@�����ɏo�ė���u���b�N��������\n"
			"�@����������������c���ĉ������B\n"
			"�@���̃��[�h�ł̓R���{�̓_���ɉ�����\n"
			"�@����̃u���b�N������オ��܂��B\n"
			"\n"
			"�E�G�f�B�^���[�h\n"
			"�@���̃��[�h�ł̓p�Y�����[�h�̃X�e�[�W��\n"
			"�@���삷�邱�Ƃ��ł��܂��B\n"
			"�@�h���ɕ����Ȃ��`�h�Ȃ�Ύ��R�Ƀe�g���~�m\n"
			"�@��z�u���邱�Ƃ��\�ł��B\n"
			"�@���[�h���̃��j���[���烊�Z�b�g�A\n"
			"�@�Z�[�u�⃍�[�h���ł��܂��B\n"
			"�@�G�f�B�^���[�h�ŕۑ������X�e�[�W�̓p�Y�����[�h\n"
			"�@�́horiginal stage�h����V�Ԃ��Ƃ��\�ł��B\n"
			"�@�Ȃ��A�X�e�[�W�͍ő�1�܂ł���\n"
			"�@�Z�[�u�ł��Ȃ��̂Ō䒍�Ӊ������B");
	}

	MikanDraw->DrawBox( ( WIDHT - 5 * 30 / 2 ) / 2 - 10, HEIGHT - 30, 5 * 30 / 2 + 10 * 2, 30, 0xFFFFFFFF );
	MikanDraw->Printf( 4, ( WIDHT - 5 * 30 / 2 ) / 2, HEIGHT - 30, "%d / 3", selection + 1 );
}


//�ȉ��A�Q�[�����̏���==============================================
//�g�̕`��
void Draw_BlockBack()
{
	MikanDraw->DrawBox( 2 * ChipSize, ( -1 ) * ChipSize, BlockWid * ChipSize, BlockHei * ChipSize, 0xFF000000 );
	MikanDraw->DrawBox( ( 2 + 1 ) * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0xFFFFFFFF );

	MikanDraw->DrawBox( ( 2 + BlockWid ) * ChipSize + ( ChipSize / 2 ), 0, 10 * ChipSize, HEIGHT, 0xFF5F5F5F );
	//�G�̕\���@���ӁI
	MikanDraw->DrawTexture( 1, WIDHT - 150, 0, 0, 0, 150, HEIGHT );
}

//�u���b�N�̕`��֐�
void Draw_Block( int block[ BlockHei ][ BlockWid ] )
{
	//���j���[���J���Ă���Ԃ̓u���b�N��`�悵�Ȃ��B
	for( int i = 0; i < BlockHei; i ++ )
	{
		for( int j = 0; j < BlockWid; j ++ )
		{
			if( block[ i ][ j ] == 1 )
			{
				MikanDraw->DrawTexture( 0, ( j + 2 ) * ChipSize, ( i - 1 ) * ChipSize,
					0 * ChipSize, 4 * 4 * ChipSize, ChipSize, ChipSize );
			}
			if( block[ i ][ j ] == 2 )
			{
				MikanDraw->DrawTexture( 0, ( j + 2 ) * ChipSize, ( i - 1 ) * ChipSize,
					8 * ChipSize, 4 * 4 * ChipSize, ChipSize, ChipSize );
			}
		}
	}
}

//���������e�g���~�m�̕`��֐�
void Draw_Tetrimino( struct tetrimino tet )
{
	for( int i = 0; i < TetriMax; i ++ )
	{
		MikanDraw->DrawTexture( 0, ( tet.x[ i ] + 2 - 1 ) * ChipSize, ( tet.y[ i ] - 1 - 1 ) * ChipSize,
			tet.t[ i ] * 4 * ChipSize, tet.dir[ i ] * 4 * ChipSize, 4 * ChipSize, 4 * ChipSize );
	}
}


//�ȉ��A�p�Y�����[�h�̏���------------------------------------------
//�J�[�\���̕`��֐�
void Draw_Silhouette_Cursor( int x, int y, int choice, int dirction )
{
	MikanDraw->SetAlpha( 0, 127 );

	MikanDraw->DrawTexture( 0, ( x + 2 - 1) * ChipSize, ( y - 1 - 1 ) * ChipSize,
		choice * 4 * ChipSize, dirction * 4 * ChipSize, 4 * ChipSize, 4 * ChipSize );

	MikanDraw->SetAlpha( 0, 255 );
}

//��ʉE�̃e�g���~�m�ꗗ�̕\���֐�
void Draw_Puzzle_Tetrinimos( int LimitTet[ 7 ], int UsedTet[ 7 ], int StageNum, int choice, bool cursorT )
{
	for( int i = 0; i < 7; i ++ )
	{
		//�I�𒆂̃e�g���~�m�̌��ɔ�������`�悷��B
		if( cursorT == true &&
			choice == i )
		{
			MikanDraw->DrawBox( ( 2 + BlockWid ) * ChipSize + ( ChipSize / 2 ), 50 + i * 3 * ChipSize + ( ChipSize / 2 ), 10 * ChipSize, 3 * ChipSize, 0xFFFFFFFF );
		}

		//���̍ۂ�Y���W�𒲐����Č��h����ǂ�����B
		if( i == T_I ||
			i == T_J ||
			i == T_L ||
			i == T_T )
		{
			MikanDraw->DrawTexture( 0, ( 2 + BlockWid + 1 ) * ChipSize, 50 + ( i * 3 + 1 ) * ChipSize, i * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
		else if ( i == T_S ||
				  i == T_Z )
		{
			MikanDraw->DrawTexture( 0, ( 2 + BlockWid + 1 ) * ChipSize, 50 + ( i * 3 + 0 ) * ChipSize, i * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
		else if ( i == T_O )
		{
			MikanDraw->DrawTexture( 0, ( 2 + BlockWid + 0 ) * ChipSize, 50 + ( i * 3 + 0 ) * ChipSize, i * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}

		//�g�p�\�e�g���~�m���̕`��
		if( UsedTet[ i ] < LimitTet[ i ] )
		{
			MikanDraw->Printf( 4, ( 2 + BlockWid + 1 + 4 + 1 ) * ChipSize, 50 + ( i * 3 + 1 ) * ChipSize + ( 2 * ChipSize - 30 ) / 2,
				"%d / %d", LimitTet[ i ] - UsedTet[ i ], LimitTet[ i ] );
		}
		else
		{
			MikanDraw->Printf( 5, ( 2 + BlockWid + 1 + 4 + 1 ) * ChipSize, 50 + ( i * 3 + 1 ) * ChipSize + ( 2 * ChipSize - 30 ) / 2,
				"%d / %d", LimitTet[ i ] - UsedTet[ i ], LimitTet[ i ] );
		}
	}
}

//���j���[��ʂ̕`��
void Draw_Puzzle_Menu( int selection )
{
	MikanDraw->DrawBox( ( 2 + 1 ) * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0x7F000000 );


	MikanDraw->Printf( 3, ( BlockWid * ChipSize - 4 * 50 ) / 2 + 2 * ChipSize, 60, "���j���[" );

	if( selection == 0 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 6 * 25 ) / 2 + 2 * ChipSize, 250 - 10 / 2, "�Q�[���ɖ߂�" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 6 * 20 ) / 2 + 2 * ChipSize, 250, "�Q�[���ɖ߂�" );
	}
	if( selection == 1 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 4 * 25 ) / 2 + 2 * ChipSize, 300 - 10 / 2, "���߂�" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 4 * 20 ) / 2 + 2 * ChipSize, 300, "���߂�" );
	}
	if( selection == 2 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 7 * 25 ) / 2 + 2 * ChipSize, 350 - 10 / 2, "�^�C�g���ɖ߂�" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 7 * 20 ) / 2 + 2 * ChipSize, 350, "�^�C�g���ɖ߂�" );
	}
}

//�������Ԃ̕`��
void Draw_Limit_Time( int timer, int EndTime )
{
	if( EndTime < 0 )
	{
		if( LimitTime - timer / 60 >= 0 )
		{
			int j = 0;
			for( int n = 100, i = 0; n >= 1; n /= 10, i ++ )
			{
				if( ( LimitTime - timer / 60 ) / n - j <= 0 &&
					j == 0 )
				{
					//�`�悵�Ȃ�
				}
				else
				{
					MikanDraw->DrawTextureScaling( 3, ( 2 + BlockWid + 1 + 4 / 2 ) * ChipSize + i * 10 * 3, 1,
						8 * ( ( LimitTime - timer / 60 ) / n - j ), 33, 8, 16, 3 );
					j += ( LimitTime - timer / 60 - j ) / n * 10;
				}
			}
			if( j == 0 )
			{
				MikanDraw->DrawTextureScaling( 3, ( 2 + BlockWid + 1 + 4 / 2 ) * ChipSize + 2 * 10 * 3, 1, 0, 33, 8, 16, 3 );
			}
		}
		else
		{
			MikanDraw->DrawTextureScaling( 3, ( 2 + BlockWid + 1 + 4 / 2 ) * ChipSize + 2 * 10 * 3, 1, 0, 33, 8, 16, 3 );
		}
	}
	else
	{
		int j = 0;
		for( int n = 100, i = 0; n >= 1; n /= 10, i ++ )
		{
			if( ( LimitTime - EndTime / 60 ) / n - j <= 0 &&
				j == 0 )
			{
				//�`�悵�Ȃ�
			}
			else
			{
				MikanDraw->DrawTextureScaling( 3, ( 2 + BlockWid + 1 + 4 / 2 ) * ChipSize + i * 10 * 3, 1,
					8 * ( ( LimitTime - EndTime / 60 ) / n - j ), 33, 8, 16, 3 );
				j += ( LimitTime - EndTime / 60 - j ) / n * 10;
			}
		}
		if( j == 0 )
		{
			MikanDraw->DrawTextureScaling( 3, ( 2 + BlockWid + 1 + 4 / 2 ) * ChipSize + 2 * 10 * 3, 1, 0, 33, 8, 16, 3 );
		}
	}
}

//�Q�[���I�[�o�[
void Draw_Puzzle_End( int timer, int EndTime, bool menu, bool timeUP, bool clear, bool fail )
{
	if( menu == true )
	{
		MikanDraw->DrawBox( ( 2 + 1 ) * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0xFFC0C0C0 );
	}

	if( timer - EndTime < 250 )
	{
		if( clear == true )
		{
			MikanDraw->Printf( 8, ( BlockWid * ChipSize - 5 * 50 / 2 ) / 2 + 2 * ChipSize, timer - EndTime - 250, "Clear" );
		}
		else if( timeUP == true )
		{
			MikanDraw->Printf( 9, ( BlockWid * ChipSize - 6 * 50 / 2 ) / 2 + 2 * ChipSize, timer - EndTime - 250, "timeUP" );
		}
		else if( fail == true )
		{
			MikanDraw->Printf( 9, ( BlockWid * ChipSize - 4 * 50 / 2 ) / 2 + 2 * ChipSize, timer - EndTime - 250, "fail" );
		}
	}
	else
	{
		if( clear == true )
		{
			MikanDraw->Printf( 8, ( BlockWid * ChipSize - 5 * 50 / 2 ) / 2 + 2 * ChipSize, 0, "Clear" );

			MikanDraw->Printf( 11, ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2 + 2 * ChipSize, 250, "Push \"Z\" key to\nlook blocks." );
			MikanDraw->Printf( 10, ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2 + 2 * ChipSize, 320, "Push \"X\" key to\nback to title." );
			//MikanDraw->Printf( 10, ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2 + 2 * ChipSize, 320, "Push \"X\" key to\nexit from game." );
		}
		else
		{
			if( timeUP == true )
			{
				MikanDraw->Printf( 9, ( BlockWid * ChipSize - 6 * 50 / 2 ) / 2 + 2 * ChipSize, 0, "timeUP" );
			}
			else if( fail == true )
			{
				MikanDraw->Printf( 9, ( BlockWid * ChipSize - 4 * 50 / 2 ) / 2 + 2 * ChipSize, 0, "fail" );
			}
			MikanDraw->Printf( 11, ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2 + 2 * ChipSize, 250, "Push \"Z\" key to\nlook blocks." );
			MikanDraw->Printf( 10, ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2 + 2 * ChipSize, 320, "Push \"X\" key to\nback to title." );
			//MikanDraw->Printf( 10, ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2 + 2 * ChipSize, 320, "Push \"X\" key to\nexit from game." );
		}
	}
}


//�ȉ��A�G���h���X���[�h�̏���--------------------------------------
//�J�[�\���̕`��֐�
void Draw_Pointer_Cursor( int x, int y )
{
	MikanDraw->DrawTexture( 0, ( x + 2 ) * ChipSize, y * ChipSize - ChipSize,
		9 * ChipSize, 4 * 4 * ChipSize, ChipSize, ChipSize );
}

//�v���C���Ԃ̕`��
void Draw_Endless_PlayTime( int timer, int EndTime )
{
	if( EndTime < 0 )
	{
		int j = 0;
		for( int n = 100, i = 0; n >= 1; n /= 10, i ++ )
		{
			if( ( timer - StartTime ) / 60 / n - j <= 0 &&
				j == 0 )
			{
				//�`�悵�Ȃ�
			}
			else
			{
				MikanDraw->DrawTextureScaling( 3, ( 2 + BlockWid + 1 + 4 / 2 ) * ChipSize + i * 10 * 3, 1,
					8 * ( ( timer - StartTime ) / 60 / n - j ), 33, 8, 16, 3 );
				j += ( ( timer - StartTime ) / 60 / n + j ) * 10;
			}
		}
		if( j == 0 )
		{
			MikanDraw->DrawTextureScaling( 3, ( 2 + BlockWid + 1 + 4 / 2 ) * ChipSize + 2 * 10 * 3, 1, 0, 33, 8, 16, 3 );
		}
	}
	else
	{
		int j = 0;
		for( int n = 100, i = 0; n >= 1; n /= 10, i ++ )
		{
			if( ( EndTime - StartTime ) / 60 / n - j <= 0 &&
				j == 0 )
			{
				//�`�悵�Ȃ�
			}
			else
			{
				MikanDraw->DrawTextureScaling( 3, ( 2 + BlockWid + 1 + 4 / 2 ) * ChipSize + i * 10 * 3, 1,
					8 * ( ( EndTime - StartTime ) / 60 / n - j ), 33, 8, 16, 3 );
				j += ( ( EndTime - StartTime ) / 60 / n + j ) * 10;
			}
		}
		if( j == 0 )
		{
			MikanDraw->DrawTextureScaling( 3, ( 2 + BlockWid + 1 + 4 / 2 ) * ChipSize + 2 * 10 * 3, 1, 0, 33, 8, 16, 3 );
		}
	}
}

//�X�R�A�Acombo�̕`��
void Draw_Endless_Score( int score, int comboN, int comboT, int comboP, int comboTime, int timer )
{
	//�X�R�A�̕\��
	MikanDraw->Printf( 8, ( 2 + BlockWid + 1 ) * ChipSize, 50 + 20, "%5d", score );
	//�R���{���̃X�R�A�̕\��
	MikanDraw->Printf( 9, 20 + ( 2 + BlockWid + 1 ) * ChipSize, 50 + 20 + 50, "+%d", comboP );

	//combo�\��
	if( comboT >= 0 )
	{
		//���̍ۂ�Y���W�𒲐����Č��h����ǂ�����B
		if( comboT == T_I ||
			comboT == T_J ||
			comboT == T_L ||
			comboT == T_T )
		{
			MikanDraw->DrawTexture( 0, ( 2 + BlockWid + 1 ) * ChipSize, 50 + ( 3 + 1 ) * ChipSize + 50,
				comboT * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
		else if ( comboT == T_S ||
			comboT == T_Z )
		{
			MikanDraw->DrawTexture( 0, ( 2 + BlockWid + 1 ) * ChipSize, 50 + ( 3 + 0 ) * ChipSize + 50,
				comboT * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
		else if ( comboT == T_O )
		{
			MikanDraw->DrawTexture( 0, ( 2 + BlockWid + 0 ) * ChipSize, 50 + ( 3 + 0 ) * ChipSize + 50,
				comboT * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
	}
	//�R���{���̕`��
	if( comboN > 0 )
	{
		MikanDraw->Printf( 9, ( 2 + BlockWid + 1 + 4 ) * ChipSize, 50 + 50 + 20 + 50, "�~%d", comboN );
	}

	//�c��R���{���Ԃ��Q�[�W�ŕ\��
	MikanDraw->DrawBox( ( 2 + BlockWid ) * ChipSize + ( ChipSize / 2 ) + 25 - 5, 50 + 50 + 20 + 50 + 20 + 50 - 5, 150 + 10, 10 + 10, 0xFF000000 );
	MikanDraw->DrawBox( ( 2 + BlockWid ) * ChipSize + ( ChipSize / 2 ) + 25, 50 + 50 + 20 + 50 + 20 + 50, 150, 10, 0xFFFF0000 );
	if( timer - comboTime < ChainTime &&
		comboTime != 0 )
	{
		MikanDraw->DrawBox( ( 2 + BlockWid ) * ChipSize + ( ChipSize / 2 ) + 25, 50 + 50 + 20 + 50 + 20 + 50, 150 - ( timer - comboTime ) * 150 / ChainTime, 10, 0xFFFFFF00 );
	}
}

//���j���[��ʂ̕`��
void Draw_Endless_Menu( int selection )
{
	MikanDraw->DrawBox( ( 2 + 1 ) * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0x7F000000 );


	MikanDraw->Printf( 3, ( BlockWid * ChipSize - 4 * 50 ) / 2 + 2 * ChipSize, 60, "���j���[" );

	if( selection == 0 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 6 * 25 ) / 2 + 2 * ChipSize, 250 - 10 / 2, "�Q�[���ɖ߂�" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 6 * 20 ) / 2 + 2 * ChipSize, 250, "�Q�[���ɖ߂�" );
	}
	if( selection == 1 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 7 * 25 ) / 2 + 2 * ChipSize, 300 - 10 / 2, "�^�C�g���ɖ߂�" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 7 * 20 ) / 2 + 2 * ChipSize, 300, "�^�C�g���ɖ߂�" );
	}
}

//�Q�[���I�[�o�[
void Draw_Endless_End( int timer, int EndTime, int score, int HighScore, bool menu )
{
	if( timer - EndTime < 100 )
	{
		MikanDraw->Printf( 9, ( BlockWid * ChipSize - 4 * 50 / 2 ) / 2 + 2 * ChipSize, timer - EndTime - 100, "Game\nOver" );
	}
	else if( menu == true )
	{
		MikanDraw->DrawBox( ( 2 + 1 ) * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0xFFC0C0C0 );

		MikanDraw->Printf( 9, ( BlockWid * ChipSize - 4 * 50 / 2 ) / 2 + 2 * ChipSize, 0, "Game\nOver" );

		MikanDraw->Printf( 11, ( BlockWid * ChipSize - 14 * 25 / 2 ) / 2 + 2 * ChipSize, 150, "PlayTime = %3d", ( EndTime - StartTime ) / 60 );
		MikanDraw->Printf( 10, ( BlockWid * ChipSize - 14 * 25 / 2 ) / 2 + 2 * ChipSize, 175, "Scoer = %5d", score );
		MikanDraw->Printf( 10, ( BlockWid * ChipSize - 14 * 25 / 2 ) / 2 + 2 * ChipSize, 200, "High Scoer\n      = %5d", HighScore );

		MikanDraw->Printf( 11, ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2 + 2 * ChipSize, 275, "Push \"Z\" key to\nlook blocks." );
		MikanDraw->Printf( 10, ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2 + 2 * ChipSize, 325, "Push \"X\" key to\nback to title." );
		//MikanDraw->Printf( 10, ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2 + 2 * ChipSize, 325, "Push \"X\" key to\nexit from game." );
	}
}


//�ȉ��A�o�g�����[�h�̏���--------------------------------------
//�g�̕`��
void Draw_Battle_BlockBack()
{
	MikanDraw->DrawBox( BlockWid * ChipSize, 0, 8 * ChipSize, 50, 0xFF000000 );

	MikanDraw->DrawBox( 0, ( -1 ) * ChipSize, BlockWid * ChipSize, BlockHei * ChipSize, 0xFFFF0000 );
	MikanDraw->DrawBox( 1 * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0xFFFFFFFF );

	MikanDraw->DrawBox( BlockWid * ChipSize, 50, 8 * ChipSize, 175, 0xFFEF8F9C );
	MikanDraw->DrawBox( BlockWid * ChipSize, 50 + 175 - 2, 8 * ChipSize, 2, 0xFF000000 );
	MikanDraw->DrawBox( 0, ( BlockHei - 1 ) * ChipSize, BlockWid * ChipSize, HEIGHT - ( BlockHei - 1 ) * ChipSize, 0xFFEF8F9C );


	MikanDraw->DrawBox( SecondX, ( -1 ) * ChipSize, BlockWid * ChipSize, BlockHei * ChipSize, 0xFF0000FF );
	MikanDraw->DrawBox( SecondX + 1 * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0xFFFFFFFF );

	MikanDraw->DrawBox( BlockWid * ChipSize, 50 + 175, 8 * ChipSize, 175, 0xFF00FFFF );
	MikanDraw->DrawBox( BlockWid * ChipSize, 50 + 175 + 175 - 2, 8 * ChipSize, 2, 0xFF000000 );
	MikanDraw->DrawBox( SecondX, ( BlockHei - 1 ) * ChipSize, BlockWid * ChipSize, HEIGHT - ( BlockHei - 1 ) * ChipSize, 0xFF00FFFF );

	//�G��\���@���ӁI
	MikanDraw->DrawTexture( 2, BlockWid * ChipSize, HEIGHT - 80, 0, 0, 160, 80 );
}

//�u���b�N�̕`��֐�
void Draw_Battle_Block( int block[ BlockHei ][ BlockWid ], int block2[ BlockHei ][ BlockWid ] )
{
	//���j���[���J���Ă���Ԃ̓u���b�N��`�悵�Ȃ��B
	for( int i = 0; i < BlockHei; i ++ )
	{
		for( int j = 0; j < BlockWid; j ++ )
		{
			if( block[ i ][ j ] == 1 )
			{
				MikanDraw->DrawTexture( 0, j * ChipSize, ( i - 1 ) * ChipSize,
					0 * ChipSize, 4 * 4 * ChipSize, ChipSize, ChipSize );
			}
			if( block[ i ][ j ] == 2 )
			{
				MikanDraw->DrawTexture( 0, j * ChipSize, ( i - 1 ) * ChipSize,
					8 * ChipSize, 4 * 4 * ChipSize, ChipSize, ChipSize );
			}

			if( block2[ i ][ j ] == 1 )
			{
				MikanDraw->DrawTexture( 0, SecondX + j * ChipSize, ( i - 1 ) * ChipSize,
					0 * ChipSize, 4 * 4 * ChipSize, ChipSize, ChipSize );
			}
			if( block2[ i ][ j ] == 2 )
			{
				MikanDraw->DrawTexture( 0, SecondX + j * ChipSize, ( i - 1 ) * ChipSize,
					8 * ChipSize, 4 * 4 * ChipSize, ChipSize, ChipSize );
			}
		}
	}
}

//���������e�g���~�m�̕`��֐�
void Draw_Battle_Tetrimino( struct tetrimino tet, struct tetrimino tet2 )
{
	for( int i = 0; i < TetriMax; i ++ )
	{
		MikanDraw->DrawTexture( 0, ( tet.x[ i ] - 1 ) * ChipSize, ( tet.y[ i ] - 1 - 1 ) * ChipSize,
			tet.t[ i ] * 4 * ChipSize, tet.dir[ i ] * 4 * ChipSize, 4 * ChipSize, 4 * ChipSize );
		MikanDraw->DrawTexture( 0, SecondX + ( tet2.x[ i ] - 1 ) * ChipSize, ( tet2.y[ i ] - 1 - 1 ) * ChipSize,
			tet2.t[ i ] * 4 * ChipSize, tet2.dir[ i ] * 4 * ChipSize, 4 * ChipSize, 4 * ChipSize );
	}
}

//�J�[�\���̕`��֐�
void Draw_Battle_Cursor( int x, int y, int x2, int y2, bool t, bool t2, int choice, int choice2, int direction, int direction2 )
{
	if( t == true )
	{
		MikanDraw->SetAlpha( 0, 127 );

		MikanDraw->DrawTexture( 0, ( x - 1) * ChipSize, ( y - 1 - 1 ) * ChipSize,
			choice * 4 * ChipSize, direction * 4 * ChipSize, 4 * ChipSize, 4 * ChipSize );

		MikanDraw->SetAlpha( 0, 255 );
	}
	else
	{
		MikanDraw->DrawTexture( 0, x * ChipSize, y * ChipSize - ChipSize,
			9 * ChipSize, 4 * 4 * ChipSize, ChipSize, ChipSize );
	}

	if( t2 == true )
	{
		MikanDraw->SetAlpha( 0, 127 );

		MikanDraw->DrawTexture( 0, ( x2 - 1) * ChipSize + SecondX, ( y2 - 1 - 1 ) * ChipSize,
			choice2 * 4 * ChipSize, direction2 * 4 * ChipSize, 4 * ChipSize, 4 * ChipSize );

		MikanDraw->SetAlpha( 0, 255 );
	}
	else
	{
		MikanDraw->DrawTexture( 0, SecondX + x2 * ChipSize, y2 * ChipSize - ChipSize,
			9 * ChipSize, 4 * 4 * ChipSize, ChipSize, ChipSize );
	}
}

//�v���C���Ԃ̕`��
void Draw_Battle_PlayTime( int timer, int EndTime )
{
	if( EndTime < 0 )
	{
		int j = 0;
		for( int n = 100, i = 0; n >= 1; n /= 10, i ++ )
		{
			if( ( timer - StartTime ) / 60 / n - j <= 0 &&
				j == 0 )
			{
				//�`�悵�Ȃ�
			}
			else
			{
				MikanDraw->DrawTextureScaling( 3, ( WIDHT - 3 * 10 * 3 ) / 2 + i * 10 * 3, 1,
					8 * ( ( timer - StartTime ) / 60 / n - j ), 33, 8, 16, 3 );
				j += ( ( timer - StartTime ) / 60 / n + j ) * 10;
			}
		}
		if( j == 0 )
		{
			MikanDraw->DrawTextureScaling( 3, ( WIDHT - 3 * 10 * 3 ) / 2 + 2 * 10 * 3, 1, 0, 33, 8, 16, 3 );
		}
	}
	else
	{
		int j = 0;
		for( int n = 100, i = 0; n >= 1; n /= 10, i ++ )
		{
			if( ( EndTime - StartTime ) / 60 / n - j <= 0 &&
				j == 0 )
			{
				//�`�悵�Ȃ�
			}
			else
			{
				MikanDraw->DrawTextureScaling( 3, ( WIDHT - 3 * 10 * 3 ) / 2 + i * 10 * 3, 1,
					8 * ( ( EndTime - StartTime ) / 60 / n - j ), 33, 8, 16, 3 );
				j += ( ( EndTime - StartTime ) / 60 / n + j ) * 10;
			}
		}
		if( j == 0 )
		{
			MikanDraw->DrawTextureScaling( 3, ( WIDHT - 3 * 10 * 3 ) / 2 + 2 * 10 * 3, 1, 0, 33, 8, 16, 3 );
		}
	}
}

//�X�R�A�Acombo�̕`��
void Draw_Battle_Score( int timer, int score, int score2, int comboN, int comboN2, int comboT, int comboT2,
	int comboP, int comboP2, int comboTime, int comboTime2 )
{
	//�X�R�A�̕\��
	MikanDraw->Printf( 3, ChipSize, ( BlockHei - 1 ) * ChipSize + 10, "%d", score );
	MikanDraw->Printf( 3, SecondX + ChipSize, ( BlockHei - 1 ) * ChipSize + 10, "%d", score2 );

	//�R���{�X�R�A�̕\��
	MikanDraw->Printf( 8, ( BlockWid + 1 ) * ChipSize, 50 + 10, "+%d", comboP );
	MikanDraw->Printf( 8, ( BlockWid + 1 ) * ChipSize, 50 + 175 + 10, "+%d", comboP2 );


	//combo�\��
	if( comboT >= 0 )
	{
		//���̍ۂ�Y���W�𒲐����Č��h����ǂ�����B
		if( comboT == T_I ||
			comboT == T_J ||
			comboT == T_L ||
			comboT == T_T )
		{
			MikanDraw->DrawTexture( 0, ( 1 + BlockWid + 1 ) * ChipSize, 50 + 50 + 1 * ChipSize - 10,
				comboT * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
		else if ( comboT == T_S ||
			comboT == T_Z )
		{
			MikanDraw->DrawTexture( 0, ( 1 + BlockWid + 1 ) * ChipSize, 50 + 50 + 0 * ChipSize - 10,
				comboT * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
		else if ( comboT == T_O )
		{
			MikanDraw->DrawTexture( 0, ( 1 + BlockWid + 1 ) * ChipSize, 50 + 50 + 0 * ChipSize - 10,
				comboT * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
	}
	//�R���{���̕`��
	if( comboN > 0 )
	{
		MikanDraw->Printf( 9, ( 1 + BlockWid + 1 ) * ChipSize, 50 + 10 + 50 + 2 * ChipSize, "�~%d", comboN );
	}
	//�c��R���{���Ԃ��Q�[�W�ŕ\��
	MikanDraw->DrawBox( BlockWid * ChipSize + 30 - 5, 50 * 4 + 5 - 5, 100 + 10, 10 + 10, 0xFF000000 );
	MikanDraw->DrawBox( BlockWid * ChipSize + 30, 50 * 4 + 5, 100, 10, 0xFFFF0000 );
	if( timer - comboTime < ChainTime &&
		comboTime != 0 )
	{
		MikanDraw->DrawBox( BlockWid * ChipSize + 30, 50 * 4 + 5, 100 - ( timer - comboTime ) * 100 / ChainTime, 10, 0xFFFFFF00 );
	}

	if( comboT2 >= 0 )
	{
		//���̍ۂ�Y���W�𒲐����Č��h����ǂ�����B
		if( comboT2 == T_I ||
			comboT2 == T_J ||
			comboT2 == T_L ||
			comboT2 == T_T )
		{
			MikanDraw->DrawTexture( 0, ( 1 + BlockWid + 1 ) * ChipSize, 50 + 175 + 50 + 1 * ChipSize - 10, comboT2 * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
		else if ( comboT2 == T_S ||
			comboT2 == T_Z )
		{
			MikanDraw->DrawTexture( 0, ( 1 + BlockWid + 1 ) * ChipSize, 50 + 175 + 50 + 0 * ChipSize - 10, comboT2 * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
		else if ( comboT2 == T_O )
		{
			MikanDraw->DrawTexture( 0, ( 1 + BlockWid + 1 ) * ChipSize, 50 + 175 + 50 + 0 * ChipSize - 10, comboT2 * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
	}
	//�R���{���̕`��
	if( comboN2 > 0 )
	{
		MikanDraw->Printf( 9, ( 1 + BlockWid + 1 ) * ChipSize, 50 + 175 + 10 + 50 + 2 * ChipSize, "�~%d", comboN2 );
	}
	//�c��R���{���Ԃ��Q�[�W�ŕ\��
	MikanDraw->DrawBox( BlockWid * ChipSize + 30 - 5, 175 + 50 * 4 + 5 - 5, 100 + 10, 10 + 10, 0xFF000000 );
	MikanDraw->DrawBox( BlockWid * ChipSize + 30, 175 + 50 * 4 + 5, 100, 10, 0xFFFF0000 );
	if( timer - comboTime2 < ChainTime &&
		comboTime2 != 0 )
	{
		MikanDraw->DrawBox( BlockWid * ChipSize + 30, 175 + 50 * 4 + 5, 100 - ( timer - comboTime2 ) * 100 / ChainTime, 10, 0xFFFFFF00 );
	}
}

//���j���[��ʂ̕`��
void Draw_Battle_Menu( int selection, int selection2 )
{
	MikanDraw->DrawBox( 1 * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0x7F000000 );
	MikanDraw->DrawBox( SecondX + 1 * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0x7F000000 );

	MikanDraw->Printf( 3, ( BlockWid * ChipSize - 4 * 50 ) / 2, 60, "���j���[" );
	MikanDraw->Printf( 3, SecondX + ( BlockWid * ChipSize - 4 * 50 ) / 2, 60, "���j���[" );

	if( selection == 0 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 6 * 25 ) / 2, 250 - 10 / 2, "�Q�[���ɖ߂�" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 6 * 20 ) / 2, 250, "�Q�[���ɖ߂�" );
	}
	if( selection2 == 0 )
	{
		MikanDraw->Printf( 6, SecondX + ( BlockWid * ChipSize - 6 * 25 ) / 2, 250 - 10 / 2, "�Q�[���ɖ߂�" );
	}
	else
	{
		MikanDraw->Printf( 7, SecondX + ( BlockWid * ChipSize - 6 * 20 ) / 2, 250, "�Q�[���ɖ߂�" );
	}

	if( selection == 1 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 7 * 25 ) / 2, 300 - 10 / 2, "�^�C�g���ɖ߂�" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 7 * 20 ) / 2, 300, "�^�C�g���ɖ߂�" );
	}
	if( selection2 == 1 )
	{
		MikanDraw->Printf( 6, SecondX + ( BlockWid * ChipSize - 7 * 25 ) / 2, 300 - 10 / 2, "�^�C�g���ɖ߂�" );
	}
	else
	{
		MikanDraw->Printf( 7, SecondX + ( BlockWid * ChipSize - 7 * 20 ) / 2, 300, "�^�C�g���ɖ߂�" );
	}
}

//�Q�[���I�[�o�[
void Draw_Battle_End( int timer, int EndTime, int score, int score2, int HighScore, bool menu, int winner )
{
	if( timer - EndTime < 100 )
	{
		if( winner == 0 )
		{
			MikanDraw->Printf( 9, ( BlockWid * ChipSize - 5 * 50 / 2 ) / 2, timer - EndTime - 2 * 50 + 25, "Drawn" );
			MikanDraw->Printf( 9, SecondX + ( BlockWid * ChipSize - 5 * 50 / 2 ) / 2, timer - EndTime - 2 * 50 + 25, "Drawn" );
		}
		else if( winner == 1 )
		{
			MikanDraw->Printf( 9, ( BlockWid * ChipSize - 3 * 50 / 2 ) / 2, timer - EndTime - 2 * 50 + 25, "Win" );
			MikanDraw->Printf( 9, SecondX + ( BlockWid * ChipSize - 4 * 50 / 2 ) / 2, timer - EndTime - 2 * 50 + 25, "Lose" );
		}
		else
		{
			MikanDraw->Printf( 9, ( BlockWid * ChipSize - 4 * 50 / 2 ) / 2, timer - EndTime - 2 * 50 + 25, "Lose" );
			MikanDraw->Printf( 9, SecondX + ( BlockWid * ChipSize - 3 * 50 / 2 ) / 2, timer - EndTime - 2 * 50 + 25, "Win" );
		}
	}
	else if( menu == true )
	{
		MikanDraw->DrawBox( 1 * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0xFFC0C0C0 );
		MikanDraw->DrawBox( SecondX + 1 * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0xFFC0C0C0 );

		if( winner == 0 )
		{
			MikanDraw->Printf( 9, ( BlockWid * ChipSize - 5 * 50 / 2 ) / 2, 25, "Drawn" );
			MikanDraw->Printf( 9, SecondX + ( BlockWid * ChipSize - 5 * 50 / 2 ) / 2, 25, "Drawn" );
		}
		else if( winner == 1 )
		{
			MikanDraw->Printf( 9, ( BlockWid * ChipSize - 3 * 50 / 2 ) / 2, 25, "Win" );
			MikanDraw->Printf( 9, SecondX + ( BlockWid * ChipSize - 4 * 50 / 2 ) / 2, 25, "Lose" );
		}
		else
		{
			MikanDraw->Printf( 9, ( BlockWid * ChipSize - 4 * 50 / 2 ) / 2, 25, "Lose" );
			MikanDraw->Printf( 9, SecondX + ( BlockWid * ChipSize - 3 * 50 / 2 ) / 2, 25, "Win" );
		}

		MikanDraw->Printf( 11, ( BlockWid * ChipSize - 14 * 25 / 2 ) / 2, 150, "PlayTime = %3d", ( EndTime - StartTime ) / 60 );
		MikanDraw->Printf( 11, SecondX + ( BlockWid * ChipSize - 14 * 25 / 2 ) / 2, 150, "PlayTime = %3d", ( EndTime - StartTime ) / 60 );
		MikanDraw->Printf( 10, ( BlockWid * ChipSize - 14 * 25 / 2 ) / 2, 175, "Scoer = %5d", score );
		MikanDraw->Printf( 10, SecondX + ( BlockWid * ChipSize - 14 * 25 / 2 ) / 2, 175, "Scoer = %5d", score2 );
		MikanDraw->Printf( 10, ( BlockWid * ChipSize - 14 * 25 / 2 ) / 2, 200, "High Scoer\n      = %5d", HighScore );
		MikanDraw->Printf( 10, SecondX + ( BlockWid * ChipSize - 14 * 25 / 2 ) / 2, 200, "High Scoer\n      = %5d", HighScore );

		MikanDraw->Printf( 11, ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2, 275, "Push \"Z\" key to\nlook blocks." );
		MikanDraw->Printf( 11, SecondX + ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2, 275, "Push \"Z\" key to\nlook blocks." );
		MikanDraw->Printf( 10, ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2, 325, "Push \"X\" key to\nback to title." );
		MikanDraw->Printf( 10, SecondX + ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2, 325, "Push \"X\" key to\nback to title." );
		//MikanDraw->Printf( 10, ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2, 325, "Push \"X\" key to\nexit from game." );
		//MikanDraw->Printf( 10, SecondX + ( BlockWid * ChipSize - 15 * 25 / 2 ) / 2, 325, "Push \"X\" key to\nexit from game." );
	}
}


//�G�f�B�^
void Draw_Editor_Tetrinimos( int UsedTet[ 7 ], int choice )
{
	for( int i = 0; i < 7; i ++ )
	{
		//�I�𒆂̃e�g���~�m�̌��ɔ�������`�悷��B
		if( choice == i )
		{
			MikanDraw->DrawBox( ( 2 + BlockWid ) * ChipSize + ( ChipSize / 2 ), i * 3 * ChipSize + ( ChipSize / 2 ), 10 * ChipSize, 3 * ChipSize, 0xFFFFFFFF );
		}

		//���̍ۂ�Y���W�𒲐����Č��h����ǂ�����B&
		if( i == T_I ||
			i == T_J ||
			i == T_L ||
			i == T_T )
		{
			MikanDraw->DrawTexture( 0, ( 2 + BlockWid + 1 ) * ChipSize, ( i * 3 + 1 ) * ChipSize, i * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
		else if ( i == T_S ||
				  i == T_Z )
		{
			MikanDraw->DrawTexture( 0, ( 2 + BlockWid + 1 ) * ChipSize, ( i * 3 + 0 ) * ChipSize, i * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}
		else if ( i == T_O )
		{
			MikanDraw->DrawTexture( 0, ( 2 + BlockWid + 0 ) * ChipSize, ( i * 3 + 0 ) * ChipSize, i * 4 * ChipSize, 0, 4 * ChipSize, 4 * ChipSize );
		}

		MikanDraw->Printf( 4, ( 2 + BlockWid + 1 + 4 + 1 ) * ChipSize,( i * 3 + 1 ) * ChipSize + ( 2 * ChipSize - 30 ) / 2,
				"%d", UsedTet[ i ] );
	}

	//�Z�[�u�E���[�h���ɒm�点��B
		//�Z�[�u�I�I�I
	if( MikanInput->GetKeyNum( K_A ) > 60 ||
		MikanInput->GetPadNum( 0, PAD_D ) > 60 )
	{
		MikanDraw->Printf( 0, 0, 0, "Saved!" );
	}

	//���[�h�I�I�I�I�I
	if( MikanInput->GetKeyNum( K_S ) > 60 ||
		MikanInput->GetPadNum( 0, PAD_C ) > 60 )
	{
		MikanDraw->Printf( 0, 0, 0, "Loaded!" );
	}
}

void Draw_Editor_Menu( int selection )
{
	MikanDraw->DrawBox( ( 2 + 1 ) * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0x7F000000 );


	MikanDraw->Printf( 3, ( BlockWid * ChipSize - 4 * 50 ) / 2 + 2 * ChipSize, 60, "���j���[" );

	if( selection == 0 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 6 * 25 ) / 2 + 2 * ChipSize, 190 - 10 / 2, "�Q�[���ɖ߂�" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 6 * 20 ) / 2 + 2 * ChipSize, 190, "�Q�[���ɖ߂�" );
	}
	if( selection == 1 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 4 * 25 ) / 2 + 2 * ChipSize, 230 - 10 / 2, "���Z�b�g" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 4 * 20 ) / 2 + 2 * ChipSize, 230, "���Z�b�g" );
	}
	if( selection == 2 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 4 * 25 ) / 2 + 2 * ChipSize, 270 - 10 / 2, "�Z�[�u�I" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 4 * 20 ) / 2 + 2 * ChipSize, 270, "�Z�[�u�I" );
	}
	if( selection == 3 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 4 * 25 ) / 2 + 2 * ChipSize, 310 - 10 / 2, "���[�h�I" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 4 * 20 ) / 2 + 2 * ChipSize, 310, "���[�h�I" );
	}
	if( selection == 4 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 7 * 25 ) / 2 + 2 * ChipSize, 350 - 10 / 2, "�^�C�g���ɖ߂�" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 7 * 20 ) / 2 + 2 * ChipSize, 350, "�^�C�g���ɖ߂�" );
	}
}
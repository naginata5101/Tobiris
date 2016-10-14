#include "main.h"


//�v���O�����N������1�x�������s
//�V�X�e���ݒ�Ȃǂ��s��
void SystemInit( void )
{
	MikanWindow->SetWindowName( "�g�r���X" );
	MikanWindow->SetWindowIcon( "GAME_ICON" );

	//�}�E�X�J�[�\��������
	ShowCursor( 0 );
}

//MainLoop�J�n�O��1�x�������s
//�e�N�X�`���̓ǂݍ��݂Ȃǂ̃Q�[���J�n�O�̏������s��
void UserInit( void )
{
	//���A����A�^�C�g���p
	MikanDraw->CreateFont( 0, "�l�r �S�V�b�N", 100, 0xFFFFFF00 );
	//���A���A�����p
	MikanDraw->CreateFont( 1, "�l�r �S�V�b�N",  30, 0xFFFFFF00 );
	//���A���A���ʕ����p
	MikanDraw->CreateFont( 2, "�l�r �S�V�b�N",  20, 0xFFFFFFFF );
	//���A��A���^�C�g���p
	MikanDraw->CreateFont( 3, "�l�r �S�V�b�N",  50, 0xFFFFFF00 );
	//�A���A�����p
	MikanDraw->CreateFont( 4, "�l�r �S�V�b�N",  30, 0xFF0000FF );
	//�ԁA���A�����p
	MikanDraw->CreateFont( 5, "�l�r �S�V�b�N",  30, 0xFFFF0000 );
	//���A���A���j���[�����p
	MikanDraw->CreateFont( 6, "�l�r �S�V�b�N",  25, 0xFFFFFF00 );
	//���A���A���j���[���ʕ����p
	MikanDraw->CreateFont( 7, "�l�r �S�V�b�N",  20, 0xFFFFFFFF );
	//�A��A�N���A�p
	MikanDraw->CreateFont( 8, "�l�r �S�V�b�N",  50, 0xFF0000FF );
	//�ԁA��A�Q�[���I�[�o�[�p
	MikanDraw->CreateFont( 9, "�l�r �S�V�b�N",  50, 0xFFFF0000 );
	//�A���A�Q�[���I�[�o�[�p
	MikanDraw->CreateFont( 10, "�l�r �S�V�b�N", 25, 0xFF0000FF );
	//�ԁA���A�Q�[���I�[�o�[�p
	MikanDraw->CreateFont( 11, "�l�r �S�V�b�N", 25, 0xFFFF0000 );

	//���A���A�f�o�b�O�p
	MikanDraw->CreateFont( 100, "�l�r �S�V�b�N",  20, 0xFF000000 );


	MikanDraw->CreateTexture( 0, "data/block.png", 0xFFFFFFFF );
	MikanDraw->CreateTexture( 1, "data/riss-bg.png", 0xFF000000 );
	MikanDraw->CreateTexture( 2, "data/riss-bg2.png", 0xFF000000 );
	//����:16*8
	MikanDraw->CreateTexture( 3, "data/riss-rogo.png", 0xFFFFFFFF );

	MikanSound->Load( 0, "data/Tetris_1_2.ogg", true );
	MikanSound->Load( 1, "data/korobutika.ogg", true );
	//���ʉ�
	//�J�[�\���ړ�
	MikanSound->Load( 10, "data/on02.wav", true );
	//�J�[�\���ړ�2
	MikanSound->Load( 11, "data/pon001.wav", true );
	//����
	MikanSound->Load( 12, "data/pi14.wav", true );
	//�L�����Z��
	MikanSound->Load( 13, "data/push14.wav", true );
	//�ˏo
	MikanSound->Load( 14, "data/fall06.wav", true );
	//�u�[
	MikanSound->Load( 15, "data/beep08.wav", true );
	//�N���A�[
	MikanSound->Load( 16, "data/clearatika.ogg", true );
	//fail
	MikanSound->Load( 17, "data/bell14.wav", true );
	//�Q�[���J�n
	MikanSound->Load( 18, "data/whistle00.wav", true );
	//�Q�[���I�[�o�[
	MikanSound->Load( 19, "data/gameoveratika.ogg", true );
	//�u���b�N����o��
	MikanSound->Load( 20, "data/power01_b.wav", true );
	
	srand( ( unsigned ) time ( NULL ) );


	Set_Back( back );
}

//1�b�Ԃ�60����s
//0��Ԃ��Ă���Ԃ͉��x�ł����s�����
int MainLoop( void )
{
	//��ʂ̏�����
	MikanDraw->ClearScreen();
	//�w�i�̕`��
	Draw_BackGround( back );

	switch( mode )
	{
		//-----------------------------------------------------
	case TITLE:
		Move_Title( &selection );
		Choice_Title( block, block2, UsedTet, &tetri, &tetri2, &mode, &selection, &selection2, &choice, &choice2
			, &direction, &direction2, &timer, &cursorX, &cursorX2, &cursorY, &cursorY2, &EndTime, &score, &score2,
			&comboN, &comboN2, &comboT, &comboT2, &comboP, &comboP2, &comboTime, &comboTime2, &winner, &menu );
		Chenge_CursorType( &cursorT, &cursorT2 );

		Draw_Title( selection, cursorT, cursorT2 );

		break;
	case STAGE_SELECT:
		Move_StageSelecte( &selection );
		Choice_StageSelecte( stage, block, stocks, UsedTet, LimitTet, &tetri, &mode, &selection, &timer, &StageNum,
			&cursorX, &cursorY, &choice, &direction, &EndTime, &menu, &timeUP, &clear, &fail );

		Draw_StageSelection( selection );
		Draw_Thumbnail( stage, selection );

		break;
	case EXPLANATION:
		Move_Explanation( &mode, &selection );

		Draw_Explanation( selection );

		break;


		//-----------------------------------------------------
	case PUZZLE_GAME:
		if( EndTime < 0 )
		{
			if( menu == false )
			{
				if( cursorT == true )
				{
					Silhouette_Cursor_Change( 0, &choice, &direction );
					Silhouette_Cursor_Move( 0, &cursorX, &cursorY, choice, direction );

					if( Silhouette_Make_Tetrimino( 0, block, LimitTet, UsedTet, LastBlockX, LastBlockY, &tetri,
						choice, direction, timer, cursorX, cursorY, StageNum, mode ) == true )
					{
						Puzzle_Check_End( block, &fail, &clear, timer, &EndTime );
					}
				}
				else
				{
					DidMove = Pointer_Cursor_Move( 0, block, &cursorX, &cursorY );
					Pointer_Choice_Block( 0, block, cursorX, cursorY, &choice, DidMove );
					DidMove = false;

					if( Pointer_Make_Tetrimino( block, LimitTet, UsedTet, LastBlockX, LastBlockY, &tetri, &choice, mode, StageNum ) == true )
					{
						Puzzle_Check_End( block, &fail, &clear, timer, &EndTime );
					}
				}

				//�Q�[���I������
				Puzzle_TimeUP( timer, &EndTime, &timeUP );
				Puzzle_Move_Tetrimino( &tetri, timer );
			}
			Puzzle_Menu( 0, block, UsedTet, LastBlockX, LastBlockY, &tetri, &mode, &selection, &choice, &menu, cursorT );
		}
		//�Q�[���I�����̏���
		else
		{
			Puzzle_GameOver( 0, &tetri, &mode, timer, EndTime, clear, &menu );
		}

		if( menu == false )
		{
			timer ++;
		}


		Draw_BlockBack();
		if( menu == false )
		{
			Draw_Block( block );
			Draw_Puzzle_Tetrinimos( LimitTet, UsedTet, StageNum, choice, cursorT );
			Draw_Tetrimino( tetri );
		}
		Draw_Limit_Time( timer, EndTime );

		if( EndTime < 0 )
		{
			if( menu == false )
			{
				if( cursorT == true )
				{
					Draw_Silhouette_Cursor( cursorX, cursorY, choice, direction );
				}
				else
				{
					Draw_Pointer_Cursor( cursorX, cursorY );
				}
			}
			else
			{
				Draw_Puzzle_Menu( selection );
			}
		}
		else
		{
			Draw_Puzzle_End( timer, EndTime, menu, timeUP, clear, fail );
		}
		break;


		//-----------------------------------------------------	
	case ENDLESS_GAME:
		if( EndTime < 0 )
		{
			//���ۂɃJ�[�\�������������ۂ��̔��� -> DidMove
			if( menu == false )
			{
				if( timer > StartTime )
				{
					if( cursorT == true )
					{
						Silhouette_Cursor_Change( 0, &choice, &direction );
						Silhouette_Cursor_Move( 0, &cursorX, &cursorY, choice, direction );

						Silhouette_Make_Tetrimino( 0, block, LimitTet, UsedTet, LastBlockX, LastBlockY, &tetri,
							choice, direction, timer, cursorX, cursorY, StageNum, mode );
					}
					else
					{
						DidMove = Pointer_Cursor_Move( 0, block, &cursorX, &cursorY );
						Pointer_Choice_Block( 0, block, cursorX, cursorY, &choice, DidMove );
						DidMove = false;

						Pointer_Make_Tetrimino( block, LimitTet, UsedTet, LastBlockX, LastBlockY, &tetri, &choice, mode, StageNum );
					}

					Endless_Move_Tetrimino( block, &tetri, timer );
					Endless_Count_Score( &tetri, &score, &comboN, &comboT, &comboP, &comboTime, timer );
				}
				Endless_Move_Blocks( 0, block, timer, &SlideTime, &EndTime, &cursorX, &cursorY, &score, &winner );
			}
			if( timer > StartTime )
			{
				Endless_Menu( 0, &mode, &selection, &menu );
			}
		}
		else
		{
			Update_HighScore( true, &score, &HighScore, timer, EndTime );
			Endless_GameOver( 0, &mode, &score, &comboP, &comboTime, timer, EndTime, &menu );
		}

		if( menu == false )
		{
			timer ++;
		}


		Draw_BlockBack();
		if( menu == false )
		{
			Draw_Block( block );
			Draw_Tetrimino( tetri );

			if( cursorT == false )
			{
				Draw_Pointer_Cursor( cursorX, cursorY );
			}
			else
			{
				Draw_Silhouette_Cursor( cursorX, cursorY, choice, direction );
			}
		}
		else
		{
			Draw_Endless_Menu( selection );
		}

		if( timer > StartTime )
		{
			Draw_Endless_PlayTime( timer, EndTime );
			Draw_Endless_Score( score, comboN, comboT, comboP, comboTime, timer );
		}

		if( EndTime >= 0 )
		{
			Draw_Endless_End( timer, EndTime, score, HighScore, menu );
		}
		break;

		//-----------------------------------------------------
	case BATTLE_GAME:
		if( EndTime < 0 )
		{
			//���ۂɃJ�[�\�������������ۂ��̔��� -> DidMove
			if( menu == false )
			{
				if( timer > StartTime )
				{
					if( cursorT == true )
					{
						Silhouette_Cursor_Change( 0, &choice, &direction );
						Silhouette_Cursor_Move( 0, &cursorX, &cursorY, choice, direction );

						Silhouette_Make_Tetrimino( 0, block, LimitTet, UsedTet, LastBlockX, LastBlockY, &tetri,
							choice, direction, timer, cursorX, cursorY, StageNum, mode );
					}
					else
					{
						DidMove = Pointer_Cursor_Move( 0, block, &cursorX, &cursorY );
						Pointer_Choice_Block( 0, block, cursorX, cursorY, &choice, DidMove );
						DidMove = false;

						Pointer_Make_Tetrimino( block, LimitTet, UsedTet, LastBlockX, LastBlockY, &tetri, &choice, mode, StageNum );
					}

					if( cursorT2 == true )
					{
						Silhouette_Cursor_Change( 1, &choice2, &direction2 );
						Silhouette_Cursor_Move( 1, &cursorX2, &cursorY2, choice2, direction2 );

						Silhouette_Make_Tetrimino( 1, block2, LimitTet, UsedTet, LastBlockX, LastBlockY, &tetri2,
							choice2, direction2, timer, cursorX2, cursorY2, StageNum, mode );
					}
					else
					{
						DidMove2 = Pointer_Cursor_Move( 1, block2, &cursorX2, &cursorY2 );
						Pointer_Choice_Block( 1, block2, cursorX2, cursorY2, &choice2, DidMove2 );
						DidMove2 = false;

						Pointer_Make_Tetrimino( block2, LimitTet, UsedTet, LastBlockX, LastBlockY, &tetri2, &choice2, mode, StageNum );
					}

					Endless_Move_Tetrimino( block , &tetri , timer );
					Endless_Move_Tetrimino( block2, &tetri2, timer );
					Battle_Count_Score( &tetri , &score , &comboN , &comboT , &comboP , &comboTime , timer, block2, &cursorY2 );
					Battle_Count_Score( &tetri2, &score2, &comboN2, &comboT2, &comboP2, &comboTime2, timer, block , &cursorY );
				}
				Endless_Move_Blocks( 0, block , timer, &SlideTime , &EndTime, &cursorX , &cursorY , &score , &winner );
				Endless_Move_Blocks( 1, block2, timer, &SlideTime2, &EndTime, &cursorX2, &cursorY2, &score2, &winner );
			}
			if( timer > StartTime )
			{
				Endless_Menu( 0, &mode, &selection , &menu );
				Endless_Menu( 1, &mode, &selection2, &menu );
			}
		}
		else
		{
			Update_HighScore( false, &score , &HighScore, timer, EndTime );
			Update_HighScore( false, &score2, &HighScore, timer, EndTime );

			Endless_GameOver( 0, &mode, &score , &comboP , &comboTime , timer, EndTime, &menu );
			Endless_GameOver( 1, &mode, &score2, &comboP2, &comboTime2, timer, EndTime, &menu );
		}

		if( menu == false )
		{
			timer ++;
		}


		Draw_Battle_BlockBack();
		if( menu == false )
		{
			Draw_Battle_Block( block, block2 );
			Draw_Battle_Tetrimino( tetri, tetri2 );
			Draw_Battle_Cursor( cursorX, cursorY, cursorX2, cursorY2, cursorT, cursorT2, choice, choice2, direction, direction2 );
		}
		else
		{
			Draw_Battle_Menu( selection, selection2 );
		}

		if( timer > StartTime )
		{
			Draw_Battle_PlayTime( timer, EndTime );
			Draw_Battle_Score( timer, score, score2, comboN, comboN2, comboT, comboT2, comboP, comboP2, comboTime, comboTime2 );
		}

		if( EndTime >= 0 )
		{
			Draw_Battle_End( timer, EndTime, score, score2, HighScore, menu, winner );
		}
		break;


		//-----------------------------------------------------
	case EDITOR:
		if( menu == false )
		{
			Silhouette_Cursor_Change( 0, &choice, &direction );
			Silhouette_Cursor_Move( 0, &cursorX, &cursorY, choice, direction );
		}
		Editor_Make_Tetrimino( block, UsedTet, &tetri, &mode, choice, &selection, direction, cursorX, cursorY, &menu );

		Draw_BlockBack();
		if( menu == false )
		{
			Draw_Block( block );
			Draw_Tetrimino( tetri );
			Draw_Silhouette_Cursor( cursorX, cursorY, choice, direction );
			Draw_Editor_Tetrinimos( UsedTet, choice );
		}
		else
		{
			Draw_Editor_Menu( selection );
		}

		break;
	
	
	default:
		mode = TITLE;
	}



	if( MikanInput->GetKeyNum( K_ESC ) > 0 ||
		mode < 0 )
	{
		return 1;
	}

	//MikanDraw->Printf( 100, 0,0,"%d", timer );

  return 0;
}

//MainLoop�I�����1�x�������s
//��Еt���Ȃǂ��s��
void CleanUp( void )
{
}
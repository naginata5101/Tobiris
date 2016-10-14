#include "common.h"


//以下、共通処理====================================================
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


//以下、タイトル画面の処理==========================================
void Draw_Title( int selection, bool cursorT, bool cursorT2 )
{
	MikanDraw->DrawBox( ( WIDHT - 128 * 4 ) / 2, 0, 128 * 4, 32 * 4 + 20 * 2, 0xFF000000 );
	MikanDraw->DrawBox( ( WIDHT - 30 * 8 ) / 2, 32 * 4 + 20 * 2, 30 * 8, HEIGHT - 32 * 4 - 20 * 2, 0xFF000000 );

	MikanDraw->DrawBox( 0, 0, 50, HEIGHT, 0xFFFFFFFF );
	MikanDraw->DrawBox( WIDHT - 50, 0, 50, HEIGHT, 0xFFFFFFFF );

	MikanDraw->DrawTextureScaling( 3, ( WIDHT - 128 * 4 ) / 2, 20, 0, 0, 128, 32, 4 );

	if( selection == 0 )
	{
		MikanDraw->Printf( 1, ( WIDHT - 6 * 30 ) / 2, 200 - 10 / 2, "パズルモード" );
	}
	else
	{
		MikanDraw->Printf( 2, ( WIDHT - 6 * 20 ) / 2, 200, "パズルモード" );
	}
	if( selection == 1 )
	{
		MikanDraw->Printf( 1, ( WIDHT - 8 * 30 ) / 2, 250 - 10 / 2, "エンドレスモード" );
	}
	else
	{
		MikanDraw->Printf( 2, ( WIDHT - 8 * 20 ) / 2, 250, "エンドレスモード" );
	}
	if( selection == 2 )
	{
		MikanDraw->Printf( 1, ( WIDHT - 6 * 30 ) / 2, 300 - 10 / 2, "バトルモード" );
	}
	else
	{
		MikanDraw->Printf( 2, ( WIDHT - 6 * 20 ) / 2, 300, "バトルモード" );
	}
	if( selection == 3 )
	{
		MikanDraw->Printf( 1, ( WIDHT - 7 * 30 ) / 2, 350 - 10 / 2, "エディタモード" );
	}
	else
	{
		MikanDraw->Printf( 2, ( WIDHT - 7 * 20 ) / 2, 350, "エディタモード" );
	}
	if( selection == 4 )
	{
		MikanDraw->Printf( 1, ( WIDHT - 5 * 30 ) / 2, 400 - 10 / 2, "ゲーム説明" );
	}
	else
	{
		MikanDraw->Printf( 2, ( WIDHT - 5 * 20 ) / 2, 400, "ゲーム説明" );
	}
	if( selection == 5 )
	{
		MikanDraw->Printf( 1, ( WIDHT - 5 * 30 ) / 2, 450 - 10 / 2, "ゲーム終了" );
	}
	else
	{
		MikanDraw->Printf( 2, ( WIDHT - 5 * 20 ) / 2, 450, "ゲーム終了" );
	}

	//カーソルタイプの描画
	if( cursorT == true )
	{
		MikanDraw->Printf( 8, 0, 0, "1P\nシ\nル\nエ\nッ\nト\nモ\n｜\nド" );
	}
	else
	{
		MikanDraw->Printf( 9, 0, 0, "1P\nポ\nイ\nン\nタ\n｜\nモ\n｜\nド" );
	}
	if( cursorT2 == true )
	{
		MikanDraw->Printf( 8, WIDHT - 50, 0, "2P\nシ\nル\nエ\nッ\nト\nモ\n｜\nド" );
	}
	else
	{
		MikanDraw->Printf( 9, WIDHT - 50, 0, "2P\nポ\nイ\nン\nタ\n｜\nモ\n｜\nド" );
	}
}

void Draw_StageSelection( int selection )
{
	MikanDraw->DrawBox( ( WIDHT - 8 * 50 ) / 2, 40, 8 * 50, 50, 0xFF000000 );
	MikanDraw->DrawBox( 60 - ( 10 / 2 * 3 ), 150 - ( 10 / 2 ), 120 * 2 + ( 30 / 2 * 8 ), 50 * 4 + 30, 0xFF000000 );

	MikanDraw->Printf( 3, ( WIDHT - 8 * 50 ) / 2, 40, "ステージセレクト" );

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
			"【ゲーム概要】\n"
			"　本作は「飛ばし物系パズルゲーム」です。\n"
			"　に溜まっているテトリスブロックに\n"
			"　各種テトリミノ（テトリスで扱う\n"
			"　4つのブロックが繋がった奴）に当てはめ、\n"
			"　画面上部に飛ばしてしまって下さい。" );
	}
	else if( selection == 1 )
	{
		MikanDraw->Printf( 6, 0, 0,
			"【モード説明】\n"
			"・パズルモード\n"
			"　右に表示される制限内でテトリミノを作り、\n"
			"　制限時間内に全てのブロックを飛ばして下さい。\n"
			"　ステージによって、テトリミノの制限に\n"
			"　余裕が有ったり無かったりします。\n"
			"　このモードでは、上部が完全に空いていなければ\n"
			"　テトリミノを作ることはできません。\n"
			"\n"
			"・エンドレスモード\n"
			"　無限に出て来るブロックを飛ばしまくり、\n"
			"　高得点を目指して下さい。\n"
			"　同じテトリミノを連続して消すと\n"
			"　コンボの点数が増え、難しい形のテトリミノの方が\n"
			"　増える点数が高いです。\n"
			"　このモードでは、上部に隙間があればテトリミノを\n"
			"　作ることができ、出来たテトリミノは\n"
			"　ブロックにぶつかった時点で停止します。" );
	}
	else if( selection == 2 )
	{
		MikanDraw->Printf( 6, 0, 0,
			"【モード説明】\n"
			"・バトルモード\n"
			"　無限に出て来るブロックを消して\n"
			"　相手よりも長く生き残って下さい。\n"
			"　このモードではコンボの点数に応じて\n"
			"　相手のブロックをせり上がります。\n"
			"\n"
			"・エディタモード\n"
			"　このモードではパズルモードのステージを\n"
			"　自作することができます。\n"
			"　”宙に浮かない形”ならば自由にテトリミノ\n"
			"　を配置することが可能です。\n"
			"　モード中のメニューからリセット、\n"
			"　セーブやロードができます。\n"
			"　エディタモードで保存したステージはパズルモード\n"
			"　の”original stage”から遊ぶことも可能です。\n"
			"　なお、ステージは最大1つまでしか\n"
			"　セーブできないので御注意下さい。");
	}

	MikanDraw->DrawBox( ( WIDHT - 5 * 30 / 2 ) / 2 - 10, HEIGHT - 30, 5 * 30 / 2 + 10 * 2, 30, 0xFFFFFFFF );
	MikanDraw->Printf( 4, ( WIDHT - 5 * 30 / 2 ) / 2, HEIGHT - 30, "%d / 3", selection + 1 );
}


//以下、ゲーム中の処理==============================================
//枠の描画
void Draw_BlockBack()
{
	MikanDraw->DrawBox( 2 * ChipSize, ( -1 ) * ChipSize, BlockWid * ChipSize, BlockHei * ChipSize, 0xFF000000 );
	MikanDraw->DrawBox( ( 2 + 1 ) * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0xFFFFFFFF );

	MikanDraw->DrawBox( ( 2 + BlockWid ) * ChipSize + ( ChipSize / 2 ), 0, 10 * ChipSize, HEIGHT, 0xFF5F5F5F );
	//絵の表示　感謝！
	MikanDraw->DrawTexture( 1, WIDHT - 150, 0, 0, 0, 150, HEIGHT );
}

//ブロックの描画関数
void Draw_Block( int block[ BlockHei ][ BlockWid ] )
{
	//メニューを開いている間はブロックを描画しない。
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

//完成したテトリミノの描画関数
void Draw_Tetrimino( struct tetrimino tet )
{
	for( int i = 0; i < TetriMax; i ++ )
	{
		MikanDraw->DrawTexture( 0, ( tet.x[ i ] + 2 - 1 ) * ChipSize, ( tet.y[ i ] - 1 - 1 ) * ChipSize,
			tet.t[ i ] * 4 * ChipSize, tet.dir[ i ] * 4 * ChipSize, 4 * ChipSize, 4 * ChipSize );
	}
}


//以下、パズルモードの処理------------------------------------------
//カーソルの描画関数
void Draw_Silhouette_Cursor( int x, int y, int choice, int dirction )
{
	MikanDraw->SetAlpha( 0, 127 );

	MikanDraw->DrawTexture( 0, ( x + 2 - 1) * ChipSize, ( y - 1 - 1 ) * ChipSize,
		choice * 4 * ChipSize, dirction * 4 * ChipSize, 4 * ChipSize, 4 * ChipSize );

	MikanDraw->SetAlpha( 0, 255 );
}

//画面右のテトリミノ一覧の表示関数
void Draw_Puzzle_Tetrinimos( int LimitTet[ 7 ], int UsedTet[ 7 ], int StageNum, int choice, bool cursorT )
{
	for( int i = 0; i < 7; i ++ )
	{
		//選択中のテトリミノの後ろに白い箱を描画する。
		if( cursorT == true &&
			choice == i )
		{
			MikanDraw->DrawBox( ( 2 + BlockWid ) * ChipSize + ( ChipSize / 2 ), 50 + i * 3 * ChipSize + ( ChipSize / 2 ), 10 * ChipSize, 3 * ChipSize, 0xFFFFFFFF );
		}

		//この際にY座標を調整して見栄えを良くする。
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

		//使用可能テトリミノ数の描画
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

//メニュー画面の描画
void Draw_Puzzle_Menu( int selection )
{
	MikanDraw->DrawBox( ( 2 + 1 ) * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0x7F000000 );


	MikanDraw->Printf( 3, ( BlockWid * ChipSize - 4 * 50 ) / 2 + 2 * ChipSize, 60, "メニュー" );

	if( selection == 0 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 6 * 25 ) / 2 + 2 * ChipSize, 250 - 10 / 2, "ゲームに戻る" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 6 * 20 ) / 2 + 2 * ChipSize, 250, "ゲームに戻る" );
	}
	if( selection == 1 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 4 * 25 ) / 2 + 2 * ChipSize, 300 - 10 / 2, "一手戻す" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 4 * 20 ) / 2 + 2 * ChipSize, 300, "一手戻す" );
	}
	if( selection == 2 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 7 * 25 ) / 2 + 2 * ChipSize, 350 - 10 / 2, "タイトルに戻る" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 7 * 20 ) / 2 + 2 * ChipSize, 350, "タイトルに戻る" );
	}
}

//制限時間の描画
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
					//描画しない
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
				//描画しない
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

//ゲームオーバー
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


//以下、エンドレスモードの処理--------------------------------------
//カーソルの描画関数
void Draw_Pointer_Cursor( int x, int y )
{
	MikanDraw->DrawTexture( 0, ( x + 2 ) * ChipSize, y * ChipSize - ChipSize,
		9 * ChipSize, 4 * 4 * ChipSize, ChipSize, ChipSize );
}

//プレイ時間の描画
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
				//描画しない
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
				//描画しない
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

//スコア、comboの描画
void Draw_Endless_Score( int score, int comboN, int comboT, int comboP, int comboTime, int timer )
{
	//スコアの表示
	MikanDraw->Printf( 8, ( 2 + BlockWid + 1 ) * ChipSize, 50 + 20, "%5d", score );
	//コンボ中のスコアの表示
	MikanDraw->Printf( 9, 20 + ( 2 + BlockWid + 1 ) * ChipSize, 50 + 20 + 50, "+%d", comboP );

	//combo表示
	if( comboT >= 0 )
	{
		//この際にY座標を調整して見栄えを良くする。
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
	//コンボ数の描画
	if( comboN > 0 )
	{
		MikanDraw->Printf( 9, ( 2 + BlockWid + 1 + 4 ) * ChipSize, 50 + 50 + 20 + 50, "×%d", comboN );
	}

	//残りコンボ時間をゲージで表示
	MikanDraw->DrawBox( ( 2 + BlockWid ) * ChipSize + ( ChipSize / 2 ) + 25 - 5, 50 + 50 + 20 + 50 + 20 + 50 - 5, 150 + 10, 10 + 10, 0xFF000000 );
	MikanDraw->DrawBox( ( 2 + BlockWid ) * ChipSize + ( ChipSize / 2 ) + 25, 50 + 50 + 20 + 50 + 20 + 50, 150, 10, 0xFFFF0000 );
	if( timer - comboTime < ChainTime &&
		comboTime != 0 )
	{
		MikanDraw->DrawBox( ( 2 + BlockWid ) * ChipSize + ( ChipSize / 2 ) + 25, 50 + 50 + 20 + 50 + 20 + 50, 150 - ( timer - comboTime ) * 150 / ChainTime, 10, 0xFFFFFF00 );
	}
}

//メニュー画面の描画
void Draw_Endless_Menu( int selection )
{
	MikanDraw->DrawBox( ( 2 + 1 ) * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0x7F000000 );


	MikanDraw->Printf( 3, ( BlockWid * ChipSize - 4 * 50 ) / 2 + 2 * ChipSize, 60, "メニュー" );

	if( selection == 0 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 6 * 25 ) / 2 + 2 * ChipSize, 250 - 10 / 2, "ゲームに戻る" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 6 * 20 ) / 2 + 2 * ChipSize, 250, "ゲームに戻る" );
	}
	if( selection == 1 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 7 * 25 ) / 2 + 2 * ChipSize, 300 - 10 / 2, "タイトルに戻る" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 7 * 20 ) / 2 + 2 * ChipSize, 300, "タイトルに戻る" );
	}
}

//ゲームオーバー
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


//以下、バトルモードの処理--------------------------------------
//枠の描画
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

	//絵を表示　感謝！
	MikanDraw->DrawTexture( 2, BlockWid * ChipSize, HEIGHT - 80, 0, 0, 160, 80 );
}

//ブロックの描画関数
void Draw_Battle_Block( int block[ BlockHei ][ BlockWid ], int block2[ BlockHei ][ BlockWid ] )
{
	//メニューを開いている間はブロックを描画しない。
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

//完成したテトリミノの描画関数
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

//カーソルの描画関数
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

//プレイ時間の描画
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
				//描画しない
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
				//描画しない
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

//スコア、comboの描画
void Draw_Battle_Score( int timer, int score, int score2, int comboN, int comboN2, int comboT, int comboT2,
	int comboP, int comboP2, int comboTime, int comboTime2 )
{
	//スコアの表示
	MikanDraw->Printf( 3, ChipSize, ( BlockHei - 1 ) * ChipSize + 10, "%d", score );
	MikanDraw->Printf( 3, SecondX + ChipSize, ( BlockHei - 1 ) * ChipSize + 10, "%d", score2 );

	//コンボスコアの表示
	MikanDraw->Printf( 8, ( BlockWid + 1 ) * ChipSize, 50 + 10, "+%d", comboP );
	MikanDraw->Printf( 8, ( BlockWid + 1 ) * ChipSize, 50 + 175 + 10, "+%d", comboP2 );


	//combo表示
	if( comboT >= 0 )
	{
		//この際にY座標を調整して見栄えを良くする。
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
	//コンボ数の描画
	if( comboN > 0 )
	{
		MikanDraw->Printf( 9, ( 1 + BlockWid + 1 ) * ChipSize, 50 + 10 + 50 + 2 * ChipSize, "×%d", comboN );
	}
	//残りコンボ時間をゲージで表示
	MikanDraw->DrawBox( BlockWid * ChipSize + 30 - 5, 50 * 4 + 5 - 5, 100 + 10, 10 + 10, 0xFF000000 );
	MikanDraw->DrawBox( BlockWid * ChipSize + 30, 50 * 4 + 5, 100, 10, 0xFFFF0000 );
	if( timer - comboTime < ChainTime &&
		comboTime != 0 )
	{
		MikanDraw->DrawBox( BlockWid * ChipSize + 30, 50 * 4 + 5, 100 - ( timer - comboTime ) * 100 / ChainTime, 10, 0xFFFFFF00 );
	}

	if( comboT2 >= 0 )
	{
		//この際にY座標を調整して見栄えを良くする。
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
	//コンボ数の描画
	if( comboN2 > 0 )
	{
		MikanDraw->Printf( 9, ( 1 + BlockWid + 1 ) * ChipSize, 50 + 175 + 10 + 50 + 2 * ChipSize, "×%d", comboN2 );
	}
	//残りコンボ時間をゲージで表示
	MikanDraw->DrawBox( BlockWid * ChipSize + 30 - 5, 175 + 50 * 4 + 5 - 5, 100 + 10, 10 + 10, 0xFF000000 );
	MikanDraw->DrawBox( BlockWid * ChipSize + 30, 175 + 50 * 4 + 5, 100, 10, 0xFFFF0000 );
	if( timer - comboTime2 < ChainTime &&
		comboTime2 != 0 )
	{
		MikanDraw->DrawBox( BlockWid * ChipSize + 30, 175 + 50 * 4 + 5, 100 - ( timer - comboTime2 ) * 100 / ChainTime, 10, 0xFFFFFF00 );
	}
}

//メニュー画面の描画
void Draw_Battle_Menu( int selection, int selection2 )
{
	MikanDraw->DrawBox( 1 * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0x7F000000 );
	MikanDraw->DrawBox( SecondX + 1 * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0x7F000000 );

	MikanDraw->Printf( 3, ( BlockWid * ChipSize - 4 * 50 ) / 2, 60, "メニュー" );
	MikanDraw->Printf( 3, SecondX + ( BlockWid * ChipSize - 4 * 50 ) / 2, 60, "メニュー" );

	if( selection == 0 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 6 * 25 ) / 2, 250 - 10 / 2, "ゲームに戻る" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 6 * 20 ) / 2, 250, "ゲームに戻る" );
	}
	if( selection2 == 0 )
	{
		MikanDraw->Printf( 6, SecondX + ( BlockWid * ChipSize - 6 * 25 ) / 2, 250 - 10 / 2, "ゲームに戻る" );
	}
	else
	{
		MikanDraw->Printf( 7, SecondX + ( BlockWid * ChipSize - 6 * 20 ) / 2, 250, "ゲームに戻る" );
	}

	if( selection == 1 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 7 * 25 ) / 2, 300 - 10 / 2, "タイトルに戻る" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 7 * 20 ) / 2, 300, "タイトルに戻る" );
	}
	if( selection2 == 1 )
	{
		MikanDraw->Printf( 6, SecondX + ( BlockWid * ChipSize - 7 * 25 ) / 2, 300 - 10 / 2, "タイトルに戻る" );
	}
	else
	{
		MikanDraw->Printf( 7, SecondX + ( BlockWid * ChipSize - 7 * 20 ) / 2, 300, "タイトルに戻る" );
	}
}

//ゲームオーバー
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


//エディタ
void Draw_Editor_Tetrinimos( int UsedTet[ 7 ], int choice )
{
	for( int i = 0; i < 7; i ++ )
	{
		//選択中のテトリミノの後ろに白い箱を描画する。
		if( choice == i )
		{
			MikanDraw->DrawBox( ( 2 + BlockWid ) * ChipSize + ( ChipSize / 2 ), i * 3 * ChipSize + ( ChipSize / 2 ), 10 * ChipSize, 3 * ChipSize, 0xFFFFFFFF );
		}

		//この際にY座標を調整して見栄えを良くする。&
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

	//セーブ・ロード時に知らせる。
		//セーブ！！！
	if( MikanInput->GetKeyNum( K_A ) > 60 ||
		MikanInput->GetPadNum( 0, PAD_D ) > 60 )
	{
		MikanDraw->Printf( 0, 0, 0, "Saved!" );
	}

	//ロード！！！！！
	if( MikanInput->GetKeyNum( K_S ) > 60 ||
		MikanInput->GetPadNum( 0, PAD_C ) > 60 )
	{
		MikanDraw->Printf( 0, 0, 0, "Loaded!" );
	}
}

void Draw_Editor_Menu( int selection )
{
	MikanDraw->DrawBox( ( 2 + 1 ) * ChipSize, 0 * ChipSize, ( BlockWid - 2 ) * ChipSize, ( BlockHei - 2 ) * ChipSize, 0x7F000000 );


	MikanDraw->Printf( 3, ( BlockWid * ChipSize - 4 * 50 ) / 2 + 2 * ChipSize, 60, "メニュー" );

	if( selection == 0 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 6 * 25 ) / 2 + 2 * ChipSize, 190 - 10 / 2, "ゲームに戻る" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 6 * 20 ) / 2 + 2 * ChipSize, 190, "ゲームに戻る" );
	}
	if( selection == 1 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 4 * 25 ) / 2 + 2 * ChipSize, 230 - 10 / 2, "リセット" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 4 * 20 ) / 2 + 2 * ChipSize, 230, "リセット" );
	}
	if( selection == 2 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 4 * 25 ) / 2 + 2 * ChipSize, 270 - 10 / 2, "セーブ！" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 4 * 20 ) / 2 + 2 * ChipSize, 270, "セーブ！" );
	}
	if( selection == 3 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 4 * 25 ) / 2 + 2 * ChipSize, 310 - 10 / 2, "ロード！" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 4 * 20 ) / 2 + 2 * ChipSize, 310, "ロード！" );
	}
	if( selection == 4 )
	{
		MikanDraw->Printf( 6, ( BlockWid * ChipSize - 7 * 25 ) / 2 + 2 * ChipSize, 350 - 10 / 2, "タイトルに戻る" );
	}
	else
	{
		MikanDraw->Printf( 7, ( BlockWid * ChipSize - 7 * 20 ) / 2 + 2 * ChipSize, 350, "タイトルに戻る" );
	}
}
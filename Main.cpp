//======================================
//	ターン制バトル メイン
//======================================
#include "Character.h"
#include "TurnBattle.h"
#include "CommandUI.h"
#include "Utility.h"  // InitRand(),GetKey()
#include <stdio.h>  // printf()
// 関数プロトタイプ
void game();
void RndCh(int rnd);
int _stage = 0;
bool win = false;
bool lose = false;

int main()
{
	InitRand();

	int c = 0;
	do {
		game();
		printf("もう一度(y/n)?");
		_stage = 0;

		while (true) {
			c = GetKey();
			if (c == 'y' || c == 'n') {
			break;
			}
		}
	} while (c == 'y');

	return 0;
}

void game()
{
	Character player;
	Character boss;
	Character zako;
	Character midBoss;
	TurnBattle btl;

	SetCharacter(&player,
		100,        // HP
		15,         // MP
		30,         // 攻撃力
		"ゆうしゃ", // 名前
		"");        // アスキーアート
	SetCharacter(&boss,
		255,      // HP
		3,        // MP
		40,       // 攻撃力
		"まおう", // 名前
		"　　Ａ＠Ａ\n" // アスキーアート
		"ψ（▼皿▼）ψ\n"
	);
	SetCharacter(&zako,
		3,          // HP
		0,          // MP
		2,          // 攻撃力
		"スライム", // 名前 
		"／・Д・＼\n" // アスキーアート
		"～～～～～"
	);
	SetCharacter(&midBoss,
		150,	// HP
		3,		// MP
		20,		// 攻撃力
		"まおうのかんぶ",	// 名前
		"_(:3 」∠)_\n"		// アスキーアート
		"=====床=====\n"
	);

	SetTurnBattle(&btl, &player, &zako);
	StartTurnBattle(&btl);
	IntroTurnBattle(&btl);
	Command cmd;
	while (true) {
		cmd = GetPlayerCommand(&btl);
		win = ExecPlayerTurn(&btl, cmd);
		if (win) {
			_stage++;
			switch (_stage)
			{
			case 0:
				SetTurnBattle(&btl, &player, &zako);
				StartTurnBattle(&btl);
				IntroTurnBattle(&btl);
				break;
			case 1:
				SetTurnBattle(&btl, &player, &midBoss);
				StartTurnBattle(&btl);
				IntroTurnBattle(&btl);
				break;
			case 2:
				SetTurnBattle(&btl, &player, &boss);
				StartTurnBattle(&btl);
				IntroTurnBattle(&btl);
				break;
			}
		}
		cmd = GetEnemyCommand();
		lose = ExecEnemyTurn(&btl, cmd);
		if (lose) {
			break;
		}
		NextTurnBattle(&btl);
	}
	
}
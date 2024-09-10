//======================================
//	�^�[�����o�g�� ���C��
//======================================
#include "Character.h"
#include "TurnBattle.h"
#include "CommandUI.h"
#include "Utility.h"  // InitRand(),GetKey()
#include <stdio.h>  // printf()
// �֐��v���g�^�C�v
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
		printf("������x(y/n)?");
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
		30,         // �U����
		"�䂤����", // ���O
		"");        // �A�X�L�[�A�[�g
	SetCharacter(&boss,
		255,      // HP
		3,        // MP
		40,       // �U����
		"�܂���", // ���O
		"�@�@�`���`\n" // �A�X�L�[�A�[�g
		"�Ձi���M���j��\n"
	);
	SetCharacter(&zako,
		3,          // HP
		0,          // MP
		2,          // �U����
		"�X���C��", // ���O 
		"�^�E�D�E�_\n" // �A�X�L�[�A�[�g
		"�`�`�`�`�`"
	);
	SetCharacter(&midBoss,
		150,	// HP
		3,		// MP
		20,		// �U����
		"�܂����̂����",	// ���O
		"_(:3 �v��)_\n"		// �A�X�L�[�A�[�g
		"=====��=====\n"
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
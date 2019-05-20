#include "DxLib.h"
#include "BaseScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "SoundMng.h"
#include "MapControl.h"
#include "classObj.h"
#include "SpeedMng.h"
#include "EnemyAct.h"
#include "Enemy.h"

Enemy::Enemy(VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
{
	init("image/constellation.png", VECTOR2(250, 250), VECTOR2(4, 4));
	

}

Enemy::Enemy()
{
	enemyType = GEMINI;
	maxHp = ENEMY_DEF_HP;
	frequency = ENEMY_DEF_FREQUENCY;
	enemyHp = maxHp;
	at_Cnt = 3;

	meteoPos = VECTOR2(0, 0);
	speed = VECTOR2(0, 0);
	AttackType[SHOT] = false;
	AttackType[METEORITE] = false;
	shotFlag = false;
	enemyBossFlag = true;
}

Enemy::~Enemy()
{
}

void Enemy::SetMove(const GameCtl & controller, weekListObj objList)
{
	lpEnemyAct.SelectAct(pos , meteoPos, frequency, AttackType[SHOT], AttackType[METEORITE]);
	if (!lpEnemyAct.GetshotFlag())
	{
		pos.x = 0;
	}
	
	if (!lpEnemyAct.GetmeteoriteFlag())
	{
		meteoPos.x = 0;
		pos.y = 0;
	}

	switch (lpEnemyAct.SetAngle())
	{
	case 3:
		speed = VECTOR2(4, 4);
		break;
	case 4:
		speed = VECTOR2(5, 4);
		break;
	case 5:
		speed = VECTOR2(SPEED, 4);
		break;
	case 6:
		speed = VECTOR2(SPEED, 4);
		break;
	case 7:
		speed = VECTOR2(SPEED, 3);
		break;
	case 8:
		speed = VECTOR2(SPEED, 3);
		break;
	default:
		break;
	}
	HitCheck();
}

VECTOR2 Enemy::EnemyType(void)
{
	switch (enemyType)
	{
		//�t�̐���
	case CANCER:
		maxHp = 100;
		enemyHp = 100;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = false;
		frequency = 20;
		at_Cnt = 3;
		return VECTOR2(3, 0);
		break;
	case LEO:
		maxHp = 200;
		enemyHp = 200;
		AttackType[SHOT] = false;
		AttackType[METEORITE] = true;
		frequency = 20;
		at_Cnt = 3;
		return VECTOR2(0, 1);
		break;
	case VIRGO:
		maxHp = 250;
		enemyHp = 250;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = true;
		frequency = 20;
		at_Cnt = 3;
		return VECTOR2(1, 1);
		break;
		//�Ă̐���
	case LIBRA:
		maxHp = 350;
		enemyHp = 350;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = false;
		frequency = 15;
		at_Cnt = 3;
		return VECTOR2(2, 1);
		break;
	case SCORPIO:
		maxHp = 500;
		enemyHp = 500;
		AttackType[SHOT] = false;
		AttackType[METEORITE] = true;
		frequency = 15;
		at_Cnt = 3;
		return VECTOR2(3, 1);
		break;
	case SAGITTARIUS:
		maxHp = 650;
		enemyHp = 650;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = true;
		frequency = 15;
		at_Cnt = 3;
		return VECTOR2(0, 2);
		break;
		//�H�̐���
	case ARIES:
		maxHp = 800;
		enemyHp = 800;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = false;
		frequency = 10;
		at_Cnt = 3;
		return VECTOR2( 0, 0);
		break;
	case TAURUS:
		maxHp = 950;
		enemyHp = 950;
		AttackType[SHOT] = false;
		AttackType[METEORITE] = true;
		frequency = 10;
		at_Cnt = 3;
		return VECTOR2( 1, 0);
		break;
	case GEMINI:
		maxHp = 1050;
		enemyHp = 1050;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = true;
		frequency = 10;
		at_Cnt = 3;
		return VECTOR2( 2, 0);
		break;
		//�~�̐���
	case CAPRICORN:
		maxHp = 1250;
		enemyHp = 1250;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = false;
		frequency = 5;
		at_Cnt = 3;
		return VECTOR2(1, 2);
		break;
	case AQUARIUS:
		maxHp = 1450;
		enemyHp = 1450;
		AttackType[SHOT] = false;
		AttackType[METEORITE] = true;
		frequency = 5;
		at_Cnt = 3;
		return VECTOR2(2, 2);
		break;
	case PISCES:
		maxHp = 1650;
		enemyHp = 1650;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = true;
		frequency = 5;
		at_Cnt = 3;
		return VECTOR2(3, 2);
		break;
	default:
		break;
	}
}

void Enemy::Draw(void)
{
	auto Draw = [&](VECTOR2 divID)
	{
		DrawRectGraph(SCREEN_SIZE_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 4, divID.x * 250, divID.y * 250, 250, 250, IMAGE_ID("image/constellation.png")[0], true, false);
	};
	int Pos = (SCREEN_SIZE_X - 80)*(enemyHp / maxHp);
		DrawBox(100, SCREEN_SIZE_Y - 64, Pos, SCREEN_SIZE_Y - 32, 0x00ffff, true);
		DrawBox(100, SCREEN_SIZE_Y - 64, SCREEN_SIZE_X - 80, SCREEN_SIZE_Y - 32, 0xff0000, false);
		DrawBox( 99, SCREEN_SIZE_Y - 63, SCREEN_SIZE_X - 81, SCREEN_SIZE_Y - 33, 0xff0000, false);


	if (lpEnemyAct.GetshotFlag())
	{
		pos.x += 2;
		if (!lpSoundMng.CheckSound("Sound/Sound effect/earth-tremor1.mp3"))
		{
			lpSoundMng.PlaySound("Sound/Sound effect/earth-tremor1.mp3", DX_PLAYTYPE_LOOP);
		}
		DrawRotaGraph(SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos.x, SCREEN_SIZE_Y - SCREEN_SIZE_Y / 5 - SCREEN_SIZE_Y /10, 0.25f, 0, IMAGE_ID("image/tama.png")[0], true, true);
	}
	if (lpEnemyAct.GetmeteoriteFlag())
	{
		meteoPos.x += speed.x;
		pos.y += speed.y;
		DrawRotaGraph(GIMMICK_POP_X + CHIP_SIZE * lpEnemyAct.SetPos() - meteoPos.x, pos.y, 1, -(PI/ lpEnemyAct.SetAngle()), IMAGE_ID("image/tama.png")[0], true, true);
	}

	DrawFormatString(1100, 0, 0xffff00,  "�G�̎��......%d", static_cast<int>(enemyBossFlag));
	DrawFormatString(1100, 25, 0xffff00, "�G�̍ő�HP....%d", maxHp);
	DrawFormatString(1100, 50, 0xffff00, "�G�̎c��HP....%d", enemyHp);
	DrawFormatString(1100, 75, 0xffff00, "�U��SHOT......%d", AttackType[SHOT]);
	DrawFormatString(1100, 100, 0xffff00, "�U��METEO.....%d", AttackType[METEORITE]);
	DrawFormatString(1100, 125, 0xffff00, "�G�̍U���p�x..%d", frequency);
	if (AttackType[SHOT])
	{
		DrawFormatString(1100, 150, 0xffff00, "�e��Flag......%d", lpEnemyAct.GetshotFlag());
		DrawFormatString(1100, 200, 0xffff00, "�e�̍��W......%d", SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos.x);
	}

	if (AttackType[METEORITE])
	{
		DrawFormatString(1100, 175, 0xffff00, "覐΂�Flag....%d", lpEnemyAct.GetmeteoriteFlag());
		DrawFormatString(1100, 225, 0xffff00, "覐΂̍��W....%d", pos.y);
		DrawFormatString(1100, 250, 0xffff00, "覐΂̊p�x....%d", lpEnemyAct.SetAngle());
	}

	if (enemyType < ENEMY_ID_MAX)
	{
		Draw(EnemyType());
	}
}

void Enemy::HitCheck(void)
{
	if (CheckHitKey(KEY_INPUT_P)==1 && enemyType < ENEMY_ID_MAX - 1)
	{
		enemyType = static_cast<BOSS_ID>(enemyType + 1);
		bool enemyBossFlag = false;
	}
}

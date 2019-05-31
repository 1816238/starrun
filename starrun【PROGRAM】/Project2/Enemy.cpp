#include <math.h>
#include "DxLib.h"
#include "BaseScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "SoundMng.h"
#include "MapControl.h"
#include "classObj.h"
#include "SpeedMng.h"
#include "Shot.h"
#include "Meteo.h"
#include "EnemyAct.h"
#include "EnemyBit.h"
#include "Enemy.h"

#define PI  3.1415926535897932384626433832795f
#define CIRCLE_PI ( PI*2 )
#define CENTER_POS_X ( SCREEN_SIZE_X - SCREEN_SIZE_X / 4 + 125) 
#define CENTER_POS_Y ( SCREEN_SIZE_Y / 4 + 125 )
#define CIRCLE_RANGE ( 250 -(60+43))

Enemy::Enemy(OBJ_TYPE objType)
{
	Obj::init("image/constellation.png", VECTOR2(250, 250), VECTOR2(4, 4));
	Obj::init("image/boss_body.png", VECTOR2(215, 45), VECTOR2(5, 1));
	this->objType = objType;
	init();
}

Enemy::Enemy()
{
	Obj::init("image/boss_body.png", VECTOR2(215, 45), VECTOR2(5, 1));

	init();
}

Enemy::~Enemy()
{

}

void Enemy::SetMove(const GameCtl & controller, weekListObj objList)
{
	HitCheck();
	lpEnemyAct.SelectAct(pos, meteoPos, frequency[enemyType], enemyType, at_wait, waitCnt[0], waitCnt[1], waitCnt[2]);
	//�G���ޯĂ̲ݽ�ݽ
	if (enemyBossFlag)
	{
		for (int bit_cnt = 0; bit_cnt < enemy_bit_cnt[enemyType]; bit_cnt++)
		{
			auto obj=AddObjList()(objList, std::make_unique<EnemyBit>(VECTOR2{ CIRCLE_RANGE + 43 / 2 , 45 / 2 }, VECTOR2{ 0,0 }, bit_cnt,max_hp[enemyType]/4));
			enemyBossFlag = false;
		}
	}
	
	//覐΂̲ݽ�ݽ
	if (lpEnemyAct.GetmeteoriteFlag())
	{
		if (meteo_waitCnt > 120)
		{
			AddObjList()(objList, std::make_unique<Meteo>(VECTOR2{ GIMMICK_POP_X + CHIP_SIZE * lpEnemyAct.SetPos(), -500 }, VECTOR2{ 0,0 }));
			lpEnemyAct.SetMeteoFlag(false);
			meteo_waitCnt = 0;
		}
		meteo_waitCnt++;
	}

	//�G�̒e�̲ݽ�ݽ�y�є��˂܂ł̊Ǘ�
	if (At_Type[enemyType][SHOT])
	{


		if (!shotFlag[0] || !shotFlag[1] || !shotFlag[2])
		{
			VECTOR2 tmpPos = VECTOR2(SCREEN_SIZE_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y);
		
			if ((shot_waitCnt / at_wait) % at_wait == 1 || (shot_waitCnt / at_wait) % at_wait == 3 || (shot_waitCnt / at_wait) % at_wait == 7)
			{
				auto DrawShot = [&](int h) {
					AddObjList()(objList, std::make_unique<Shot>(VECTOR2{ tmpPos.x,tmpPos.y - h * CHIP_SIZE }, VECTOR2{ 0,0 }, TYPE_ENEMY_SHOT, 6));
				};
				switch ((shot_waitCnt / at_wait) % at_wait)
				{
				case 1:
					if (!shotFlag[0])
					{
						DrawShot(9);
						shotFlag[0] = true;
					}
					break;
				case 3:
					if (!shotFlag[1])
					{
						DrawShot(7);
						shotFlag[1] = true;
					}
					break;
				case 7:
					if (!shotFlag[2])
					{
						DrawShot(6);
						shotFlag[2] = true;
					}
					break;
				default:
					break;
				}
			}
			shot_waitCnt++;
		}
		else
		{
			OutputDebugString("shot_waitCnt = 0 \n");

			for (int num = 0; num < AT_DRAW_MAX; num++)
			{
				shotFlag[num] = false;
			}
			shot_waitCnt = shot_waitCnt / 2;
		}
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		HP = 0;
	}
	enemy_hp[enemyType] = static_cast<float>(HP);
	deathFlag = (enemy_hp[enemyType] <= 0 ? true : false);
}

VECTOR2 Enemy::GetCircleMove_pos(void)
{
	return VECTOR2(pos.x, pos.y);
}

void Enemy::Draw(void)
{
	auto ATCnt = SEASONE_LIM - Speed(Main);
	SetAnim("�ʏ�");

	auto Draw = [&](VECTOR2 divID)
	{
		DrawCircle(CENTER_POS_X, CENTER_POS_Y, CIRCLE_RANGE, 0xff0000, false);
		DrawCircle(SCREEN_SIZE_X - SCREEN_SIZE_X / 4 + 125, SCREEN_SIZE_Y / 4 + 125, 4, 0xff0000, true);
		DrawRectGraph(SCREEN_SIZE_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 4, divID.x * 250, divID.y * 250, 250, 250, IMAGE_ID("image/constellation.png")[0], true, false);
	};
	int Pos = (SCREEN_SIZE_X - 80)*(enemy_hp[enemyType] / max_hp[enemyType]);
	if (enemy_hp[enemyType] > 0)
	{
		DrawBox(100, SCREEN_SIZE_Y - 64, Pos, SCREEN_SIZE_Y - 32, 0x00ffff, true);

	}
	DrawBox(100, SCREEN_SIZE_Y - 64, SCREEN_SIZE_X - 80, SCREEN_SIZE_Y - 32, 0xff0000, false);
	DrawBox(99, SCREEN_SIZE_Y - 63, SCREEN_SIZE_X - 81, SCREEN_SIZE_Y - 33, 0xff0000, false);

	DrawRectGraph(CENTER_POS_X - 43 / 2 - CIRCLE_RANGE, CENTER_POS_Y - 45 / 2, 43, 0, 43, 45,
		IMAGE_ID("image/boss_body.png")[0], true, false);
	
	//�f�o�b�N�p====================================================================================================================
	DrawLine((SCREEN_SIZE_X - SCREEN_SIZE_X / 4) - pos.x, 0, (SCREEN_SIZE_X - SCREEN_SIZE_X / 4) - pos.x, SCREEN_SIZE_Y, 0xff0000);
	DrawFormatString(1100, 0, 0xffff00, "�G�̎��......%d", enemy_name[enemyType]);
	DrawFormatString(1100, 25, 0xffff00, "�G�̍ő�HP....%d", max_hp[enemyType]);
	DrawFormatString(1100, 50, 0xffff00, "�G�̎c��HP....%d", enemy_hp[enemyType]);
	DrawFormatString(1100, 75, 0xffff00, "�U��SHOT......%d", At_Type[enemyType][SHOT]);
	DrawFormatString(1100, 100, 0xffff00, "�U��METEO.....%d", At_Type[enemyType][METEORITE]);
	DrawFormatString(1100, 125, 0xffff00, "�G�̍U���p�x..%d", frequency[enemyType]);
	/*if (At_Type[enemyType][SHOT])
	{*/
		DrawFormatString(1100, 175, 0xffff00, "�e�̍��W......%d", SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos.x);

		for (int num = 0; num < AT_DRAW_MAX; num++)
		{
			DrawFormatString(1100, 150, 0xffff00, "�e��Flag[%d]......%d",num ,shotFlag[num]);
		}
	//}
	if (At_Type[enemyType][METEORITE])
	{
		DrawFormatString(1100, 300, 0xffff00, "覐΂�Flag....%d", lpEnemyAct.GetmeteoriteFlag());
		DrawFormatString(1100, 325, 0xffff00, "覐΂̍��W....%d", pos.y);
		DrawFormatString(1100, 350, 0xffff00, "覐΂̊p�x....%d", lpEnemyAct.SetAngle());
		for (int num = 0; num <= AT_DRAW_MAX; num++)
		{
		}
	}
	//==============================================================================================================================
	if (enemyType < ENEMY_ID_MAX)
	{
		Draw(boss_ID[enemyType]);
	}
}

void Enemy::HitCheck(void)
{
	if (lpSpeedMng.GetSeasoonFlag(Main) && !lpSpeedMng.GetSeasoonFlag(Sub))
	{
		enemy_shift_flag = true;
	}
	if (deathFlag || (enemy_shift_flag &&!lpSpeedMng.GetSeasoonFlag(Main) && lpSpeedMng.GetSeasoonFlag(Sub)))
	{
		if (enemyType < PISCES)
		{
			enemyType = static_cast<BOSS_ID>(enemyType + 1);
			HP = max_hp[enemyType];
			enemy_shift_flag = false;
			deathFlag = false;
		}
		else
		{
			enemyType = CANCER;
			HP = max_hp[enemyType];
			enemy_shift_flag = false;
			deathFlag = false;
		}
	}
}

bool Enemy::init(void)
{


	AddAnim("�ʏ�", 0, 0, 30, 1, true);

	boss_ID = { VECTOR2(3,0), VECTOR2(0,1), VECTOR2(1,1),
				VECTOR2(2,1), VECTOR2(3,1), VECTOR2(0,2),
				VECTOR2(0,0), VECTOR2(1,0), VECTOR2(2,0),
				VECTOR2(1,2), VECTOR2(2,2), VECTOR2(3,2),VECTOR2(3,0) };

	seasone = { SPRING ,SPRING ,SPRING,
				SUMMER ,SUMMER ,SUMMER,
				AUTUMN ,AUTUMN ,AUTUMN,
				WINTER ,WINTER ,WINTER };

	At_Type = { true,false,
				false,true,
				true,true,
				true,false,
				false,true,
				true,true,
				true,false,
				false,true,
				true,true,
				true,false,
				false,true,
				true,true,
				false,false };

	max_hp = { 100, 200, 250,
			   350, 500, 650,
			   800, 950,1050,
			  1250,1450,1650,0 };

	enemy_hp = { 100, 200, 250,
				 350, 500, 650,
				 800, 950,1050,
				1250,1450,1650,0 };

	enemy_bit_cnt = { 4,4,4,
					  4,4,4,
					  4,4,4,
					  4,4,4 };

	frequency = { 20,20,20,
				  15,15,15,
				  10,10,10,
				   5, 5, 5,0 };

	enemyType = CANCER;

	at_Cnt = 30;
	at_wait = 20;

	meteoPos = VECTOR2(0, 0);
	speed = VECTOR2(0, 0);
	for (int num = 0; num < AT_DRAW_MAX; num++)
	{
		shotFlag[num] = false;
	}
	enemyBossFlag = true;
	Obj::HP = enemy_hp[CANCER];
	shotcnt = 0;
	enemy_shift_flag = false;
	deathFlag = false;
	return false;
}

OBJ_TYPE Enemy::CheckObjType(void)
{
	return objType;
}

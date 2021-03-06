#include <DxLib.h>
#include "ImageMng.h"
#include "Enemy.h"
#include "VECTOR2.h"
#include "EnemyBit.h"

#define PI  3.1415926535897932384626433832795f
#define CIRCLE_PI ( PI*2 )

EnemyBit::EnemyBit(VECTOR2 pos, VECTOR2 offset,int bit_cnt,float HP)
{
	//Obj::init("image/player_W.png", VECTOR2(40, 64), VECTOR2(1, 1), pos);

	this->pos = pos;
	this->offset = offset;
	this->speed = 6;
	this->objType = TYPE_ENEMY_BIT;
	this->HP = HP;
	this->obj_no = bit_cnt;
	OutputDebugString("pop\n");

	EnemyBit::init();

}

EnemyBit::~EnemyBit()
{
	OutputDebugString("ビット死んだよ\n");
}

bool EnemyBit::initAnim(void)
{
	return false;
}

bool EnemyBit::init(void)
{
	if (objType == TYPE_ENEMY_BIT)
	{
		Obj::init("image/boss.png", VECTOR2(43, 45), VECTOR2(5, 1), pos);
		AddAnim("通常", 1, 0, 4, 10, true);
		SetAnim("通常");
	}

	circle_pos.center_pos = { CENTER_POS_X,CENTER_POS_Y };
	circle_pos.circle_r = CIRCLE_RANGE;
	circle_pos.time = 3600;
	return true;
}


void EnemyBit::SetMove(const GameCtl & controller, weekListObj objList)
{
	float x=0;
	float y=0;
	SetAnim("通常");

	cnt++;
	auto Circle_Drwa = [&](int num)
	{
		if(obj_no < 2)
		{
			tmp_pos_x = circle_pos.center_pos.x + num * sin(CIRCLE_PI / circle_pos.time * cnt) * circle_pos.circle_r;
			tmp_pos_y = circle_pos.center_pos.y - num * cos(CIRCLE_PI / circle_pos.time * cnt) * circle_pos.circle_r;
		}
		else
		{
			tmp_pos_x = circle_pos.center_pos.x + num * cos(CIRCLE_PI / circle_pos.time * cnt) * circle_pos.circle_r;
			tmp_pos_y = circle_pos.center_pos.y + num * sin(CIRCLE_PI / circle_pos.time * cnt) * circle_pos.circle_r;
		}
	};

	if (obj_no == 0 || obj_no == 2)
	{
		Circle_Drwa(1);
	}
	if (obj_no == 1 || obj_no == 3)
	{
		Circle_Drwa(-1);
	}
	if (damageFlag)
	{
		HP -= damage;
		damageFlag = false;
		
	}

	EndFlag = (HP <= 0 ? true : false);
	SetEnd(EndFlag);
	/*
	tmp_pos_x = circle_pos.center_pos.x - cos(CIRCLE_PI / circle_pos.time*cnt) * circle_pos.circle_r;
	tmp_pos_y = circle_pos.center_pos.y - sin(CIRCLE_PI / circle_pos.time*cnt) * circle_pos.circle_r;左*/
	SetPos(VECTOR2(tmp_pos_x, tmp_pos_y));
}

//void EnemyBit::Draw(void)
//{
//	SetAnim("通常");
//	DrawGraph(0, 0, IMAGE_ID("image/boss.png")[0],true);
//	DrawBox(tmp_pos_x, tmp_pos_y, tmp_pos_x + 100, tmp_pos_y + 100, 0x00ff00, false);
//}

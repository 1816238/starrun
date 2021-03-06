#include <Dxlib.h>
#include "ImageMng.h"
#include "GameCtl.h"
#include "Obj.h"

Obj::Obj(VECTOR2 drawOffset) :drawOffset(drawOffset)		//	初期化することでconstに値を渡せるようになる
{
	dir = DIR_DOWN;
}

Obj::Obj()
{
}

bool Obj::init(string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos)
{
	init(fileName, divSize, divCnt);
	SetPos(pos);
	return false;
}

bool Obj::init(string fileName, VECTOR2 divSize, VECTOR2 divCnt)
{
	lpImageMng.GetID(fileName, divSize, divCnt);
	imageName = fileName;
	this->divSize = divSize;
	this->divCnt = divCnt;
	return true;
}

Obj::~Obj()
{
}

void Obj::UpDate(const GameCtl &controller, weekListObj objList)
{
	SetMove(controller, objList);
}

void Obj::Draw(unsigned int id)
{
	if (id < IMAGE_ID(imageName).size())
	{
		DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[id], true);
	}
}

void Obj::Draw(void)
{
	if (imageName.length() == 0)
	{
		return;
	}
	unsigned int ID = 0;
	if (animTbl.find(animName) != animTbl.end())
	{
		int count = (animCnt / animTbl[animName][ANIM_TBL_INV]);
		if (count < animTbl[animName][ANIM_TBL_FRAME] || animTbl[animName][ANIM_TBL_LOOP])
		{
			count = count % animTbl[animName][ANIM_TBL_FRAME];
		}
		else
		{
			count = animTbl[animName][ANIM_TBL_FRAME] - 1;
			animEndFlag = true;
		}

		ID = animTbl[animName][ANIM_TBL_START_ID] + (int)dir
			+ count * divCnt.x;
	}
	animCnt++;

	if (ID < IMAGE_ID(imageName).size())
	{
		DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[ID], true);
	}
	DrawFormatString(0, 0, 0xFFFFFF, "PLAYERの座標\nX...%d\nY...%d\n", pos.x, pos.y);

}

const VECTOR2 & Obj::GetPos(void)
{
	return pos;
}

bool Obj::AddAnim(string animName, int ID_x, int ID_y, int frame, int inv, bool loop)
{
	animTbl[animName][ANIM_TBL_START_ID] = ID_y * divCnt.x + ID_x;
	animTbl[animName][ANIM_TBL_INV] = inv;
	animTbl[animName][ANIM_TBL_FRAME] = frame;
	animTbl[animName][ANIM_TBL_LOOP] = loop;
	return true;
}

bool Obj::SetAnim(string animName)
{
	if (Obj::animName == animName)
	{
		return true;
	}
	if (animTbl.find(animName) == animTbl.end())
	{
		return false;
	}
	Obj::animName = animName;
	Obj::animCnt = 0;
	animEndFlag = false;

	return false;
}



std::string Obj::GetAnim(void)
{
	return animName;
}

void Obj::SetPos(VECTOR2 pos)
{
	Obj::pos = pos;
}

#pragma once
#include <array>
#include "Obj.h"
#include "MapControl.h"

#define PLAYER_DF_SPEED ( 1)
#define MOUSE_ROT_VOL (Rot)

enum DIR_TBL_ID
{
	DIR_TBL_MAIN,
	DIR_TBL_OPP,
	DIR_TBL_SUB1,
	DIR_TBL_SUB2,
	DIR_TBL_MAX
};

enum BLOCK_ID
{
	BLOCK_ID_WALL1,
	BLOCK_ID_WALL2,
	BLOCK_ID_BLOCK,
	BLOCK_ID_MAX
};

using namespace std;

using DIR_TBL_ARRAY = array<int, DIR_MAX>;
using DIR_TBL_PTR_ARRAY = array<int*, DIR_MAX>;
using DIR_TBL_ARRAY_DIR = array<DIR[DIR_TBL_MAX], DIR_MAX>;
using MAP_MOVE_TBL_ARRAY = array<bool, MAP_ID_MAX>;

class Player :
	public Obj
{
public:
	Player(VECTOR2 setUpPos, VECTOR2 drawOffset);
	Player();
	virtual ~Player();
	bool initAnim(void);
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//Playerの移動
	float speed;											//移動速度

	int Rot;											//ﾎｲｰﾙ回転量

	bool jumpFlag;											//左ｸﾘｯｸしたらtrue
	bool shotFlag;											//右ｸﾘｯｸでtrue

	DIR_TBL_ARRAY keyID_Tbl;								//移動に使うｷｰ情報のﾃｰﾌﾞﾙ
	DIR_TBL_ARRAY speed_Tbl;								//移動量のﾃｰﾌﾞﾙ
	//MAP_MOVE_TBL_ARRAY mapMove_Tbl;						//移動制限をかけるﾌﾞﾛｯｸIDを保管しておく
};


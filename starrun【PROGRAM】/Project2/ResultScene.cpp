#include "DxLib.h"
#include "Obj.h"
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ResultCtl.h"
#include "ResultScene.h"
#include "SoundMng.h"

ResultScene::ResultScene()
{
	Init();
}


ResultScene::~ResultScene()
{
}

unique_Base ResultScene::UpDate(unique_Base own, const GameCtl & controller)
{

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}

	if (CheckHitKey(KEY_INPUT_F1) == 1)
	{
		
		return std::make_unique<GameScene>();
	}

	if (CheckHitKey(KEY_INPUT_RETURN) == 1)
	{
		return std::make_unique<TitleScene>();
	}
	//叙述【ﾌﾟﾚﾃﾞｨｹｰﾄ】
	(*objList).remove_if([](uniqueObj& obj) {return obj->CheckDeath(); });
	lpResultCtl.ResultLoad(objList, false);
	ResultDraw();
	return std::move(own);		//所有権を移す
}

int ResultScene::Init(void)
{
	if (!objList)//objListの中に何も入ってないと例外が走るので何も入ってない場合はobjListの中に入れる処理を行う
	{
		objList = std::make_shared<uniqueObjList>();
	}
	objList->clear();
	lpResultCtl.SetUp(0,0);
	SetWindowText("AGS.exe Result");
	lpSoundMng.StopSound("Sound/BGM/GameSceen.mp3");
	lpSoundMng.StopSound(SOUND_METEO);
	return 0;
}

bool ResultScene::ResultDraw(void)
{
	ClsDrawScreen();
	DrawFormatString(0, 0, 0x00ff00, "ENTERでTitleへ",0);
	DrawFormatString(0, 20, 0x00ff00, "F1でコンテニュー",0);
	DrawFormatString(0, 40, 0x00ff00, "SCORE...%d",lpResultCtl.GetLoadScoreData());
	int time = lpResultCtl.GetLoadTimeData();
	DrawFormatString(0, 60, 0x00ff00, "TIME...%d.%d.%d",time/3600,time/60%60,time%60);
	ScreenFlip();
	return true;
}

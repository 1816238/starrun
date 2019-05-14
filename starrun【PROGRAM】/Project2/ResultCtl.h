#pragma once
#include "classObj.h"

#define lpResultCtl ResultCtl::GetInstance()

class Obj;

class ResultCtl
{
public:
	static ResultCtl &GetInstance(void)
	{
		static ResultCtl s_Instance;
		return s_Instance;
	}
	ResultCtl();
	~ResultCtl();
	bool SetUp(const int score, const int time);
	bool ResultSave(sharedListObj objList);					//新しく制作したﾏｯﾌﾟ情報のｾｰﾌﾞ及びSUMﾁｪｯｸ
	bool ResultLoad(sharedListObj objList, bool objFlag);		//保存されたﾏｯﾌﾟ情報の読み込み及びSUMﾁｪｯｸ
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);

private:
	int score;
	int time;
};


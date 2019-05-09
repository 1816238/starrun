#include <DxLib.h>
#include "GameCtl.h"



GameCtl::GameCtl()
{
}


GameCtl::~GameCtl()
{
}

bool GameCtl::UpDate(void)
{
	dataOld = data;
	GetHitKeyStateAll(&data[0]);		// 全てのキーの入力状態を得る
	
	ClickOld = Click;
	Click = GetMouseInput();
	return true;
}

const KEY_ARRAY & GameCtl::GetCtl(KEY_TYPE type) const
{
	if (type == OLD)
	{
		return dataOld;
	}
	return data;
}

const bool GameCtl::GetClick(int mouse_type, KEY_TYPE type) const
{

	if (type == OLD)
	{
		return ClickOld & mouse_type;
	}
	return Click & mouse_type;
}

#pragma once

#include "VECTOR2.h"
class MapControl;
using namespace std;
#define lpSpeedMng SpeedMng::GetInstance()
#define Speed(x) SpeedMng::GetInstance().GetSpeed(x)	//Mainでﾒｲﾝのﾀｲﾑ+黄色い星の取得量/10*30、Subでｻﾌﾞのﾀｲﾑ+黄色い星の取得量/10*30が取得できる
#define SPEED 3

enum MapType {
	Main,
	Sub,
	Max
};


class SpeedMng
{
public:
	static SpeedMng &GetInstance(void)
	{
		static SpeedMng s_Instance;
		return s_Instance;
	}
	void move(void);
	int GetTime(void);
	void AddStar(void);
	int GetYellow(void);
	int GetSpeed(MapType type);
	bool GetFlag(MapType type);
private:
	SpeedMng();
	~SpeedMng();
	int speedTime[Max];
	int yellowstar;
	int SpeedCnt;
	int speed;
	bool speedFlag[Max];
	int time;
};


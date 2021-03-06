#pragma once
#include <vector>
#include <array>
#include "VECTOR2.h"
#include "classObj.h"
#include "SpeedMng.h"

enum MAP_ID
{
	MAP_ID_NON,
	MAP_ID_CLOUD1,
	MAP_ID_CLOUD2,
	MAP_ID_CLOUD3,
	MAP_ID_BLUE,
	MAP_ID_YELLOW,
	MAP_ID_GREEN,
	MAP_ID_RED,
	MAP_ID_PURPLE,
	MAP_ID_CLOUD_DOWN1,
	MAP_ID_CLOUD_DOWN2,
	MAP_ID_CLOUD_DOWN3,
	MAP_ID_FULL_MOON,
	MAP_ID_HALF_MOON,
	MAP_ID_CRESCENT_MOON,
	MAP_ID_MAX
};

 struct seasonBase{
	vector<MAP_ID> spring;
	vector<MAP_ID> summer;
	vector<MAP_ID> autumn;
	vector<MAP_ID> winter;
};

 struct seasonMap{
	vector<MAP_ID*> spring;
	vector<MAP_ID*> summer;
	vector<MAP_ID*> autumn;
	vector<MAP_ID*> winter;
};
 struct MapDataBase{
	seasonBase main;
	vector<MAP_ID> sub;
	seasonBase reload;
	
};

 struct MapData{
	seasonMap main;
	vector<MAP_ID*> sub;
	seasonMap reload;
};


#define lpMapControl MapControl::GetInstance()

class Obj;
//class SpeedMng;
using namespace std;

class MapControl
{
public:
	static MapControl &GetInstance(void)
	{
		static MapControl s_Instance;
		return s_Instance;
	}
	void Draw(bool TitleFlag);		//map画像の描画
	bool SetUp(const VECTOR2& size, const VECTOR2& chipsize, const VECTOR2 drawOffSet);
	bool SetMapData(const VECTOR2& pos, MAP_ID id, MapType type,SEASON season= SEASON::MAX);			//画像を配置しようとしている場所がmapの範囲内かの判定
	MAP_ID GetMapDate(const VECTOR2& pos,MapType type,SEASON season=SEASON::MAX);					//指定した座標の情報の取得,typeがtrueならmainのﾏｯﾌﾟﾃﾞｰﾀをfalseならsubのﾏｯﾌﾟﾃﾞｰﾀを返す
	bool LoadSpring(string FileName, sharedListObj objList, bool objFlag);
	bool LoadSummer(string FileName, sharedListObj objList, bool objFlag);
	bool LoadAutumn(string FileName, sharedListObj objList, bool objFlag);
	bool LoadWinter(string FileName, sharedListObj objList, bool objFlag);
	bool LoadSub(string FileName, sharedListObj objList, bool objFlag);
	bool MapLoad(string FileName,sharedListObj objList, bool objFlag,bool type,SEASON season=SEASON::MAX);		//保存されたﾏｯﾌﾟ情報の読み込み及びSUMﾁｪｯｸ
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);
	const VECTOR2 & GetChipSize(void);
	bool GetSubFlag(void);
	bool init(void);
	void ReLoadMap(void);
	MapControl(MapControl& in) {};
	void operator=(MapControl&in) {};
private:
	MapControl();
	~MapControl();
	MapDataBase mapDataBace;		//mapの情報を入れておく配列（1次元目）
	MapData mapData;			//mapの情報を入れておく配列（2次元目）
	VECTOR2 mapSize;			//mapの縦と横を入れておく変数
	VECTOR2 chipSize;			//分割後の1つ当たりの画像のｻｲｽﾞを入れておく変数
	VECTOR2 drawOffSet;		//どれだけずらすかの数値を入れておく変数
	VECTOR2 pos;
	bool SubFlag;
	array< int, int(SEASON::MAX)> offset;

};


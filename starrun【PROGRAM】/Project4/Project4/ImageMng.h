#pragma once
#include <map>
#include <vector>
#include <mutex>
#include "VECTOR2.h"

#ifdef _DEBUG
#define AST(){\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d行目￥0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "ｱｻｰﾄ表示", MB_OK);\
	}
#else
#define AST()
#endif    // _DEBUG
class VECTOR2;

using namespace std;
using VEC_INT = vector<int>;
#define lpImageMng ImageMng::GetInstance()
#define IMAGE_ID(X) (ImageMng::GetInstance().GetID(X))

class ImageMng
{
public:
	static ImageMng &GetInstance(void)
	{
		static ImageMng s_Instance;
		return s_Instance;
	}

	const VEC_INT& GetID(string f_name);			//ﾒﾓﾘの取得
	const VEC_INT& GetID(string f_name, VECTOR2 divSize, VECTOR2 divCnt);			//画像の分割読み込み

private:
	ImageMng();
	~ImageMng();
	//std::map<ｷｰの型,連想型配列の型> 連想配列名;
	//std::map<std::string, std::vector<int>> imgMap;
	map<string, VEC_INT> imgMap;
};


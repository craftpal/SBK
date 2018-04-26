#include "interface_cutout_gendxf.h"
using namespace PazzleClacDll;
using namespace cutout;

/*Convert: [cutout] CFrame => [gendxf]CDxfRectangle
* 受け取った長方形座標(CFrame)を長方形座標(CDxfRectangle)に変換
*Note+
* CFrame		  |	左上基準座標
* CDxfRectangle  |	右下基準座標
*/
CDxfRectangle CInterfaceRectance::toDxfRectangle(CFrame _frame) {
	CDxfCoordinate low_left, top_right;
	low_left.x = _frame.topL.x;
	low_left.y = _frame.lowR.y;
	top_right.x = _frame.lowR.x;
	top_right.y = _frame.topL.y;
	CDxfRectangle buff = CDxfRectangle(low_left, top_right);
	buff.laminate_id = _frame.laminate_id;
	return buff;
}

/*Convert: [cutout] CFrame => [gendxf]CDxfRectangle
* 受け取った複数の長方形座標(CFrame)を連続線座標(CDxfContinuum)に変換
*Note+
* CFrame		  |	左上基準座標
* CDxfContinuum  |	右下基準座標
*/
CDxfContinuum CInterfaceRectance::toDxfContinuum(std::vector<CFrame> _frame) {
	CDxfContinuum buff;
	std::vector<CDxfCoordinate> _coor;
	//下端の線分を追加
	_coor.push_back(CDxfCoordinate(_frame[_frame.size() - 1].topL.x, _frame[_frame.size() - 1].lowR.y));
	_coor.push_back(CDxfCoordinate(_frame[_frame.size() - 1].lowR.x, _frame[_frame.size() - 1].lowR.y));
	//下端上端以外の右辺と次の右辺を結ぶ線分を連続して追加
	for (int i = _frame.size() - 1; i > 0; i--) {
		//右辺を追加(Y方向上に動かすだけ)
		_coor.push_back(CDxfCoordinate(_frame[i].lowR.x, _frame[i].topL.y));
		//次の右辺を結ぶ線分を追加(X方向左右に動かすだけ)
		_coor.push_back(CDxfCoordinate(_frame[i - 1].lowR.x, _frame[i - 1].lowR.y));
	}
	//上端の線分を追加
	_coor.push_back(CDxfCoordinate(_frame[0].lowR.x, _frame[0].topL.y));
	_coor.push_back(CDxfCoordinate(_frame[0].topL.x, _frame[0].topL.y));
	//左辺を追加(最初の座標を追加するだけ)
	_coor.push_back(CDxfCoordinate(_frame[_frame.size() - 1].topL.x, _frame[_frame.size() - 1].lowR.y));
	//最後にﾊﾞｯﾌｧに追加
	for (int i = 0, len = _coor.size(); i < len; i++) {
		buff.forward(_coor[i]);
	}
	return buff;
}
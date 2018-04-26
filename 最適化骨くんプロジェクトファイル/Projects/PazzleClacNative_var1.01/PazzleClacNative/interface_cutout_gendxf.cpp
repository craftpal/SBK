#include "interface_cutout_gendxf.h"
using namespace PazzleClacDll;
using namespace cutout;

/*Convert: [cutout] CFrame => [gendxf]CDxfRectangle
* �󂯎���������`���W(CFrame)�𒷕��`���W(CDxfRectangle)�ɕϊ�
*Note+
* CFrame		  |	�������W
* CDxfRectangle  |	�E������W
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
* �󂯎���������̒����`���W(CFrame)��A�������W(CDxfContinuum)�ɕϊ�
*Note+
* CFrame		  |	�������W
* CDxfContinuum  |	�E������W
*/
CDxfContinuum CInterfaceRectance::toDxfContinuum(std::vector<CFrame> _frame) {
	CDxfContinuum buff;
	std::vector<CDxfCoordinate> _coor;
	//���[�̐�����ǉ�
	_coor.push_back(CDxfCoordinate(_frame[_frame.size() - 1].topL.x, _frame[_frame.size() - 1].lowR.y));
	_coor.push_back(CDxfCoordinate(_frame[_frame.size() - 1].lowR.x, _frame[_frame.size() - 1].lowR.y));
	//���[��[�ȊO�̉E�ӂƎ��̉E�ӂ����Ԑ�����A�����Ēǉ�
	for (int i = _frame.size() - 1; i > 0; i--) {
		//�E�ӂ�ǉ�(Y������ɓ���������)
		_coor.push_back(CDxfCoordinate(_frame[i].lowR.x, _frame[i].topL.y));
		//���̉E�ӂ����Ԑ�����ǉ�(X�������E�ɓ���������)
		_coor.push_back(CDxfCoordinate(_frame[i - 1].lowR.x, _frame[i - 1].lowR.y));
	}
	//��[�̐�����ǉ�
	_coor.push_back(CDxfCoordinate(_frame[0].lowR.x, _frame[0].topL.y));
	_coor.push_back(CDxfCoordinate(_frame[0].topL.x, _frame[0].topL.y));
	//���ӂ�ǉ�(�ŏ��̍��W��ǉ����邾��)
	_coor.push_back(CDxfCoordinate(_frame[_frame.size() - 1].topL.x, _frame[_frame.size() - 1].lowR.y));
	//�Ō���ޯ̧�ɒǉ�
	for (int i = 0, len = _coor.size(); i < len; i++) {
		buff.forward(_coor[i]);
	}
	return buff;
}
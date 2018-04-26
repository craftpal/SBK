#include "entities.h"
using namespace PazzleClacDll;
/* CDxfCoordinate
* �T�v: �_���W�N���X���`
*/
CDxfCoordinate::CDxfCoordinate() {}
CDxfCoordinate::CDxfCoordinate(int _x, int _y) {
	this->x = _x;
	this->y = _y;
}
void CDxfCoordinate::show() {
	std::cout << "(" << x << "," << y << ")" << std::endl;
}
std::string CDxfCoordinate::toString() {
	//���l�𕶎���ɕϊ����邽�� (C++11��������...�����ƒN�������悤��...)
	std::stringstream buff_x, buff_y;
	buff_x << x;
	buff_y << y;

	return "(" + buff_x.str() + "," + buff_y.str() + ")";
}

/* CDxfLine
* �T�v: �����N���X���`
*/
CDxfLine::CDxfLine() {
	coor_start = CDxfCoordinate();
	coor_end = CDxfCoordinate();
}
CDxfLine::CDxfLine(CDxfCoordinate _coor_start, CDxfCoordinate _coor_end) {
	this->coor_start = _coor_start;
	this->coor_end = _coor_end;
}
unsigned int CDxfLine::size() {
	return 2;
}

/* CDxfContinuum
* �T�v: �A�����N���X���`
*/
CDxfContinuum::CDxfContinuum() {}
CDxfContinuum::CDxfContinuum(CDxfCoordinate _coor) {
	coor.push_back(_coor);
}
CDxfContinuum& CDxfContinuum::forward(CDxfCoordinate _coor) {
	this->coor.push_back(_coor);
	return *this;
}
CDxfContinuum& CDxfContinuum::back() {
	this->coor.pop_back();
	return *this;
}
void CDxfContinuum::show(int _index) {
	coor[_index].show();
}
unsigned int CDxfContinuum::size() {
	return coor.size();
}


/* CDxfRectangle
* �T�v: �����`�N���X���`
*/
void CDxfRectangle::setLine() {
	line.clear();	//��̊g�����l��������
	line.push_back(CDxfLine(low_left, CDxfCoordinate(top_right.x, low_left.y)));
	line.push_back(CDxfLine(CDxfCoordinate(top_right.x, low_left.y), top_right));
	line.push_back(CDxfLine(top_right, CDxfCoordinate(low_left.x, top_right.y)));
	line.push_back(CDxfLine(CDxfCoordinate(low_left.x, top_right.y), low_left));
}
CDxfRectangle::CDxfRectangle() {}
CDxfRectangle::CDxfRectangle(CDxfCoordinate _low_left, CDxfCoordinate _top_right) {
	this->low_left = _low_left;
	this->top_right = _top_right;
	setLine();
}
void CDxfRectangle::show() {
	std::cout << "����" << low_left.toString()
		<< " : �E��" << top_right.toString() << std::endl;
}
unsigned int CDxfRectangle::size() {
	return line.size();
}
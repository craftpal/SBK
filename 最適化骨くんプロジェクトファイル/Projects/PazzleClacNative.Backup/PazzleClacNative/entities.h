#pragma once

#include <iostream>
#include <sstream>
#include <vector>

/* �e�N���X�̃����o�֐� size() �͊e�N���X�̎��_�̐���Ԃ�
* �Ⴆ�΁A���N���X�� size() �͕K�� 2 ��Ԃ��A���̖{���ł͂Ȃ��̂Œ���
*/

//�}�`�͑S�ē_(���W:coordinate)�̏W�܂�Ƃ��Ē�`����
namespace PazzleClacDll{
	class CDxfCoordinate{
	public:
		int x, y;
		CDxfCoordinate();
		CDxfCoordinate(int _x, int _y);
		void show();
		std::string toString();
	};

	class CDxfLine{
	public:
		CDxfCoordinate coor_start, coor_end;
		CDxfLine();
		CDxfLine(CDxfCoordinate _coor_start, CDxfCoordinate _coor_end);
		unsigned int size();
	};

	class CDxfContinuum{
	public:
		std::vector<CDxfCoordinate> coor;
		CDxfContinuum();
		CDxfContinuum(CDxfCoordinate _coor);
		CDxfContinuum& forward(CDxfCoordinate _coor);
		CDxfContinuum& back();
		void show(int _index);
		unsigned int size();
	};

	class CDxfRectangle{
	private:
		void setLine();
	public:
		CDxfCoordinate low_left, top_right;
		std::vector<CDxfLine> line;
		CDxfRectangle();
		CDxfRectangle(CDxfCoordinate _low_left, CDxfCoordinate _top_right);
		void show();
		unsigned int size();
	};
}

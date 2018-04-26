#pragma once

#include <iostream>
#include <sstream>
#include <vector>

/* 各クラスのメンバ関数 size() は各クラスの持つ点の数を返す
* 例えば、線クラスの size() は必ず 2 を返す、線の本数ではないので注意
*/

//図形は全て点(座標:coordinate)の集まりとして定義する
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

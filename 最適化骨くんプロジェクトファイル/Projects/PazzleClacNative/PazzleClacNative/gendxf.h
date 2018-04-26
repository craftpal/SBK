#pragma once

#include <sstream>
#include "entities.h"
namespace PazzleClacDll
{
	class CGenerateDxfData {
	private:
		std::string SECTION;
		std::string ENDSEC;
		std::string TABLES;
		std::string ENDTAB;
		std::string LAYERS;
		std::string LAYER;
		std::string ENTITIES;
		std::string END;
		enum COLOR { RED = 1, YELLOW, GREEN, LIGHTBLUE, BLUE, PURPLE, WHITE, GRAY, BLACK };
		std::string str_dxf;
		//�A�����P�ʂŊǗ�����(�_�ŊǗ�����Ƌ�؂肪�t���Ȃ�����)
		std::vector<CDxfContinuum> continuum;
		std::string genStrLINE(std::string layer_name, CDxfCoordinate _coor_start, CDxfCoordinate _coor_end);
		void genDxf();
		void genDxf2();
	public:
		//�S�͈̔͂����߂ɒǉ�����(��ԍŏ��̃��C���[�ɂ���)
		CGenerateDxfData(CDxfContinuum _continuum);
		CGenerateDxfData push(CDxfLine _line);
		CGenerateDxfData push(CDxfContinuum _continuum);
		CGenerateDxfData push(CDxfRectangle _rectangle);
		std::string getDxfString();
	};
}
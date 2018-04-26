#include "gendxf.h"
using namespace PazzleClacDll;

std::string CGenerateDxfData::genStrLINE(std::string layer_name, CDxfCoordinate _coor_start, CDxfCoordinate _coor_end){
	std::stringstream buff;
	buff << "0\nLINE\n8\n" << layer_name << "\n10\n" << _coor_start.x
		<< "\n20\n" << _coor_start.y << "\n11\n" << _coor_end.x << "\n21\n"
		<< _coor_end.y << "\n";
	return buff.str();
}

void CGenerateDxfData::genDxf(){
	str_dxf.clear();	//初期化
	char *layer_num = "20";
	str_dxf.append(SECTION + TABLES);
	str_dxf.append(LAYERS + "70\n" + layer_num + "\n");
	//画層定義
	str_dxf.append(LAYER + "2\n" + "モモクロの緑" + "\n70\n0\n62\n" + "3" + "\n6\nCONTINUOUS\n");
	str_dxf.append(LAYER + "2\n" + "プレプリグ1" + "\n70\n0\n62\n" + "1" + "\n6\nCONTINUOUS\n");
	str_dxf.append(LAYER + "2\n" + "プレプリグ2" + "\n70\n0\n62\n" + "2" + "\n6\nCONTINUOUS\n");
	str_dxf.append(LAYER + "2\n" + "プレプリグ3" + "\n70\n0\n62\n" + "4" + "\n6\nCONTINUOUS\n");
	str_dxf.append(LAYER + "2\n" + "プレプリグ4" + "\n70\n0\n62\n" + "5" + "\n6\nCONTINUOUS\n");
	str_dxf.append(LAYER + "2\n" + "プレプリグ5" + "\n70\n0\n62\n" + "6" + "\n6\nCONTINUOUS\n");
	str_dxf.append(ENDTAB + ENDSEC);
	char *layer_name = "プレプリグ";
	str_dxf.append(SECTION + ENTITIES);
	for(int i = 0, len = continuum.size(); i < len; i++){
		for(int j = 0, len = continuum[i].size()-1; j < len; j++){
			if(!i){
				str_dxf.append(genStrLINE("モモクロの緑", continuum[i].coor[j], continuum[i].coor[j+1]));
			}else{
				std::stringstream buff;
				buff << layer_name << i%5+1;
				str_dxf.append(genStrLINE(buff.str(), continuum[i].coor[j], continuum[i].coor[j+1]));
			}
		}
	}
	str_dxf.append(ENDSEC + END);
}

CGenerateDxfData::CGenerateDxfData(CDxfContinuum _continuum){
	SECTION		= "0\nSECTION\n";
	ENDSEC		= "0\nENDSEC\n";
	TABLES		= "2\nTABLES\n0\nTABLE\n";
	ENDTAB		= "0\nENDTAB\n";
	LAYERS		= "2\nLAYER\n";
	LAYER		= "0\nLAYER\n";
	ENTITIES	= "2\nENTITIES\n";
	END			= "0\nEOF\n";
	push(_continuum);
}

CGenerateDxfData CGenerateDxfData::push(CDxfLine _line){
	CDxfContinuum buff = CDxfContinuum(_line.coor_start);
	buff.forward(_line.coor_end);
	continuum.push_back(buff);
	return *this;
}

CGenerateDxfData CGenerateDxfData::push(CDxfContinuum _continuum){
	continuum.push_back(_continuum);
	return *this;
}

CGenerateDxfData CGenerateDxfData::push(CDxfRectangle _rectangle){
	CDxfContinuum buff = CDxfContinuum(_rectangle.low_left);
	for(int i = 0, len = _rectangle.size(); i < len; i++){
		buff.forward(_rectangle.line[i].coor_end);
	}
	continuum.push_back(buff);
	return *this;
}

std::string CGenerateDxfData::getDxfString(){
	genDxf();
	return str_dxf;
}
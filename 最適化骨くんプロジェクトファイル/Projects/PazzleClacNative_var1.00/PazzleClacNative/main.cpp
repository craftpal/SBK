#include <fstream>
#include <windows.data.json.h>
#include "cutout.h"
#include "gendxf.h"
#include "interface_cutout_gendxf.h"
#include "json_perser.h"

using namespace PazzleClacDll;

int main(int argc, char *argv[]) {
	//�e�X�g�f�[�^(json�`���ǂݍ��݃e�X�g)
	json_perser::CJsonPerser jsper;
	if (argc == 1) {
		jsper.load_json_file("input.json");
	} else {
		jsper.load_json_file(argv[1]);
	}
	if (!jsper.err.empty()) {
		std::cout << jsper.err << std::endl;
		system("pause");
		return -1;
	}
	CListRectance lire_targets = jsper.get("target");
	CListRectance lire_parts = jsper.get("parts");
	std::cout << "�ǂݍ��݊���" << std::endl;
	std::cout << "�v�Z���J�n���Ă���낵���ł��傤��." << std::endl;
	system("pause");

	CCoreRectance core = CCoreRectance(lire_targets, lire_parts);
	std::vector<CFrame> results = core.cutouts();

	//�S�͈̔͂̌v�Z
	std::vector<CFrame> frame_union;
	for (int i = 0, len = lire_targets.lenght(); i < len; i++) {
		int Upp_Y = 0, Low_Y = 0;	//�S�̂̏�[���畔�i�̏�[�܂ł̍����ƁA���i�̉��[�܂ł̍���
		for (int j = 0; j < i + 1; j++) {
			Low_Y += lire_targets.get(j).Y();
		}
		if (i) {
			for (int j = 0; j < i; j++) {
				Upp_Y += lire_targets.get(j).Y();
			}
		}
		frame_union.push_back(CFrame(
			CXY(0, Upp_Y),
			CXY(lire_targets.get(i).X(), Low_Y)
			));
	}

	/* Dxf�`���o�� */

	//Cutout�`������Dxf�`���ɕϊ�
	CDxfContinuum dxf_union = CDxfContinuum(CInterfaceRectance::toDxfContinuum(frame_union));
	std::vector<CDxfRectangle> dxf_result;
	for (int i = 0, len = results.size(); i < len; i++) {
		dxf_result.push_back(CInterfaceRectance::toDxfRectangle(results[i]));
	}

	CGenerateDxfData gendxf = CGenerateDxfData(dxf_union);
	for (int i = 0, len = dxf_result.size(); i < len; i++) {
		gendxf.push(dxf_result[i]);
	}

	std::string filepath;
	std::cout << "�o�̓t�@�C����, ���͏o�̓t�@�C���p�X����͂��Ă�������" << std::endl;
	std::cout << "(.dxf)>";
	filepath.clear();
	std::cin >> filepath;
	if (filepath.size() < 5 || filepath.find(".dxf", filepath.size() - 4) != filepath.size() - 4) {
		filepath.append(".dxf");
	}
	std::ofstream ofs(filepath.c_str());
	ofs << gendxf.getDxfString() << std::endl;

	//std::ifstream ifs("input.json");
	//picojson::object o;
	//std::cout << picojson::value(o).serialize() << std::endl;

	return 0;
}
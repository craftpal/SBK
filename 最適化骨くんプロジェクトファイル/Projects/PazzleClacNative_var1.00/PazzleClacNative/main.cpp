#include <fstream>
#include <windows.data.json.h>
#include "cutout.h"
#include "gendxf.h"
#include "interface_cutout_gendxf.h"
#include "json_perser.h"

using namespace PazzleClacDll;

int main(int argc, char *argv[]) {
	//テストデータ(json形式読み込みテスト)
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
	std::cout << "読み込み完了" << std::endl;
	std::cout << "計算を開始してもよろしいでしょうか." << std::endl;
	system("pause");

	CCoreRectance core = CCoreRectance(lire_targets, lire_parts);
	std::vector<CFrame> results = core.cutouts();

	//全体範囲の計算
	std::vector<CFrame> frame_union;
	for (int i = 0, len = lire_targets.lenght(); i < len; i++) {
		int Upp_Y = 0, Low_Y = 0;	//全体の上端から部品の上端までの高さと、部品の下端までの高さ
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

	/* Dxf形式出力 */

	//Cutout形式からDxf形式に変換
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
	std::cout << "出力ファイル名, 又は出力ファイルパスを入力してください" << std::endl;
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
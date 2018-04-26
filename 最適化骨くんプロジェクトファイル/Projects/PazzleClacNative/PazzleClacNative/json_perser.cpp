#include "json_perser.h"

using namespace json_perser;

CJsonPerser::CJsonPerser() {}

void CJsonPerser::load_json_file(std::string path) {
	ifstream ifs = ifstream(path);
	if (!ifs) {
		err = "Couldn't open file!: [" + path + "]";
#ifdef _DEBUG
		cout << err << endl;
#endif //DEBUG
		return;
	}
	string buff, data;
	while (ifs >> buff) data.append(buff);
	picojson::parse(json, data);
#ifdef _DEBUG
	cout << json.serialize() << endl;
#endif //DEBUG
}

cutout::CListRectance CJsonPerser::get(string key) {
	picojson::object& obj = json.get < picojson::object >();
	cutout::CListRectance buff;

	//picojson::array (key="target")
	if (key == "target") {
		for (int i = 0, len = obj[key].get<picojson::array>().size(); i < len; i++) {
			picojson::value item = obj[key].get<picojson::array>()[i];
			picojson::object obj_item = item.get < picojson::object >();
#ifdef _DEBUG
			cout << "(" << (int)obj_item["x"].get<double>()
				<< "," << (int)obj_item["y"].get<double>() << ")" << endl;
#endif // _DEBUG
			buff.add(cutout::CRectance(
				(int)obj_item["x"].get<double>(), (int)obj_item["y"].get<double>()
				));
		}
	}

	//picojson::object (key="parts")
	if (key == "parts") {
		for (int i = 0, len = obj[key].get<picojson::array>().size(); i < len; i++) {
			picojson::value item = obj[key].get<picojson::array>()[i];
			picojson::object obj_item = item.get < picojson::object >();
#ifdef _DEBUG
			cout << obj_item["id"].get<string>() << "‘w–Ú: (" << (int)obj_item["x"].get<double>()
				<< "," << (int)obj_item["y"].get<double>() << ")" << endl;
#endif // _DEBUG
			buff.add(cutout::CRectance(
				(int)obj_item["x"].get<double>(), (int)obj_item["y"].get<double>(),
				obj_item["id"].get<string>()
				));
		}
	}

	return buff;
}
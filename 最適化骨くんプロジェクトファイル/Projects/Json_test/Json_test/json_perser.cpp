#include "json_perser.h"

using namespace json_perser;

CJsonPerser::CJsonPerser(){}

void CJsonPerser::load_json_file(std::string path){
	ifstream ifs = ifstream(path);
	if (!ifs){
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

cutout::CListRectance CJsonPerser::get(string key){
	picojson::object& obj = json.get < picojson::object >();
	cutout::CListRectance buff;

	//picojson::array (key="target")
	if (obj[key].is<picojson::array>()){
		for (int i = 0, len = obj[key].get<picojson::array>().size(); i < len; i++){
			picojson::value item = obj[key].get<picojson::array>()[i];
			picojson::object obj_item = item.get < picojson::object >();
			buff.add(cutout::CRectance(
				(int)obj_item["x"].get<double>(), (int)obj_item["y"].get<double>()
				));
		}
	}

	//picojson::object (key="parts")
	if (obj[key].is<picojson::object>()){
		picojson::object& parts = obj[key].get<picojson::object>();
		for (picojson::object::iterator it = parts.begin(); it != parts.end(); it++)
		{
			if (!it->second.is<picojson::object>()) continue;
#ifdef _DEBUG
			cout << it->first << "‘w–Ú: " << it->second << endl;
#endif // _DEBUG
			picojson::object obj_item = it->second.get<picojson::object>();
			buff.add(cutout::CRectance(
				(int)obj_item["x"].get<double>(), (int)obj_item["y"].get<double>()
				));
		}
	}

	return buff;
}
#include <iostream>
#include "json_perser.h"
#include "cutout.h"

using namespace std;

int main(){
	const char *path = "input.json";

	json_perser::CJsonPerser jper;
	jper.load_json_file(path);

	picojson::value json = jper.json;
	picojson::object& obj = json.get<picojson::object>();

	cout << "----- target -----" << endl;
	for (int i = 0, len = obj["target"].get<picojson::array>().size(); i < len; i++){
		cout << obj["target"].get<picojson::array>()[i] << endl;
	}

	cout << "----- num: parts -----" << endl;
	for (picojson::object::iterator it = obj["parts"].get<picojson::object>().begin();
		it != obj["parts"].get<picojson::object>().end();
		it++)
	{
		if (!it->second.is<picojson::object>()) continue;
		cout << it->first << "‘w–Ú: " << it->second << endl;
	}

	cout << "----- target -----" << endl;
	cutout::CListRectance target = jper.get("target");
	for (int i = 0, len = target.lenght(); i < len; i++){
		cout << "(" << target.get(i).X() << ", " << target.get(i).Y() << ")" << endl;
	}

	cout << "----- parts -----" << endl;
	cutout::CListRectance parts = jper.get("parts");
	for (int i = 0, len = parts.lenght(); i < len; i++){
		cout << "(" << parts.get(i).X() << ", " << parts.get(i).Y() << ")" << endl;
	}

	return 0;
}
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "picojson.h"
#include "cutout.h"

using namespace std;

namespace json_perser{
	class CJsonPerser
	{
	public:
		picojson::value json;
		string err;
		CJsonPerser();
		void load_json_file(std::string path);
		cutout::CListRectance get(string key);
	};
}
// MIT License

// Copyright (c) 2017 - 2018 Vasileios Kon. Pothos (terablade2001)
// https://github.com/terablade2001/vkp_Config

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "vkpConfigReader.hpp"

namespace vkp_Config {


int cfg_LoadFile(const char* cfgfile, cfg_type& cfg_data) {
	if (cfgfile == nullptr) {
		std::cout << "LoadConfigFile: 1rsg arg = NULL. Aborting..." << std::endl;
		return -1;
	}

	cfg_data.clear();

	std::string read_string;
	std::fstream infile;
	infile.open(cfgfile);
	if (!infile.is_open()) {
		std::cout << "cfg_LoadFile(): Failed to load [" << cfgfile << "] file." <<
			std::endl;
		return -1;
	}
	while(!infile.eof()) {
		size_t pos;
		std::getline(infile, read_string);
		pos = read_string.find("#",0);
		if (pos == 0) continue;
		pos = read_string.find(" ",0);
		if (pos == 0) {
			std::cout << "Error: " << std::string(cfgfile) << " contain space!" <<
			std::endl;
			infile.close();
			return -1;
		}

		pos = read_string.find(": ",0,2);
		int spacebar=2;
		if (pos == std::string::npos) { pos = read_string.find(":",0); spacebar--; }
		if (pos == std::string::npos) continue;
		if (pos == 0) continue;

		cfg_data.push_back(
			std::pair<std::string,std::string>(
				read_string.substr(0, pos),
				read_string.substr(pos+spacebar)
			)
		);
	}
	if (infile.bad()) {
		std::cout << "cfg_LoadFile(): Error while reading [" << cfgfile <<
			"] file." << std::endl;
		return -1;
	}
	return 0;
}


void cfg_ValueConvert(std::string& string_value, std::string& value) {
	value.assign(string_value);
}


int cfg_CheckParams(
	cfg_type& cfg_data,
	std::vector<std::string>& checklist,
	std::string& missing_params
) {
	missing_params.clear();
	int r = 0;
	for (auto const& i : checklist) {
		auto it = std::find_if(cfg_data.begin(), cfg_data.end(),
			[i](const std::pair<std::string, std::string>& el) {
				return el.first == i;
			}
		);
		if (it == cfg_data.end()) {
			r=1;
			if (missing_params.length() != 0)
				missing_params.append(", ");
			missing_params.append(i);
		}
	}
	return r;
}

}; // namespace vkp_Config

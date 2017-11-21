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

#ifndef __VKP_CONFIG_READER__HPP__
#define __VKP_CONFIG_READER__HPP__
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#ifdef _MSC_VER
	#include <string>
#endif

#define VERSION_STRING "[0.016]"

namespace vkp_Config {

typedef std::vector<std::pair<std::string,std::string>> cfg_type;



int cgf_LoadFile(const char* cfgfile, cfg_type& cfg_data);

void cfg_ValueConvert(std::string& string_value, std::string& value);

template <typename T>
void cfg_ValueConvert(std::string& string_value, T& value);

template <typename T>
int cgf_GetParam(cfg_type& cfg_data, const char* param, T& value);

int cfg_CheckParams(
	cfg_type& cfg_data,
	std::vector<std::string>& checklist,
	std::string& missing_params
);





// ------------------------ Implementation -------------------------------------
template <typename T>
void inline cfg_ValueConvert(std::string& string_value, T& value) {
	 if (std::is_same<T, int>::value)
		value = std::stoi(string_value);
	else if (std::is_same<T, float>::value)
		value = std::stof(string_value);
	else if (std::is_same<T, double>::value)
		value = std::stod(string_value);
	else if (std::is_same<T, long int>::value)
		value = std::stol(string_value);
	else if (std::is_same<T, long double>::value)
		value = std::stold(string_value);
	else if (std::is_same<T, long long>::value)
		value = std::stoll(string_value);
	else if (std::is_same<T, unsigned long>::value)
		value = std::stoul(string_value);
	else if (std::is_same<T, unsigned long long>::value)
		value = std::stoull(string_value);
	else if (std::is_same<T, bool>::value)
		value = (bool)std::stoi(string_value);
	else {
		std::cout << "cfg_ValueConvert(): Not defined type!" << std::endl;
	}
}

template <typename T>
int inline cgf_GetParam(cfg_type& cfg_data, const char* param, T& value) {
	if (param == nullptr) {
		std::cout << "cfg_GetParam():: Error: 2nd argument == NULL. Aborting." <<
		std::endl;
		return -1;
	}
	std::string string_param(param);
	auto it = std::find_if(cfg_data.begin(), cfg_data.end(),
			[param](const std::pair<std::string, std::string>& el) {
				return el.first == param;
			}
		);

	if (it == cfg_data.end()) {
		std::cout << "cgf_GetParam():: Error: [" << param << "] not found!" <<
		std::endl;
		return -1;
	}

	cfg_ValueConvert((*it).second, value);
	return 0;
}

}; // namespace vkp_Config

#endif

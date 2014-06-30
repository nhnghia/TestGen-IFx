/*
 * Tool.cpp
 *
 *  Created on: 29 juin 2014
 *      Author: nhnghia
 */

#include "Tool.h"
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

namespace tsp {

Tool::Tool() {

}

Tool::~Tool() {
}

std::vector<std::string> Tool::split(const std::string &text, char delim){
	std::vector<std::string> elems;

	int start = 0, end = 0;
	std::string s;
	while ((end = text.find(delim, start)) != std::string::npos) {
		s = text.substr(start, end - start);
		if (!s.empty())
			elems.push_back(s);
	    start = end + 1;
	}
	s = text.substr(start);
	if (!s.empty())
		elems.push_back(s);

	return elems;
}
} /* namespace tsp */

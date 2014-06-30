/*
 * Tool.h
 *
 *  Created on: 29 juin 2014
 *      Author: nhnghia
 */

#ifndef TOOL_H_
#define TOOL_H_

#include <string>
#include <vector>

namespace tsp {

class Tool {
public:
	Tool();
	virtual ~Tool();
	static std::vector<std::string> split(const std::string &s, char delim);
};

} /* namespace tsp */

#endif /* TOOL_H_ */

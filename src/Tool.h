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
#include <sstream>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <iostream>
#include <xercesc/framework/MemBufInputSource.hpp>

#include "simulator.h"

using namespace std;
using namespace xercesc;
namespace tsp {

class Tool {
public:
	Tool();
	virtual ~Tool();
	/**
	 * split a string separated by "delim"
	 */
	static vector<std::string> split(const string &str, char delim);

	/**
	 * init Xercesc Engine
	 */
	static bool initXmlEngine();
	static bool endXmlEngine();

	static string xmlNode2String(const DOMNode *node);

	static DOMDocument *parserXml(string txt);

	/**
	 * return value of the first attribute that has "name"
	*/
	static string getXmlAttributeValue(const DOMNode *node, string name);

	/**
	 * return a DOMNode of the first element that has "name"
	*/
	static DOMNode* getXmlNodeByTagName(const DOMNode *node, string name);


	/**
	 * return value of the first element that has "name"
	 */
	static string getXmlElementValue(const DOMNode *node, string name);

	//IfObject
	static string ifObject2Xml(const IfObject *obj);

	/**
	 * return a hash of a string
	 * @param str
	 */
	static unsigned long hash(const char* str);

};

} /* namespace tsp */

#endif /* TOOL_H_ */

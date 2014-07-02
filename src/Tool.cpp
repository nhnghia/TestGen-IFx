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

std::vector<std::string> Tool::split(const std::string &text, char delim) {
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

bool tsp::Tool::initXmlEngine() {
	static bool xercesInit = false;
	if (xercesInit)
		return true;
	xercesInit = true;

	try {
		XMLPlatformUtils::Initialize();
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Error during initialization! :\n" << message << "\n";
		XMLString::release(&message);
		return false;
	}
	return true;
}

bool tsp::Tool::endXmlEngine() {
	return true;
}

DOMDocument* tsp::Tool::parserXml(string myxml) {
	if (!initXmlEngine() || myxml.empty())
		return NULL;

	XercesDOMParser* parser = new XercesDOMParser();
	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setDoNamespaces(true);    // optional

	ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
	parser->setErrorHandler(errHandler);

	try {
		MemBufInputSource src((const XMLByte*) myxml.c_str(), myxml.length(),
				"dummy", false);

		parser->parse(src);

	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n" << message << "\n";
		XMLString::release(&message);
		return NULL;
	} catch (const DOMException& toCatch) {
		char* message = XMLString::transcode(toCatch.msg);
		cout << "Exception message is: \n" << message << "\n";
		XMLString::release(&message);
		return NULL;
	} catch (...) {
		cout << "Unexpected Exception \n";
		return NULL;
	}

	DOMDocument* doc;
	doc = parser->getDocument();

	delete errHandler;
	return doc;
}

string tsp::Tool::xmlNode2String(DOMNode* node) {
	if (!initXmlEngine())
		return NULL;

	DOMImplementation *implementation =
			DOMImplementationRegistry::getDOMImplementation(
					XMLString::transcode("LS"));

	// Create a DOMLSSerializer which is used to serialize a DOM tree into an XML document.
	DOMLSSerializer *serializer =
			((DOMImplementationLS*) implementation)->createLSSerializer();
	// Make the output more human readable by inserting line feeds.
	if (serializer->getDomConfig()->canSetParameter(
			XMLUni::fgDOMWRTFormatPrettyPrint, true))
		serializer->getDomConfig()->setParameter(
				XMLUni::fgDOMWRTFormatPrettyPrint, true);

	// The end-of-line sequence of characters to be used in the XML being written out.
	serializer->setNewLine(XMLString::transcode("\r\n"));

	return XMLString::transcode(serializer->writeToString(node));

}

string tsp::Tool::getXmlAttributeValue(DOMNode *node, string name) {
	if (!initXmlEngine())
		return NULL;

	if (node->getNodeType() &&  // true is not NULL
			node->getNodeType() == DOMNode::ELEMENT_NODE) // is element
					{
		DOMElement* elem = dynamic_cast<xercesc::DOMElement*>(node);
		const XMLCh *val = elem->getAttribute(XMLString::transcode(name.c_str()));
		string str = XMLString::transcode(val);
		if (!str.empty()){
			return str;
		}
	}

	DOMNodeList* list = node->getChildNodes();
	int n = list->getLength();
	for (XMLSize_t i = 0; i < n; i++) {
		string str = tsp::Tool::getXmlAttributeValue(list->item(i), name);
		if (!str.empty())
			return str;
	}
	return "";
}

string tsp::Tool::getXmlElementValue(DOMNode *node, string name) {
	if (!initXmlEngine())
			return NULL;
}

string tsp::Tool::ifObject2Xml(IfObject* obj) {
	if (obj == NULL)
		return NULL;
	stringstream buf;
	obj->printXML(buf);
	return buf.str();
}

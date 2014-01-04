#pragma once

#include <map>
#include "ofTypes.h"
#include "ofParameter.h"
#include "ofRectangle.h"

class ofxFlowNode
{
	friend class ofxFlowGraph;
	
	public:
	
		struct Connection
		{
			Connection() {};
			Connection(ofxFlowNode *node, string paramName) : node(node), paramName(paramName) {};
			ofxFlowNode *node;
			string paramName;
		};
		
		string name;
		ofRectangle rect;
	
		ofxFlowNode(std::string name);
	
		virtual void evaluate() = 0;
		virtual void customDraw();
	
		// Don't override. Override customDraw instead.
		void draw();
	
		void connectInputTo(const string &inputParamName, ofxFlowNode *outputNode, const string &outputParamName);
		void connectOutputTo(const string &outputParamName, ofxFlowNode *inputNode, const string &inputParamName);
		void setInputValue(const string &name, ofPtr<ofAbstractParameter> value);
		int getInputIndex(const string &inputName);
		int getOutputIndex(const string &outputName);
		ofRectangle getInputRect(const int &index);
		ofRectangle getInputRect(const string &inputName);
		ofRectangle getOutputRect(const int &index);
		ofRectangle getOutputRect(const string &outputName);
		ofPtr<ofAbstractParameter> getOutputValue(const string name);
	
	protected:
	
		vector<string> _inputs;
		vector<string> _outputs;
		map<string, Connection> _inputConnections;
		multimap<string, Connection> _outputConnections;
		map<string, ofPtr<ofAbstractParameter> > _outputValues;
		map<string, ofPtr<ofAbstractParameter> > _inputValues;
	
		void _addInput(string name);
		void _addOutput(string name);
		void _setOutputValue(string name, ofPtr<ofAbstractParameter> value);
	
		template <typename inType>
		inType _getInputValue(string name)
		{
			ofPtr<ofAbstractParameter> p = _getInputValue(name);
			inType v = dynamic_cast<ofParameter<inType> *>(p.get())->get();
			
			return v;
		}
	
		ofPtr<ofAbstractParameter> _getInputValue(string name);
};

typedef ofPtr<ofxFlowNode> ofxFlowNodePtr;

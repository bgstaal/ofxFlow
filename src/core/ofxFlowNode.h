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
	
		void connectInputTo(string inputParamName, ofxFlowNode *outputNode, string outputParamName);
		void connectOutputTo(string outputParamName, ofxFlowNode *inputNode, string inputParamName);
		int getInputIndex(string inputName);
		int getOutputIndex(string outputName);
		void setInputValue(string name, ofPtr<ofAbstractParameter> value);
		ofPtr<ofAbstractParameter> getOutputValue(string name);
	
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
		ofPtr<ofAbstractParameter> _getInputValue(string name);
};

typedef ofPtr<ofxFlowNode> ofxFlowNodePtr;

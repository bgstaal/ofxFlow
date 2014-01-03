#ifndef __emptyExample__Node__
#define __emptyExample__Node__

#include <map>
#include "ofTypes.h"
#include "ofParameter.h"
#include "ofRectangle.h"

class Node
{
	friend class ofxFlowGraph;
	
	public:
	
		struct Connection
		{
			Connection() {};
			Connection(Node *node, string paramName) : node(node), paramName(paramName) {};
			Node *node;
			string paramName;
		};
		
		string name;
		ofRectangle rect;
	
		Node(std::string name);
	
		virtual void evaluate() = 0;
		virtual void draw();
	
		void connectInputTo(string inputParamName, Node *outputNode, string outputParamName);
		void connectOutputTo(string outputParamName, Node *inputNode, string inputParamName);
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

typedef ofPtr<Node> NodePtr;

#endif /* defined(__emptyExample__Node__) */

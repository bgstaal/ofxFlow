#pragma once

#include <map>
#include "ofTypes.h"
#include "ofParameter.h"
#include "ofRectangle.h"

class ofxFlowNode
{
	friend class ofxFlowGraph;
	
	public:
	
		enum PORT_TYPE
		{
			PORT_TYPE_INPUT = 0,
			PORT_TYPE_OUTPUT
		};
		
		class ofxFlowNodeEventArgs : public ofEventArgs
		{
			public:
				ofxFlowNode *node;
				string paramName;
		};
	
		ofEvent<ofxFlowNodeEventArgs> inputMouseDown;
		ofEvent<ofxFlowNodeEventArgs> inputMouseUp;
		ofEvent<ofxFlowNodeEventArgs> outputMouseDown;
		ofEvent<ofxFlowNodeEventArgs> outputMouseUp;
	
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
	
		virtual bool validate() = 0;
		virtual void evaluate() = 0;
		virtual void customDraw();
	
		// Don't override. Override customDraw instead.
		void draw();
	
		void mousePressed(const ofPoint &p);
		void mouseReleased(const ofPoint &p);
		bool isDraggableAtPoint(const ofPoint &p);
		void connectInputTo(const string &inputParamName, ofxFlowNode *outputNode, const string &outputParamName);
		void connectOutputTo(const string &outputParamName, ofxFlowNode *inputNode, const string &inputParamName);
		void disconnectInputFrom(const string &inputParamName, ofxFlowNode *outputNode, const string &outputParamName);
		void disconnectOutputTo(const string &outputParamName, ofxFlowNode *inputNode, const string &inputParamName);
		void setInputValue(const string &name, ofPtr<ofAbstractParameter> value);
		int getInputIndex(const string &inputName);
		int getOutputIndex(const string &outputName);
		string getInputName(int index);
		string getOutputName(int index);
		int getInputIndexAtPoint(const ofPoint &p);
		int getOutputIndexAtPoint(const ofPoint &p);
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
		void _notifyEvent(ofEvent<ofxFlowNodeEventArgs> &event, const string &paramName);
		bool _doesAllInputValuesExist();
	
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

#pragma once

#include "ofxFlowNode.h"

template<typename T>
class ofxFlowNodeSin : public ofxFlowNode
{
	public:

		ofxFlowNodeSin (string name = "Sin")
		:ofxFlowNode(name)
		{
			_addInput("value1");
			_addOutput("result");
		};
	
		virtual void evaluate ()
		{
			T r = sin(_getInputValue<T>("value1"));
			_setOutputValue("result", ofPtr<ofAbstractParameter>(new ofParameter<float>(r)));
		}
	

};

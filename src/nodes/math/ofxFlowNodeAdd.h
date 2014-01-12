#pragma once

#include "ofxFlowNode.h"

class ofxFlowNodeAdd : public ofxFlowNode
{
	public:
	
		ofxFlowNodeAdd ()
		: ofxFlowNode("addition")
		{
			_addInput("value1");
			_addInput("value2");
			_addOutput("result");
		}
		
		void customDraw()
		{
			ofxFlowNode::customDraw();
			
			if (validate())
			{
				stringstream ss;
				ss << _getInputValue("value1")->toString() << " + " << _getInputValue("value2")->toString() << " = " << getOutputValue("result")->toString() << endl;
				
				ofSetColor(150);
				ofDrawBitmapString(ss.str(), 10, 100);
			}
		}
	
		virtual bool validate()
		{
			return _doesAllInputValuesExist();
		}
		
		virtual void evaluate()
		{
			float v1 = _getInputValue<float>("value1");
			float v2 = _getInputValue<float>("value2");
			
			_setOutputValue("result", ofPtr<ofAbstractParameter>(new ofParameter<float>(v1 + v2)));
		}
};

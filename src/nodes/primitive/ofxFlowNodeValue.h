#pragma once

#include "ofxFlowNode.h"

template <typename T>
class ofxFlowNodeValue : public ofxFlowNode
{
	public:
		
		ofPtr<ofParameter<T> > value;
	
		ofxFlowNodeValue(string name, T val)
		:ofxFlowNode(name)
		{
			value = ofPtr<ofParameter<T> >(new ofParameter<T>(val));
			_addOutput("value");
		}
	
		virtual bool validate()
		{
			return true;
		}
		
		virtual void evaluate()
		{
			_setOutputValue("value", value);
		}
	
		virtual void customDraw ()
		{
			ofxFlowNode::customDraw();
			
			stringstream ss;
			ss << value->toString() << endl;
			
			ofSetColor(150);
			ofDrawBitmapString(ss.str(), ofPoint(rect.width - 40, 20));
		}
};

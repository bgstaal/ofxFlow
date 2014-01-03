#ifndef __emptyExample__NodeValue__
#define __emptyExample__NodeValue__

#include "ofxFlowNode.h"

template <typename T>
class ofxFlowNodeValue : public ofxFlowNode
{
	public:
		ofxFlowNodeValue(string name, T val)
		:ofxFlowNode(name)
		{
			value = ofPtr<ofParameter<T> >(new ofParameter<T>(val));
			_addOutput("value");
		};
	
		ofPtr<ofParameter<T> > value;
	
		virtual void evaluate()
		{
			_setOutputValue("value", value);
		}
	
		virtual void draw ()
		{
			ofxFlowNode::draw();
			
			stringstream ss;
			ss << value->toString() << endl;
			
			ofSetColor(150);
			ofDrawBitmapString(ss.str(), rect.position + ofPoint(rect.width - 40, 20));
		}
};

#endif /* defined(__emptyExample__NodeValue__) */

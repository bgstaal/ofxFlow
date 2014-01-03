#include "ofxFlowNodeAdd.h"
#include "ofGraphics.h"

ofxFlowNodeAdd::ofxFlowNodeAdd ()
: ofxFlowNode("addition")
{
	_addInput("value1");
	_addInput("value2");
	_addOutput("result");
}

void ofxFlowNodeAdd::customDraw()
{
	ofxFlowNode::customDraw();
	stringstream ss;
	ss << _getInputValue("value1")->toString() << " + " << _getInputValue("value2")->toString() << " = " << getOutputValue("result")->toString() << endl;
	
	ofSetColor(150);
	ofDrawBitmapString(ss.str(), 10, 100);
}

void ofxFlowNodeAdd::evaluate()
{
	ofPtr<ofAbstractParameter> p1 = _getInputValue("value1");
	ofPtr<ofAbstractParameter> p2 = _getInputValue("value2");
	float v1 = dynamic_cast<ofParameter<float> *>(p1.get())->get();
	float v2 = dynamic_cast<ofParameter<float> *>(p2.get())->get();
	
	_setOutputValue("result", ofPtr<ofAbstractParameter>(new ofParameter<float>(v1 + v2)));
}
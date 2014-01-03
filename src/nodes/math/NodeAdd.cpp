#include "NodeAdd.h"
#include "ofGraphics.h"

NodeAdd::NodeAdd ()
: Node("addition")
{
	_addInput("value1");
	_addInput("value2");
	_addOutput("result");
}

void NodeAdd::draw()
{
	Node::draw();
	stringstream ss;
	ss << _getInputValue("value1")->toString() << " + " << _getInputValue("value2")->toString() << " = " << getOutputValue("result")->toString() << endl;
	
	ofSetColor(150);
	ofDrawBitmapString(ss.str(), rect.position + ofPoint(10, 100));
}

void NodeAdd::evaluate()
{
	ofPtr<ofAbstractParameter> p1 = _getInputValue("value1");
	ofPtr<ofAbstractParameter> p2 = _getInputValue("value2");
	float v1 = dynamic_cast<ofParameter<float> *>(p1.get())->get();
	float v2 = dynamic_cast<ofParameter<float> *>(p2.get())->get();
	
	_setOutputValue("result", ofPtr<ofAbstractParameter>(new ofParameter<float>(v1 + v2)));
}
#include "ofxFlowNode.h"
#include "ofGraphics.h"

ofxFlowNode::ofxFlowNode (string name)
:name(name)
{
	
}

void ofxFlowNode::connectInputTo(const string &inputParamName, ofxFlowNode *outputNode, const string &outputParamName)
{
	map<string, Connection>::iterator i = _inputConnections.find(inputParamName);
	
	if (i != _inputConnections.end() && i->second.node == outputNode && i->second.paramName == outputParamName)
	{
		return;
	}
	
	_inputConnections[inputParamName] = Connection(outputNode, outputParamName);
	outputNode->connectOutputTo(outputParamName, this, inputParamName);
}

void ofxFlowNode::connectOutputTo(const string &outputParamName, ofxFlowNode *inputNode, const string &inputParamName)
{
	map<string, Connection>::iterator i = _outputConnections.find(outputParamName);
	
	if (i != _outputConnections.end() && i->second.node == inputNode && i->second.paramName == inputParamName)
	{
		return;
	}
	
	_outputConnections.insert(pair<string, Connection>(outputParamName, Connection(inputNode, inputParamName)));
	inputNode->connectInputTo(inputParamName, this, outputParamName);
}

ofPtr<ofAbstractParameter> ofxFlowNode::getOutputValue(string name)
{
	return _outputValues.find(name)->second;
}

void ofxFlowNode::setInputValue(const string &name, ofPtr<ofAbstractParameter> value)
{
	_inputValues[name] = value;
	//_inputValues.insert(pair<string, ofPtr<ofAbstractParameter> >(name, value));
}

void ofxFlowNode::_setOutputValue(string name, ofPtr<ofAbstractParameter> value)
{
	_outputValues[name] = value;
	
	//_outputValues.insert(pair<string, ofPtr<ofAbstractParameter> >(name, value));
}

ofPtr<ofAbstractParameter> ofxFlowNode::_getInputValue(string name)
{
	return _inputValues.find(name)->second;
}



int ofxFlowNode::getInputIndex(const string &inputName)
{
	for (int i = 0; i < _inputs.size(); i++)
	{
		if (inputName == _inputs[i])
		{
			return i;
		}
	}
	
	return -1;
}


int ofxFlowNode::getOutputIndex(const string &outputName)
{
	for (int i = 0; i < _outputs.size(); i++)
	{
		if (outputName == _outputs[i])
		{
			return i;
		}
	}
	
	return -1;
}

ofRectangle ofxFlowNode::getInputRect(const int &index)
{
	return ofRectangle(0, 30 + (15 * index), 10, 10);
}

ofRectangle ofxFlowNode::getInputRect(const string &inputName)
{
	return getInputRect(getInputIndex(inputName));
}

ofRectangle ofxFlowNode::getOutputRect(const int &index)
{
	return ofRectangle(rect.width - 10, 30 + (15 * index), 10, 10);
}

ofRectangle ofxFlowNode::getOutputRect(const string &outputName)
{
	return getOutputRect(getOutputIndex(outputName));
}


void ofxFlowNode::_addInput(string name)
{
	_inputs.push_back(name);
}

void ofxFlowNode::_addOutput(string name)
{
	_outputs.push_back(name);
}

void ofxFlowNode::mousePressed(const ofPoint &p)
{
	ofLog() << name << " mouse pressed" << endl;
}

void ofxFlowNode::mouseReleased(const ofPoint &p)
{
	ofLog() << name << " mouse released" << endl;
}

void ofxFlowNode::draw()
{
	ofPushMatrix();
	ofTranslate(rect.position);
		customDraw();
	ofPopMatrix();
}

void ofxFlowNode::customDraw()
{
	ofSetColor(0, 0, 0, 100);
	ofRect(0, 0, rect.width, rect.height);
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(name, 10, 20);
	
	ofSetColor(255, 0, 0);
	
	for (int i = 0; i < _inputs.size(); i++)
	{
		ofCircle(getInputRect(i).getCenter(), 3);
	}
	
	ofSetColor(0, 255, 0);
	
	for (int i = 0; i < _outputs.size(); i++)
	{
		ofCircle(getOutputRect(i).getCenter(), 3);
	}
}
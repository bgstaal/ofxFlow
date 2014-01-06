#include "ofxFlowNode.h"
#include "ofGraphics.h"

ofxFlowNode::ofxFlowNode (string name)
:name(name)
{
	
}

void ofxFlowNode::connectInputTo(const string &inputParamName, ofxFlowNode *outputNode, const string &outputParamName)
{
	map<string, Connection>::iterator i = _inputConnections.find(inputParamName);
	cout << "connect input to" << endl;
	
	if (i != _inputConnections.end())
	{
		if (i->second.node == outputNode && i->second.paramName == outputParamName)
		{
			// stop an endless loop by returning at this point because the connection already exists
			return;
		}
		else
		{
			// remove existing connection in the other end as it is about to be overwritten underneath
			i->second.node->disconnectOutputTo(i->second.paramName, this, i->first);
		}
	}
	
	_inputConnections[inputParamName] = Connection(outputNode, outputParamName);
	outputNode->connectOutputTo(outputParamName, this, inputParamName);
}

void ofxFlowNode::connectOutputTo(const string &outputParamName, ofxFlowNode *inputNode, const string &inputParamName)
{
	cout << "connect output " << outputParamName << " to " << inputParamName << endl;
	map<string, Connection>::iterator i = _outputConnections.find(outputParamName);
	
	if (i != _outputConnections.end() && i->second.node == inputNode && i->second.paramName == inputParamName)
	{
		return;
	}
	
	_outputConnections.insert(pair<string, Connection>(outputParamName, Connection(inputNode, inputParamName)));
	inputNode->connectInputTo(inputParamName, this, outputParamName);
}

void ofxFlowNode::disconnectInputFrom(const string &inputParamName, ofxFlowNode *outputNode, const string &outputParamName)
{
	// not implemented yet
}

void ofxFlowNode::disconnectOutputTo(const string &outputParamName, ofxFlowNode *inputNode, const string &inputParamName)
{
	for (multimap<string, Connection>::iterator c = _outputConnections.lower_bound(outputParamName); c != _outputConnections.upper_bound(outputParamName); c++)
	{
		if (c->first == outputParamName && c->second.node == inputNode && c->second.paramName == inputParamName)
		{
			ofLog() << "remove this bitch!" << endl;
			_outputConnections.erase(c);
			break;
		}
	}
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

string ofxFlowNode::getOutputName(int index)
{
	return _outputs[index];
}

string ofxFlowNode::getInputName(int index)
{
	return _inputs[index];
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

bool ofxFlowNode::isDraggableAtPoint(const ofPoint &p)
{
	// return false if mouse pointer is over input/output
	if (getOutputIndexAtPoint(p) != -1 || getInputIndexAtPoint(p) != -1) return false;
	return true;
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
	int inIndex = getInputIndexAtPoint(p);
	int outIndex = getOutputIndexAtPoint(p);
	
	if (inIndex >= 0) _notifyEvent(inputMouseDown, getInputName(inIndex));
	if (outIndex >= 0) _notifyEvent(outputMouseDown, getOutputName(outIndex));
}

void ofxFlowNode::mouseReleased(const ofPoint &p)
{
	int inIndex = getInputIndexAtPoint(p);
	int outIndex = getOutputIndexAtPoint(p);
	
	if (inIndex >= 0) _notifyEvent(inputMouseUp, getInputName(inIndex));
	if (outIndex >= 0) _notifyEvent(outputMouseUp, getOutputName(outIndex));
}

void ofxFlowNode::_notifyEvent(ofEvent<ofxFlowNode::ofxFlowNodeEventArgs> &event, const string &paramName)
{
	cout << "param name: " << paramName << endl;
	ofxFlowNodeEventArgs a;
	a.paramName = paramName;
	a.node = this;
	ofNotifyEvent(event, a, this);
}

int ofxFlowNode::getInputIndexAtPoint(const ofPoint &p)
{
	for (int i = 0; i < _inputs.size(); i++)
	{
		if (getInputRect(i).inside(p))
			return i;
	}
	
	return -1;
}

int ofxFlowNode::getOutputIndexAtPoint(const ofPoint &p)
{
	for (int i = 0; i < _outputs.size(); i++)
	{
		if (getOutputRect(i).inside(p))
			return i;
	}
	
	return -1;
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
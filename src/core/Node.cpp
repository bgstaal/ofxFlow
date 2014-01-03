#include "Node.h"
#include "ofGraphics.h"

Node::Node (string name)
:name(name)
{
	
}

void Node::connectInputTo(string inputParamName, Node *outputNode, string outputParamName)
{
	map<string, Connection>::iterator i = _inputConnections.find(inputParamName);
	
	if (i != _inputConnections.end() && i->second.node == outputNode && i->second.paramName == outputParamName)
	{
		return;
	}
	
	_inputConnections[inputParamName] = Connection(outputNode, outputParamName);
	outputNode->connectOutputTo(outputParamName, this, inputParamName);
}

void Node::connectOutputTo(string outputParamName, Node *inputNode, string inputParamName)
{
	map<string, Connection>::iterator i = _outputConnections.find(outputParamName);
	
	if (i != _outputConnections.end() && i->second.node == inputNode && i->second.paramName == inputParamName)
	{
		return;
	}
	
	_outputConnections.insert(pair<string, Connection>(outputParamName, Connection(inputNode, inputParamName)));
	inputNode->connectInputTo(inputParamName, this, outputParamName);
}

ofPtr<ofAbstractParameter> Node::getOutputValue(string name)
{
	return _outputValues.find(name)->second;
}

void Node::setInputValue(string name, ofPtr<ofAbstractParameter> value)
{
	_inputValues[name] = value;
	//_inputValues.insert(pair<string, ofPtr<ofAbstractParameter> >(name, value));
}

void Node::_setOutputValue(string name, ofPtr<ofAbstractParameter> value)
{
	_outputValues[name] = value;
	
	//_outputValues.insert(pair<string, ofPtr<ofAbstractParameter> >(name, value));
}

ofPtr<ofAbstractParameter> Node::_getInputValue(string name)
{
	return _inputValues.find(name)->second;
}



int Node::getInputIndex(string inputName)
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


int Node::getOutputIndex(string outputName)
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
 

void Node::_addInput(string name)
{
	_inputs.push_back(name);
}

void Node::_addOutput(string name)
{
	_outputs.push_back(name);
}

void Node::draw()
{
	ofSetColor(0, 0, 0, 100);
	ofRect(rect);
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(name, rect.position + ofPoint(10, 20));
	
	ofSetColor(255, 0, 0);
	
	for (int i = 0; i < _inputs.size(); i++)
	{
		ofRect(rect.x, rect.y + 30 + (15*i), 10, 10);
	}
	
	ofSetColor(0, 255, 0);
	
	for (int i = 0; i < _outputs.size(); i++)
	{
		ofRect(rect.x + rect.width - 10, rect.y + 30 + (15*i), 10, 10);
	}
}
#pragma once

#include "ofxFlowNode.h"

class ofxFlowGraph
{	
	public:
		void addNode(ofxFlowNodePtr node);
		void update();
		void draw();
	
	private:
		vector<ofxFlowNodePtr> _nodes;
	
		void _drawInputConnections(ofxFlowNode *node);
		void _evaluateInputs(ofxFlowNode *node);
};

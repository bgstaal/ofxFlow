#pragma once

#include "ofxFlowNode.h"

class ofxFlowGraph
{	
	public:
		void addNode(ofxFlowNodePtr node);
		void update();
		void draw();
		void mouseMoved(ofMouseEventArgs &e);
		void mouseDragged(ofMouseEventArgs &e);
		void mousePressed(ofMouseEventArgs &e);
		void mouseReleased(ofMouseEventArgs &e);
	
	private:
		vector<ofxFlowNodePtr> _nodes;
		vector<ofxFlowNodePtr> _nodesBeingDragged;
		map<ofxFlowNodePtr, ofRectangle> _nodeOrigRect;
		ofPoint _prevMousePos;
	
		void _drawInputConnections(ofxFlowNode *node);
		void _evaluateInputs(ofxFlowNode *node);
};

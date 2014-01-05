#pragma once

#include "ofxFlowNode.h"

class ofxFlowGraph
{	
	public:
		ofxFlowGraph();
		void addNode(ofxFlowNodePtr node);
		void update();
		void draw();
		void mouseMoved(ofMouseEventArgs &e);
		void mouseDragged(ofMouseEventArgs &e);
		void mousePressed(ofMouseEventArgs &e);
		void mouseReleased(ofMouseEventArgs &e);
	
	private:
	
		struct TempConnection
		{
			ofPoint p1;
		};
	
		vector<ofxFlowNodePtr> _nodes;
		vector<ofxFlowNodePtr> _nodesBeingDragged;
		vector<TempConnection> _tempConnections;
		map<ofxFlowNodePtr, ofRectangle> _nodeOrigRect;
		ofPoint _prevMousePos;
	
		void _drawInputConnections(ofxFlowNode *node);
		void _evaluateInputs(ofxFlowNode *node);
		void _inputMouseDown(ofxFlowNode::ofxFlowNodeEventArgs &e);
		void _inputMouseUp(ofxFlowNode::ofxFlowNodeEventArgs &e);
		void _outputMouseDown(ofxFlowNode::ofxFlowNodeEventArgs &e);
		void _outputMouseUp(ofxFlowNode::ofxFlowNodeEventArgs &e);
};

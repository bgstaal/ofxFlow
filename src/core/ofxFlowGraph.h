#ifndef __emptyExample__NodeManager__
#define __emptyExample__NodeManager__

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

#endif /* defined(__emptyExample__NodeManager__) */

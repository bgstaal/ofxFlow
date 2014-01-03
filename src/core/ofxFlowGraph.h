#ifndef __emptyExample__NodeManager__
#define __emptyExample__NodeManager__

#include "Node.h"

class ofxFlowGraph
{	
	public:
		void addNode(NodePtr node);
		void update();
		void draw();
	
	private:
		vector<NodePtr> _nodes;
	
		void _drawInputConnections(Node *node);
		void _updateInputs(Node *node);
};

#endif /* defined(__emptyExample__NodeManager__) */

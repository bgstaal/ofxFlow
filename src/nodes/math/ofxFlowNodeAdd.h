#include "ofxFlowNode.h"

#ifndef __emptyExample__NodeAdd__
#define __emptyExample__NodeAdd__

class ofxFlowNodeAdd : public ofxFlowNode
{
	public:
		ofxFlowNodeAdd();
		virtual void draw();
		virtual void evaluate();
};

#endif /* defined(__emptyExample__NodeAdd__) */

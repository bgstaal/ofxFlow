#ifndef __emptyExample__NodeValue__
#define __emptyExample__NodeValue__

#include "Node.h"

template <typename T>
class NodeValue : public Node
{
	public:
		NodeValue(string name, T val)
		:Node(name)
		{
			value = ofPtr<ofParameter<T> >(new ofParameter<T>(val));
			cout << "type " << value->type() << endl;
			_addOutput("value");
		};
	
		ofPtr<ofParameter<T> > value;
	
		virtual void evaluate()
		{
			//value->set(ofGetElapsedTimef());
			_setOutputValue("value", value);
		}
	
		virtual void draw ()
		{
			Node::draw();
			
			stringstream ss;
			ss << value->toString() << endl;
			
			ofSetColor(150);
			ofDrawBitmapString(ss.str(), rect.position + ofPoint(rect.width - 40, 20));
		}
};

#endif /* defined(__emptyExample__NodeValue__) */

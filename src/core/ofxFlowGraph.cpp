#include "ofGraphics.h"
#include "ofxFlowGraph.h"
#include "ofPath.h"

void ofxFlowGraph::addNode (ofxFlowNodePtr node)
{
	_nodes.push_back(node);
	ofRegisterMouseEvents(this);
}

void ofxFlowGraph::update()
{
	for (vector<ofxFlowNodePtr>::iterator n = _nodes.begin(); n != _nodes.end(); n++)
	{
		ofxFlowNodePtr &node = (*n);
		
		if (node->_outputConnections.size() == 0) // this is an endpoint so start evaluating backwards from here
		{
			_evaluateInputs(node.get());
		}
	}
}

void ofxFlowGraph::_evaluateInputs(ofxFlowNode *node)
{
	map<string, ofxFlowNode::Connection>::iterator c = node->_inputConnections.begin();
	
	for (; c != node->_inputConnections.end(); c++)
	{
		// traverese the tree backwards and evaluate all inputs and pass the values on down the tree
		_evaluateInputs(c->second.node);
		node->setInputValue(c->first, c->second.node->getOutputValue(c->second.paramName));
	}
	
	node->evaluate();
}

void ofxFlowGraph::draw ()
{
	for (vector<ofxFlowNodePtr>::iterator n = _nodes.begin(); n != _nodes.end(); n++)
	{
		ofxFlowNodePtr &node = (*n);
		
		if (node->_outputConnections.size() == 0) // this is an endpoint
		{
			_drawInputConnections(node.get());
		}
		
		node->draw();
	}
}

void ofxFlowGraph::_drawInputConnections(ofxFlowNode *node)
{
	map<string, ofxFlowNode::Connection>::iterator c = node->_inputConnections.begin();
	
	ofSetColor(255);
	
	for (; c != node->_inputConnections.end(); c++)
	{
		ofxFlowNode *node2 = c->second.node;
		
		ofRectangle r1 = node2->getOutputRect(c->second.paramName);
		ofRectangle r2 = node->getInputRect(c->first);
		ofPoint p1 = node2->rect.position + r1.position + (r1.width*.5f);
		ofPoint p2 = node->rect.position + r2.position + (r1.width*.5f);
		
		glBegin(GL_LINES);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(p1.x, p1.y);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(p2.x, p2.y);
		glEnd();
		
		_drawInputConnections(node2);
	}
}

void ofxFlowGraph::mousePressed(ofMouseEventArgs &e)
{
	_prevMousePos = e;
	
	for (vector<ofxFlowNodePtr>::reverse_iterator n = _nodes.rbegin(); n != _nodes.rend(); n++)
	{
		ofxFlowNodePtr &node = *n;
		if (node->rect.inside(e))
		{
			ofPoint p = e;
			e -= node->rect.position;
			node->mousePressed(p);
			
			_nodesBeingDragged.push_back(node);
			_nodeOrigRect[node] = node->rect;
			break;
		}
	}
}

void ofxFlowGraph::mouseReleased(ofMouseEventArgs &e)
{
	_nodesBeingDragged.clear();
	
	for (vector<ofxFlowNodePtr>::reverse_iterator n = _nodes.rbegin(); n != _nodes.rend(); n++)
	{
		ofxFlowNodePtr &node = *n;
		if (node->rect.inside(e))
		{
			ofPoint p = e;
			e -= node->rect.position;
			node->mouseReleased(p);
			break;
		}
	}
}

void ofxFlowGraph::mouseMoved(ofMouseEventArgs &e)
{
	
}

void ofxFlowGraph::mouseDragged(ofMouseEventArgs &e)
{
	for (vector<ofxFlowNodePtr>::iterator n = _nodesBeingDragged.begin(); n != _nodesBeingDragged.end(); n++)
	{
		ofxFlowNodePtr &node = *n;
		node->rect.position = _nodeOrigRect[node].position - (_prevMousePos - e);
	}
}




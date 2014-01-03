#include "ofGraphics.h"
#include "Graph.h"
#include "ofPath.h"

void Graph::addNode (NodePtr node)
{
	_nodes.push_back(node);
}

void Graph::update()
{
	for (vector<NodePtr>::iterator n = _nodes.begin(); n != _nodes.end(); n++)
	{
		NodePtr node = (*n);
		
		if (node->_outputConnections.size() == 0) // this is an endpoint
		{
			_updateInputs(node.get());
		}
	}
}

void Graph::_updateInputs(Node *node)
{
	map<string, Node::Connection>::iterator c = node->_inputConnections.begin();
	
	for (; c != node->_inputConnections.end(); c++)
	{
		_updateInputs(c->second.node);
		node->setInputValue(c->first, c->second.node->getOutputValue(c->second.paramName));
	}
	
	node->evaluate();
}

void Graph::draw ()
{
	for (vector<NodePtr>::iterator n = _nodes.begin(); n != _nodes.end(); n++)
	{
		NodePtr node = (*n);
		
		if (node->_outputConnections.size() == 0) // this is an endpoint
		{
			_drawInputConnections(node.get());
		}
		
		node->draw();
	}
}

void Graph::_drawInputConnections(Node *node)
{
	map<string, Node::Connection>::iterator c = node->_inputConnections.begin();
	
	ofSetColor(255);
	
	for (; c != node->_inputConnections.end(); c++)
	{
		Node *node2 = c->second.node;
		
		int outIndex = node2->getOutputIndex(c->second.paramName);
		int inIndex = node->getInputIndex(c->first);
		ofPoint p1 = node2->rect.position;
		p1.x += node2->rect.width;
		p1.y += 35 + (15*outIndex);
		ofPoint p2 = node->rect.position;
		p2.y += 35 + (15*inIndex);
		
		glBegin(GL_LINES);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(p1.x, p1.y);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(p2.x, p2.y);
		glEnd();
		
		_drawInputConnections(node2);
	}
}


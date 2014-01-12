#include "ofApp.h"
#include "ofxFlowNodeAdd.h"
#include "ofxFlowNodeValue.h"
#include "ofxFlowNodeElapsedTime.h"
#include "ofxFlowNodeSin.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	
	ofPtr<ofxFlowNodeValue<float> > valueNode = ofPtr<ofxFlowNodeValue<float> >(new ofxFlowNodeValue<float>("One point five", 1.5f));
	valueNode->rect = ofRectangle(100, 100, 200, 40);
	_graph.addNode(valueNode);
	
	ofPtr<ofxFlowNodeValue<float> > timeNode = ofPtr<ofxFlowNodeElapsedTime<float> >(new ofxFlowNodeElapsedTime<float>());
	timeNode->rect = ofRectangle(100, 300, 200, 40);
	_graph.addNode(timeNode);
	
	ofPtr<ofxFlowNodeAdd> additionNode = ofPtr<ofxFlowNodeAdd>(new ofxFlowNodeAdd());
	additionNode->rect = ofRectangle(350, 100, 200, 150);
	_graph.addNode(additionNode);
	
	ofPtr<ofxFlowNodeAdd> additionNode2 = ofPtr<ofxFlowNodeAdd>(new ofxFlowNodeAdd());
	additionNode2->rect = ofRectangle(600, 250, 200, 150);
	_graph.addNode(additionNode2);
	
	// TODO: add validation
	ofPtr<ofxFlowNodeAdd> additionNode3 = ofPtr<ofxFlowNodeAdd>(new ofxFlowNodeAdd());
	additionNode3->rect = ofRectangle(850, 400, 200, 150);
	_graph.addNode(additionNode3);
	
	ofPtr<ofxFlowNodeSin<float> > sinNode = ofPtr<ofxFlowNodeSin<float> >(new ofxFlowNodeSin<float>());
	sinNode->rect = ofRectangle(350, 400, 200, 150);
	_graph.addNode(sinNode);
	
	additionNode->connectInputTo("value1", valueNode.get(), "value");
	additionNode->connectInputTo("value2", valueNode.get(), "value");
	
	/*
	additionNode2->connectInputTo("value1", additionNode.get(), "result");
	additionNode2->connectInputTo("value2", valueNode.get(), "value");
	
	additionNode3->connectInputTo("value1", sinNode.get(), "result");
	additionNode3->connectInputTo("value2", additionNode2.get(), "result");
	sinNode->connectInputTo("value1", timeNode.get(), "value");
	 */
	
}

//--------------------------------------------------------------
void ofApp::update()
{
	_graph.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(30);
	_graph.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
	
}
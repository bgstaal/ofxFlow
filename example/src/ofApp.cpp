#include "ofApp.h"
#include "ofxFlowNodeAdd.h"
#include "ofxFlowNodeValue.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofPtr<ofxFlowNodeValue<float> > valueNode = ofPtr<ofxFlowNodeValue<float> >(new ofxFlowNodeValue<float>("One point five", 1.5f));
	valueNode->rect = ofRectangle(100, 100, 200, 40);
	_graph.addNode(valueNode);
	
	ofPtr<ofxFlowNodeValue<float> > valueNode2 = ofPtr<ofxFlowNodeValue<float> >(new ofxFlowNodeValue<float>("PI", M_PI));
	valueNode2->rect = ofRectangle(100, 300, 200, 40);
	_graph.addNode(valueNode2);
	
	ofPtr<ofxFlowNodeAdd> additionNode = ofPtr<ofxFlowNodeAdd>(new ofxFlowNodeAdd());
	additionNode->rect = ofRectangle(350, 100, 200, 150);
	_graph.addNode(additionNode);
	
	//additionNode->value1 = 33.0f;
	
	ofPtr<ofxFlowNodeAdd> additionNode2 = ofPtr<ofxFlowNodeAdd>(new ofxFlowNodeAdd());
	additionNode2->rect = ofRectangle(600, 250, 200, 150);
	_graph.addNode(additionNode2);
	
	// TODO: add validation
	ofPtr<ofxFlowNodeAdd> additionNode3 = ofPtr<ofxFlowNodeAdd>(new ofxFlowNodeAdd());
	additionNode3->rect = ofRectangle(850, 400, 200, 150);
	_graph.addNode(additionNode3);
	
	additionNode->connectInputTo("value1", valueNode.get(), "value");
	additionNode->connectInputTo("value2", valueNode.get(), "value");
	additionNode2->connectInputTo("value1", additionNode.get(), "result");
	additionNode2->connectInputTo("value2", valueNode.get(), "value");
	additionNode3->connectInputTo("value2", valueNode2.get(), "value");
	additionNode3->connectInputTo("value1", additionNode2.get(), "result");
	valueNode->connectOutputTo("value", additionNode.get(), "value2");
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
#pragma once

#include "ofMain.h"
#include "ofxFlowNodeValue.h"

template<typename T>
class ofxFlowNodeElapsedTime : public ofxFlowNodeValue<T>
{
	public:
	
		ofxFlowNodeElapsedTime ()
		:ofxFlowNodeValue<T>("time", 0.0f)
		{
			
		}
		
		virtual bool validate()
		{
			return true;
		}
	
		virtual void evaluate ()
		{
			this->value->set(ofGetElapsedTimef());
			ofxFlowNodeValue<T>::evaluate();
		}
};
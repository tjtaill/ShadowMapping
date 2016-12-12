// ShadowMapping.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GlutViewer.h"
#include "Shader.h"
#include <iostream>
#include "Program.h"
#include "GlutTimer.h"
#include <boost/bind.hpp>

const unsigned int periodInMilliSeconds = 100;

int main(int argc, char** argv)
{
	GlutViewer viewer(argc, argv, 200.0);
	GlutTimer timer(periodInMilliSeconds);
	timer.time_signal_->connect( boost::bind(&GlutViewer::update, &viewer) );
	viewer.EnterMainLoop();
	return 0;
}


#include "StdAfx.h"
#include "GlutTimer.h"
#include <boost/thread/once.hpp>
#include <cassert>
#include <GL/glut.h>
#include <iostream>

boost::once_flag timerOnceFlag = BOOST_ONCE_INIT;

unsigned int GlutTimer::instances_;
GlutTimer* GlutTimer::glutTimerPointer;

GlutTimer::GlutTimer(unsigned int signal_period) :
	signal_period_( signal_period ), time_signal_( new time_signal_type )
{
	boost::call_once( &GlutTimer::initInstances, timerOnceFlag );
	instances_++;
	assert( 1 == instances_ );
	glutTimerPointer = this;

	// register glut function timer call back
	glutTimerFunc( signal_period, &GlutTimer::OnSignalCallWrapper, 0 );

}

void GlutTimer::OnSignalCallWrapper( int value )
{
	glutTimerPointer->OnSignal( value );
}

void GlutTimer::OnSignal( int value )
{
	
	(*time_signal_)();
	glutPostRedisplay();
	glutTimerFunc( signal_period_, &GlutTimer::OnSignalCallWrapper, 0 );
}



GlutTimer::~GlutTimer(void)
{
	
}
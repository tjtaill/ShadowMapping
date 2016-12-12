#ifndef GLUTTIMER_DOT_H
#define GLUTTIMER_DOT_H


#include <boost/signal.hpp>
#include <boost/shared_ptr.hpp>

/**
  *@file GlutTimer.h
  *@author Troy Taillefer
  *@version 0.1
  *@date Decemeber 11, 2007
  *
  */


/**
  *@class GlutTimer
  *This class abstracts a glut timer registers all relevant call backs
  *these call backs can be overriden in classes that inherit form this one
  *This class uses the observer pattern through the boost signals library
  *it also uses boost thread to implement the singleton pattern
  */
class GlutTimer
{
private:
	static void OnSignalCallWrapper( int value );
	static void initInstances(void) { instances_ = 0; }

protected:
	
	typedef boost::signal<void ()> time_signal_type;
	unsigned int signal_period_;
	static unsigned int instances_;
	static GlutTimer* glutTimerPointer;
	GlutTimer(void) {};
	virtual void OnSignal( int value );

public:
	boost::shared_ptr<time_signal_type> time_signal_;
	
	GlutTimer(unsigned int signal_period);
	virtual ~GlutTimer(void);
	
};
#endif

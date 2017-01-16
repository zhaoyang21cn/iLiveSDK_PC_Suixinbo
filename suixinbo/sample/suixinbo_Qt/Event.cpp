#include "stdafx.h"
#include "Event.h"

Event::Event( E_CustomEvent eventType, int errCode, const std::string& szDesc )
	:QEvent( (Type)eventType )
{
	this->code = errCode;
	this->desc = szDesc;
}

void postCusEvent( QObject *receiver, Event* event )
{
	QApplication::postEvent( receiver, event );
}
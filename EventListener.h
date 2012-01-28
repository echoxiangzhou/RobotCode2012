#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

/**
 * An interface for a class that can handle events.
 * 
 * \tparam Event the Event class to be handled by the listener.
 */
template <class Event>
class EventListener
{
public:
	/**
	 * Handle an event.
	 * 
	 * \param event the event to handle.
	 */
	virtual void HandleEvent(Event event)=0;
};

#endif // EVENTLISTENER_H

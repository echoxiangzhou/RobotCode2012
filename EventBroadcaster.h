#ifndef EVENTBROADCASTER_H
#define EVENTBROADCASTER_H

#include <list>

#include "EventListener.h"

/**
 * An interface for a class that can broadcast events to listeners that subscribe to it.
 * 
 * \tparam Event the event class to broadcast.
 */
template <class Event>
class EventBroadcaster
{
public:
	/**
	 * Subscribe a listener to receive broadcasts.
	 * 
	 * \param listener the event listener to add.
	 */
	void AddListener(EventListener<Event>& listener)
	{
		this->listenerList.push_back(&listener);
	}
	
	/**
	 * Remove a listener from future event broadcasts.
	 * 
	 * \param listener the listener to remove.
	 */
	void RemoveListener(EventListener<Event>& listener)
	{
		this->listenerList.remove(&listener);
	}
	
protected:
	/**
	 * Broadcast an event to all subscribed listeners.
	 * 
	 * \param event the event instance to broadcast.
	 */
	void FireEvent(Event event)
	{
		for( std::list< EventListener<Event>* >::iterator it = this->listenerList.begin(); it != this->listenerList.end(); ++it )
		{
			(*it)->handleEvent(event);
		}
	}
	
private:
	std::list< EventListener<Event>* > listenerList; /**< The list of event listeners subscribed to the broadcaster. */
};

#endif // EVENTBROADCASTER_H

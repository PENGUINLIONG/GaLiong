#include "Event.hpp"

_L_BEGIN
EventArgs::EventArgs()
{
}

EventArgs::~EventArgs()
{
}

template<class _Args>
Event<_Args> &Event<_Args>::operator+=(EventHandler<_Args> handler)
{
	_Callbacks[handler.target()] = EventHandler(handler);
	return *this;
}

template<class _Args>
Event<_Args> &Event<_Args>::operator-=(EventHandler<_Args> handler)
{
	_Callbacks.erase(_Callback.find(handler.target()));
	return *this;
}

template<class _Args>
Event<_Args> &Event<_Args>::operator()(void *sender, _Args &e)
{
	for (const auto &callback : _Callbacks)
		callback.second(sender, e);

	return *this;
}

template<class _Args>
Event<_Args> &Event<_Args>::operator()(void *sender, _Args *e)
{
	for (const auto &callback : _Callbacks)
		callback.second(sender, *e);

	delete e;
	return *this;
}
_L_END
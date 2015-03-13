#pragma once
#include "Preprocess.hpp"

_L_BEGIN
template<class _Args>
using EventHandler = function<void(void *sender, _Args e)>;

class _L_ EventArgs
{
public:
	EventArgs();
	virtual ~EventArgs();
};

template<class _Args>
class _L_ Event
{
public:
	virtual Event<_Args> &operator+=(EventHandler<_Args> handler);
	virtual Event<_Args> &operator-=(EventHandler<_Args> handler);
	virtual Event<_Args> &operator()(void *sender, _Args &e);
	virtual Event<_Args> &operator()(void *sender, _Args *e);
protected:
	map<long, EventHandler<_Args>> _Callbacks;
};
_L_END
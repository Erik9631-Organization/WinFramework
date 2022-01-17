#pragma once
enum class EventUpdateFlags
{
	None = 0,
	Redraw = 1,
	Resize = 2,
	Move = 4,
};
inline EventUpdateFlags operator|(EventUpdateFlags a, EventUpdateFlags b)
{
	return (EventUpdateFlags)((int)a | (int)b);
}

inline EventUpdateFlags operator&(EventUpdateFlags a, EventUpdateFlags b)
{
	return (EventUpdateFlags)((int)a & (int)b);
}

inline EventUpdateFlags operator~(EventUpdateFlags a)
{
	return (EventUpdateFlags)~((int)a);
}
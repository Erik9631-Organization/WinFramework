#pragma once
#include "Enums/EventUpdateFlags.h"

/**
 * This class is responsible for holding event data related to updates.
 */
//TODO Deprecated and should be deleted
class EventUpdateInfo
{
public:
	/**
	 * NOTE: The flags are implementation specific. The framework generally understands these flags and will perform the updates
	 * based on the information provided in the EventUpdateFlags enum.
	 * \param flags the update flags according to which the update should proceed. Check EventUpdateFlags enum for more info.
	 */
	explicit EventUpdateInfo(EventUpdateFlags flags);

	/**
	 * \param flags overrides the old flags with the flags specified in this parameter
	 */
	void SetFlags(EventUpdateFlags flags);

	/**
	 * \param flags disables the flag specified in this parameter
	 */
	void DisableFlag(EventUpdateFlags flags);

	/**
	 * \param flag performs a check on the flag specified in this parameter
	 * \return returns true if the flag is set, returns false otherwise.
	 */
	bool HasFlag(EventUpdateFlags flag);
private:
	EventUpdateFlags updateFlags;
};


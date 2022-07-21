/*
 * counted.cpp
 *
 *  Created on: Apr 10, 2017
 *      Author: zeil
 */

#include "memoryChecked.h"

#include <iostream>

int MemoryChecked::numObjects = 0;
bool MemoryChecked::memoryViolationDetected = false;

MemoryChecked& MemoryChecked::operator= (const MemoryChecked& rhs)
{
	if (hasBeenDestroyed)
	{
		memoryViolationDetected = true;
		throw DanglingPointerException("*** Attempted to assign to an already destroyed object");
	}
	if (rhs.hasBeenDestroyed)
	{
		memoryViolationDetected = true;
		throw DanglingPointerException ("*** Attempted to assign from an already destroyed object");
	}
	return *this;
}

MemoryChecked::MemoryChecked (const MemoryChecked& c)
: hasBeenDestroyed(false)
{
	++numObjects;
	if (c.hasBeenDestroyed)
	{
		memoryViolationDetected = true;
		throw DanglingPointerException ("*** Attempted to copy an already destroyed object");
	}
}


MemoryChecked::~MemoryChecked() noexcept(false)
{
	if (hasBeenDestroyed)
	{
		memoryViolationDetected = true;
		throw DanglingPointerException ("*** Attempted to destroy an already destroyed object");
	}
	else
	{
		hasBeenDestroyed = true;
		--numObjects;
	}
}

void MemoryChecked::resetMemoryChecks()
{
	numObjects = 0;
	memoryViolationDetected = false;
}


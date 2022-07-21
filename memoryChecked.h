/*
 * counted.h
 *
 *  Created on: Apr 10, 2017
 *      Author: zeil
 */

#ifndef MEMORYCHECKED_H_
#define MEMORYCHECKED_H_

#include <exception>

/**
 * Utility for detecting memory leaks and dangling pointers.
 *
 *
 * Detection can be added to a class by adding a data member of this type.
 *
 */
class MemoryChecked
{
	/**
	 * A count of the number of Counted objects currently in use.
	 */
	static int numObjects; // = 0;

	/**
	 * Indicates if a dangling pointer problem has
	 * been detected during this execution.
	 */
	static bool memoryViolationDetected; // = false;

	/**
	 * Indicates whether this object has been destroyed.
	 */
	bool hasBeenDestroyed;

public:

	/**
	 * This exception will be thrown when an attempt to copy
	 * an object that has already been destroyed, when an
	 * attempt is made to assign to/from a destroyed object, or
	 * when an attempt is made to destroy an already-destroyed
	 * object.
	 */
	class DanglingPointerException: public std::exception {
		const char* explain;
	public:
		DanglingPointerException (const char* explanation)
		  : explain(explanation) {}

		virtual const char* what() const throw()
		{
		    return explain;
		 }
	};


	MemoryChecked () : hasBeenDestroyed(false) { ++numObjects; }
	MemoryChecked (const MemoryChecked& c);
	MemoryChecked& operator= (const MemoryChecked& rhs);
	virtual ~MemoryChecked() noexcept(false);

	/**
	 *  How many checked objects have been created but not yet
	 *  destroyed?
	 */
	static int getCurrentCount() {return numObjects;}

	/**
	 * Have we detected any attempts to manipulate objects via
	 * dangling pointers?
	 */
	static bool danglingPointersDetected() {return memoryViolationDetected;}

	/**
	 * This is intended only for use when unit testing
	 * the MemoryChecked class itself.
	 */
	static void resetMemoryChecks();
};



#endif /* MEMORYCHECKED_H_ */

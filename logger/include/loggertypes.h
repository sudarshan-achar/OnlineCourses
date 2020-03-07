/*
 * loggertypes.h
 *
 *  Created on: 07-Mar-2020
 *      Author: sudarshan
 */

#ifndef INCLUDE_LOGGERTYPES_H_
#define INCLUDE_LOGGERTYPES_H_


/**
 * with the help of this enum, sources can report their availability
 * state
 */
enum Availability_e
{
	/**
	 * default
	 */
	A_UNKNOWN = 0,
	/**
	 * The source / sink is available
	 */
	A_AVAILABLE = 1,
	/**
	 * the source / sink is not available
	 */
	A_UNAVAILABLE = 2,
	A_MAX
};

/**
 *To print interrupts enumerations
 */
enum InterruptState_e
{
	/**
	 * default
	 */
	IS_UNKNOWN = 0,    //!< IS_UNKNOWN
	/**
	 * the interrupt state is off - no interrupt
	 */
	IS_OFF = 1,        //!< IS_OFF
	/**
	 * the interrupt state is interrupted - the interrupt is active
	 */
	IS_INTERRUPTED = 2,//!< IS_INTERRUPTED
	IS_MAX             //!< IS_MAX
};


#endif /* INCLUDE_LOGGERTYPES_H_ */

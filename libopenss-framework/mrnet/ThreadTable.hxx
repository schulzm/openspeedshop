////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2007,2008 William Hachfeld. All Rights Reserved.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2.1 of the License, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
// details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////

/** @file
 *
 * Declaration of the ThreadTable class.
 *
 */

#ifndef _OpenSpeedShop_Framework_ThreadTable_
#define _OpenSpeedShop_Framework_ThreadTable_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "Thread.hxx"

#include <map>
#include <pthread.h>
#include <string>
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#include <utility>



namespace OpenSpeedShop { namespace Framework {

    class Lockable;
    class ThreadGroup;

    /**
     * Thread table.
     *
     * Table used to keep track of which threads have been attached and the
     * current state of those threads. Facilitates providing thread state to
     * the rest of the framework.
     *
     * @ingroup Implementation
     */
    class ThreadTable :
	private Lockable,
	private std::map<Thread, Thread::State>
    {

    public:

	static ThreadTable TheTable;

	ThreadTable();

	bool isEmpty() const;

	void addThread(const Thread&);
	void removeThread(const Thread&);

	ThreadGroup getThreads(const std::string&, const pid_t&,
			       const std::pair<bool, pthread_t>&);
	
	Thread::State getThreadState(const Thread&);
	void setThreadState(const Thread&, const Thread::State&);

	bool isConnected(const Thread&);
	bool setConnecting(const Thread&);

	void validateThreads(const ThreadGroup&);

    };

} }



#endif

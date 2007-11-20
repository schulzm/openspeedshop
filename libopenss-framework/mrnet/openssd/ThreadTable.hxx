////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2007 William Hachfeld. All Rights Reserved.
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

#include "Lockable.hxx"
#include "ThreadName.hxx"

#include <BPatch.h>
#include <map>



namespace OpenSpeedShop { namespace Framework {

    /**
     * Thread table.
     *
     * Table used to keep track of Dyninst thread object pointers. Dyninst does
     * provide a list of active thread pointers, but using it to find a specific
     * thread requires a linear time search. This table provides the same search
     * in logarithmic time.
     *
     * @ingroup Implementation
     */
    class ThreadTable :
	private Lockable,
	private std::map<ThreadName, BPatch_thread*>
    {

    public:

	static ThreadTable TheTable;

	ThreadTable();
	
	void addThread(const ThreadName&, BPatch_thread*);
	void removeThread(const ThreadName&);
	
	BPatch_thread* getPtr(const ThreadName&);
	
    };

} }



#endif

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
 * Declaration of the ThreadNameGroup class.
 *
 */

#ifndef _OpenSpeedShop_Framework_ThreadNameGroup_
#define _OpenSpeedShop_Framework_ThreadNameGroup_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "Protocol.h"
#include "ThreadName.hxx"

#include <set>



namespace OpenSpeedShop { namespace Framework {

    /**
     * Arbitrary group of thread names.
     *
     * Container holding an arbitrary group of thread names. No specific
     * relationship is implied between the thread names within a given thread
     * name group.
     *
     * @ingroup Implementation
     */
    class ThreadNameGroup :
	public std::set<ThreadName>
    {

    public:

	/** Default constructor. */
	ThreadNameGroup() :
	    std::set<ThreadName>()
	{
	}

	/** Copy constructor. */
	ThreadNameGroup(const ThreadNameGroup& other) :
	    std::set<ThreadName>(other)
	{
	}

	/** Constructor from a OpenSS_Protocol_ThreadNameGroup object. */
	ThreadNameGroup(const OpenSS_Protocol_ThreadNameGroup& object) :
	    std::set<ThreadName>()
	{
	    for(int i = 0; i < object.names.names_len; ++i)
		insert(ThreadName(object.names.names_val[i]));
	}

	/** Type conversion to a OpenSS_Protocol_ThreadNameGroup object. */
	operator OpenSS_Protocol_ThreadNameGroup() const
	{
	    OpenSS_Protocol_ThreadNameGroup object;
	    object.names.names_len = size();
	    if(!empty()) {
		object.names.names_val = new OpenSS_Protocol_ThreadName[size()];
		int idx = 0;
		for(ThreadNameGroup::const_iterator
			i = begin(); i != end(); ++i, ++idx)
		    object.names.names_val[idx] = *i;
	    }
	    return object;
	}
	
    };

} }



#endif

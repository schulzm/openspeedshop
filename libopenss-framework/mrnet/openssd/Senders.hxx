////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2007 William Hachfeld. All Rights Reserved.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////

/** @file
 *
 * Declaration of the Senders namespace.
 *
 */

#ifndef _OpenSpeedShop_Framework_Senders_
#define _OpenSpeedShop_Framework_Senders_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "AddressRange.hxx"
#include "Job.hxx"

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#include <string>



namespace OpenSpeedShop { namespace Framework {

    class FileName;
    class ThreadName;
    class ThreadNameGroup;
    class Time;
    
    /**
     * Message senders.
     *
     * Namespace containing the message sender functions. These functions
     * package and send outgoing requests to the frontend.
     *
     * @ingroup Implementation
     */
    namespace Senders
    {
	void attachedToThread();
	void globalIntegerValue(const ThreadName&, const std::string&,
				const int64_t&);
	void globalJobValue(const ThreadName&, const std::string&,
			    const Job&);
	void globalStringValue(const ThreadName&, const std::string&,
			       const std::string&);
	void loadedLinkedObject(const ThreadNameGroup&, const Time&,
				const AddressRange&, const FileName&,
				const bool&);
	void reportError();
	void symbolTable();
	void threadsStateChanged(const ThreadNameGroup&,
				 const OpenSS_Protocol_ThreadState&);
	void unloadedLinkedObject(const ThreadNameGroup&, const Time&,
				  const FileName&);
    }
    
} }



#endif

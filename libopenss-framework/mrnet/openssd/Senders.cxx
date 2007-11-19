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
 * Definition of the Senders namespace.
 *
 */

#include "Backend.hxx"
#include "Blob.hxx"
#include "Collector.hxx"
#include "FileName.hxx"
#include "Protocol.h"
#include "Senders.hxx"
#include "ThreadName.hxx"
#include "ThreadNameGroup.hxx"
#include "Time.hxx"
#include "Utility.hxx"

using namespace OpenSpeedShop::Framework;



namespace {



    /**
     * Convert string for protocol use.
     *
     * Converts the specified C++ string to a C character array as used in
     * protocol messages.
     *
     * @note    The caller assumes responsibility for releasing the C character
     *          array when it is no longer needed.
     *
     * @param in      C++ string to be converted.
     * @retval out    C character array to hold the results.
     */
    void convert(const std::string& in, char*& out)
    {
        if(!in.empty()) {
            out = new char[in.size()];
            strcpy(out, in.c_str());
        }
        else
            out = NULL;
    }



    /**
     * Convert job for protocol use.
     *
     * Converts the specified framework job object to the structure used in
     * protocol messages.
     *
     * @note    The caller assumes responsibility for releasing all allocated
     *          memory when it is no longer needed.
     *
     * @param in      Job to be converted.
     * @retval out    Structure to hold the results.
     */
    void convert(const Job& in, OpenSS_Protocol_Job& out)
    {
	// Is the job non-empty?
	if(!in.empty()) {

	    // Allocate an appropriately sized array of entries
	    out.entries.entries_len = in.size();
	    out.entries.entries_val = new OpenSS_Protocol_JobEntry[in.size()];

	    // Iterate over each entry of this job
	    OpenSS_Protocol_JobEntry* ptr = out.entries.entries_val;
	    for(Job::const_iterator
		    i = in.begin(); i != in.end(); ++i, ++ptr) {
		convert(i->first, ptr->host);
		ptr->pid = i->second;
	    }
	    
	}
	else {
	    out.entries.entries_len = 0;
	    out.entries.entries_val = NULL;
	}
    }
    
    
    
}



/**
 * Attached to a thread.
 *
 * ...
 */
void Senders::attachedToThread()
{
    // TODO: implement!
}



/**
 * Value of an integer global variable.
 *
 * Issue a message to the frontend to return the current value of a signed
 * integer global variable within a thread.
 *
 * @param thread    Thread from which the global variable value was retrieved.
 * @param global    Name of global variable whose value is being returned.
 * @param value     Current value of that variable.
 */
void Senders::globalIntegerValue(const ThreadName& thread,
				 const std::string& global,
				 const int64_t& value)
{
    // Assemble the request into a message
    OpenSS_Protocol_GlobalIntegerValue message;
    message.thread = thread;
    convert(global, message.global);
    message.value = value;

#ifndef NDEBUG
    if(Backend::isDebugEnabled()) {
	std::stringstream output;
	output << "[TID " << pthread_self() << "] Senders::"
	       << toString(message);
	std::cerr << output.str();
    }
#endif

    // Encode the message into a blob
    Blob blob(
        reinterpret_cast<xdrproc_t>(xdr_OpenSS_Protocol_GlobalIntegerValue),
	&message
	);

    // Send the encoded message to the frontend
    Backend::sendToFrontend(OPENSS_PROTOCOL_TAG_GLOBAL_INTEGER_VALUE, blob);

    // Destroy the message
    xdr_free(
        reinterpret_cast<xdrproc_t>(xdr_OpenSS_Protocol_GlobalIntegerValue),
	reinterpret_cast<char*>(&message)
	);    
}



/**
 * Value of a job description variable.
 *
 * Issue a message to the frontend to return the current value of a job
 * description global variable within a thread.
 *
 * @param thread    Thread from which the global variable value was retrieved.
 * @param global    Name of global variable whose value is being returned.
 * @param job       Current value of that variable.
 */
void Senders::globalJobValue(const ThreadName& thread,
			     const std::string& global,
			     const Job& job)
{
    // Assemble the request into a message
    OpenSS_Protocol_GlobalJobValue message;
    message.thread = thread;
    convert(global, message.global);
    convert(job, message.value);
    
#ifndef NDEBUG
    if(Backend::isDebugEnabled()) {
	std::stringstream output;
	output << "[TID " << pthread_self() << "] Senders::"
	       << toString(message);
	std::cerr << output.str();
    }
#endif
    
    // Encode the message into a blob
    Blob blob(
        reinterpret_cast<xdrproc_t>(xdr_OpenSS_Protocol_GlobalJobValue),
	&message
	);

    // Send the encoded message to the frontend
    Backend::sendToFrontend(OPENSS_PROTOCOL_TAG_GLOBAL_JOB_VALUE, blob);

    // Destroy the message
    xdr_free(
        reinterpret_cast<xdrproc_t>(xdr_OpenSS_Protocol_GlobalJobValue),
	reinterpret_cast<char*>(&message)
	);    
}



/**
 * Value of a string global variable.
 *
 * Issue a message to the frontend to return the current value of a character
 * string global variable within a thread.
 *
 * @param thread    Thread from which the global variable value was retrieved.
 * @param global    Name of global variable whose value is being returned.
 * @param value     Current value of that variable.
 */
void Senders::globalStringValue(const ThreadName& thread,
				const std::string& global,
				const std::string& value)
{
    // Assemble the request into a message
    OpenSS_Protocol_GlobalStringValue message;
    message.thread = thread;
    convert(global, message.global);
    convert(value, message.value);

#ifndef NDEBUG
    if(Backend::isDebugEnabled()) {
	std::stringstream output;
	output << "[TID " << pthread_self() << "] Senders::"
	       << toString(message);
	std::cerr << output.str();
    }
#endif

    // Encode the message into a blob
    Blob blob(
        reinterpret_cast<xdrproc_t>(xdr_OpenSS_Protocol_GlobalStringValue),
	&message
	);

    // Send the encoded message to the frontend
    Backend::sendToFrontend(OPENSS_PROTOCOL_TAG_GLOBAL_STRING_VALUE, blob);

    // Destroy the message
    xdr_free(
        reinterpret_cast<xdrproc_t>(xdr_OpenSS_Protocol_GlobalStringValue),
	reinterpret_cast<char*>(&message)
	);    
}



/**
 * Linked object has been loaded.
 *
 * Issue a message to the frontend to indicate that the specified linked object
 * has been loaded into the address space of the specified threads. Includes the
 * time at which the load occured as well as a description of what was loaded.
 *
 * @param threads          Threads which loaded the linked object.
 * @param time             Time at which the linked object was loaded.
 * @param range            Address range at which this linked object was loaded.
 * @param linked_object    Name of the linked object's file.
 * @param is_executable    Boolean "true" if this linked object is an
 *                         executable, or "false" otherwise.
 */
void Senders::loadedLinkedObject(const ThreadNameGroup& threads,
				 const Time& time,
				 const AddressRange& range,
				 const FileName& linked_object,
				 const bool& is_executable)
{
    // Assemble the request into a message
    OpenSS_Protocol_LoadedLinkedObject message;
    message.threads = threads;
    message.time = time.getValue();
    message.range.begin = range.getBegin().getValue();
    message.range.end = range.getEnd().getValue();
    message.linked_object = linked_object;
    message.is_executable = is_executable;
    
#ifndef NDEBUG
    if(Backend::isDebugEnabled()) {
	std::stringstream output;
	output << "[TID " << pthread_self() << "] Senders::"
	       << toString(message);
	std::cerr << output.str();
    }
#endif

    // Encode the message into a blob
    Blob blob(
        reinterpret_cast<xdrproc_t>(xdr_OpenSS_Protocol_LoadedLinkedObject),
	&message
	);

    // Send the encoded message to the frontend
    Backend::sendToFrontend(OPENSS_PROTOCOL_TAG_LOADED_LINKED_OBJECT, blob);

    // Destroy the message
    xdr_free(
        reinterpret_cast<xdrproc_t>(xdr_OpenSS_Protocol_LoadedLinkedObject),
	reinterpret_cast<char*>(&message)
	);    
}



/**
 * Report an error.
 *
 * ...
 */
void Senders::reportError()
{
    // TODO: implement!
}



/**
 * Symbol table.
 *
 * Issue a message to the frontend to provide the symbol table for a single
 * linked object.
 */
void Senders::symbolTable()
{
    // TODO: implement!
}



/**
 * Thread's state has changed.
 *
 * Issue a message to the frontend to indicate that the current state of
 * every thread in the specified group has changed to the specified value.
 *
 * @param threads    Threads whose state has changed.
 * @param state      State to which these threads have changed.
 */
void Senders::threadsStateChanged(const ThreadNameGroup& threads,
				  const OpenSS_Protocol_ThreadState& state)
{
    // Assemble the request into a message
    OpenSS_Protocol_ThreadsStateChanged message;
    message.threads = threads;
    message.state = state;
    
#ifndef NDEBUG
    if(Backend::isDebugEnabled()) {
	std::stringstream output;
	output << "[TID " << pthread_self() << "] Senders::"
	       << toString(message);
	std::cerr << output.str();
    }
#endif

    // Encode the message into a blob
    Blob blob(
        reinterpret_cast<xdrproc_t>(xdr_OpenSS_Protocol_ThreadsStateChanged),
	&message
	);

    // Send the encoded message to the frontend
    Backend::sendToFrontend(OPENSS_PROTOCOL_TAG_THREADS_STATE_CHANGED, blob);

    // Destroy the message
    xdr_free(
        reinterpret_cast<xdrproc_t>(xdr_OpenSS_Protocol_ThreadsStateChanged),
	reinterpret_cast<char*>(&message)
	);
}



/**
 * Linked object has been unloaded.
 *
 * Issue a message to the frontend to indicate that the specified linked object
 * has been unloaded from the address space of the specified threads. Includes
 * the time at which the unload occured as well as a description of what was
 * unloaded.
 *
 * @param threads          Threads which unloaded the linked object.
 * @param time             Time at which the linked object was unloaded.
 * @param linked_object    Name of the linked object's file.
 */
void Senders::unloadedLinkedObject(const ThreadNameGroup& threads,
				   const Time& time,
				   const FileName& linked_object)
{
    // Assemble the request into a message
    OpenSS_Protocol_UnloadedLinkedObject message;
    message.threads = threads;
    message.time = time.getValue();
    message.linked_object = linked_object;
    
#ifndef NDEBUG
    if(Backend::isDebugEnabled()) {
	std::stringstream output;
	output << "[TID " << pthread_self() << "] Senders::"
	       << toString(message);
	std::cerr << output.str();
    }
#endif

    // Encode the message into a blob
    Blob blob(
        reinterpret_cast<xdrproc_t>(xdr_OpenSS_Protocol_UnloadedLinkedObject),
	&message
	);

    // Send the encoded message to the frontend
    Backend::sendToFrontend(OPENSS_PROTOCOL_TAG_UNLOADED_LINKED_OBJECT, blob);

    // Destroy the message
    xdr_free(
        reinterpret_cast<xdrproc_t>(xdr_OpenSS_Protocol_UnloadedLinkedObject),
	reinterpret_cast<char*>(&message)
	);
}

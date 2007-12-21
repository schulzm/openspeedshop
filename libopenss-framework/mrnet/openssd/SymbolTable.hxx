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
// You should have received a copy of the GNU Lesser General Public License.
// along with this library; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
////////////////////////////////////////////////////////////////////////////////

/** @file
 *
 * Declaration of the SymbolTable class.
 *
 */

#ifndef _OpenSpeedShop_Framework_SymbolTable_
#define _OpenSpeedShop_Framework_SymbolTable_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "AddressBitmap.hxx"
#include "AddressRange.hxx"
#include "FileName.hxx"
#include "Protocol.h"

#include <BPatch.h>
#include <map>
#include <string>
#include <vector>



namespace OpenSpeedShop { namespace Framework {
    
    /**
     * Symbol table.
     *
     * Table containing the symbols for a single linked object. Encapsulates
     * the retrieval of the symbols from Dyninst and the conversion of those
     * symbols into the format of the frontend/backend communication protocol.
     *
     * @note    This class has intentionally been given an identical name to
     *          the similar class in the framework library itself. In the near
     *          future, the experiment database functionality may be split into
     *          a separate library and utilized by the daemon. If that happens,
     *          this class will be removed in favor of the existing framework
     *          class.
     *    
     * @ingroup Implementation
     */   
    class SymbolTable
    {
	
    public:
	
	SymbolTable();
	SymbolTable(/* const */ BPatch_module&);
	
	void addModule(/* const */ BPatch_module&);
	
	operator OpenSS_Protocol_SymbolTable() const;
	
    private:
	
	static std::vector<AddressBitmap>
	partitionAddressRanges(const std::vector<AddressRange>&);

	static void convert(const std::vector<AddressBitmap>&,
			    u_int&, OpenSS_Protocol_AddressBitmap*&);
	
	/** Functions in this symbol table. */
	std::map<std::string, std::vector<AddressRange> > dm_functions;
	
	/**
	 * Statement entry.
	 * 
	 * Structure for a source statement's entry in the symbol table's
	 * internal tables. Contains the full path name, line number, column
	 * number, and address bitmaps of the source statement.
	 */
	struct StatementEntry
	{

	    FileName dm_path;  /**< Name of this statement's source file. */
	    int dm_line;       /**< Line number of this statement. */
	    int dm_column;     /**< Column number of this statement. */
	    
	    /** Constructor from fields. */
	    StatementEntry(const FileName& path,
			   const int& line, const int& column) :
		dm_path(path),
		dm_line(line),
		dm_column(column)
	    {
	    }
	    
	    /** Operator "<" defined for two StatementEntry objects. */
	    bool operator<(const StatementEntry& other) const
	    {
		if(dm_path < other.dm_path)
		    return true;
		if(dm_path > other.dm_path)
		    return false;
		if(dm_line < other.dm_line)
		    return true;
		if(dm_line > other.dm_line)
		    return false;
		return dm_column < other.dm_column;
	    }

	};
	
	/** Statements in this symbol table. */
	std::map<StatementEntry, std::vector<AddressRange> > dm_statements;

    };

} }



#endif
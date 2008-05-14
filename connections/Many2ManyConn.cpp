/**********************************************************************
** This program is part of 'MOOSE', the
** Messaging Object Oriented Simulation Environment,
** also known as GENESIS 3 base code.
**           copyright (C) 2003-2008 Upinder S. Bhalla. and NCBS
** It is made available under the terms of the
** GNU Lesser General Public License version 2.1
** See the file COPYING.LIB for the full notice.
**********************************************************************/

#include "header.h"
#include "SimpleConn.h"
#include "../utility/SparseMatrix.h"
#include "Many2ManyConn.h"

Many2ManyConnTainer::Many2ManyConnTainer( Eref e1, Eref e2, 
			int msg1, int msg2,
			unsigned int i1, unsigned int i2 )
			: 
	ConnTainer( e1.e, e2.e, msg1, msg2 ), 
	entries_( e1.e->numEntries(), e2.e->numEntries() ),
	i1_( i1 )
{
	entries_.set( e1.i, e2.i, i2 );
}

Conn* Many2ManyConnTainer::conn( unsigned int eIndex, bool isReverse ) const
{
	//	numIter_++; // For reference counting. Do we need it?
	if ( isReverse )
		return new ReverseMany2ManyConn( this, eIndex );
	else
		return new Many2ManyConn( this, eIndex );
}

Conn* Many2ManyConnTainer::conn( unsigned int eIndex, bool isReverse,
	unsigned int connIndex ) const
{
	//	numIter_++; // For reference counting. Do we need it?
	if ( connIndex != 0 )
		return 0;

	if ( isReverse )
		return new ReverseMany2ManyConn( this, 0 );
	else
		return new Many2ManyConn( this, 0 );
}

/**
 * Creates a duplicate ConnTainer for message(s) between 
 * new elements e1 and e2,
 * It checks the original version for which msgs to put the new one on.
 * e1 must be the new source element.
 * Returns the new ConnTainer on success, otherwise 0.
 */
ConnTainer* Many2ManyConnTainer::copy( Element* e1, Element* e2 ) const
{
	// assert( e1->numMsg() > msg1() );
	// assert( e2->numMsg() > msg2() );

	Many2ManyConnTainer* ret = 
		new Many2ManyConnTainer( e1, e2, msg1(), msg2(), i1_, 0 );
	ret->entries_ = entries_;
	return ret;
}


/**
 * Traverse through all messages to find one that matches
 * Check connTainer type.
 * Add it.
 */
bool addToConnTainer( unsigned int srcI, unsigned int destI )
{
	
}

unsigned int Many2ManyConnTainer::getRow( unsigned int i, 
			const unsigned int** index, const unsigned int** eIndex ) const
{
	return entries_.getRow( i, index, eIndex );
}

unsigned int Many2ManyConnTainer::getColumn( unsigned int i, 
			vector< unsigned int >& index,
			vector< unsigned int >& eIndex ) const
{
	return entries_.getColumn( i, index, eIndex );
}

//////////////////////////////////////////////////////////////////////
//  Many2ManyConn
//////////////////////////////////////////////////////////////////////

const Conn* Many2ManyConn::flip() const
{
	return new ReverseMany2ManyConn( s_, *tgtEindexIter_ );
}

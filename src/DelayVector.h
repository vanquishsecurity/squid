
/*
 * $Id: DelayVector.h,v 1.4 2003/03/04 01:40:25 robertc Exp $
 *
 *
 * SQUID Web Proxy Cache          http://www.squid-cache.org/
 * ----------------------------------------------------------
 *
 *  Squid is the result of efforts by numerous individuals from
 *  the Internet community; see the CONTRIBUTORS file for full
 *  details.   Many organizations have provided support for Squid's
 *  development; see the SPONSORS file for full details.  Squid is
 *  Copyrighted (C) 2001 by the Regents of the University of
 *  California; see the COPYRIGHT file for full details.  Squid
 *  incorporates software developed and/or copyrighted by other
 *  sources; see the CREDITS file for full details.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 *
 * Copyright (c) 2003, Robert Collins <robertc@squid-cache.org>
 */

#ifndef SQUID_DELAYVECTOR_H
#define SQUID_DELAYVECTOR_H

#include "CompositePoolNode.h"

class DelayVector : public CompositePoolNode
{

public:
    typedef RefCount<DelayVector> Pointer;
    void *operator new(size_t);
    void operator delete (void *);
    virtual void deleteSelf() const;
    virtual ~DelayVector();
    virtual void stats(StoreEntry * sentry);
    virtual void dump(StoreEntry *entry) const;
    virtual void update(int incr);
    virtual void parse();

    virtual DelayIdComposite::Pointer id(struct in_addr &src_addr, AuthUserRequest *);
    void push_back (CompositePoolNode::Pointer);

private:

class Id:public DelayIdComposite
    {

    public:
        void *operator new(size_t);
        void operator delete (void *);
        virtual void deleteSelf() const;

        Id (DelayVector::Pointer,struct in_addr &src_addr, AuthUserRequest *);
        ~Id();
        virtual int bytesWanted (int min, int max) const;
        virtual void bytesIn(int qty);
        virtual void delayRead(DeferredRead const &);

    private:
        DelayVector::Pointer theVector;
        Vector<DelayIdComposite::Pointer> ids;
        typedef Vector<DelayIdComposite::Pointer>::iterator iterator;
        typedef Vector<DelayIdComposite::Pointer>::const_iterator const_iterator;
    };

    Vector<CompositePoolNode::Pointer> pools;
    typedef Vector<CompositePoolNode::Pointer>::iterator iterator;
    typedef Vector<CompositePoolNode::Pointer>::const_iterator const_iterator;
};

#endif /* SQUID_DELAYVECTOR_H */

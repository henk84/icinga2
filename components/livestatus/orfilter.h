/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2013 Icinga Development Team (http://www.icinga.org/)   *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef ORFILTER_H
#define ORFILTER_H

#include "livestatus/combinerfilter.h"

using namespace icinga;

namespace icinga
{

/**
 * @ingroup livestatus
 */
class OrFilter : public CombinerFilter
{
public:
	DECLARE_PTR_TYPEDEFS(OrFilter);

	OrFilter(void);

	virtual bool Apply(const Table::Ptr& table, const Value& row);
};

}

#endif /* ORFILTER_H */

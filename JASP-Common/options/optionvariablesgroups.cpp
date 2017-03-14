//
// Copyright (C) 2013-2017 University of Amsterdam
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "optionvariablesgroups.h"

#include <boost/foreach.hpp>

using namespace std;

OptionVariablesGroups::OptionVariablesGroups()
	: OptionI(true)
{
}

Json::Value OptionVariablesGroups::asJSON() const
{
	Json::Value v = Json::arrayValue;

	BOOST_FOREACH(const vector<string> &group, _value)
	{
		Json::Value u = Json::arrayValue;

		BOOST_FOREACH(const string &variable, group)
			u.append(variable);

		v.append(u);
	}

	return v;
}

void OptionVariablesGroups::set(const Json::Value &value)
{
	vector<vector<string> > groups;

	for (Json::ValueIterator itr = value.begin(); itr != value.end(); itr++)
	{
		vector<string> group;

		Json::Value &g = *itr;

		for (Json::ValueIterator gtr = g.begin(); gtr != g.end(); gtr++)
		{
			Json::Value &v = *gtr;
			string variable = v.asString();
			group.push_back(variable);
		}

		groups.push_back(group);
	}

	setValue(groups);
}

Option *OptionVariablesGroups::clone() const
{
	OptionVariablesGroups *c = new OptionVariablesGroups();
	c->setValue(value());
	return c;
}

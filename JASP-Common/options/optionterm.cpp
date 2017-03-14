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

#include "optionterm.h"

#include <boost/foreach.hpp>

using namespace std;

OptionTerm::OptionTerm()
	: OptionTerms(false, true)
{
}

Json::Value OptionTerm::asJSON() const
{
	Json::Value v(Json::arrayValue);

	if (_value.size() > 0)
	{
		BOOST_FOREACH(string field, _value.front())
		{
			v.append(field);
		}
	}

	return v;
}

void OptionTerm::set(const Json::Value &value)
{
	vector<string> terms;

	if (value.isArray())
	{
		for (uint i = 0; i < value.size(); i++)
			terms.push_back(value[i].asString());
	}

	setValue(terms);
}

Option *OptionTerm::clone() const
{
	OptionTerm *c = new OptionTerm();
	c->setValue(this->term());
	return c;
}

void OptionTerm::setValue(const vector<string> &value)
{
	vector<vector<string> > terms;
	terms.push_back(value);
	OptionTerms::setValue(terms);
}

vector<string> OptionTerm::term() const
{
	if (_value.size() > 0)
		return _value.front();
	else
		return vector<string>();
}

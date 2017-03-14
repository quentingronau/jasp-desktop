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

#include "option.h"

using namespace std;

Option::Option(bool transient)
{
	_isTransient = transient;
	_signalsBlocked = 0;
	_shouldSignalOnceUnblocked = false;
}

Option::~Option()
{
}

void Option::blockSignals(bool block)
{
	if (block)
	{
		_signalsBlocked++;
	}
	else
	{
		_signalsBlocked--;
		if (_signalsBlocked < 0)
			_signalsBlocked = 0;

		if (_signalsBlocked == 0 && _shouldSignalOnceUnblocked)
		{
			changed(this);
			_shouldSignalOnceUnblocked = false;
		}
	}
}

bool Option::isTransient() const
{
	return _isTransient;
}

void Option::notifyChanged()
{
	if (_signalsBlocked)
		_shouldSignalOnceUnblocked = true;
	else
		changed(this);
}






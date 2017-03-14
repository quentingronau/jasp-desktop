//
// Copyright (C) 2017 University of Amsterdam
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

#ifndef EXPORTER_H
#define EXPORTER_H

#include <string>
#include "datasetpackage.h"
#include <boost/function.hpp>
#include <boost/assign/list_of.hpp>
#include <vector>

#include "common.h"
#include "utils.h"

class Exporter
{
protected:
	Utils::FileType _defaultFileType;
	Utils::FileTypeVector _allowedFileTypes;
	Utils::FileType _currentFileType;
	Exporter();

public:

	virtual ~Exporter();
	virtual void saveDataSet(const std::string &path, DataSetPackage* package, boost::function<void (const std::string &, int)> progressCallback) = 0;

	Utils::FileType getDefaultFileType();
	bool isFileTypeAllowed(Utils::FileType filetype);
	Utils::FileTypeVector getAllowedFileTypes();
	bool setFileType(Utils::FileType filetype);
};

#endif // EXPORTER_H

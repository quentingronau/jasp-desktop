/*
	Copyright (C) Copyright (C) 2013-2017 University of Amsterdam

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.


	File created by patrick, on 11-01-2017
	Original file name was odsimportcolumn.cpp
*/

#ifndef ODSIMPORTCOLUMN_H
#define ODSIMPORTCOLUMN_H

#include "../importcolumn.h"
#include "odssheetcell.h"

#include <set>

namespace ods
{

class ODSImportColumn : public ImportColumn
{
public:

	// The empty value for a cell.
	static const ODSSheetCell EmptySheetCell;

	// The constainer used to hold rows within the column.
	typedef std::vector<ODSSheetCell>	Cases;

	ODSImportColumn(int columnNumber);
	virtual ~ODSImportColumn();

	/**
	 * @brief setName Setter for long name (label).
	 * @param longname The long name (label) to set.
	 */
//	void setLongName(const string &longname) { _longName = longname; }
	void setName(const std::string &name) { _name = name; }


	// ImportColumn interface
	/**
	 * @brief size Returns the size of (i.e. number of) rows.
	 * @return The size of (i.e. number of) rows.
	 */
	virtual size_t size() const;

	/**
	 * @brief isValueEqual Returns true if the column/row are identical.
	 * @param col The columns
	 * @param row
	 * @return true if equal.
	 */
	virtual bool isValueEqual(Column &col, size_t row) const;

	/**
	 * @brief hasCall Checks for presence of a cell at row.
	 * @param row Row check for.
	 * @return true if value in column.
	 */
	inline bool hasCell(size_t row) const
	{
		return (_index.find(row) != _index.end());
	}

	/**
	 * @brief _createSpace Ensures that we have enough elements in _rows.
	 * @param row Row number to check for.
	 */
	void createSpace(size_t row);


	/**
	 * @brief setValue Inserts one cell value.
	 * @param row Row to insert
	 * @param type ODS data type.
	 * @param data ODS cell value.
	 */
	void setValue(int row, XmlDatatype type, const QString& data);

	/**
	 * @brief setValue Inserts string value for cell, irrespective of type.
	 * @param row
	 * @param data
	 */
	void setValue(int row, const QString& data);

	const ODSSheetCell &getCell(int row) const { return _rows.at(row); }

	/**
	 * @brief postLoadProcess Performs posy load processing.
	 *
	 * This includes finding the long column name,
	 * and the type of the column, and converting all
	 * the cells to the same type.
	 *
	 */
	void postLoadProcess();

	Column::ColumnType	columnType() const { return _columnType; }

	// As per Importers.
	void fillSharedMemoryColumn(Column &column) const;

	// Getters.
	Column::ColumnType getJASPColumnType() const { return _columnType; }

private:

	// The cells/rows (as read).
	Cases	_rows;

	typedef std::map< int, size_t > CellIndex;
	CellIndex			_index;		///< cell indexes indexed by row.
	int					_columnNumber; //<- We know our own column number
	Column::ColumnType	_columnType; // Our column type.

	/**
	 * @brief _forceToType Force all cells to the type.
	 * @param type Type to force.
	 */
	void _forceToType(Column::ColumnType type);

	/**
	 * @brief colNumberAsExcel Returns the column number as a string (base 26 A-Z).
	 * @param column Column number
	 * @return
	 */
	static std::string _colNumberAsExcel(int column);

	/**
	 * @brief setColumnConvertStringData Sets String data into the column, after doing a code page convert.
	 * @param column The columns to insert into.
	 */
	void _setColumnConvertStringData(Column &column);

	/**
	 * @brief setColumnConvertDblToString Sets String data into the column.
	 * @param column The columns to insert into.
	 */
	void _setColumnConvertDblToString(Column &column);

	/**
	 * @brief setColumnLabeledData Sets numeric data into the column, with labels.
	 * @param column The columns to insert into.
	 */
	void _setColumnLabeledData(Column &column);

	/**
	 * @brief setColumnScaleData Sets floating point / scalar data into the column.
	 * @param column The columns to insert into.
	 */
	void _setColumnScaleData(Column &column);

};

} // end namespace.
#endif // sentinal ODSIMPORTCOLUMN_H

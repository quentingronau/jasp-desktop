//
// Copyright (C) 2015 University of Amsterdam
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public
// License along with this program.  If not, see
// <http://www.gnu.org/licenses/>.
//

#include "backstageosf.h"

#include <QLabel>

#include "fsbmosf.h"

BackstageOSF::BackstageOSF(QWidget *parent) : BackstagePage(parent)
{
	QGridLayout *layout = new QGridLayout(this);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);

	QLabel *label = new QLabel("Open Science Framework", this);
	label->setContentsMargins(12, 12, 0, 1);
	layout->addWidget(label);

	QLabel *name = new QLabel("User: Damian Dropmann", this);
	name->setContentsMargins(12, 12, 0, 1);
	layout->addWidget(name);

	_breadCrumbs = new BreadCrumbs(this);
	layout->addWidget(_breadCrumbs);

	QWidget *line;

	line = new QWidget(this);
	line->setFixedHeight(1);
	line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	line->setStyleSheet("QWidget { background-color: #A3A4A5 ; }");
	layout->addWidget(line);

	_model = new FSBMOSF();
	_model->refresh();

	_fsBrowser = new FSBrowser(this);
	_fsBrowser->setViewType(FSBrowser::ListView);
	_fsBrowser->setFSModel(_model);
	layout->addWidget(_fsBrowser);

	_breadCrumbs->setModel(_model);

	connect(_fsBrowser, SIGNAL(entryOpened(QString)), this, SLOT(notifyDataSetOpened(QString)));

	line = new QWidget(this);
	line->setFixedHeight(1);
	line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	line->setStyleSheet("QWidget { background-color: #A3A4A5 ; }");
	layout->addWidget(line);

	QWidget *browseContainer = new QWidget(this);
	browseContainer->setObjectName("browseContainer");
	layout->addWidget(browseContainer);

	QHBoxLayout *browseLayout = new QHBoxLayout(browseContainer);
	browseContainer->setLayout(browseLayout);

	_browseButton = new QPushButton(browseContainer);
	_browseButton->setText("Browse");
	browseLayout->addWidget(_browseButton, 0, Qt::AlignRight);

	line = new QWidget(this);
	line->setFixedWidth(1);
	line->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	line->setStyleSheet("QWidget { background-color: #A3A4A5 ; }");
	layout->addWidget(line, 0, 1, 6, 1);
}

void BackstageOSF::setOnlineDataManager(OnlineDataManager *odm)
{
	_model->setOnlineDataManager(odm);
	_model->refresh();
}

void BackstageOSF::notifyDataSetOpened(QString path)
{
	FSBMOSF::OnlineNodeData nodeData = _model->getNodeData(path);
	openFile(nodeData.nodePath, nodeData.name);
}


FileEvent *BackstageOSF::openFile(const QString &nodePath, const QString &filename)
{

	FileEvent *event = new FileEvent(this);
	event->setOperation(FileEvent::FileOpen);

	if (filename != "")
	{
		event->setPath(nodePath + "#" + filename);

		if ( ! filename.endsWith(".jasp", Qt::CaseInsensitive))
			event->setReadOnly();

		emit dataSetIORequest(event);
	}
	else
	{
		event->setComplete(false);
	}

	return event;
}

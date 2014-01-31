
#include "utils.h"

#include <QStringList>
#include <boost/foreach.hpp>

using namespace std;

std::string fq(const QString &from)
{
	QByteArray bytes = from.toUtf8();
	return std::string(bytes.constData(), bytes.length());
}

QString tq(const std::string &from)
{
	return QString::fromUtf8(from.c_str(), from.length());
}

QStringList tql(const std::vector<std::string> &from)
{
	(void)from;

	QStringList result;

	BOOST_FOREACH(const std::string &str, from)
	{
		(void)from;
		result.append(tq(str));
	}

	return result;
}


bool remove(vector<string> &array, string &value)
{
	vector<string>::iterator itr = array.begin();

	while (itr != array.end())
	{
		if (*itr == value)
		{
			array.erase(itr);
			return true;
		}

		itr++;
	}

	return false;
}

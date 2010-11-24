#include <QHBoxLayout>

#include "Table.h"
#include "Row.h"

Table::Table(QString rowsTitle, QStringList *rows, QStringList *cols, bool showSum)
{
	QHBoxLayout *colsLayout = new QHBoxLayout;
	colsLayout->addStretch();

	m_columnList = new QList<Column *>;

	Row *rowsColumn = new Row(rowsTitle, rows, showSum);
	colsLayout->addWidget(rowsColumn);

	int rowsNum = rows->size();
	int colsNum = cols->size();

	for(int i = 0; i < colsNum; i++)
	{
		Column *column = new Column(cols->at(i), rowsNum, showSum, false);
		colsLayout->addWidget(column);
		m_columnList->append(column);
	}
	colsLayout->addStretch();

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addStretch();
	mainLayout->addLayout(colsLayout);
	mainLayout->addStretch();

	setLayout(mainLayout);
}

QString Table::getValues()
{
	QString values;

	int length = m_columnList->size();

	for(int i = 0; i < length; i++)
	{
		values += (m_columnList->at(i)->getValues() + "\n");
	}

	return values;
}

QString Table::getColumnValues(int column)
{
	return m_columnList->at(column)->getValues();
}

void Table::setValues(QString values)
{
	QStringList valuesList = values.split("\n");

	int length = valuesList.size() - 1;

	for(int i = 0; i < length; i++)
	{
		m_columnList->at(i)->setValues(valuesList.at(i));
	}
}

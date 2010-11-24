#ifndef TABLE_H
#define TABLE_H

#include <QWidget>

#include "Column.h"

class Table : public QWidget
{
	Q_OBJECT

public:
	Table(QString rowsTitle, QStringList *rows, QStringList *cols, bool showSum);

public slots:
	QString getValues();
	QString getColumnValues(int column);
	void setValues(QString values);

private:
	QList<Column *> *m_columnList;
};

#endif // TABLE_H

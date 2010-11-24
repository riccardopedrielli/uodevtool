#ifndef ROW_H
#define ROW_H

#include <QGroupBox>

class Row : public QGroupBox
{
	Q_OBJECT

public:
	Row(QString title, QStringList *rows, bool showSum, QWidget *parent = 0);
};

#endif // ROW_H

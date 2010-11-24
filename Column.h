#ifndef COLUMN_H
#define COLUMN_H

#include <QGroupBox>
#include <QLineEdit>

class Column : public QGroupBox
{
	Q_OBJECT

public:
	Column(QString title, int rows, bool showSum, bool readOnly, QWidget *parent = 0);

public slots:
	QString getValues();
	void setValues(QString values);

private:
	QList<QLineEdit *> *m_valuesEditList;

private slots:
	void getSum();

signals:
	void sumChanged(QString sum);
};

#endif // COLUMN_H

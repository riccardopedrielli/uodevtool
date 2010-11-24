#include <QVBoxLayout>
#include <QLabel>

#include "Column.h"

Column::Column(QString title, int rows, bool showSum, bool readOnly, QWidget *parent) : QGroupBox(title, parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout;

	m_valuesEditList = new QList<QLineEdit *>;

	for(int i = 0; i < rows; i++)
	{
		QLineEdit *lineEdit = new QLineEdit("0");
		lineEdit->setAlignment(Qt::AlignCenter);
		lineEdit->setReadOnly(readOnly);
		mainLayout->addWidget(lineEdit);
		m_valuesEditList->append(lineEdit);
		connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(getSum()));
	}

	if(showSum)
	{
		QLabel *label = new QLabel("0");
		label->setAlignment(Qt::AlignCenter);
		mainLayout->addWidget(label);
		connect(this, SIGNAL(sumChanged(QString)), label, SLOT(setText(QString)));
	}

	setAlignment(Qt::AlignCenter);
	setLayout(mainLayout);
	setFixedWidth(80);
}

QString Column::getValues()
{
	QString values;

	int length = m_valuesEditList->size();

	for(int i = 0; i < length; i++)
	{
		values += (m_valuesEditList->at(i)->text() + "\t");
	}

	return values;
}

void Column::setValues(QString values)
{
	QStringList valuesList = values.split("\t");

	int length = valuesList.size() - 1;

	for(int i = 0; i < length; i++)
	{
		m_valuesEditList->at(i)->setText(valuesList.at(i));
	}
}

void Column::getSum()
{
	int sum = 0;
	int length = m_valuesEditList->size();

	for(int i = 0; i < length; i++)
	{
		sum += m_valuesEditList->at(i)->text().toInt();
	}

	emit sumChanged(QString::number(sum));
}

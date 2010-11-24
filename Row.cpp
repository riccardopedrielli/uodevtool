#include <QVBoxLayout>
#include <QLabel>

#include "Row.h"

Row::Row(QString title, QStringList *rows, bool showSum, QWidget *parent) : QGroupBox(title, parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout;

	int rowsNum = rows->size();

	for(int i = 0; i < rowsNum; i++)
	{
		QLabel *label = new QLabel(rows->at(i));
		label->setAlignment(Qt::AlignCenter);
		mainLayout->addWidget(label);
	}

	if(showSum)
	{
		QLabel *label = new QLabel("Total");
		label->setAlignment(Qt::AlignCenter);
		mainLayout->addWidget(label);
	}

	setAlignment(Qt::AlignCenter);
	setLayout(mainLayout);
	setFixedWidth(80);
}

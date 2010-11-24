#include <QHBoxLayout>
#include <QLabel>

#include "ArmorCalc.h"
#include "Row.h"

ArmorCalc::ArmorCalc(QString rowsTitle, QStringList *rows, QStringList *armor, QStringList *ingots, QStringList *leather, QStringList *scales)
{
	m_ingotsList = ingots;
	m_leatherList = leather;
	m_scalesList = scales;

	armorType = new QComboBox;
	armorType->addItems(*armor);
	armorType->setFixedWidth((int)(armorType->sizeHint().width() * 1.5));
	matherialType = new QComboBox;
	matherialType->addItems(*leather);
	matherialType->setFixedWidth((int)(matherialType->sizeHint().width() * 1.5));

	QHBoxLayout *comboLayout = new QHBoxLayout;
	comboLayout->addWidget(new QLabel("Armor"));
	comboLayout->addWidget(armorType);
	comboLayout->addSpacing(10);
	comboLayout->addWidget(new QLabel("Matherial"));
	comboLayout->addWidget(matherialType);
	comboLayout->addStretch();

	int rowsNum = rows->size();
	Row *row = new Row(rowsTitle, rows, true);
	m_regularPart = new Column("Part", rowsNum, true, true);
	m_regularSet = new Column("Set", rowsNum, true, true);
	m_exceptionalPart = new Column("Exc Part", rowsNum, true, true);
	m_exceptionalSet = new Column("Exc Set", rowsNum, true, true);

	QHBoxLayout *colsLayout = new QHBoxLayout;
	colsLayout->addWidget(row);
	colsLayout->addStretch();
	colsLayout->addWidget(m_regularPart);
	colsLayout->addStretch();
	colsLayout->addWidget(m_regularSet);
	colsLayout->addStretch();
	colsLayout->addWidget(m_exceptionalPart);
	colsLayout->addStretch();
	colsLayout->addWidget(m_exceptionalSet);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(comboLayout);
	mainLayout->addStretch();
	mainLayout->addLayout(colsLayout);
	mainLayout->addStretch();

	setLayout(mainLayout);

	connect(armorType, SIGNAL(currentIndexChanged(int)), this, SLOT(updateMatherials(int)));
	connect(matherialType, SIGNAL(currentIndexChanged(int)), this, SLOT(requestValues(int)));
}

void ArmorCalc::computeArmor(QString armor, QString matherial)
{
	QStringList arResList = armor.split("\t");
	QStringList matResList = matherial.split("\t");

	QString regPart;
	QString regSet;
	QString excPart;
	QString excSet;

	int length = arResList.size() - 1;
	for(int i = 0; i < length; i++)
	{
		int arRes = arResList.at(i).toInt();
		int matRes = matResList.at(i).toInt();
		regPart += QString(QString::number(arRes + matRes) + "\t");
		excPart += QString(QString::number(arRes + matRes + 2) + "\t");
		regSet += QString(QString::number((arRes + matRes) * 6) + "\t");
		excSet += QString(QString::number((arRes + matRes + 2) * 6) + "\t");
	}

	m_regularPart->setValues(regPart);
	m_regularSet->setValues(regSet);
	m_exceptionalPart->setValues(excPart);
	m_exceptionalSet->setValues(excSet);
}

void ArmorCalc::requestValues(int matherialID)
{
	if(matherialType->count() > 0)
	{
		emit valuesRequired(armorType->currentIndex(), matherialID);
	}
}

void ArmorCalc::updateMatherials(int armorID)
{
	matherialType->clear();

	if(armorID > 5)
	{
		matherialType->addItems(*m_scalesList);
	}
	else if(armorID > 2)
	{
		matherialType->addItems(*m_ingotsList);
	}
	else
	{
		matherialType->addItems(*m_leatherList);
	}
}

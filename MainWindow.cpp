#include <QApplication>
#include <QHBoxLayout>
#include <QFile>

#include "MainWindow.h"

MainWindow::MainWindow()
{
	QStringList *resRows = new QStringList;
	resRows->append("Physical");
	resRows->append("Fire");
	resRows->append("Cold");
	resRows->append("Poison");
	resRows->append("Energy");

	QStringList *shieldsRows = new QStringList;
	shieldsRows->append("Tear kite");
	shieldsRows->append("Wooden");
	shieldsRows->append("Buckler");
	shieldsRows->append("Bronze");
	shieldsRows->append("Metal");
	shieldsRows->append("Metal kite");
	shieldsRows->append("Heater");
	shieldsRows->append("Chaos");
	shieldsRows->append("Order");

	QStringList *spellsRows = new QStringList;
	spellsRows->append("1");
	spellsRows->append("2");
	spellsRows->append("3");
	spellsRows->append("4");
	spellsRows->append("5");
	spellsRows->append("6");
	spellsRows->append("7");
	spellsRows->append("8");
	spellsRows->append("Medit");

	QStringList *armorCols = new QStringList;
	armorCols->append("Leather");
	armorCols->append("Studded");
	armorCols->append("Bone");
	armorCols->append("Ring");
	armorCols->append("Chain");
	armorCols->append("Plate");
	armorCols->append("Dragon");

	QStringList *shieldsCols = new QStringList;
	shieldsCols->append("Physical");
	shieldsCols->append("Medit");

	QStringList *ingotsCols = new QStringList;
	ingotsCols->append("Iron");
	ingotsCols->append("Dull Copper");
	ingotsCols->append("Shadow");
	ingotsCols->append("Copper");
	ingotsCols->append("Bronze");
	ingotsCols->append("Gold");
	ingotsCols->append("Agapite");
	ingotsCols->append("Verite");
	ingotsCols->append("Valorite");

	QStringList *leatherCols = new QStringList;
	leatherCols->append("Regular");
	leatherCols->append("Spined");
	leatherCols->append("Horned");
	leatherCols->append("Barbed");

	QStringList *scalesCols = new QStringList;
	scalesCols->append("Yellow");
	scalesCols->append("Red");
	scalesCols->append("Blue");
	scalesCols->append("Green");
	scalesCols->append("White");
	scalesCols->append("Black");

	QStringList *spellsCols = new QStringList;
	spellsCols->append("None");
	spellsCols->append("Leather");
	spellsCols->append("Studded");
	spellsCols->append("Bone");
	spellsCols->append("Ring");
	spellsCols->append("Chain");
	spellsCols->append("Dragon");
	spellsCols->append("Plate");

	Table *table;
	QTabWidget *pages = new QTabWidget;
	m_tablesList = new QList<Table *>;

	table = new Table("Resists", resRows, armorCols, true);
	pages->addTab(table, QIcon(":icons/armor"), "Armor");
	m_tablesList->append(table);

	table = new Table("Type", shieldsRows, shieldsCols, false);
	pages->addTab(table, QIcon(":icons/shields"), "Shields");
	m_tablesList->append(table);

	table = new Table("Resists", resRows, ingotsCols, true);
	pages->addTab(table, QIcon(":icons/ingots"), "Ingots");
	m_tablesList->append(table);

	table = new Table("Resists", resRows, leatherCols, true);
	pages->addTab(table, QIcon(":icons/leather"), "Leather");
	m_tablesList->append(table);

	table = new Table("Resists", resRows, scalesCols, true);
	pages->addTab(table, QIcon(":icons/scales"), "Scales");
	m_tablesList->append(table);

	table = new Table("Spells", spellsRows, spellsCols, false);
	pages->addTab(table, QIcon(":icons/spells"), "Spells");
	m_tablesList->append(table);

	ArmorCalc *arCalc= new ArmorCalc("Resists", resRows, armorCols, ingotsCols, leatherCols, scalesCols);
	pages->addTab(arCalc, QIcon(":icons/calc"), "Armor Calc");

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget(pages);

	setLayout(mainLayout);

	setWindowTitle(QString("UO Dev Tool %1").arg(VERSION));
	setWindowIcon(QIcon(":icons/uodt"));

	setFixedSize(minimumSizeHint());

	connect(arCalc, SIGNAL(valuesRequired(int, int)), this, SLOT(sendValues(int, int)));
	connect(this, SIGNAL(newValues(QString, QString)), arCalc, SLOT(computeArmor(QString, QString)));
	connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(saveData()));

	loadData();
	sendValues(0, 0);
}

void MainWindow::loadData()
{
	QFile *file = new QFile(FILE_NAME);
	if(file->open(QIODevice::ReadOnly))
	{
		QString values = file->readAll();
		file->close();

		QStringList m_valuesList = values.split("###\n");

		int length = m_valuesList.size() - 1;

		for(int i = 0; i < length; i++)
		{
			m_tablesList->at(i)->setValues(m_valuesList.at(i));
		}
	}
}

void MainWindow::saveData()
{
	QString values;

	int length = m_tablesList->size();

	for(int i = 0; i < length; i++)
	{
		values += (m_tablesList->at(i)->getValues() + "###\n");
	}

	QFile *file = new QFile(FILE_NAME);
	file->open(QIODevice::WriteOnly);
	file->write(values.toAscii());
	file->close();
}

void MainWindow::sendValues(int armorID, int matherialID)
{
	QString armor;
	QString matherial;

	armor = m_tablesList->at(0)->getColumnValues(armorID);

	if(armorID > 5)
	{
		matherial = m_tablesList->at(4)->getColumnValues(matherialID);
	}
	else if(armorID > 2)
	{
		matherial = m_tablesList->at(2)->getColumnValues(matherialID);
	}
	else
	{
		matherial = m_tablesList->at(3)->getColumnValues(matherialID);
	}

	emit newValues(armor, matherial);
}

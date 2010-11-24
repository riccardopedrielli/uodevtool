#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "Table.h"
#include "ArmorCalc.h"

const QString VERSION = "1.2";
const QString FILE_NAME = "uodt.txt";

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow();

private:
	QList<Table *> *m_tablesList;

private slots:
	void loadData();
	void saveData();
	void sendValues(int armorID, int matherialID);

signals:
	void newValues(QString armor, QString matherial);
};

#endif // MAINWINDOW_H

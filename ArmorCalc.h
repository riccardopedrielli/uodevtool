#ifndef ARMORCALC_H
#define ARMORCALC_H

#include <QWidget>
#include <QComboBox>

#include "Column.h"

class ArmorCalc : public QWidget
{
	Q_OBJECT

public:
	ArmorCalc(QString rowsTitle, QStringList *rows, QStringList *armor, QStringList *ingots, QStringList *leather, QStringList *scales);
	QComboBox *armorType;
	QComboBox *matherialType;

public slots:
	void requestValues(int matherialID);
	void computeArmor(QString armor, QString matherial);

private:
	QStringList *m_ingotsList;
	QStringList *m_leatherList;
	QStringList *m_scalesList;
	Column *m_regularPart;
	Column *m_regularSet;
	Column *m_exceptionalPart;
	Column *m_exceptionalSet;

private slots:
	void updateMatherials(int armorID);

signals:
	void valuesRequired(int armorID, int matherialID);
};

#endif // ARMORCALC_H

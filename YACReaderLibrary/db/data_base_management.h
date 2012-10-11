#ifndef __DATA_BASE_MANAGEMENT_H
#define __DATA_BASE_MANAGEMENT_H

#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>

#include "treemodel.h"

class ComicsInfoExporter : public QThread
{
	Q_OBJECT
public:
	ComicsInfoExporter();
	void exportComicsInfo(QSqlDatabase & source, QSqlDatabase & dest);
private:
	void run();
};

class ComicsInfoImporter : public QThread
{
	Q_OBJECT
public:
	ComicsInfoImporter();
	void importComicsInfo(QSqlDatabase & source, QSqlDatabase & dest);
private:
	void run();

};

class DataBaseManagement : public QObject
{
	Q_OBJECT
private:
	QList<QString> dataBasesList;
	static void bindString(const QString & name, const QSqlRecord & record, QSqlQuery & query);
	static void bindInt(const QString & name, const QSqlRecord & record, QSqlQuery & query);
	static void bindValuesFromRecord(const QSqlRecord & record, QSqlQuery & query);

public:
	DataBaseManagement();
	//TreeModel * newTreeModel(QString path);
	//crea una base de datos y todas sus tablas
	static QSqlDatabase createDatabase(QString name, QString path);
	static QSqlDatabase createDatabase(QString dest);
	//carga una base de datos desde la ruta path
	static QSqlDatabase loadDatabase(QString path);
	static QSqlDatabase loadDatabaseFromFile(QString path);
	static bool createTables(QSqlDatabase & database);

	static void exportComicsInfo(QString source, QString dest);
	static bool importComicsInfo(QString source, QString dest);

	static QString checkValidDB(const QString & fullPath); //retorna "" si la DB es inv�lida � la versi�n si es v�lida.
	static int compareVersions(const QString & v1, const QString v2); //retorna <0 si v1 < v2, 0 si v1 = v2 y >0 si v1 > v2
};

#endif
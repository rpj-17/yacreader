#ifndef __OPTIONS_DIALOG_H
#define __OPTIONS_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QPushButton>
#include <QRadioButton>
#include <QColorDialog>

#include "custom_widgets.h"

class OptionsDialog : public YACReaderOptionsDialog
{
Q_OBJECT
	public:
		OptionsDialog(QWidget * parent = 0);
	private:
		//QLabel * pathLabel;
		QLineEdit * pathEdit;
		QPushButton * pathFindButton;

		QLabel * magGlassSizeLabel;

		QLabel * zoomLevel;

		//QLabel * slideSizeLabel;
		QSlider * slideSize;
		
		//QLabel * fitToWidthRatioLabel;
		QSlider * fitToWidthRatioS;

		QLabel * backgroundColor;
		QPushButton * selectBackgroundColorButton;

		QColorDialog * colorDialog;

	public slots:
		void saveOptions();
		void restoreOptions(QSettings * settings);
		void findFolder();
		void updateColor(const QColor & color);
		void fitToWidthRatio(int value);

signals:
		void changedOptions();
		void fitToWidthRatioChanged(float ratio);

};


#endif
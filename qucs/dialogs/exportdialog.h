/***************************************************************************
                               exportdiagramdialog.h
                              ------------------
    begin                : Thu Nov 28 2013
    copyright            : (C) 2013 by Vadim Kuznetzov
    email                : <ra3xdh@gmail.com>
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QObject>
#include <QtGui>
#include <QDialog>


class ExportDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ExportDialog(int w, int h, int wsel, int hsel, QString filename_, bool nosel_=true, QWidget *parent = 0);
    
private:
    QPushButton* ExportButt;
    QPushButton* CancelButt;
    QPushButton* SaveButt;

    QLabel* lblFilename;
    QLabel* lblResolutionX;
    QLabel* lblResolutionY;
    QLabel* lblRatio;

    QCheckBox* cbResolution;
    QCheckBox* cbRatio;
    QCheckBox* cbSelected;

    QLineEdit* editFilename;
    QLineEdit* editResolutionX;
    QLineEdit* editResolutionY;
    QLineEdit* editScale;

    QHBoxLayout* lower1;
    QHBoxLayout* lower2;
    QHBoxLayout* lower3;
    QVBoxLayout* top;

    int dwidth, dheight;

    int dwidthsel, dheightsel;

    float scale;

    bool svg, noselected;

    QString filename;

public:
    QString FileToSave();
    bool isOriginalSize();
    bool isExportSelected();
    int Xpixels();
    int Ypixels();
    bool isSvg();
    bool isValidFilename();
    void setDiagram();
    float getScale();

signals:
    
private slots:
    void setFileName();
    void calcWidth();
    void calcHeight();
    void recalcRatio();
    void restoreOriginalWtoH();
    void setSvg(QString filename);
    void setSelectedWH();
    void recalcScale();

public slots:
    
};

#endif // EXPORTDIALOG_H

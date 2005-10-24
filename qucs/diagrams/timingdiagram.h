/***************************************************************************
                              timingdiagram.h
                             -----------------
    begin                : Sat Oct 22 2005
    copyright            : (C) 2004 by Michael Margraf
    email                : michael.margraf@alumni.tu-berlin.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef TIMINGDIAGRAM_H
#define TIMINGDIAGRAM_H

#include "diagram.h"


class TimingDiagram : public Diagram  {
public: 
  TimingDiagram(int _cx=0, int _cy=0);
 ~TimingDiagram();

  Diagram* newOne();
  static Element* info(QString&, char* &, bool getNewOne=false);
  void paint(ViewPainter*);
  int  calcDiagram();
  bool scroll(int);

  void createAxisLabels() {};   // no labels in this diagram

private:
  int  checkColumnWidth(const QString&, const QFontMetrics&, int, int, int);
};

#endif
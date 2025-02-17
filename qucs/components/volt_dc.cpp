/***************************************************************************
                               volt_dc.cpp
                              -------------
    begin                : Sat Aug 23 2003
    copyright            : (C) 2003 by Michael Margraf
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

#include "volt_dc.h"


Volt_dc::Volt_dc()
{
  Description = QObject::tr("ideal dc voltage source");

  Lines.push_back(qucs::Line(  4,-13,  4, 13,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( -4, -6, -4,  6,QPen(Qt::darkBlue,4)));
  Lines.push_back(qucs::Line( 30,  0,  4,  0,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( -4,  0,-30,  0,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 11,  5, 11, 11,QPen(Qt::red,1)));
  Lines.push_back(qucs::Line( 14,  8,  8,  8,QPen(Qt::red,1)));
  Lines.push_back(qucs::Line(-11,  5,-11, 11,QPen(Qt::black,1)));

  Ports.push_back(qucs::Port( 30,  0));
  Ports.push_back(qucs::Port(-30,  0));

  x1 = -30; y1 = -14;
  x2 =  30; y2 =  14;

  tx = x1+4;
  ty = y2+4;
  Model = "Vdc";
  Name  = "V";

  Props.push_back(qucs::Property("U", "1 V", true,
		QObject::tr("voltage in Volts")));

  rotate();  // fix historical flaw
}

Volt_dc::~Volt_dc()
{
}

Component* Volt_dc::newOne()
{
  return new Volt_dc();
}

Element* Volt_dc::info(QString& Name, char* &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("dc Voltage Source");
  BitmapFile = (char *) "dc_voltage";

  if(getNewOne)  return new Volt_dc();
  return 0;
}

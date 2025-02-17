/***************************************************************************
                             hpribin4bit
                            -------------
    begin                : January 2009
    copyright            : (C) 2008 by Mike Brinson
    email                : mbrin72043@yahoo.co.uk
 ***************************************************************************/

/*
 * hpribin4bit.cpp - device implementations for hpribin4bit module
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 */
#include "hpribin4bit.h"
#include "node.h"
#include "misc.h"

hpribin4bit::hpribin4bit()
{
  Type = isComponent; // Analogue and digital component.
  Description = QObject::tr ("4bit highest priority encoder (binary form) verilog device");

  Props.push_back(qucs::Property("TR", "6", false,
    QObject::tr ("transfer function scaling factor")));
  Props.push_back(qucs::Property("Delay", "1 ns", false,
    QObject::tr ("output delay")
    +" ("+QObject::tr ("s")+")"));

  createSymbol ();
  tx = x1 + 19;
  ty = y2 + 4;
  Model = "hpribin4bit";
  Name  = "Y";
}

Component * hpribin4bit::newOne()
{
  hpribin4bit * p = new hpribin4bit();
  p->Props.front().Value = Props.front().Value; 
  p->recreate(0); 
  return p;
}

Element * hpribin4bit::info(QString& Name, char * &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("4Bit HPRI-Bin");
  BitmapFile = (char *) "hpribin4bit";

  if(getNewOne) return new hpribin4bit();
  return 0;
}

void hpribin4bit::createSymbol()
{
  Lines.push_back(qucs::Line(-40, -50, 40,-50,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 40, -50, 40, 60,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 40,  60,-40, 60,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line(-40,  60,-40, -50,QPen(Qt::darkBlue,2)));

  Lines.push_back(qucs::Line(-60,-10,-40,-10,QPen(Qt::darkBlue,2)));  // A
  Lines.push_back(qucs::Line(-60, 10,-40, 10,QPen(Qt::darkBlue,2)));  // B
  Lines.push_back(qucs::Line(-60, 30,-40, 30,QPen(Qt::darkBlue,2)));  // C
  Lines.push_back(qucs::Line(-60, 50,-40, 50,QPen(Qt::darkBlue,2)));  // D
  Lines.push_back(qucs::Line( 40, 30, 60, 30,QPen(Qt::darkBlue,2)));  // V
  Lines.push_back(qucs::Line( 40, 10, 60, 10,QPen(Qt::darkBlue,2)));  // Y
  Lines.push_back(qucs::Line( 40,-10, 60,-10,QPen(Qt::darkBlue,2)));  // X

  Texts.push_back(qucs::Text(-35,-45, "HPRI/BIN", Qt::darkBlue, 12.0));

  Texts.push_back(qucs::Text(-35,-23,  "0",  Qt::darkBlue, 12.0));
  Texts.push_back(qucs::Text(-35, -3,  "1",  Qt::darkBlue, 12.0)); 
  Texts.push_back(qucs::Text(-35, 17,  "2",  Qt::darkBlue, 12.0));
  Texts.push_back(qucs::Text(-35, 37,  "3",  Qt::darkBlue, 12.0));

  Texts.push_back(qucs::Text( 25, 17,  "V",  Qt::darkBlue, 12.0)); 
  Texts.push_back(qucs::Text( 25, -3,  "Y",  Qt::darkBlue, 12.0));
  Texts.push_back(qucs::Text( 25,-23,  "X",  Qt::darkBlue, 12.0));

  Ports.push_back(qucs::Port(-60,-10));  // A
  Ports.push_back(qucs::Port(-60, 10));  // B
  Ports.push_back(qucs::Port(-60, 30));  // C
  Ports.push_back(qucs::Port(-60, 50));  // D
  Ports.push_back(qucs::Port( 60, 30));  // V
  Ports.push_back(qucs::Port( 60, 10));  // Y
  Ports.push_back(qucs::Port( 60,-10));  // X

  x1 = -60; y1 = -54;
  x2 =  60; y2 =  64;
}

QString hpribin4bit::vhdlCode( int )
{
  QString s;

  QString td = prop(1).Value;     // delay time
  if(!misc::VHDL_Delay(td, Name)) return td; // time has not VHDL format
  td += ";\n";

  QString A    = port(0).getConnection()->Name;
  QString B    = port(1).getConnection()->Name;
  QString C    = port(2).getConnection()->Name;
  QString D    = port(3).getConnection()->Name;
  QString V    = port(4).getConnection()->Name;
  QString Y    = port(5).getConnection()->Name;
  QString X    = port(6).getConnection()->Name;

  s = "\n  "+Name+":process ("+A+", "+B+", "+C+", "+D+")\n"+
      "  begin\n" +
      "    "+X+" <= "+D+" or "+C+td+ 
      "    "+Y+" <= "+D+" or ((not "+C+") and "+B+")"+td+
      "    "+V+" <= "+D+" or "+C+" or "+B+" or "+A+td+ 
      "  end process;\n";
  return s;
}

QString hpribin4bit::verilogCode( int )
{
  QString td = prop(1).Value;        // delay time
  if(!misc::Verilog_Delay(td, Name)) return td; // time does not have VHDL format
  
  QString l = "";

  QString A    = port(0).getConnection()->Name;
  QString B    = port(1).getConnection()->Name;
  QString C    = port(2).getConnection()->Name;
  QString D    = port(3).getConnection()->Name;
  QString V    = port(4).getConnection()->Name;
  QString Y    = port(5).getConnection()->Name;
  QString X    = port(6).getConnection()->Name;

  QString VR  = "V_reg"  + Name + V;
  QString YR  = "Y_reg"  + Name + Y;
  QString XR  = "X_reg"  + Name + X;

  l = "\n  // "+Name+" 4bit hpribin\n"+
      "  assign  "+V+" = "+VR+";\n"+
      "  reg     "+VR+" = 0;\n"+
      "  assign  "+Y+" = "+YR+";\n"+
      "  reg     "+YR+" = 0;\n"+
      "  assign  "+X+" = "+XR+";\n"+
      "  reg     "+XR+" = 0;\n"+
      "  always @ ("+A+" or "+B+" or "+C+" or "+D+")\n"+
      "  begin\n" +
      "    " +XR+" <="+td+" "+D+" || "+C+";\n"+
      "    " +YR+" <="+td+" "+D+" || ((~"+C+") && "+B+");\n" +
      "    " +VR+" <="+td+" "+D+" || "+C+" || "+B+" || "+A+";\n"+     
      "  end\n";

  return l;
}

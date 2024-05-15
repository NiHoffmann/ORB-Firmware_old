//*******************************************************************
/*!
\file   UserInterface.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "UserInterface.h"

//*******************************************************************
extern DigitalIndicator      indUsr1;
extern DigitalIndicator      indUsr2;
//extern Digital      btnUsr1;
//extern Digital      btnUsr2;
extern DigitalButton btn;
extern DigitalButton btnAlt;

extern DigitalIndicator pwrIndicator;

//*******************************************************************
//
// UserInterface
//
//*******************************************************************
//-------------------------------------------------------------------
UserInterface::UserInterface( AppTask      &app,
                              Settings     &settings )

 : settings(settings)
 , app     ( app )

{
}

//-------------------------------------------------------------------
void UserInterface::update()
{
  DigitalButton::Action action1 = btn   .getAction();
  DigitalButton::Action action2 = btnAlt.getAction();

  switch( action1 == DigitalButton::NONE ? action2 : action1 )
  {
    case DigitalButton::SHORT:
      if( app.isRunning() )  stopApp();
      else                   startApp(0);
      break;

    case DigitalButton::LONG:
      if( app.isRunning() )  stopApp();
      else                   startApp(1);
      break;
  }

  if( !app.isRunning() )
  {
     indUsr1.clr();
     indUsr2.clr();
  }
}

//-------------------------------------------------------------------
void UserInterface::startApp( BYTE param )
{
  if( !app.isRunning())
  {
    if( param )
      indUsr2.set();
    else
      indUsr1.set();
    app.Start(param);
  }
}

//-------------------------------------------------------------------
void UserInterface::stopApp()
{
  if( app.isRunning())
    app.stop();
}

//-------------------------------------------------------------------
bool UserInterface::isAppActive()
{
  return( app.isRunning() );
}

//-------------------------------------------------------------------
void UserInterface::setMonitorEvent( BYTE event )
{
  app.MonitorEvent = event;
}

//-------------------------------------------------------------------
void UserInterface::setVcc( BYTE Vcc )
{
    /*
  if     ( Vcc > settings.getVccLevelOK()  )  { pwrIndicator.setBrightness( 20); pwrIndicator.blink(1000, 90); }
  else if( Vcc > settings.getVccLevelLow() )  { pwrIndicator.setBrightness( 50); pwrIndicator.blink(1000, 50); }
  else                                        { pwrIndicator.setBrightness(100); pwrIndicator.blink( 200, 50); }
    */
}
//EOF

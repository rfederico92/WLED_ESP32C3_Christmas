#pragma once

#include "wled.h"

class OledDisplayUserMod : public Usermod
{

private:
public:
  // gets called once at boot. Do all initialization that doesn't depend on
  // network here
  void setup()
  {
  }

  // gets called every time WiFi is (re-)connected. Initialize own network
  // interfaces here
  void connected()
  {
  }

  /*
   * Da loop.
   */
  void loop()
  {
  }
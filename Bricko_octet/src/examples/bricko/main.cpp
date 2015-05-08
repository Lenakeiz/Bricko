////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
// Text overlay
//

//Define if BRICKO physics must be used or not
#define BRICKO 1

//if this is defined does not count the value...
#define OCTET_BULET 0

#include "../../octet.h"

#include "bricko_example.h"

/// Create a box with octet
int main(int argc, char **argv) {
  // set up the platform.
  octet::app::init_all(argc, argv);

  // our application.
  octet::bricko_example app(argc, argv);
  app.init();

  // open windows
  octet::app::run_all_apps();
}



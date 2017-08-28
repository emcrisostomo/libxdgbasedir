#include "library.h"

#include <iostream>
#include "gettext_defs.h"

void hello()
{
  std::cout << _("Hello, World!") << std::endl;
}
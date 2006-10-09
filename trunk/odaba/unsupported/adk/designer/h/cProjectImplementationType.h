#ifndef   ProjectImplementationType_HPP
#define   ProjectImplementationType_HPP

enum ProjectImplementationType
{
  PIT_ClassLibrary                = 1,
  PIT_ConsoleApplications         = 2,
  PIT_DBContextInterfaceDLL       = 4,
  PIT_GUIApplications             = 3,
  PIT_GUIContextInterfaceDLL      = 5,
  PIT_undefined                   = 0,
};

#endif

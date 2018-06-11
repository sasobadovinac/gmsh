// Gmsh - Copyright (C) 1997-2018 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@onelab.info>.

#ifndef _FUNCTION_MANAGER_H_
#define _FUNCTION_MANAGER_H_

#include <cstdio>
#include <string>

// Singleton, one function manager for all parsers.

class FunctionManagerStack;
class FunctionManagerMap;

class FunctionManager
{
  FunctionManagerMap *functions;
  FunctionManagerStack *calls;
  FunctionManager ();
  static FunctionManager *instance;
 public :
  static FunctionManager* Instance();
  int createFunction(const std::string &name, FILE *f,
                     const std::string &filename, int lineno);
  int enterFunction(const std::string &name, FILE **f,
                    std::string &filename, int &lineno) const;
  int leaveFunction(FILE **f, std::string &filename, int &lineno);
  void clear();
};

#endif

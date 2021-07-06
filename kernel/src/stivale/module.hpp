//
// Created by Martin on 06.07.2021.
//

#ifndef MATESOS2_MODULE_HPP
#define MATESOS2_MODULE_HPP

#include "stddef.h"

struct Module {
  void*	header;
  void*	body;
  size_t size;
};

#endif //MATESOS2_MODULE_HPP

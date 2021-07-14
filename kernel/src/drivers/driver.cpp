#include "stddef.h"
#include "driver.hpp"
#include "../logging.hpp"
#include "../lib/ststr.hpp"

namespace driver
{
  DriverManager g_DriverManager = DriverManager();

  Driver::Driver() {}

  Driver::~Driver(){}

  const char *Driver::getName()
  {
    return "Not defined";
  }

  bool Driver::activate()
  {
    return false;
  }

  bool Driver::deactivate()
  {
    return false;
  }

  DriverManager::DriverManager()
  {
    num_of_drivers = 0;
  }

  void DriverManager::activate_all()
  {
    bool failed = false;

    logging::log(logging::INFO, "Loading %d drivers", num_of_drivers);

    for (uint64_t i = 0; i < num_of_drivers; i++)
    {
      if (drivers[i] != NULL)
      {
        if (!drivers[i]->activate())
        {
          failed = true;
          logging::log(logging::WARNING, "Driver <%s> failed to load", drivers[i]->getName());
        }
      }
    }

    if (failed) logging::log(logging::WARNING, "Drivers load failed");
    else logging::log(logging::SUCCESS, "Drivers loaded");
  }

  void DriverManager::add_driver(Driver *driver)
  {
    if (num_of_drivers == DRIVER_NUM)
    {
      logging::log(logging::WARNING, "Unable to add %s driver to list of drivers, limit of %d drivers reached!", driver->getName(), DRIVER_NUM);
      return;
    }

    drivers[num_of_drivers] = driver;
    num_of_drivers++;
  }

  Driver *DriverManager::get_by_index(uint64_t index)
  {
    if (index > (num_of_drivers - 1)) return NULL;
    return drivers[index];
  }

  Driver *DriverManager::get_by_name(const char *name)
  {
    if (num_of_drivers == 0) return NULL;
    for (uint64_t i = 0; i < num_of_drivers; i++)
    {
      if (strcmp(name, drivers[i]->getName()) == 0) return drivers[i];
    }

    return NULL;
  }

  uint64_t DriverManager::get_num_of_drivers()
  {
    return num_of_drivers;
  }
}

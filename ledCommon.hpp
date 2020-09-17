#pragma once

#include "group.hpp"
#include "manager.hpp"
#include "serialize.hpp"

#include <sdbusplus/server.hpp>
#include <sdeventplus/event.hpp>

#include <map>

namespace phosphor
{
namespace led
{

/**
 * @brief The interfaces class for Test
 */
class TestInterfaces
{
  public:
    explicit TestInterfaces(sdbusplus::bus::bus& bus,
                            const sdeventplus::Event& event, Manager& manager) :
        bus(bus),
        event(event), manager(manager)
    {}

    virtual ~TestInterfaces() = default;

    virtual void testHandler() = 0;

  public:
    /** @brief sdbusplus handler */
    sdbusplus::bus::bus& bus;

    /** @brief sdbusplus event */
    const sdeventplus::Event& event;

    /** @brief Reference to Manager object */
    Manager& manager;
};

} // namespace led
} // namespace phosphor

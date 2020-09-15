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
    explicit TestInterfaces(
        sdbusplus::bus::bus& bus, const sdeventplus::Event& event,
        Manager& manager, Serialize& serialize,
        std::map<std::string, std::unique_ptr<phosphor::led::Group>> groups) :
        bus(bus),
        event(event), manager(manager), serialize(serialize),
        groups(std::move(groups))
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

    /** @brief The serialize class for storing and restoring groups of LEDs */
    Serialize& serialize;

    /** @brief map of led groups */
    std::map<std::string, std::unique_ptr<phosphor::led::Group>> groups;
};

} // namespace led
} // namespace phosphor

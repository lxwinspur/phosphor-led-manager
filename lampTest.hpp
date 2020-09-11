#pragma once

#include "manager.hpp"
#include "serialize.hpp"

#include <sdeventplus/event.hpp>
#include <sdeventplus/utility/timer.hpp>

#include <vector>

namespace phosphor
{
namespace led
{

using ObjectPaths = std::vector<std::string>;

/** @class LampTest
 *  @brief Initiate a Lamp Test request
 */
class LampTest
{
  public:
    LampTest() = delete;
    ~LampTest() = default;
    LampTest(const LampTest&) = delete;
    LampTest& operator=(const LampTest&) = delete;
    LampTest(LampTest&&) = default;
    LampTest& operator=(LampTest&&) = default;

    /** @brief Constructs LED LampTest
     *
     * @param[in] bus     - Handle to system dbus
     * @param[in] manager - Reference to Manager
     * @param[in] serialize - Serialize object fot lamp test
     */
    LampTest(sdbusplus::bus::bus& bus, Manager& manager, Serialize& serialize) :
        bus(bus), event(sdeventplus::Event::get_default()), manager(manager),
        serialize(serialize),
        timer(event, std::bind(&LampTest::lampTestTimeout, this))
    {
        lampTestInitiated();
    }

  private:
    /** @brief sdbusplus handler */
    sdbusplus::bus::bus& bus;

    /** @brief sdbusplus event */
    const sdeventplus::Event& event;

    /** @brief Reference to Manager object */
    Manager& manager;

    /** @brief The serialize class for storing and restoring groups of LEDs */
    Serialize& serialize;

    /** @brief Timer used for host transition with seconds */
    sdeventplus::utility::Timer<sdeventplus::ClockId::RealTime> timer;

    /** @brief  Call back the restore function when timeout. */
    void lampTestTimeout();

    /** @brief The handler method of lamp test */
    void lampTestHandler(sdbusplus::message::message& msg);

    /** @brief Subscribe Lamp test initiated signal */
    void lampTestInitiated();

    /** @brief Set all the physical action to On for lamp test */
    void updatePhysicalAction();

    /** @brief Get all the LED physical paths */
    ObjectPaths getLedPhysicalPahts();

    /** @brief Get all the LED group paths */
    ObjectPaths getLedGroupPahts();

    /** @brief Get Asserted property from group path
     *
     *  @param[in] path   - dbus path of group
     *  @param[in] status - true(default) or false
     */
    void setAssertedStatus(const std::string& path, bool status = true);
};

} // namespace led
} // namespace phosphor

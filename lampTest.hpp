#pragma once

#include "group.hpp"
#include "ledCommon.hpp"
#include "manager.hpp"

#include <sdbusplus/server.hpp>
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
class LampTest : public TestInterfaces
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
     * @param[in] serialize - Serialize object for lamp test
     * @param[in] groups - map of led groups
     */
    LampTest(sdbusplus::bus::bus& bus, const sdeventplus::Event& event,
             Manager& manager) :
        TestInterfaces(bus, event, manager),
        timer(event, std::bind(&LampTest::lampTestTimeout, this))
    {
        testHandler();
    }

    /** @brief The handler method of lamp test */
    void testHandler() override;

  private:
    /** @brief Timer used for host transition with seconds */
    sdeventplus::utility::Timer<sdeventplus::ClockId::RealTime> timer;

    /** @brief  Call back the restore function when timeout. */
    void lampTestTimeout();

    /** @brief Set all the physical action to On for lamp test */
    void updatePhysicalAction();
};

} // namespace led
} // namespace phosphor

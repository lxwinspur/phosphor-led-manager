#pragma once

#include "group.hpp"
#ifdef USE_LAMP_TEST
#include "lampTest.hpp"
#endif
#include "ledCommon.hpp"
#include "manager.hpp"

#include <sdeventplus/event.hpp>

#include <vector>

namespace phosphor
{
namespace led
{
namespace sdbusRule = sdbusplus::bus::match::rules;

/** @class LedEvents
 *  @brief Initiate a Led event class
 */
class LedEvents
{
  public:
    LedEvents() = delete;
    ~LedEvents() = default;
    LedEvents(const LedEvents&) = delete;
    LedEvents& operator=(const LedEvents&) = delete;
    LedEvents(LedEvents&&) = default;
    LedEvents& operator=(LedEvents&&) = default;

    /** @brief Constructs LED LedEvents
     *
     * @param[in] bus     - Handle to system dbus
     * @param[in] manager - Reference to Manager
     */
    LedEvents(sdbusplus::bus::bus& bus, const sdeventplus::Event& event,
              Manager& manager) :
        bus(bus),
        event(event), manager(manager)
    {
        initSignals();
    }

  private:
    /** @brief sdbusplus handler */
    sdbusplus::bus::bus& bus;

    /** @brief sdbusplus event */
    const sdeventplus::Event& event;

    /** @brief Reference to Manager object */
    Manager& manager;

    /** @brief Used to subscribe to dbus systemd signals */
    std::vector<sdbusplus::bus::match_t> systemdSignals;

    std::vector<std::unique_ptr<phosphor::led::TestInterfaces>> testInterfaces;

    void initSignals();

    void addLampTestSignals();

    /** @brief The handler method of lamp test
     *
     *  @param[in] msg - bus message
     */
    void lampTestHandler(sdbusplus::message::message& msg);
};

} // namespace led
} // namespace phosphor

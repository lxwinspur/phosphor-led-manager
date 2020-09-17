#include "config.h"

#include "ledEvents.hpp"

namespace phosphor
{
namespace led
{

void LedEvents::initSignals()
{
    addLampTestSignals();
}

void LedEvents::addLampTestSignals()
{
    systemdSignals.emplace_back(
        bus,
        sdbusRule::type::signal() + sdbusRule::member("LampTestInitiated") +
            sdbusRule::path("/xyz/openbmc_project/led/groups/bmc_booted") +
            sdbusRule::interface("xyz.openbmc_project.Led.Group"),
        std::bind(&LedEvents::lampTestHandler, this, std::placeholders::_1));
}

void LedEvents::lampTestHandler(sdbusplus::message::message& /*msg*/)
{
#ifdef USE_LAMP_TEST
    testInterfaces.push_back(std::make_unique<LampTest>(bus, event, manager));
#endif
}

} // namespace led
} // namespace phosphor

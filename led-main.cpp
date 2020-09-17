#include "config.h"

#include "group.hpp"
#ifdef LED_USE_JSON
#include "json-config.hpp"
#else
#include "led-gen.hpp"
#endif
#include "ledEvents.hpp"
#include "ledlayout.hpp"
#include "manager.hpp"
#include "serialize.hpp"

#include <sdbusplus/server.hpp>
#include <sdeventplus/event.hpp>

int main(void)
{
    // Get a default event loop
    auto event = sdeventplus::Event::get_default();

    /** @brief Dbus constructs used by LED Group manager */
    sdbusplus::bus::bus bus = sdbusplus::bus::new_default();

#ifdef LED_USE_JSON
    auto systemLedMap = loadJsonConfig(LED_JSON_FILE);
#endif

    /** @brief store and re-store Group */
    phosphor::led::Serialize serialize(SAVED_GROUPS_FILE);

    /** @brief Group manager object */
    phosphor::led::Manager manager(bus, systemLedMap, serialize);

    /** @brief sd_bus object manager */
    sdbusplus::server::manager::manager objManager(bus, OBJPATH);

    /** @brief vector of led groups */
    std::vector<std::unique_ptr<phosphor::led::Group>> groups;

    /** Now create so many dbus objects as there are groups */
    for (auto& grp : systemLedMap)
    {
        groups.emplace_back(std::make_unique<phosphor::led::Group>(
            bus, grp.first, manager, serialize));
    }

    phosphor::led::LedEvents ledEvents(bus, event, manager);

    /** @brief Claim the bus */
    bus.request_name(BUSNAME);

    // Attach the bus to sd_event to service user requests
    bus.attach_event(event.get(), SD_EVENT_PRIORITY_NORMAL);
    event.loop();

    return 0;
}

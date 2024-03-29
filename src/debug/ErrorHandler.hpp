#pragma once

#include <string>

#include <pico/stdlib.h>

#include <display/Display.hpp>
#include <config/Constants.hpp>

#include "ErrorMessages.hpp"
#include "DebugMessage.hpp"

const inline uint32_t irqs_to_mask = TIMER_IRQ_0 | TIMER_IRQ_1 | TIMER_IRQ_2 | TIMER_IRQ_3;
const inline uint32_t all_irq_levels = GPIO_IRQ_LEVEL_LOW | GPIO_IRQ_LEVEL_HIGH | GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE;
const inline uint32_t all_gpios = ~(~0u << 30); // Pico has 29 GPIOs

static void fatal_error(ErrorMessage message)
{
    irq_set_mask_enabled(irqs_to_mask, false);
    gpio_set_irq_enabled(StaticConstants::BUTTON_DOWN_GPIO, all_irq_levels, false);
    gpio_set_irq_enabled(StaticConstants::BUTTON_OK_GPIO, all_irq_levels, false);
    gpio_set_irq_enabled(StaticConstants::BUTTON_UP_GPIO, all_irq_levels, false);

    const auto &error_msg = error_messages_map.at(message);
    print(MessageType::ERR, error_msg);
    
    auto display_instance = Display::get_instance();
    display_instance->clear();
    display_instance->print_line("System panic! " + std::to_string(int(message)));
    display_instance->print_line(error_msg);

    gpio_put_masked(all_gpios, 0);

    panic("");
}
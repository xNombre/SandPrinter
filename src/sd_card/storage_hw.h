#pragma once

#include "hw_config.h"
#include "ff.h"
#include "diskio.h"

#include <config/Constants.hpp>

void spi0_dma_isr();

static spi_t spis[] = {
    {
        .hw_inst = StaticConstants::CARD_READER_SPI_PORT,
        .miso_gpio = StaticConstants::CARD_READER_MISO_GPIO,
        .mosi_gpio = StaticConstants::CARD_READER_MOSI_GPIO,
        .sck_gpio = StaticConstants::CARD_READER_SCLK_GPIO,

        .baud_rate = 12500 * 1000,
        .dma_isr = spi0_dma_isr
    }
};

static sd_card_t sd_cards[] = {
    {
        .pcName = "0:",
        .spi = &spis[0],
        .ss_gpio = StaticConstants::CARD_READER_CS_GPIO,
        .use_card_detect = false,
        .m_Status = STA_NOINIT
    }
};

void spi0_dma_isr()
{
    spi_irq_handler(&spis[0]);
}

size_t sd_get_num()
{
    return count_of(sd_cards);
}

size_t spi_get_num()
{
    return count_of(spis);
}

sd_card_t *sd_get_by_num(size_t num)
{
    if (num <= sd_get_num()) {
        return &sd_cards[num];
    } else {
        return NULL;
    }
}

spi_t *spi_get_by_num(size_t num)
{
    if (num <= sd_get_num()) {
        return &spis[num];
    } else {
        return NULL;
    }
}
#pragma once
#include <stdint.h>
#include <stdbool.h>

static volatile uint32_t * const DMA_SRC_ADDR  = (uint32_t * const)0x70000000;
static volatile uint32_t * const DMA_DST_ADDR  = (uint32_t * const)0x70000004;
static volatile uint32_t * const DMA_LEN_ADDR  = (uint32_t * const)0x70000008;
static volatile uint32_t * const DMA_OP_ADDR   = (uint32_t * const)0x7000000C;
static volatile uint32_t * const DMA_STAT_ADDR = (uint32_t * const)0x70000010;

static const uint32_t DMA_OP_NOP = 0;
static const uint32_t DMA_OP_MEMCPY = 1;

volatile _Bool dma_completed = 0;

void dma_irq_handler();

/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Vijai Kumar K <vijai@behindbytes.com>
 *
 */

#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/serial/fdt_serial.h>
#include <sbi_utils/serial/mindgrove-uart.h>

#define MINDGROVE_UART_BASE   0x00011300UL 
#define SECURE_IOT_UART_FREQ  100000000 
#define SECURE_IOT_UART_BAUD  1250000

static int serial_mindgrove_init(const void *fdt, int nodeoff,
			      const struct fdt_match *match)
{
	int rc;
	struct platform_uart_data uart = { 
		.addr = MINDGROVE_UART_BASE,
		.freq = SECURE_IOT_UART_FREQ,
		.baud = SECURE_IOT_UART_BAUD
	 };

	rc = fdt_parse_mindgrove_uart_node(fdt, nodeoff, &uart);
	if (rc)
		return rc;

	return mindgrove_uart_init(uart.addr, uart.freq, uart.baud);
}

static const struct fdt_match serial_mindgrove_match[] = {
	{ .compatible = "mindgrove,uart0" },
	{ },
};

const struct fdt_driver fdt_serial_mindgrove = {
	.match_table = serial_mindgrove_match,
	.init = serial_mindgrove_init
};

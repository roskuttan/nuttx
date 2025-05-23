/****************************************************************************
 * arch/arm64/include/goldfish/chip.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM64_INCLUDE_GOLDFISH_CHIP_H
#define __ARCH_ARM64_INCLUDE_GOLDFISH_CHIP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Number of bytes in x kibibytes/mebibytes/gibibytes */

#define KB(x)           ((x) << 10)
#define MB(x)           (KB(x) << 10)
#define GB(x)           (MB(UINT64_C(x)) << 10)

#if defined(CONFIG_ARCH_CHIP_GOLDFISH)

/* Addresses and sizes of goldfish (external/qemu/hw/arm/virt.c).
 *
 * 0x00000000 ~ 0x08000000 (128MB):
 *         Space for a flash device so we can run bootrom code
 *         such as UEFI.
 * 0x08000000 ~ 0x10000000 (128MB..256MB):
 *         Used for miscellaneous device I/O (GIC, UART, RTC,
 *         GPIO, MMIO, FB, AUDIO, PIPE etc)
 * 0x10000000 ~ 0x40000000 (256MB..1GB):
 *         Reserved for possible future PCI support
 * 0x40000000 ~ 0x48000000 (1GB up):
 *         RAM, 128MB, The RAM can be config up to 255GB, but
 *         it's useless for NuttX
 */

#if CONFIG_ARM64_GIC_VERSION == 2
#define CONFIG_GICD_BASE          0x8000000
#define CONFIG_GICR_BASE          0x8010000
#elif CONFIG_ARM64_GIC_VERSION == 3 || CONFIG_ARM64_GIC_VERSION == 4
#define CONFIG_GICD_BASE          0x8000000
#define CONFIG_GICR_BASE          0x80a0000
#define CONFIG_GICR_OFFSET        0x20000
#else
#error CONFIG_ARM64_GIC_VERSION should be 2, 3 or 4
#endif /* CONFIG_ARM64_GIC_VERSION */

#define CONFIG_FLASH_BASEADDR     0x7000000
#define CONFIG_FLASH_SIZE         MB(128)

#define CONFIG_DEVICEIO_BASEADDR  0x08000000
#define CONFIG_DEVICEIO_SIZE      MB(512)

#define CONFIG_RAM_ADDR           0x40000000
#define CONFIG_RAM_SIZE           MB(128)

#define CONFIG_LOAD_BASE          0x40280000

#define MPID_TO_CLUSTER_ID(mpid)  ((mpid) & ~0xff)

#endif

/****************************************************************************
 * Assembly Macros
 ****************************************************************************/

#ifdef __ASSEMBLY__

.macro  get_cpu_id xreg0
  mrs    \xreg0, mpidr_el1
  ubfx   \xreg0, \xreg0, #0, #8
.endm

#endif /* __ASSEMBLY__ */

#endif /* __ARCH_ARM64_INCLUDE_GOLDFISH_CHIP_H */

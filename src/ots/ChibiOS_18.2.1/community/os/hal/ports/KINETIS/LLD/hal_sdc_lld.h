/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio
              Copyright (C) 2017 Wim Lewis

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    hal_sdc_lld.h
 * @brief   PLATFORM SDC subsystem low level driver header.
 *
 * @addtogroup SDC
 * @{
 */

#ifndef HAL_SDC_LLD_H
#define HAL_SDC_LLD_H

#if (HAL_USE_SDC == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

#define SDHC_XFERTYP_CMDTYP_NORMAL	SDHC_XFERTYP_CMDTYP(0)
#define SDHC_XFERTYP_CMDTYP_SUSPEND	SDHC_XFERTYP_CMDTYP(1)
#define SDHC_XFERTYP_CMDTYP_RESUME	SDHC_XFERTYP_CMDTYP(2)
#define SDHC_XFERTYP_CMDTYP_ABORT	SDHC_XFERTYP_CMDTYP(3)

#define SDHC_XFERTYP_RSPTYP_NONE	SDHC_XFERTYP_RSPTYP(0)  /* no response */
#define SDHC_XFERTYP_RSPTYP_136		SDHC_XFERTYP_RSPTYP(1)	/* 136-bit response */
#define SDHC_XFERTYP_RSPTYP_48		SDHC_XFERTYP_RSPTYP(2)	/* 48-bit response */
#define SDHC_XFERTYP_RSPTYP_48b		SDHC_XFERTYP_RSPTYP(3)	/* 48-bit plus busy */

#define SDHC_PROCTL_DTW_1BIT            SDHC_PROCTL_DTW(0)
#define SDHC_PROCTL_DTW_4BIT            SDHC_PROCTL_DTW(1)
#define SDHC_PROCTL_DTW_8BIT            SDHC_PROCTL_DTW(2)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    PLATFORM configuration options
 * @{
 */
/**
 * @brief   SDC1 driver enable switch.
 * @details If set to @p TRUE the support for SDC1 is included.
 * @note    The default is @p TRUE if HAL_USE_SDC is set.
 */
#if !defined(PLATFORM_SDC_USE_SDC1) || defined(__DOXYGEN__)
#define PLATFORM_SDC_USE_SDC1                  TRUE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of card flags.
 */
typedef uint32_t sdcmode_t;

/**
 * @brief   SDC Driver condition flags type.
 */
typedef uint32_t sdcflags_t;

/**
 * @brief   Type of a structure representing an SDC driver.
 */
typedef struct SDCDriver SDCDriver;

/**
 * @brief   Driver configuration structure.
 * @note    It could be empty on some architectures.
 */
typedef struct {
  /**
   * @brief   Working area for memory consuming operations.
   * @note    It is mandatory for detecting MMC cards bigger than 2GB else it
   *          can be @p NULL.
   * @note    Memory pointed by this buffer is only used by @p sdcConnect(),
   *          afterward it can be reused for other purposes.
   */
  uint8_t       *scratchpad;
  /**
   * @brief   Bus width.
   */
  sdcbusmode_t  bus_width;
  /* End of the mandatory fields.*/
} SDCConfig;

/**
 * @brief   @p SDCDriver specific methods.
 */
#define _sdc_driver_methods                                                 \
  _mmcsd_block_device_methods

/**
 * @extends MMCSDBlockDeviceVMT
 *
 * @brief   @p SDCDriver virtual methods table.
 */
struct SDCDriverVMT {
  _sdc_driver_methods
};

/**
 * @brief   Structure representing an SDC driver.
 */
struct SDCDriver {
  /**
   * @brief Virtual Methods Table.
   */
  const struct SDCDriverVMT *vmt;
  _mmcsd_block_device_data
  /**
   * @brief Current configuration data.
   */
  const SDCConfig           *config;
  /**
   * @brief Various flags regarding the mounted card.
   */
  sdcmode_t                 cardmode;
  /**
   * @brief Errors flags.
   */
  sdcflags_t                errors;
  /**
   * @brief Card RCA.
   */
  uint32_t                  rca;
  /* End of the mandatory fields.*/

  /* Platform specific fields */
  thread_reference_t        thread;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if (PLATFORM_SDC_USE_SDC1 == TRUE) && !defined(__DOXYGEN__)
extern SDCDriver SDCD1;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void sdc_lld_init(void);
  void sdc_lld_start(SDCDriver *sdcp);
  void sdc_lld_stop(SDCDriver *sdcp);
  void sdc_lld_start_clk(SDCDriver *sdcp);
  void sdc_lld_set_data_clk(SDCDriver *sdcp, sdcbusclk_t clk);
  void sdc_lld_stop_clk(SDCDriver *sdcp);
  void sdc_lld_set_bus_mode(SDCDriver *sdcp, sdcbusmode_t mode);
  void sdc_lld_send_cmd_none(SDCDriver *sdcp, uint8_t cmd, uint32_t arg);
  bool sdc_lld_send_cmd_short(SDCDriver *sdcp, uint8_t cmd, uint32_t arg,
                              uint32_t *resp);
  bool sdc_lld_send_cmd_short_crc(SDCDriver *sdcp, uint8_t cmd, uint32_t arg,
                                  uint32_t *resp);
  bool sdc_lld_send_cmd_long_crc(SDCDriver *sdcp, uint8_t cmd, uint32_t arg,
                                 uint32_t *resp);
  bool sdc_lld_read_special(SDCDriver *sdcp, uint8_t *buf, size_t bytes,
                            uint8_t cmd, uint32_t argument);
  bool sdc_lld_read(SDCDriver *sdcp, uint32_t startblk,
                    uint8_t *buf, uint32_t n);
  bool sdc_lld_write(SDCDriver *sdcp, uint32_t startblk,
                     const uint8_t *buf, uint32_t n);
  bool sdc_lld_sync(SDCDriver *sdcp);
  bool sdc_lld_is_card_inserted(SDCDriver *sdcp);
  bool sdc_lld_is_write_protected(SDCDriver *sdcp);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_SDC == TRUE */

#endif /* HAL_SDC_LLD_H */

/** @} */

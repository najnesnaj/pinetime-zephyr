/*
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef PINETIME_INCLUDE_HRS3300_H
#define PINETIME_INCLUDE_HRS3300_H

#include <device.h>

#ifdef __cplusplus
extern "C" {
#endif

enum hrs3300_hwt {
	HRS3300_HWT_800MS = 0x0,
	HRS3300_HWT_400MS = 0x1,
	HRS3300_HWT_200MS = 0x2,
	HRS3300_HWT_100MS = 0x3,
	HRS3300_HWT_75MS = 0x4,
	HRS3300_HWT_50MS = 0x5,
	HRS3300_HWT_12_5MS = 0x6,
	HRS3300_HWT_0MS = 0x7
};

enum hrs3300_pdrive {
	HRS3300_PDRIVE_12_5 = 0,
	HRS3300_PDRIVE_20 = 1,
	HRS3300_PDRIVE_30 = 2,
	HRS3300_PDRIVE_40 = 3
};

enum hrs3300_hgain {
	HRS3300_HGAIN_1 = 0,
	HRS3300_HGAIN_2 = 1,
	HRS3300_HGAIN_4 = 2,
	HRS3300_HGAIN_8 = 3,
	HRS3300_HGAIN_64 = 4,
};

/** @brief Enable measurement.
 *
 * @param dev Device.
 *
 * @return 0 on suucess, negative error code otherwise.
 */
int hrs3300_enable(struct device *dev);

/** @brief Disable measurement.
 *
 * @param dev Device.
 *
 * @return 0 on suucess, negative error code otherwise.
 */
int hrs3300_disable(struct device *dev);


/** @brief Set hgain.
 *
 * @param dev Device.
 * @param val Hgain.
 *
 * @return 0 on suucess, negative error code otherwise.
 */
int hrs3300_hgain_set(struct device *dev, enum hrs3300_hgain val);


/** @brief Get hgain.
 *
 * @param dev Device.
 * @param val Location to store hgain.
 *
 * @return 0 on suucess, negative error code otherwise.
 */
int hrs3300_hgain_get(struct device *dev, enum hrs3300_hgain *val);

/** @brief Set HWT.
 *
 * @param dev Device.
 * @param val Gain.
 *
 * @return 0 on suucess, negative error code otherwise.
 */
int hrs3300_hwt_set(struct device *dev, enum hrs3300_hwt val);

/** @brief Get HWT.
 *
 * @param dev Device.
 * @param val Location to store HWT.
 *
 * @return 0 on suucess, negative error code otherwise.
 */
int hrs3300_hwt_get(struct device *dev, enum hrs3300_hwt *val);

/** @brief Set PDrive.
 *
 * @param dev Device.
 * @param val Gain.
 *
 * @return 0 on suucess, negative error code otherwise.
 */
int hrs3300_pdrive_set(struct device *dev, enum hrs3300_pdrive val);

/** @brief Get PDrive.
 *
 * @param dev Device.
 * @param val Location to store PDrive.
 *
 * @return 0 on suucess, negative error code otherwise.
 */
int hrs3300_pdrive_get(struct device *dev, enum hrs3300_pdrive *val);

#ifdef __cplusplus
}
#endif

#endif /* PINETIME_INCLUDE_HRS3300_H */

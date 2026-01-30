/*
 * Copyright (c) 2026 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef HPF_PM_H_
#define HPF_PM_H_

#ifdef __cplusplus
extern "C" {
#endif

void hpf_pm_go_to_wait(void);
void hpf_pm_go_to_sleep(void);
void hpf_pm_go_to_hibernate(void);

#ifdef __cplusplus
}
#endif

#endif /* HPF_PM_H_ */

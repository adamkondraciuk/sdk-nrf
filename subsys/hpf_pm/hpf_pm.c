/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <hpf_pm/hpf_pm.h>
#include <hal/nrf_vpr_csr.h>
#include <hal/nrf_memconf.h>

#define VPR_POWER_IDX 1
#define VPR_RET_BIT   MEMCONF_POWER_RET_MEM0_Pos

void hpf_pm_go_to_wait(void)
{
	csr_write(VPRCSR_NORDIC_VPRNORDICSLEEPCTRL,
		  VPRCSR_NORDIC_VPRNORDICSLEEPCTRL_SLEEPSTATE_WAIT);
	nrf_barrier_w();
	arch_cpu_idle();
	csr_write(VPRCSR_NORDIC_VPRNORDICSLEEPCTRL,
		  VPRCSR_NORDIC_VPRNORDICSLEEPCTRL_SLEEPSTATE_SLEEP);
}

void hpf_pm_go_to_sleep(void)
{
	csr_write(VPRCSR_NORDIC_VPRNORDICSLEEPCTRL,
		  VPRCSR_NORDIC_VPRNORDICSLEEPCTRL_SLEEPSTATE_SLEEP);
	nrf_barrier_w();
	arch_cpu_idle();
}

void hpf_pm_go_to_hibernate(void)
{
	nrf_memconf_ramblock_ret_enable_set(NRF_MEMCONF, VPR_POWER_IDX, VPR_RET_BIT, true);
	csr_write(VPRCSR_NORDIC_VPRNORDICSLEEPCTRL,
		  VPRCSR_NORDIC_VPRNORDICSLEEPCTRL_SLEEPSTATE_HIBERNATE);
	nrf_barrier_w();
	arch_cpu_idle();
	nrf_memconf_ramblock_ret_enable_set(NRF_MEMCONF, VPR_POWER_IDX, VPR_RET_BIT, false);
	csr_write(VPRCSR_NORDIC_VPRNORDICSLEEPCTRL,
		  VPRCSR_NORDIC_VPRNORDICSLEEPCTRL_SLEEPSTATE_SLEEP);
}



/* SPDX-License-Identifier: GPL-2.0-only */
/*
 *  linux/include/linux/cpu_cooling.h
 *
 *  Copyright (C) 2012	Samsung Electronics Co., Ltd(http://www.samsung.com)
 *  Copyright (C) 2012  Amit Daniel <amit.kachhap@linaro.org>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#ifndef __CPU_COOLING_H__
#define __CPU_COOLING_H__

#include <linux/of.h>
#include <linux/thermal.h>
#include <linux/cpumask.h>

struct cpufreq_policy;

#ifdef CONFIG_CPU_FREQ_THERMAL
/**
 * cpufreq_cooling_register - function to create cpufreq cooling device.
 * @policy: cpufreq policy.
 */
struct thermal_cooling_device *
cpufreq_cooling_register(struct cpufreq_policy *policy);

/**
 * cpufreq_cooling_unregister - function to remove cpufreq cooling device.
 * @cdev: thermal cooling device pointer.
 */
void cpufreq_cooling_unregister(struct thermal_cooling_device *cdev);

/**
 * of_cpufreq_cooling_register - create cpufreq cooling device based on DT.
 * @policy: cpufreq policy.
 */
struct thermal_cooling_device *
of_cpufreq_cooling_register(struct cpufreq_policy *policy);

/* Bind a frequency cap against the actual, hardware-filtered OPP table. */
int cpufreq_cooling_get_state_for_freq(struct thermal_cooling_device *cdev,
				     unsigned int freq_khz,
				     unsigned long *state);

#else /* !CONFIG_CPU_FREQ_THERMAL */
static inline int
cpufreq_cooling_get_state_for_freq(struct thermal_cooling_device *cdev,
				 unsigned int freq_khz, unsigned long *state)
{
	return -ENOSYS;
}

static inline struct thermal_cooling_device *
cpufreq_cooling_register(struct cpufreq_policy *policy)
{
	return ERR_PTR(-ENOSYS);
}

static inline
void cpufreq_cooling_unregister(struct thermal_cooling_device *cdev)
{
	return;
}

static inline struct thermal_cooling_device *
of_cpufreq_cooling_register(struct cpufreq_policy *policy)
{
	return NULL;
}
#endif /* CONFIG_CPU_FREQ_THERMAL */

struct cpuidle_driver;

#ifdef CONFIG_CPU_IDLE_THERMAL
void cpuidle_cooling_register(struct cpuidle_driver *drv);
#else /* CONFIG_CPU_IDLE_THERMAL */
static inline void cpuidle_cooling_register(struct cpuidle_driver *drv)
{
}
#endif /* CONFIG_CPU_IDLE_THERMAL */

#endif /* __CPU_COOLING_H__ */

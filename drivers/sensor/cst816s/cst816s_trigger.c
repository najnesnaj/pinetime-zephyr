/*
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <drivers/i2c.h>
#include <sys/util.h>
#include <kernel.h>
#include <drivers/sensor.h>

#include "cst816s.h"

#include <logging/log.h>

#define PULL_UP  (1<<8)
#define EDGE    (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)

#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F005)
#define MY_REGISTER2 (*(volatile uint8_t*)0x2000F006)
#define MY_REGISTER3 (*(volatile uint8_t*)0x2000F007)
#define MY_REGISTER4 (*(volatile uint8_t*)0x2000F008)
#define MY_REGISTER5 (*(volatile uint8_t*)0x2000F009)
#define MY_REGISTER6 (*(volatile uint8_t*)0x2000F00A)

LOG_MODULE_DECLARE(CST816S, CONFIG_SENSOR_LOG_LEVEL);

int cst816s_attr_set(struct device *dev,
		    enum sensor_channel chan,
		    enum sensor_attribute attr,
		    const struct sensor_value *val)
{
	//struct cst816s_data *drv_data = dev->driver_data;

	if (chan != SENSOR_CHAN_ACCEL_XYZ) {
		return -ENOTSUP;
	}


	return 0;
}

static void cst816s_gpio_callback(struct device *dev,
				 struct gpio_callback *cb, u32_t pins)
{
	struct cst816s_data *drv_data =
		CONTAINER_OF(cb, struct cst816s_data, gpio_cb);

	ARG_UNUSED(pins);

	gpio_pin_disable_callback(dev, CONFIG_CST816S_GPIO_PIN_NUM);

#if defined(CONFIG_CST816S_TRIGGER_OWN_THREAD)
	MY_REGISTER1=0xaa;
	k_sem_give(&drv_data->gpio_sem);
#elif defined(CONFIG_CST816S_TRIGGER_GLOBAL_THREAD)
	k_work_submit(&drv_data->work);
#endif
}

static void cst816s_thread_cb(void *arg)
{
	struct device *dev = arg;
	struct cst816s_data *drv_data = dev->driver_data;


	if (drv_data->data_ready_handler != NULL) {
		drv_data->data_ready_handler(dev, &drv_data->data_ready_trigger);
                MY_REGISTER3=0xaa;
	    }



	gpio_pin_enable_callback(drv_data->gpio, CONFIG_CST816S_GPIO_PIN_NUM);
}

#ifdef CONFIG_CST816S_TRIGGER_OWN_THREAD
int tellerio;
static void cst816s_thread(int dev_ptr, int unused)
{
	struct device *dev = INT_TO_POINTER(dev_ptr);
	struct cst816s_data *drv_data = dev->driver_data;
        tellerio++;

//reset touchscreen



     //   gpio_pin_configure(drv_data->gpio, 10,GPIO_DIR_OUT); //push button out
      //  gpio_pin_write(drv_data->gpio, 10, 0); //set port low 
       // gpio_pin_write(drv_data->gpio, 10, 1); //set port high
//



if (tellerio > 200) tellerio=0;
	ARG_UNUSED(unused);

	while (1) {
		MY_REGISTER4=0xaa;
		k_sem_take(&drv_data->gpio_sem, K_FOREVER);
		cst816s_thread_cb(dev);
MY_REGISTER6=tellerio;
	}
}
#endif

#ifdef CONFIG_CST816S_TRIGGER_GLOBAL_THREAD
static void cst816s_work_cb(struct k_work *work)
{
	struct cst816s_data *drv_data =
		CONTAINER_OF(work, struct cst816s_data, work);

	cst816s_thread_cb(drv_data->dev);
}
#endif

int cst816s_trigger_set(struct device *dev,
		       const struct sensor_trigger *trig,
		       sensor_trigger_handler_t handler)
{
	struct cst816s_data *drv_data = dev->driver_data;

	if (trig->type == SENSOR_TRIG_DATA_READY) {

		drv_data->data_ready_handler = handler;
		if (handler == NULL) {
			return 0;
		}
		drv_data->data_ready_trigger = *trig;

	} 
	else {
		return -ENOTSUP;
	}

	return 0;
}

int cst816s_init_interrupt(struct device *dev)
{
	struct cst816s_data *drv_data = dev->driver_data;
MY_REGISTER1=0x00;
MY_REGISTER2=0x00;
MY_REGISTER3=0x00;
MY_REGISTER4=0x00;
MY_REGISTER5=0x00;
MY_REGISTER6=0x00;
	/* setup data ready gpio interrupt */
	drv_data->gpio = device_get_binding(CONFIG_CST816S_GPIO_DEV_NAME);
	if (drv_data->gpio == NULL) {
		LOG_DBG("Cannot get pointer to %s device",
		    CONFIG_CST816S_GPIO_DEV_NAME);
		return -EINVAL;
	}



	gpio_pin_configure(drv_data->gpio, CONFIG_CST816S_GPIO_PIN_NUM ,GPIO_DIR_IN | GPIO_INT | PULL_UP| EDGE | GPIO_INT_ACTIVE_HIGH );

//	gpio_pin_configure(drv_data->gpio, CONFIG_CST816S_GPIO_PIN_NUM
//			   GPIO_DIR_IN | GPIO_INT | GPIO_INT_LEVEL |
//			   GPIO_INT_ACTIVE_HIGH | GPIO_INT_DEBOUNCE);
MY_REGISTER6=CONFIG_CST816S_GPIO_PIN_NUM;

	gpio_init_callback(&drv_data->gpio_cb,
			   cst816s_gpio_callback,
			   BIT(CONFIG_CST816S_GPIO_PIN_NUM));

	if (gpio_add_callback(drv_data->gpio, &drv_data->gpio_cb) < 0) {
		MY_REGISTER2=0xee;
		LOG_DBG("Could not set gpio callback");
		return -EIO;
	}


#if defined(CONFIG_CST816S_TRIGGER_OWN_THREAD)
	k_sem_init(&drv_data->gpio_sem, 0, UINT_MAX);

	k_thread_create(&drv_data->thread, drv_data->thread_stack,
			CONFIG_CST816S_THREAD_STACK_SIZE,
			(k_thread_entry_t)cst816s_thread, dev,
			0, NULL, K_PRIO_COOP(CONFIG_CST816S_THREAD_PRIORITY),
			0, K_NO_WAIT);
#elif defined(CONFIG_CST816S_TRIGGER_GLOBAL_THREAD)
	drv_data->work.handler = cst816s_work_cb;
	drv_data->dev = dev;
#endif

	gpio_pin_enable_callback(drv_data->gpio, CONFIG_CST816S_GPIO_PIN_NUM);

	return 0;
}

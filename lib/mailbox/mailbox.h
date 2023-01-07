#ifndef MAILBOX_H
#define MAILBOX_H

#include <Arduino.h>


/**
 * \brief Read current battery voltage and go to sleep when to low
 */
void getBatteryVoltage(void);

/**
 * \brief Check reset cause if new post arrived
 */
uint8_t newMailArrived(void);

/**
 * \brief ESP sleep function
 */
void enterSleepmode(void);

/**
 * \brief ESP wifi connection function
 */
void wifiCon(void);

/**
 * \brief ESP wifi disconnection function
 */
void wifiDiscon(void);

/**
 * \brief ESP mqtt connection function
 */
void mqttCon(void);

/**
 * \brief ESP mqtt run function
 */
void mqttRun(void);

#endif /* ifndef MAILBOX_H */

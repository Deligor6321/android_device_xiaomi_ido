/*
 * Copyright (C) 2014 The Android Open Source Project
 * Copyright (C) 2016 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdlib>
#include <cutils/klog.h>
#include <cutils/android_reboot.h>
#include <fcntl.h>

#include <healthd.h>

#define BACKLIGHT_PATH         "/sys/class/leds/lcd-backlight/brightness"
#define CHARGING_ENABLED_PATH  "/sys/class/power_supply/battery/charging_enabled"

#define LOGE(x...) do { KLOG_ERROR("charger", x); } while (0)
#define LOGW(x...) do { KLOG_WARNING("charger", x); } while (0)
#define LOGV(x...) do { KLOG_DEBUG("charger", x); } while (0)

void healthd_board_init(struct healthd_config*)
{
    // use defaults
}


int healthd_board_battery_update(struct android::BatteryProperties*)
{
    // return 0 to log periodic polled battery status to kernel log
    return 1;
}

void healthd_board_mode_charger_draw_battery(struct android::BatteryProperties*)
{

}

void healthd_board_mode_charger_battery_update(struct android::BatteryProperties*)
{

}


#define BACKLIGHT_ON_LEVEL  100
#define BACKLIGHT_OFF_LEVEL 0
void healthd_board_mode_charger_set_backlight(bool on)
{
    int fd;
    char buffer[10];

    memset(buffer, '\0', sizeof(buffer));
    fd = open(BACKLIGHT_PATH, O_RDWR);
    if (fd < 0) {
        LOGE("Could not open backlight node : %s\n", strerror(errno));
        return;
    }
    LOGV("Enabling backlight\n");
    if (on)
        snprintf(buffer, sizeof(buffer), "%d\n", BACKLIGHT_ON_LEVEL);
    else
        snprintf(buffer, sizeof(buffer), "%d\n", BACKLIGHT_OFF_LEVEL);
    if (write(fd, buffer,strlen(buffer)) < 0) {
        LOGE("Could not write to backlight node : %s\n", strerror(errno));
    }
    close(fd);
}

void healthd_board_mode_charger_init()
{
    int ret;
    char buff[8] = "\0";
    int charging_enabled = 0;
    int fd;

    /* check the charging is enabled or not */
    fd = open(CHARGING_ENABLED_PATH, O_RDONLY);
    if (fd < 0)
        return;
    ret = read(fd, buff, sizeof(buff));
    close(fd);
    if (ret > 0 && sscanf(buff, "%d\n", &charging_enabled)) {
        /* if charging is disabled, reboot and exit power off charging */
        if (charging_enabled)
            return;
        LOGW("android charging is disabled, exit!\n");
        android_reboot(ANDROID_RB_RESTART, 0, 0);
    }
}

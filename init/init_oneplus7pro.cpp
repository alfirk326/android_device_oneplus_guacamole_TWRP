/*
   Copyright (C) 2017-2018 The Android Open Source Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <android-base/logging.h>
#include <android-base/properties.h>

#include "property_service.h"
#include "log.h"

namespace android {
namespace init {

void load_op7pro(const char *model) {
    property_set("ro.product.model", model);
    property_set("ro.build.product", "OnePlus7Pro");
    property_set("ro.product.device", "OnePlus7Pro");
    property_set("ro.vendor.product.device", "OnePlus7Pro");
    property_set("ro.display.series", "OnePlus 7 Pro");
}

static bool file_exist (const std::string& name) {
    return ( access( name.c_str(), F_OK ) == 0 );
}

void load_op7pro5g(const char *model) {
    property_set("ro.product.model", model);
    property_set("ro.build.product", "OnePlus7ProNR");
    property_set("ro.product.device", "OnePlus7ProNR");
    property_set("ro.vendor.product.device", "OnePlus7ProNR");
    property_set("ro.display.series", "OnePlus 7 Pro 5G");
}

void vendor_load_properties() {
    int rf_version = stoi(android::base::GetProperty("ro.boot.rf_version", ""));

    switch (rf_version) {
    case 1:
        if (file_exist("/dev/block/bootdevice/by-name/5gdump")){
            /* 5g Europe */
            load_op7pro5g("GM1920");
            break;
            } else {
            /* China */
            load_op7pro("GM1910");
            break;
            }
    case 2:
        /* T-Mobile */
        load_op7pro("GM1915");
        break;
    case 3:
        /* India*/
        load_op7pro("GM1911");
        break;
    case 4:
        /* Europe */
        load_op7pro("GM1913");
        break;
    case 5:
        /* Global / US Unlocked */
        load_op7pro("GM1917");
        break;
    default:
        LOG(ERROR) << __func__ << ": unexcepted rf version!";
    }
}

}  // namespace init
}  // namespace android

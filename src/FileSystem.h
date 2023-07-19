#pragma once

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <config.h>

#if ESP_USELITTLEFS
#include <LittleFS.h>
#define FILESYSTEM LittleFS
#else
#include <SPIFFS.h>
#define FILESYSTEM SPIFFS
#endif

#endif
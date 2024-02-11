#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_spiffs.h"

static const char *TAG = "SPIFFS";

esp_err_t mountSPIFFS(const char * partition_label, const char * mount_point) {
	ESP_LOGI(TAG, "Initializing SPIFFS");
	esp_vfs_spiffs_conf_t conf = {
		.base_path = mount_point,
		.partition_label = partition_label,
		.max_files = 10, // maximum number of files which can be open at the same time
		.format_if_mount_failed = true
	};

	// Use settings defined above to initialize and mount SPIFFS filesystem.
	// Note: esp_vfs_spiffs_register is an all-in-one convenience function.
	esp_err_t ret = esp_vfs_spiffs_register(&conf);

	if (ret != ESP_OK) {
		if (ret == ESP_FAIL) {
			ESP_LOGE(TAG, "Failed to mount or format filesystem");
		} else if (ret == ESP_ERR_NOT_FOUND) {
			ESP_LOGE(TAG, "Failed to find SPIFFS partition");
		} else {
			ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
		}
		return ret;
	}

	size_t total = 0, used = 0;
	//ret = esp_spiffs_info(NULL, &total, &used);
	ret = esp_spiffs_info(partition_label, &total, &used);
	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
	} else {
		ESP_LOGI(TAG, "Partition [%s] size: total: %d, used: %d", mount_point, total, used);
	}
	return ret;
}

static int getFileSize(char *fullPath) {
	struct stat st;
	if (stat(fullPath, &st) == 0)
		return st.st_size;
	return -1;
}

void printDirectory(const char * path) {
	DIR* dir = opendir(path);
	assert(dir != NULL);
	while (true) {
		struct dirent *pe = readdir(dir);
		if (!pe) break;
		if (pe->d_type == 1) {
			char fullPath[64];
			strcpy(fullPath, path);
			strcat(fullPath, "/");
			strcat(fullPath, pe->d_name);
			int fsize = getFileSize(fullPath);
			ESP_LOGI(__FUNCTION__,"%s d_name=%s d_ino=%d fsize=%d", path, pe->d_name, pe->d_ino, fsize);
		}
		if (pe->d_type == 2) {
			char subDir[127];
			sprintf(subDir,"%s%.64s", path, pe->d_name);
			ESP_LOGI(TAG, "subDir=[%s]", subDir);
			printDirectory(subDir);

		}
	}
	closedir(dir);
}

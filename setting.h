#pragma once


#ifndef SETTING_H
#define SETTING_H

#include "common_headers.h"

class Setting {
private:
	string fileStoragePath;
public:
	Setting(string filePath);
	~Setting();
};

#endif
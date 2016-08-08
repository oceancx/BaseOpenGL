#pragma once
//=========== 包含文件 ============
#include "base.h"
//=================================
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class ReadGameWdf
{
public:
	ReadGameWdf(void);
	~ReadGameWdf(void);
	void ReadWas(string filename);
};


#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ReadGameWdf.h"
#include "Sprite.h"
using namespace std;

int main(){
	// ReadGameWdf wdf;
	Sprite mSprite;
	mSprite.OpenSpriteFile("42DC698F.was");
	return 0;
}
#pragma once

// include Windows header file thats needed for all Windows applications
#include <Windows.h>
// we might not need stdio but we will have it in case we run into a situation
// in which we need it 
#include <stdio.h>

// these files are created by us

#include "map.h"
#include "XY.h"
#include "object.h"

// DirectX files
#include "dxManager.h"
#include "directInput.h"
#include "sound.h"
#include <d3d9.h>
#include <d3dx9tex.h>
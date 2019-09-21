#pragma once

#include "KeyModule.h"
#define _KeyCode KeyModule::GetInstance()

#include "TimerModule.h"
#define _Timer TimerModule::GetInstance()

#include "ImageManager.h"
#define _ImageManager ImageManager::GetInstance()

#include "CameraManager.h"
#define _Camera CameraManager::GetInstance()

#include "SceneManager.h"
#define _Scene SceneManager::GetInstance()

#include "Database.h"
#define _DB Database::GetInstance()

#include "FontManager.h"
#define _FontManager FontManager::GetInstance()

#include "BulletManager.h"
#define _BulletManager BulletManager::GetInstance()

#include "EnemyManager.h"
#define _EnemyManager EnemyManager::GetInstance()
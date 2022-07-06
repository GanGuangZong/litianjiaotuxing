//
//  EEOBridgeClass.h
//  EEOBezierKit
//
//  Created by 侯嘉晖 on 2021/7/8.
//  Copyright © 2021 侯嘉晖. All rights reserved.
//
#include <stdio.h>
#include <string>

/// 获取新的图元ID
/// @param instanceID 实例ID
void* getNewUUID(int instanceID);

/// 获取新的指令ID
/// @param instanceID 实例ID
void* getNewActionID(int instanceID);

/// 打印日志
/// @param instanceID 实例ID
/// @param log 日志字符串
void onPrintLog(int instanceID, std::string log);

/// 收到新数据,每次调用均为单条指令
/// @param instanceID 实例ID
/// @param data 数据流
/// @param length 数据长度
void onNewCommandData(int instanceID, void* data, int length);


//
//  LXBluetoothDeviceMeshCommandManager.h
//  TelinkBlueDemo
//
//  Created by ifeegoo on 16/8/19.
//  Copyright © 2016年 Green. All rights reserved.

/**
0x26：APP查询闹钟
0x27：固件回馈闹钟信息
0x28：APP查询时间
0x29:固件回馈时间
0x2A:app查询灯的一些状态信息
0x2B：固件回馈灯的状态信息*/
//

#import <Foundation/Foundation.h>
//#import "BTCentralManager.h"
#import "LXBluetoothDeviceManager.h"
#import "LXBluetoothDeviceCommandManager.h"

#define bluetooth_commnuication_delay_time 0x08 // 0x10



typedef NS_ENUM(NSUInteger, LXMeshCommandParameterType)
{
    // 查询当前状态
    LXMeshCommandParameterTypeCurrentState = 1,
     // 查询上一次状态
    LXMeshCommandParameterTypeLastState = 2,

};

typedef NS_ENUM(NSUInteger, LXMeshCommandParameterFeedbackType)
{
    // 设备绑定
    LXMeshCommandParameterFeedbackTypeDeviceBind = 1,
    // 白灯参数
    LXMeshCommandParameterFeedbackTypeWhiteLampStatus = 2,
    // 彩灯参数
    LXMeshCommandParameterFeedbackTypeColorLampStatus = 3,
    // 蜂鸣器参数
    LXMeshCommandParameterFeedbackTypeBuzzerStatus = 4,
    // 是否出发了摇一摇
    LXMeshCommandParameterFeedbackTypeIsShaked = 5,
    // 电池电量的变化
    LXMeshCommandParameterFeedbackTypeBatteryChanged = 6,
};



/**
 * 查询的命令区分，是为了查询当前状态，还是用来触发上一次控制的状态回调。
 */
typedef NS_ENUM(NSUInteger, LXMeshCommandInquiryType)
{
    
    LXMeshCommandInquiryTypeCurrentStatus = 1,
    LXMeshCommandInquiryTypeControlLastTime = 2
};

typedef NS_ENUM(NSUInteger, LXMeshCommandOperationCode)
{
    // 查询类
    LXMeshCommandOperationCodeInquiry = 0x2A | 0xC0,
    // 查询反馈类，由固件返回
    LXMeshCommandOperationCodeFeedback = 0x2B | 0xC0,
    
    // 控制类
    LXMeshCommandOperationCodeControl = 0x30 | 0xC0,
    
    // 硬件信息类：摇一摇,电池电量返回
    LXMeshCommandOperationCodePhoneInfo = 0x00 | 0x00,
    
    // 蜂鸣器
//    LXMeshCommandOperationCodeBuzzer = 0x03 | 0xC0,
    
};

/**
 * 控制命令是否需要附带查询命令
 */
typedef NS_ENUM(NSUInteger, LXMeshCommandControlWhetherInquireType)
{
    LXMeshCommandControlWhetherInquireTypeNo = 1,
    LXMeshCommandControlWhetherInquireTypeYes = 2
};


@interface LXBluetoothDeviceMeshCommandManager : LXBluetoothDeviceCommandManager

+ (LXBluetoothDeviceMeshCommandManager*)sharedInstance;

//- (void)setBTCentralManagerDelegate:(id<BTCentralManagerDelegate>)delegate;

- (void)sendWithOperationCode:(int)opCode bytes:(Byte*)bytes length:(int)length;

- (void)lxOnDevNofifyByte:(uint8_t *)byte;


@end

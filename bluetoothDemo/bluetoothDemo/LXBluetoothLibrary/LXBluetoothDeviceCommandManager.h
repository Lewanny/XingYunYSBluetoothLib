//
//  LXBluetoothDeviceCommandManager.h
//  bluetoothDemo
//
//  Created by ifeegoo on 2017/1/14.
//  Copyright © 2017年 arrfu. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, LXBluetoothDeviceCommandType)
{
    LXBluetoothDeviceCommandTypeFeedbackInquiry = 1,
    LXBluetoothDeviceCommandTypeFeedbackControl
};

@interface LXBluetoothDeviceCommandManager : NSObject

@end

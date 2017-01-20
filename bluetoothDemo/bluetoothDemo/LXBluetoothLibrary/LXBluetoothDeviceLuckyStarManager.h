#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "LXBluetoothDeviceLuckyStarManager.h"
#import "LXBluetoothDeviceCommandManager.h"
#import "LXBluetoothDeviceMeshCommandManager.h"

/*!
 *  @enum LXBluetoothDeviceLuckyStarManagerSwitch
 *
 *  @discussion App 开关动作。
 *
 *  @constant LXBluetoothDeviceLuckyStarManagerSwitchOn 开。
 *  @constant LXBluetoothDeviceLuckyStarManagerSwitchOff 关。
 *
 */
typedef NS_ENUM(NSUInteger, LXBluetoothDeviceLuckyStarManagerSwitch)
{
    LXBluetoothDeviceLuckyStarManagerSwitchUnknow,
    LXBluetoothDeviceLuckyStarManagerSwitchOn = 1,
    LXBluetoothDeviceLuckyStarManagerSwitchOff = 2,
};

/*!
 *  @enum LXBluetoothDeviceLuckyStarManagerBindingAction
 *
 *  @discussion App 执行的设备绑定动作。
 *
 *  @constant LXBluetoothDeviceLuckyStarManagerBindingActionBind 设备绑定。
 *  @constant LXBluetoothDeviceLuckyStarManagerBindingActionUnbind 设备解绑。
 *
 */
typedef NS_ENUM(NSUInteger, LXBluetoothDeviceLuckyStarManagerBindingAction)
{
    LXBluetoothDeviceLuckyStarManagerBindingActionNone,
    LXBluetoothDeviceLuckyStarManagerBindingActionBind = 1,
    LXBluetoothDeviceLuckyStarManagerBindingActionUnbind = 2,
};

/*!
 *  @enum LXBluetoothDeviceLuckyStarManagerLightEffectType
 *
 *  @discussion 设备灯效。
 *
 *  @constant LXBluetoothDeviceLuckyStarManagerLightEffectTypeSevenColors 七彩灯效。
 *  @constant LXBluetoothDeviceLuckyStarManagerLightEffectTypeBreath 呼吸灯效。
 *
 */
typedef NS_ENUM(NSUInteger, LXBluetoothDeviceLuckyStarManagerLightEffectType)
{
    LXBluetoothDeviceLuckyStarManagerLightEffectTypeSevenColors = 1,
    LXBluetoothDeviceLuckyStarManagerLightEffectTypeBreath
};

/*!
 *  @enum LXBluetoothDeviceLuckyStarManagerKeyEvent
 *
 *  @discussion 设备按键事件。
 *
 *  @constant LXBluetoothDeviceLuckyStarManagerKeyEventSingleClick 按键单击事件。
 *  @constant LXBluetoothDeviceLuckyStarManagerKeyEventDoubleClick 按键双击事件。
 *  @constant LXBluetoothDeviceLuckyStarManagerKeyEventLongPress 按键长按事件。
 *
 */
typedef NS_ENUM(NSUInteger, LXBluetoothDeviceLuckyStarManagerKeyEvent)
{
    LXBluetoothDeviceLuckyStarManagerKeyEventSingleClick = 1,
    LXBluetoothDeviceLuckyStarManagerKeyEventDoubleClick,
    LXBluetoothDeviceLuckyStarManagerKeyEventLongPress
};

/*!
 *  @protocol LXBluetoothDeviceLuckyStarManagerDelegate
 *
 *  @discussion 设备管理器代理。
 *
 */
@protocol LXBluetoothDeviceLuckyStarManagerDelegate <NSObject>

@optional

/*!
 *  @method bluetoothDeviceLuckyStarDeviceBindingStatusDidReceiveWithUserID:bindingAction:device:successful:commandType:
 *
 *  @param userID  用户 ID。
 *  @param bindingAction  绑定动作。
 *  @param successful  绑定是否成功。
 *  @param commandType  命令类型，是查询的回馈，还是控制的回馈。
 *
 *  @discussion 当执行绑定设备或解除绑定设备之后，设备回调的当前设备绑定的执行结果。
 *
 *  @see LXBluetoothDeviceLuckyStarManagerBindingAction
 *  @see LXBluetoothDeviceCommandType
 *
 */
- (void)bluetoothDeviceLuckyStarDeviceBindingStatusDidReceiveWithUserID:(int)userID bindingAction:(LXBluetoothDeviceLuckyStarManagerBindingAction)bindingAction successful:(BOOL)successful commandType:(LXBluetoothDeviceCommandType)commandType;

/*!
 *  @method bluetoothDeviceLuckyStarWhiteLightStatusDidReceiveWithSwitchStatus:brightness:warmness:commandType:
 *
 *  @param switchStatus  开关状态。TRUE：开。FALSE：关。
 *  @param brightness  亮度值。取值范围：0-255。
 *  @param warmness   冷暖白值。取值范围：0-255。
 *  @param commandType  命令类型，是查询的回馈，还是控制的回馈。
 *
 *  @discussion 当设置设备颜色之后，设备回调的当前灯的实际颜色。
 *
 *  @see LXBluetoothDeviceCommandType
 *
 */
- (void)bluetoothDeviceLuckyStarWhiteLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus brightness:(int)brightness warmness:(int)warmness commandType:(LXBluetoothDeviceCommandType)commandType;

/*!
 *  @method bluetoothDeviceLuckyStarColorLightStatusDidReceiveWithSwitchStatus:effectType:brightness:red:green:blue:commandType:
 *
 *  @param switchStatus  开关状态。TRUE：开。FALSE：关。
 *  @param brightness  亮度值。取值范围：0-255。
 *  @param red  颜色 R 值。取值范围：0-255。
 *  @param green  颜色 G 值。取值范围：0-255。
 *  @param blue  颜色 B 值。取值范围：0-255。
 *  @param commandType  命令类型，是查询的回馈，还是控制的回馈。
 *
 *  @discussion 当设置设备颜色之后，设备回调的当前灯的实际颜色。
 *
 *  @see LXBluetoothDeviceCommandType
 *
 */
- (void)bluetoothDeviceLuckyStarColorLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus effectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType brightness:(int)brightness red:(int)red green:(int)green blue:(int)blue commandType:(LXBluetoothDeviceCommandType)commandType;

/*!
 *  @method bluetoothDeviceLuckyStarGravitySensorDataDidReceiveWithAxisX:(int)axisX axisY:(int)axisY axisZ:(int)axisZ
 *  @param axisX 重力传感器 X 轴方向数据变化
 *  @param axisY 重力传感器 Y 轴方向数据变化
 *  @param axisZ 重力传感器 Z 轴方向数据变化
 *
 *  @discussion 设备摇一摇动作被触发的消息回调。
 *
 */
- (void)bluetoothDeviceLuckyStarGravitySensorDataDidReceiveWithAxisX:(int)axisX axisY:(int)axisY axisZ:(int)axisZ;

/*!
 *  @method bluetoothDeviceLuckyStarBuzzerStatusDidReceiveWithStatus:time:commandType:
 *
 *  @param status  蜂鸣器状态。取值说明：TRUE 开启 / FALSE 关闭。
 *  @param time  蜂鸣器开启状态下的蜂鸣时间。取值说明：status = TRUE 的时候，time 取值为 0-N，0为一直蜂鸣，其他为 N 秒蜂鸣。status = FALSE 的时候，time 为默认值 0。
 *  @param commandType  命令类型，是查询的回馈，还是控制的回馈。
 *
 *  @discussion 当开启或关闭蜂鸣器之后，设备返回的当前蜂鸣器的实际状态。
 *
 *  @see LXBluetoothDeviceCommandType
 *
 */
- (void)bluetoothDeviceLuckyStarBuzzerStatusDidReceiveWithStatus:(BOOL)status time:(int)time commandType:(LXBluetoothDeviceCommandType)commandType;

/*!
 *  @method bluetoothDeviceLuckyStarBatteryStatusDidChangeWithChargingStatus:level:
 *
 *  @param chargingStatus  充电状态。取值说明：TRUE 充电中 / FALSE 非充电状态。
 *  @param level  电池电量状态。取值说明：0-100 百分比值。
 *
 *  @discussion 设备电池状态发生变化的时候，返回的电池状态。
 *
 */
- (void)bluetoothDeviceLuckyStarBatteryStatusDidChangeWithChargingStatus:(BOOL)chargingStatus level:(int)level;

/*!
 *  @method bluetoothDeviceLuckyStarPressKeyEventDidRecevieWithKeyEvent:
 *
 *  @param keyEvent  按键消息。
 *
 *  @discussion 当设备上的按键被按的时候，返回的设备按键消息。
 *
 *  @see LXBluetoothDeviceLuckyStarManagerKeyEvent
 *
 */
- (void)bluetoothDeviceLuckyStarPressKeyEventDidRecevieWithKeyEvent:(LXBluetoothDeviceLuckyStarManagerKeyEvent)keyEvent;

@end

/*!
 *  @class LXBluetoothDeviceLuckyStarManager
 *
 *  @discussion 设备管理器。备注：请注意获取当前管理器对象的方式。是通过调用 LXBluetoothDeviceManager 中的 getLXBluetoothDeviceLuckyStarManager 方法获取的。
 *
 */
@interface LXBluetoothDeviceLuckyStarManager : NSObject

+ (LXBluetoothDeviceLuckyStarManager*)sharedInstance;

@property (nonatomic,strong)id<LXBluetoothDeviceLuckyStarManagerDelegate> delegate;
/*!
 *  @method setLXBluetoothDeviceLuckyStarManagerDelegate:
 *  @param delegate 代理对象。
 *
 *  @discussion 设置代理对象。
 *
 */
- (void)setLXBluetoothDeviceLuckyStarManagerDelegate:(id<LXBluetoothDeviceLuckyStarManagerDelegate>)delegate;

/*!
 *  @method getDeviceBindingStatus:
 *
 *  @discussion 获取当前设备绑定状态。
 * 
 *  @see bluetoothDeviceLuckyStarDeviceBindingStatusDidReceiveWithUserID:bindingAction:device:successful:commandType:
 *
 */
- (void)getDeviceBindingStatus;

/*!
 *  @method bindDeviceWithUserID:
 *  @param userID 用户 ID 值。
 *
 *  @discussion 传入用户 ID 值来与设备进行绑定。备注：这个用户 ID 值会写入设备固件中。
 *
 *  @see bluetoothDeviceLuckyStarDeviceBindingStatusDidReceiveWithUserID:bindingAction:device:successful:commandType:
 *
 */
- (void)bindDeviceWithUserID:(int)userID;

/*!
 *  @method unbindDeviceWithUserID:
 *  @param userID 用户 ID 值。
 *
 *  @discussion 传入用户 ID 值来与设备进行解绑。备注：这个用户 ID 值会和原先写入设备中的用户 ID 值比对，如果相同就清除，如果不同，就是解绑失败。
 *
 *  @see bluetoothDeviceLuckyStarDeviceBindingStatusDidReceiveWithUserID:bindingAction:device:successful:commandType:
 *
 */
- (void)unbindDeviceWithUserID:(int)userID;

/*!
 *  @method getWhiteLightStatus
 *
 *  @discussion 获取设备白灯的状态。
 *
 *  @see bluetoothDeviceLuckyStarWhiteLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus brightness:(int)brightness warmness:(int)warmness commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)getWhiteLightStatus;

/*!
 *  @method turnOnWhiteLight
 *
 *  @discussion 打开白灯。
 *
 *  @see bluetoothDeviceLuckyStarWhiteLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus brightness:(int)brightness warmness:(int)warmness commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)turnOnWhiteLight;

/*!
 *  @method turnOffWhiteLight
 *
 *  @discussion 关闭白灯。
 *
 *  @see bluetoothDeviceLuckyStarWhiteLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus brightness:(int)brightness warmness:(int)warmness commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)turnOffWhiteLight;

/*!
 *  @method setWhiteLightStatusWithBrightness:(int)brightness
 *
 *  @discussion 设置白灯亮度。
 *
 *  @see bluetoothDeviceLuckyStarWhiteLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus brightness:(int)brightness warmness:(int)warmness commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)setWhiteLightStatusWithBrightness:(int)brightness;

/*!
 *  @method setWhiteLightStatusWithWarmness:(int)warmness
 *
 *  @discussion 设置白灯冷暖白。
 *
 *  @see bluetoothDeviceLuckyStarWhiteLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus brightness:(int)brightness warmness:(int)warmness commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)setWhiteLightStatusWithWarmness:(int)warmness;

/*!
 *  @method setWhiteLightStatusWithSwitchStatus:(BOOL)switchStatus brightness:(int)brightness warmness:(int)warmness
 *
 *  @discussion 设置白灯开关，亮度，冷暖白参数。
 *
 *  @see bluetoothDeviceLuckyStarWhiteLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus brightness:(int)brightness warmness:(int)warmness commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)setWhiteLightStatusWithSwitchStatus:(BOOL)switchStatus brightness:(int)brightness warmness:(int)warmness;

/*!
 *  @method getLightColorStatus
 *
 *  @discussion 获取设备彩灯的状态。
 *
 *  @see bluetoothDeviceLuckyStarColorLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus effectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType brightness:(int)brightness red:(int)red green:(int)green blue:(int)blue commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)getColorLightStatus;

/*!
 *  @method turnOnColorLight
 *
 *  @discussion 打开彩灯。
 *
 *  @see bluetoothDeviceLuckyStarColorLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus effectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType brightness:(int)brightness red:(int)red green:(int)green blue:(int)blue commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)turnOnColorLight;

/*!
 *  @method turnOffColorLight
 *
 *  @discussion 关闭彩灯。
 *
 *  @see bluetoothDeviceLuckyStarColorLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus effectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType brightness:(int)brightness red:(int)red green:(int)green blue:(int)blue commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)turnOffColorLight;

/*!
 *  @method setColorLightStatusWithEffectType
 *
 *  @discussion 设置彩灯灯效。
 *
 *  @see bluetoothDeviceLuckyStarColorLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus effectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType brightness:(int)brightness red:(int)red green:(int)green blue:(int)blue commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)setColorLightStatusWithEffectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType;

/*!
 *  @method setColorLightStatusWithBrightness
 *
 *  @discussion 设置彩灯亮度。
 *
 *  @see bluetoothDeviceLuckyStarColorLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus effectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType brightness:(int)brightness red:(int)red green:(int)green blue:(int)blue commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)setColorLightStatusWithBrightness:(int)brightness;

/*!
 *  @method setColorLightStatusWithRed:(int)red green:(int)green blue:(int)blue
 *
 *  @discussion 设置彩灯RGB。
 *
 *  @see bluetoothDeviceLuckyStarColorLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus effectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType brightness:(int)brightness red:(int)red green:(int)green blue:(int)blue commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)setColorLightStatusWithRed:(int)red green:(int)green blue:(int)blue;

/*!
 *  @method setColorLightStatusWithSwitchStatus:(BOOL)switchStatus effectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType
 *
 *  @discussion 设置彩灯灯效和开关。
 *
 *  @see bluetoothDeviceLuckyStarColorLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus effectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType brightness:(int)brightness red:(int)red green:(int)green blue:(int)blue commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)setColorLightStatusWithSwitchStatus:(BOOL)switchStatus effectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType;

/*!
 *  @method setColorLightStatusWithSwitchStatus:(BOOL)switchStatus brightness:(int)brightness red:(int)red green:(int)green blue:(int)blue
 *
 *  @discussion 设置彩灯RGB和开关。
 *
 *  @see bluetoothDeviceLuckyStarColorLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus effectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType brightness:(int)brightness red:(int)red green:(int)green blue:(int)blue commandType:(LXBluetoothDeviceCommandType)commandType
 */
- (void)setColorLightStatusWithSwitchStatus:(BOOL)switchStatus brightness:(int)brightness red:(int)red green:(int)green blue:(int)blue;

/*!
 *  @method getBuzzerStatus
 *
 *  @discussion 获取蜂鸣器的状态。
 *
 *  @see bluetoothDeviceLuckyStarBuzzerStatusDidReceiveWithStatus:time:
 */
- (void)getBuzzerStatus;

/*!
 *  @method turnOnBuzzerWithTime:
 *  @param time 开启蜂鸣器时间，单位秒。取值说明：0 表示一直蜂鸣，N 表示蜂鸣 N 秒。
 *
 *  @discussion 开启蜂鸣器。
 *
 *  @see bluetoothDeviceLuckyStarBuzzerStatusDidReceiveWithStatus:time:
 */
- (void)turnOnBuzzerWithTime:(int)time;

/*!
 *  @method turnOffBuzzer
 *
 *  @discussion 关闭蜂鸣器。
 *
 *  @see bluetoothDeviceLuckyStarBuzzerStatusDidReceiveWithStatus:time:
 */
- (void)turnOffBuzzer;

- (void)lxOnDevNofifyByte:(uint8_t *)byte;

@end

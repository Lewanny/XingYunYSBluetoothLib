#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "LXBluetoothDeviceLuckyStarManager.h"

#define LXLog(...)  NSLog(@"%s %d \n %@\n\n",__func__,__LINE__,[NSString stringWithFormat:__VA_ARGS__])

@class LXBluetoothDeviceLuckyStarManager;
/*!
 *  @enum LXBluetoothDeviceManagerBluetoothDeviceProfile
 *
 *  @discussion 蓝牙配置选项
 *
 *  @constant LXBluetoothDeviceManagerBluetoothDeviceProfileUnknown
 *  @constant LXBluetoothDeviceManagerBluetoothDeviceProfileA2DP
 *
 */
typedef NS_ENUM(NSUInteger, LXBluetoothDeviceManagerBluetoothDeviceProfile)
{
    LXBluetoothDeviceManagerBluetoothDeviceProfileUnknown = 0,
    LXBluetoothDeviceManagerBluetoothDeviceProfileA2DP = 1,
    LXBluetoothDeviceManagerBluetoothDeviceProfileATT = 2,
    LXBluetoothDeviceManagerBluetoothDeviceProfileAVRCP = 3,
    LXBluetoothDeviceManagerBluetoothDeviceProfileBIP = 4,
    LXBluetoothDeviceManagerBluetoothDeviceProfileBPP = 5,
    LXBluetoothDeviceManagerBluetoothDeviceProfileCIP = 6,
    LXBluetoothDeviceManagerBluetoothDeviceProfileCTP = 7,
    LXBluetoothDeviceManagerBluetoothDeviceProfileDIP = 8,
    LXBluetoothDeviceManagerBluetoothDeviceProfileDUN = 9,
    LXBluetoothDeviceManagerBluetoothDeviceProfileFAX = 10,
    LXBluetoothDeviceManagerBluetoothDeviceProfileFTP = 11,
    LXBluetoothDeviceManagerBluetoothDeviceProfileGAVDP = 12,
    LXBluetoothDeviceManagerBluetoothDeviceProfileGAP = 13,
    LXBluetoothDeviceManagerBluetoothDeviceProfileGATT = 14,
    LXBluetoothDeviceManagerBluetoothDeviceProfileGOEP = 15,
    LXBluetoothDeviceManagerBluetoothDeviceProfileHCRP = 16,
    LXBluetoothDeviceManagerBluetoothDeviceProfileHDP = 17,
    LXBluetoothDeviceManagerBluetoothDeviceProfileHFP = 18,
    LXBluetoothDeviceManagerBluetoothDeviceProfileHID = 19,
    LXBluetoothDeviceManagerBluetoothDeviceProfileHSP = 20,
    LXBluetoothDeviceManagerBluetoothDeviceProfileICP = 21,
    LXBluetoothDeviceManagerBluetoothDeviceProfileLAP = 22,
    LXBluetoothDeviceManagerBluetoothDeviceProfileMAP = 23,
    LXBluetoothDeviceManagerBluetoothDeviceProfileOBEX = 24,
    LXBluetoothDeviceManagerBluetoothDeviceProfileOPP = 25,
    LXBluetoothDeviceManagerBluetoothDeviceProfilePAN = 26,
    LXBluetoothDeviceManagerBluetoothDeviceProfilePBAP = 27,
    LXBluetoothDeviceManagerBluetoothDeviceProfilePXP = 28,
    LXBluetoothDeviceManagerBluetoothDeviceProfileSPP = 29,
    LXBluetoothDeviceManagerBluetoothDeviceProfileSDAP = 30,
    LXBluetoothDeviceManagerBluetoothDeviceProfileSIMAP = 31,
    LXBluetoothDeviceManagerBluetoothDeviceProfileSYNCH = 32,
    LXBluetoothDeviceManagerBluetoothDeviceProfileSYNCML = 33,
    LXBluetoothDeviceManagerBluetoothDeviceProfileVDP = 34,
    LXBluetoothDeviceManagerBluetoothDeviceProfileWAPB = 35,
    LXBluetoothDeviceManagerBluetoothDeviceProfileUDI = 36,
    LXBluetoothDeviceManagerBluetoothDeviceProfileESDP = 37,
    LXBluetoothDeviceManagerBluetoothDeviceProfileVCP = 38
};

/*!
 *  @enum LXBluetoothDeviceManagerBluetoothType
 *
 *  @discussion 蓝牙类型
 *
 *  @constant LXBluetoothDeviceManagerBluetoothTypeClassic 传统蓝牙A2DP协议
 *  @constant LXBluetoothDeviceManagerBluetoothTypeBLE    蓝牙低功耗BLE协议
 *
 */
typedef NS_ENUM(NSUInteger, LXBluetoothDeviceManagerBluetoothType)
{
    LXBluetoothDeviceManagerBluetoothTypeClassic = 1,
    LXBluetoothDeviceManagerBluetoothTypeBLE = 2
};

/*!
 *  @enum LXBluetoothDeviceManagerBluetoothStatus
 *
 *  @discussion 蓝牙状态
 *
 *  @constant LXBluetoothDeviceManagerBluetoothStatusTurningOn  开启蓝牙
 *  @constant LXBluetoothDeviceManagerBluetoothStatusOn         蓝牙已打开
 *  @constant LXBluetoothDeviceManagerBluetoothStatusTurningOff 关闭蓝牙
 *  @constant LXBluetoothDeviceManagerBluetoothStatusOff        蓝牙已关闭
 *  @constant LXBluetoothDeviceManagerBluetoothStatusScanning   扫描蓝牙
 *
 */
typedef NS_ENUM(NSUInteger, LXBluetoothDeviceManagerBluetoothStatus)
{
    LXBluetoothDeviceManagerBluetoothStatusTurningOn = 1,
    LXBluetoothDeviceManagerBluetoothStatusOn = 2,
    LXBluetoothDeviceManagerBluetoothStatusTurningOff = 3,
    LXBluetoothDeviceManagerBluetoothStatusOff = 4,
    LXBluetoothDeviceManagerBluetoothStatusScanning = 5
};

/*!
 *  @enum LXBluetoothDeviceManagerBluetoothConnectionStatus
 *
 *  @discussion 蓝牙连接状态
 *
 *  @constant LXBluetoothDeviceManagerBluetoothConnectionStatusConnecting    连接蓝牙
 *  @constant LXBluetoothDeviceManagerBluetoothConnectionStatusConnected     蓝牙已连接
 *  @constant LXBluetoothDeviceManagerBluetoothConnectionStatusDisconnecting 断开蓝牙
 *  @constant LXBluetoothDeviceManagerBluetoothConnectionStatusDisconnected  蓝牙已断开
 *
 */
typedef NS_ENUM(NSUInteger, LXBluetoothDeviceManagerBluetoothConnectionStatus)
{
    LXBluetoothDeviceManagerBluetoothConnectionStatusConnecting = 1,
    LXBluetoothDeviceManagerBluetoothConnectionStatusConnected = 2,
    LXBluetoothDeviceManagerBluetoothConnectionStatusConnectionFailure = 3,
    LXBluetoothDeviceManagerBluetoothConnectionStatusDisconnecting = 4,
    LXBluetoothDeviceManagerBluetoothConnectionStatusDisconnected = 5,
    LXBluetoothDeviceManagerBluetoothConnectionStatusDisconnectionFailure = 6
};


/*!
 *  @protocol LXBluetoothDeviceManagerDelegate
 *
 *  @discussion LXBluetoothDeviceManager 回调代理
 *  当蓝牙打开后需要设置代理
 *
 *
 */
@protocol LXBluetoothDeviceManagerDelegate <NSObject>

@optional

/*!
 *  @method bluetoothDeviceBluetoothStatusDidChangeWithStatus:
 *
 *  @param bluetoothStatus 蓝牙状态回调
 *
 *  @discussion 当蓝牙状态变化时，返回状态信息
 *
 *  @see LXBluetoothDeviceManagerBluetoothStatus
 *
 */
- (void)bluetoothDeviceBluetoothStatusDidChangeWithStatus:(LXBluetoothDeviceManagerBluetoothStatus)bluetoothStatus;

/*!
 *  @method bluetoothDeviceBluetoothConnectionStatusDidChangeWithPeripheral:bluetoothType:bluetoothDeviceProfile:bluetoothConnectionStatus:
 *
 *  @param peripheral CBPeripheral对象
 *  @param bluetoothType  蓝牙类型
 *  @param bluetoothDeviceProfile  蓝牙配置选项
 *  @param bluetoothConnectionStatus  蓝牙连接状态
 *
 *  @discussion 蓝牙连接成功或失败状态回调
 *
 *  @see LXBluetoothDeviceManagerBluetoothConnectionStatus
 *
 */
- (void)bluetoothDeviceBluetoothConnectionStatusDidChangeWithPeripheral:(CBPeripheral *)peripheral bluetoothType:(LXBluetoothDeviceManagerBluetoothType)bluetoothType bluetoothDeviceProfile:(LXBluetoothDeviceManagerBluetoothDeviceProfile)bluetoothDeviceProfile bluetoothConnectionStatus:(LXBluetoothDeviceManagerBluetoothConnectionStatus)bluetoothConnectionStatus;

/*!
 * TODO
 *
 */
- (void)bluetoothDeviceBluetoothScanningClassicDidReceive;

/*!
 *  @method bluetoothDeviceBluetoothScanningBLEDidReceiveWithPeripheral:RSSI:advertisementData:
 *
 *  @param peripheral  CBPeripheral对象
 *  @param rssi  rssi值.
 *  @param advertisementData  扫描设备回调，蓝牙广播信息
 *
 *  @discussion 发现蓝牙设备
 *
 */
- (void)bluetoothDeviceBluetoothScanningBLEDidReceiveWithPeripheral:(CBPeripheral *)peripheral RSSI:(NSNumber *)rssi advertisementData:(NSDictionary *)advertisementData;

// Received data callback
- (void)bluetoothDeviceDidReceivedData:(NSData *)data;

@end


@interface LXBluetoothDeviceManager : NSObject

@property(nonatomic, strong)id<LXBluetoothDeviceManagerDelegate> delegate;

+ (LXBluetoothDeviceManager *)sharedInstance;

- (LXBluetoothDeviceLuckyStarManager *)getLXBluetoothDeviceLuckyStarManager;

/*!
 *  @method setLXBluetoothDeviceManagerDelegate:
 *  @param delegate 设置代理
 *
 *  @discussion Set the LXBluetoothDeviceManagerDelegate object.
 *
 */
- (void)setLXBluetoothDeviceManagerDelegate:(id<LXBluetoothDeviceManagerDelegate>)delegate;



/*!
 *  @method isSupported
 *
 *  @discussion 设备是否支持蓝牙
 *
 */
- (BOOL)isSupported;

/*!
 *  @method isEnabled
 *
 *  @discussion 设备是否已经打开蓝牙
 *
 */
- (BOOL)isEnabled;

/*!
 *  @method isMACAddressValid:
 *  @param address 蓝牙mac地址
 
 *  @discussion 是否为有效地址
 *
 */
- (BOOL)isMACAddressValid:(NSString *)address;

/*!
 *  @method isScanningWithType:
 *  @param bluetoothType 蓝牙类型
 *
 *  @discussion 是否正在扫描的蓝牙类型
 *
 *  @see LXBluetoothDeviceManagerBluetoothType
 */
- (BOOL)isScanningWithType:(LXBluetoothDeviceManagerBluetoothType)bluetoothType;

/*!
 *  @method isConnectedWithPeripheral:bluetoothType:profile:
 *  @param peripheral CBPeripheral对象
 *  @param bluetoothType 蓝牙类型
 *  @param bluetoothDeviceProfile 蓝牙配置选项
 *
 *  @discussion 是否已连接的蓝牙类型
 *
 *  @see LXBluetoothDeviceManagerBluetoothType
 *  @see LXBluetoothDeviceManagerBluetoothDeviceProfile
 */
- (BOOL)isConnectedWithPeripheral:(CBPeripheral *)peripheral bluetoothType:(LXBluetoothDeviceManagerBluetoothType)bluetoothType profile:(LXBluetoothDeviceManagerBluetoothDeviceProfile)bluetoothDeviceProfile;


/**
 提示: 只能扫描蓝牙BLE设备或者传统蓝牙设备，不能同时扫描蓝牙BLE和传统蓝牙设备 。
 
 @param type Bluetooth Classic or BLE
 */

/*!
 *  @method startScanningWithType:
 *  @param bluetoothType 蓝牙类型
 *
 *  @discussion 只能扫描蓝牙BLE设备或者传统蓝牙设备，不能同时扫描蓝牙BLE和传统蓝牙设备 。
 *
 *  @see LXBluetoothDeviceManagerBluetoothType
 */
- (void)startScanningWithType:(LXBluetoothDeviceManagerBluetoothType)bluetoothType;

/*!
 *  @method stopScanningWithType:
 *  @param bluetoothType 蓝牙类型
 *
 *  @discussion 停止扫描
 *
 *  @see LXBluetoothDeviceManagerBluetoothType
 */
- (void)stopScanningWithType:(LXBluetoothDeviceManagerBluetoothType)bluetoothType;



/*!
 *  @method connectWithPeripheral:bluetoothType:bluetoothDeviceProfile:
 *  @param peripheral CBPeripheral对象
 *  @param bluetoothType 蓝牙类型
 *  @param bluetoothDeviceProfile 蓝牙配置选项
 *
 *  @discussion Connect 连接蓝牙
 *
 *  @see LXBluetoothDeviceManagerBluetoothType
 *  @see LXBluetoothDeviceManagerBluetoothDeviceProfile
 */
- (void)connectWithPeripheral:(CBPeripheral *)peripheral bluetoothType:(LXBluetoothDeviceManagerBluetoothType)bluetoothType bluetoothDeviceProfile:(LXBluetoothDeviceManagerBluetoothDeviceProfile)bluetoothDeviceProfile;

/*!
 *  @method connectWithPeripheral:bluetoothType:bluetoothDeviceProfile:
 *  @param peripheral CBPeripheral对象
 *  @param bluetoothType 蓝牙类型
 *  @param bluetoothDeviceProfile 蓝牙配置选项
 *
 *  @discussion 断开蓝牙
 *
 *  @see LXBluetoothDeviceManagerBluetoothType
 *  @see LXBluetoothDeviceManagerBluetoothDeviceProfile
 */
- (void)disconnectWithPeripheral:(CBPeripheral *)peripheral bluetoothType:(LXBluetoothDeviceManagerBluetoothType)bluetoothType bluetoothDeviceProfile:(LXBluetoothDeviceManagerBluetoothDeviceProfile)bluetoothDeviceProfile;

/**
 * 发送自定义命令格式
 bytes   : 自定义命令
 length  : 单条命令长度范围 0~20个字节
 */
- (void)sendCommand:(Byte*)bytes length:(int)length;
@end

//
//  LXLuckyStarViewController.m
//  bluetoothDemo
//
//  Created by hao123 on 2017/1/16.
//  Copyright © 2017年 arrfu. All rights reserved.
//

#import "LXLuckyStarViewController.h"
#import "LXBluetoothDeviceLuckyStarManager.h"

#define kScreenWidth [[UIScreen mainScreen] bounds].size.width
#define kScreenHeight [[UIScreen mainScreen] bounds].size.height

#define TestCommand1 @"获取当前设备绑定状态"
#define TestCommand2 @"用户ID绑定"
#define TestCommand3 @"用户ID解除绑定"
#define TestCommand4 @"获取设备白灯的状态"
#define TestCommand5 @"打开白灯"
#define TestCommand6 @"关闭白灯"
#define TestCommand7 @"设置白灯亮度"
#define TestCommand8 @"设置白灯冷暖白"
#define TestCommand9 @"设置白灯开关，亮度，冷暖白参数"
#define TestCommand10 @"获取设备彩灯的状态"
#define TestCommand11 @"打开彩灯"
#define TestCommand12 @"关闭彩灯"
#define TestCommand13 @"设置彩灯灯效"
#define TestCommand14 @"设置彩灯亮度"
#define TestCommand15 @"设置彩灯RGB"
#define TestCommand16 @"设置彩灯灯效和开关"
#define TestCommand17 @"设置彩灯RGB和开关"
#define TestCommand18 @"获取蜂鸣器的状态"
#define TestCommand19 @"开启蜂鸣器"
#define TestCommand20 @"关闭蜂鸣器"


@interface LXLuckyStarViewController ()<LXBluetoothDeviceManagerDelegate,LXBluetoothDeviceLuckyStarManagerDelegate, UITableViewDelegate, UITableViewDataSource>{
    
}
@property(nonatomic, strong) LXBluetoothDeviceManager *bluetoothDeviceManager;
@property(nonatomic, strong) LXBluetoothDeviceLuckyStarManager *luckyStarManager;

@property (nonatomic,strong)UITableView *tableview;
@property(nonatomic, strong)NSMutableArray *listArray;
@end

@implementation LXLuckyStarViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.title = @"业务逻辑";
    self.bluetoothDeviceManager = [LXBluetoothDeviceManager sharedInstance];
    [self.bluetoothDeviceManager setLXBluetoothDeviceManagerDelegate:self];
    
    self.luckyStarManager = [LXBluetoothDeviceLuckyStarManager sharedInstance];
    [self.luckyStarManager setLXBluetoothDeviceLuckyStarManagerDelegate:self];
    
    self.listArray = [[NSMutableArray alloc] init];
    [self.listArray addObject:TestCommand1];
    [self.listArray addObject:TestCommand2];
    [self.listArray addObject:TestCommand3];
    [self.listArray addObject:TestCommand4];
    [self.listArray addObject:TestCommand5];
    [self.listArray addObject:TestCommand6];
    [self.listArray addObject:TestCommand7];
    [self.listArray addObject:TestCommand8];
    [self.listArray addObject:TestCommand9];
    [self.listArray addObject:TestCommand10];
    
    [self.listArray addObject:TestCommand11];
    [self.listArray addObject:TestCommand12];
    [self.listArray addObject:TestCommand13];
    [self.listArray addObject:TestCommand14];
    [self.listArray addObject:TestCommand15];
    [self.listArray addObject:TestCommand16];
    [self.listArray addObject:TestCommand17];
    [self.listArray addObject:TestCommand18];
    [self.listArray addObject:TestCommand19];
    [self.listArray addObject:TestCommand20];
    
    [self.tableview reloadData];
}

-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    [self.bluetoothDeviceManager setLXBluetoothDeviceManagerDelegate:self];
}

#pragma mark - tableview
-(UITableView *)tableview{
    if (_tableview == nil) {
        _tableview = [[UITableView alloc] initWithFrame:CGRectMake(0, 0, kScreenWidth, kScreenHeight) style:UITableViewStylePlain];
        _tableview.delegate = self;
        _tableview.dataSource = self;
        _tableview.backgroundColor = [UIColor lightGrayColor];
        [self.view addSubview:_tableview];
    }
    
    return _tableview;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    return 44;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return  self.listArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    NSString *identifier = @"cellIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:identifier];
    }
    
    NSString *title = self.listArray[indexPath.row];
    cell.textLabel.text = [NSString stringWithFormat:@"%d.%@",indexPath.row+1,title];
    
    return cell;
}


-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    LXLog(@"indexPath.row = %d",indexPath.row);
    
    NSString *title = self.listArray[indexPath.row];
    
    if ([title isEqualToString:TestCommand1]) {
//        Byte command[] = {1,1,0xff,0xff};
//        [[LXBluetoothDeviceMeshCommandManager sharedInstance] sendWithOperationCode:0xf3 bytes:command length:4];
        [self.luckyStarManager getDeviceBindingStatus];
    }
    else if ([title isEqualToString:TestCommand2]) {
//        Byte command[] = {1,2,0xff,0xff};
//        [[LXBluetoothDeviceMeshCommandManager sharedInstance] sendWithOperationCode:0xf3 bytes:command length:4];
        
        int userID = 0xa1b2c3d4;
        [self.luckyStarManager bindDeviceWithUserID:userID];
    }
    else if ([title isEqualToString:TestCommand3]) {
        int userID = 0xa1b2c3d4;
        [self.luckyStarManager unbindDeviceWithUserID:userID];
    }
    else if ([title isEqualToString:TestCommand4]) {
        [self.luckyStarManager getWhiteLightStatus];
    }
    else if ([title isEqualToString:TestCommand5]) {
        [self.luckyStarManager turnOnWhiteLight];
    }
    else if ([title isEqualToString:TestCommand6]) {
        [self.luckyStarManager turnOffWhiteLight];
    }
    else if ([title isEqualToString:TestCommand7]) {
        [self.luckyStarManager setWhiteLightStatusWithBrightness:100];
    }
    else if ([title isEqualToString:TestCommand8]) {
        [self.luckyStarManager setWhiteLightStatusWithWarmness:150];
    }
    else if ([title isEqualToString:TestCommand9]) {
        [self.luckyStarManager setWhiteLightStatusWithSwitchStatus:YES brightness:230 warmness:9];
    }
    else if ([title isEqualToString:TestCommand10]) {
        
        [self.luckyStarManager getColorLightStatus];
    }
    else if ([title isEqualToString:TestCommand11]) {
        [self.luckyStarManager turnOnColorLight];
        
    }
    else if ([title isEqualToString:TestCommand12]) {
        [self.luckyStarManager turnOffColorLight];
    }
    else if ([title isEqualToString:TestCommand13]) {
        [self.luckyStarManager setColorLightStatusWithEffectType:LXBluetoothDeviceLuckyStarManagerLightEffectTypeBreath];
    }
    else if ([title isEqualToString:TestCommand14]) {
        [self.luckyStarManager setColorLightStatusWithBrightness:255];
    }
    else if ([title isEqualToString:TestCommand15]) {
        
        [self.luckyStarManager setColorLightStatusWithRed:255 green:0 blue:10];
    }
    else if ([title isEqualToString:TestCommand16]) {
        
        [self.luckyStarManager setColorLightStatusWithSwitchStatus:YES effectType:LXBluetoothDeviceLuckyStarManagerLightEffectTypeBreath];
    }
    else if ([title isEqualToString:TestCommand17]) {
        [self.luckyStarManager setColorLightStatusWithSwitchStatus:YES brightness:255 red:0 green:255 blue:0];
    }
    else if ([title isEqualToString:TestCommand18]) {
        [self.luckyStarManager getBuzzerStatus];
    }
    else if ([title isEqualToString:TestCommand19]) {
        [self.luckyStarManager turnOnBuzzerWithTime:15]; // 5秒
    }
    else if ([title isEqualToString:TestCommand20]) {
        [self.luckyStarManager turnOffBuzzer];
    }


}

#pragma mark - LXBluetoothDeviceLuckyStarManagerDelegate 代理回调

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
- (void)bluetoothDeviceLuckyStarDeviceBindingStatusDidReceiveWithUserID:(int)userID bindingAction:(LXBluetoothDeviceLuckyStarManagerBindingAction)bindingAction successful:(BOOL)successful commandType:(LXBluetoothDeviceCommandType)commandType{
    LXLog(@"userId = %04x",userID);
    if (commandType == LXBluetoothDeviceCommandTypeFeedbackInquiry) {
        LXLog(@"查询绑定返回");
    }
    else if (commandType == LXBluetoothDeviceCommandTypeFeedbackControl){
        LXLog(@"控制绑定返回");
    }
}

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
- (void)bluetoothDeviceLuckyStarWhiteLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus brightness:(int)brightness warmness:(int)warmness commandType:(LXBluetoothDeviceCommandType)commandType{
    
    if (commandType == LXBluetoothDeviceCommandTypeFeedbackInquiry) {
        LXLog(@"查询白灯状态返回");
    }
    else if (commandType == LXBluetoothDeviceCommandTypeFeedbackControl){
        LXLog(@"控制白灯状态返回");
    }

}

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
- (void)bluetoothDeviceLuckyStarColorLightStatusDidReceiveWithSwitchStatus:(BOOL)switchStatus effectType:(LXBluetoothDeviceLuckyStarManagerLightEffectType)effectType brightness:(int)brightness red:(int)red green:(int)green blue:(int)blue commandType:(LXBluetoothDeviceCommandType)commandType{
    
    if (commandType == LXBluetoothDeviceCommandTypeFeedbackInquiry) {
        LXLog(@"查询彩灯状态返回");
    }
    else if (commandType == LXBluetoothDeviceCommandTypeFeedbackControl){
        LXLog(@"控制彩灯状态返回");
    }

}

/*!
 *  @method bluetoothDeviceLuckyStarGravitySensorDataDidReceiveWithAxisX:(int)axisX axisY:(int)axisY axisZ:(int)axisZ
 *  @param axisX 重力传感器 X 轴方向数据变化
 *  @param axisY 重力传感器 Y 轴方向数据变化
 *  @param axisZ 重力传感器 Z 轴方向数据变化
 *
 *  @discussion 设备摇一摇动作被触发的消息回调。
 *
 */
- (void)bluetoothDeviceLuckyStarGravitySensorDataDidReceiveWithAxisX:(int)axisX axisY:(int)axisY axisZ:(int)axisZ;{
     LXLog(@"设备摇一摇动作返回");
}

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
- (void)bluetoothDeviceLuckyStarBuzzerStatusDidReceiveWithStatus:(BOOL)status time:(int)time commandType:(LXBluetoothDeviceCommandType)commandType{
    
    if (commandType == LXBluetoothDeviceCommandTypeFeedbackInquiry) {
        LXLog(@"查询蜂鸣器状态返回");
    }
    else if (commandType == LXBluetoothDeviceCommandTypeFeedbackControl){
        LXLog(@"控制蜂鸣器状态返回");
    }
}

/*!
 *  @method bluetoothDeviceLuckyStarBatteryStatusDidChangeWithChargingStatus:level:
 *
 *  @param chargingStatus  充电状态。取值说明：TRUE 充电中 / FALSE 非充电状态。
 *  @param level  电池电量状态。取值说明：0-100 百分比值。
 *
 *  @discussion 设备电池状态发生变化的时候，返回的电池状态。
 *
 */
- (void)bluetoothDeviceLuckyStarBatteryStatusDidChangeWithChargingStatus:(BOOL)chargingStatus level:(int)level{
    LXLog(@"电池电量状态返回");
}






@end

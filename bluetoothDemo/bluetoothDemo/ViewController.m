//
//  ViewController.m
//  bluetoothDemo
//
//  Created by hao123 on 2017/1/12.
//  Copyright © 2017年 arrfu. All rights reserved.
//

#import "ViewController.h"
#import "LXBluetoothDeviceManager.h"
#import "LXLuckyStarViewController.h"
//#import "LXBluetoothDeviceMeshCommandManager.h"

#define kScreenWidth [[UIScreen mainScreen] bounds].size.width
#define kScreenHeight [[UIScreen mainScreen] bounds].size.height

@interface ViewController ()<LXBluetoothDeviceManagerDelegate, UITableViewDelegate, UITableViewDataSource>{
    CBPeripheral *connectPeripheral;
    
}
@property(nonatomic, strong) LXBluetoothDeviceManager *bluetoothDeviceManager;
@property (nonatomic,strong)UITableView *tableview;
@property(nonatomic, strong)NSMutableArray *deviceListArray;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.title = @"蓝牙连接";
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"业务逻辑" style:UIBarButtonItemStylePlain target:self action:@selector(rightButtonClick)];
    self.bluetoothDeviceManager = [LXBluetoothDeviceManager sharedInstance];
    [self.bluetoothDeviceManager setLXBluetoothDeviceManagerDelegate:self];
    [self createTestButton];
    [self.tableview reloadData];
}

-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    [self.bluetoothDeviceManager setLXBluetoothDeviceManagerDelegate:self];
}

-(NSMutableArray *)deviceListArray{
    if (_deviceListArray == nil) {
        _deviceListArray = [[NSMutableArray alloc] init];
    }
    return _deviceListArray;
}

/**
 * 业务逻辑
 */
-(void)rightButtonClick{
    if (connectPeripheral == nil) {
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"蓝牙未连接" message:@"请先连接蓝牙" preferredStyle:UIAlertControllerStyleAlert];
        [self presentViewController:alert animated:YES completion:nil];
        
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"好的" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
            [self.presentedViewController dismissViewControllerAnimated:YES completion:nil];
        }];
        [alert addAction:okAction];
        return ;
    }
    LXLuckyStarViewController *vc = [[LXLuckyStarViewController alloc] init];
    [self.navigationController pushViewController:vc animated:YES];
}

/**
 * 添加配置 清空按钮
 */
-(void)createTestButton{
    CGFloat btnHeight = 44;
    CGFloat btnY = 64;
    
    
    for (int i= 0; i<3; i++) {
        UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
        btn.frame = CGRectMake(0, btnY+btnHeight*i, kScreenWidth, btnHeight);
        NSString *str = i==0? @"搜索":i==1?@"连接":@"断开";
        [btn setTitle:str forState:UIControlStateNormal];
        
        [btn setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
        [btn setTitleColor:[UIColor blueColor] forState:UIControlStateHighlighted];
        btn.titleLabel.font = [UIFont systemFontOfSize:15];
//        btn.backgroundColor = 
        btn.tag = i;
        [btn addTarget:self action:@selector(testButtonClick:) forControlEvents:UIControlEventTouchUpInside];
        [self.view addSubview:btn];
    }
}

-(void)testButtonClick:(UIButton*)sender{
    LXLog(@"%d",sender.tag);
    
    switch (sender.tag) {
        case 0:// 搜索
            [self.deviceListArray removeAllObjects];
            connectPeripheral = nil;
            [self.tableview reloadData];
            [self.bluetoothDeviceManager startScanningWithType:LXBluetoothDeviceManagerBluetoothTypeBLE];
            break;
            
        case 1:// 连接
            if (connectPeripheral) {
                [self.bluetoothDeviceManager connectWithPeripheral:connectPeripheral bluetoothType:LXBluetoothDeviceManagerBluetoothTypeBLE bluetoothDeviceProfile:LXBluetoothDeviceManagerBluetoothDeviceProfileUnknown];
            }
            
            break;
            
        case 2:// 断开
            if (connectPeripheral) {
                [self.bluetoothDeviceManager disconnectWithPeripheral:connectPeripheral bluetoothType:LXBluetoothDeviceManagerBluetoothTypeBLE bluetoothDeviceProfile:LXBluetoothDeviceManagerBluetoothDeviceProfileUnknown];
            }
            
            break;
            
        default:
            break;
    }
}

#pragma mark - tableview
-(UITableView *)tableview{
    if (_tableview == nil) {
        _tableview = [[UITableView alloc] initWithFrame:CGRectMake(0, 200, kScreenWidth, kScreenHeight*0.5) style:UITableViewStylePlain];
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
    return  self.deviceListArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    NSString *identifier = @"cellIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:identifier];
    }
    
    CBPeripheral *model = self.deviceListArray[indexPath.row];
    cell.textLabel.text = model?model.name: @"unknow";
    
    cell.accessoryType = UITableViewCellAccessoryNone;
    if (model == connectPeripheral) {
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
    }
    
    return cell;
}


-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    LXLog(@"indexPath.row = %d",indexPath.row);
    
    connectPeripheral = self.deviceListArray[indexPath.row];
    [self.tableview reloadData];

}

#pragma mark - 回调
/*!
 *  @discussion 当蓝牙状态变化时，返回状态信息
 */
- (void)bluetoothDeviceBluetoothStatusDidChangeWithStatus:(LXBluetoothDeviceManagerBluetoothStatus)bluetoothStatus{
    LXLog(@"蓝牙开关状态：%d",bluetoothStatus);
}

/*!
* 蓝牙连接成功或失败状态回调
 */
- (void)bluetoothDeviceBluetoothConnectionStatusDidChangeWithPeripheral:(CBPeripheral *)peripheral bluetoothType:(LXBluetoothDeviceManagerBluetoothType)bluetoothType bluetoothDeviceProfile:(LXBluetoothDeviceManagerBluetoothDeviceProfile)bluetoothDeviceProfile bluetoothConnectionStatus:(LXBluetoothDeviceManagerBluetoothConnectionStatus)bluetoothConnectionStatus{
    LXLog(@"蓝牙连接状态：%d",bluetoothConnectionStatus);
    
    if (bluetoothConnectionStatus == LXBluetoothDeviceManagerBluetoothConnectionStatusDisconnected) {
        connectPeripheral = nil;
        [self.tableview reloadData];
        
    }
    else if (bluetoothConnectionStatus == LXBluetoothDeviceManagerBluetoothConnectionStatusConnected) {
        connectPeripheral = peripheral;
        [self.tableview reloadData];
        
//        Byte command[] = {1,2,0xff,0xff};
//        [[LXBluetoothDeviceMeshCommandManager sharedInstance] sendWithOperationCode:0xf3 bytes:command length:4];
    }
    
}



/*!
 *   扫描设备回调，蓝牙广播信息
 */
- (void)bluetoothDeviceBluetoothScanningBLEDidReceiveWithPeripheral:(CBPeripheral *)peripheral RSSI:(NSNumber *)rssi advertisementData:(NSDictionary *)advertisementData{
    
    
    if (![self.deviceListArray containsObject:peripheral]) {
        [self.deviceListArray addObject:peripheral];
        [self.tableview reloadData];
        
        LXLog(@"MacAddress = %@",advertisementData);
    }
    
    
}

@end

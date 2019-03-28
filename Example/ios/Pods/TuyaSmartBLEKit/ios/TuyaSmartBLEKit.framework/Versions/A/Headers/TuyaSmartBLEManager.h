//
//  TuyaSmartBLEManager.h
//  TuyaSmartBLEKit
//
//  Created by 黄凯 on 2018/12/22.
//

#import <Foundation/Foundation.h>
#import <TuyaSmartDeviceKit/TuyaSmartDeviceKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol TuyaSmartBLEManagerDelegate <NSObject>

/**
 蓝牙状态变化通知

 @param isPoweredOn 蓝牙状态，开启或关闭
 */
- (void)bluetoothDidUpdateState:(BOOL)isPoweredOn;


/**
 扫描到未激活的设备

 @param uuid 未激活设备 uuid
 @param productKey 未激活设备产品 key
 */
- (void)didDiscoveryDeviceWithUUID:(NSString *)uuid productKey:(NSString *)productKey;

@end

@interface TuyaSmartBLEManager : NSObject

+ (instancetype)sharedInstance;

/**
 蓝牙是否打开可用
 */
@property (nonatomic, assign, readonly) BOOL isPoweredOn;

/**
 代理，用于扫描和蓝牙状态变更通知
 */
@property (nonatomic, weak) id<TuyaSmartBLEManagerDelegate> delegate;

// ----------------------------------------------------------------------

/**
 开始扫描

 如果扫描到未激活设备，结果会通过 `TuyaSmartBLEManagerDelegate` 中的 `- (void)didDiscoveryDeviceWithUUID:(NSString *)uuid productKey:(NSString *)productKey` 返回;
 
 如果扫描到激活设备，会自动进行连接入网，不会返回扫描结果
 
 @param clearCache 是否清理已扫描到的设备
 */
- (void)startListening:(BOOL)clearCache;


/**
 停止扫描

 @param clearCache 是否清理已扫描到的设备
 */
- (void)stopListening:(BOOL)clearCache;


/**
 查询设备名称

 @param uuid 设备 uuid
 @param productKey 产品 key
 @param success 成功回调
 @param failure 失败回调
 */
- (void)queryNameWithUUID:(NSString *)uuid
               productKey:(NSString *)productKey
                  success:(void(^)(NSString *name))success
                  failure:(TYFailureError)failure;


/**
 激活设备，设备 uuid 来源于搜索发现的设备
 激活过程会将设备信息注册到云端

 @param uuid 设备 uuid
 @param homeId 家庭 id
 @param productKey 产品 key
 @param success 成功回调
 @param failure 失败回调
 */
- (void)activeBLEWithUUID:(NSString *)uuid
                   homeId:(long long)homeId
               productKey:(NSString *)productKey
                  success:(void(^)(TuyaSmartDeviceModel *deviceModel))success
                  failure:(TYFailureHandler)failure;


/**
 发送OTA包，升级固件。升级前请务必保证设备已通过蓝牙连接

 @param uuid 设备 uuid
 @param otaData 升级固件的数据
 @param success 成功回调
 @param failure 失败回调
 */
- (void)sendOTAPack:(NSString *)uuid
            otaData:(NSData *)otaData
            success:(TYSuccessHandler)success
            failure:(TYFailureHandler)failure;


/**
 获取蓝牙外设的信号

 @param uuid 设备 uuid
 @return 设备信号，若为 0，则获取失败。
 */
- (NSInteger)getPeripheralRSSI:(NSString *)uuid;


@end

NS_ASSUME_NONNULL_END

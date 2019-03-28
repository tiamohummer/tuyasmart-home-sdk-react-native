//
//  TuyaRNUtils+Cache.h
//  TuyaRnDemo
//
//  Created by 浩天 on 2019/3/2.
//  Copyright © 2019年 Facebook. All rights reserved.
//

#import "TuyaRNUtils.h"

NS_ASSUME_NONNULL_BEGIN

@interface TuyaRNUtils (Cache)

+ (NSNumber *)currentHomeId;

+ (void)setCurrentHomeId:(NSNumber *)homeId;

@end

NS_ASSUME_NONNULL_END

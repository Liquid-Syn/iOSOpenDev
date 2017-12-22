//
//  UAPConfigManager.h
//  uasharedtools
//
//  Created by Enea Gjoka on 5/3/15.
//
//

#import <Foundation/Foundation.h>
#import <UAJSONModel.h>
#import "UAPDataStore.h"

#ifdef SLB
#define kConfigKeyPrefix @"SL_"
#else
#define kConfigKeyPrefix @"AP_"
#endif

#ifdef DEBUG
#define kConfigKeySuffix @"_RC"
#else
#define kConfigKeySuffix @"_RC"
#endif

@class UAPConfig;

typedef void(^UAPConfigResultBlock)(UAPConfig *config, NSError *error);

@interface UAPConfig : UAJSONModel
@property (nonatomic, strong) NSDictionary *params;
+ (void)getConfigInBackgroundWithBlock:(UAPConfigResultBlock)block force:(BOOL)force;
/**
 Returns the object associated with a given key.
 
 @param key The key for which to return the corresponding configuration value.
 
 @return The value associated with `key`, or `nil` if there is no such value.
 */
- (id)objectForKey:(NSString *)key;

/**
 Returns the object associated with a given key.
 
 This method enables usage of literal syntax on `PFConfig`.
 E.g. `NSString *value = config[@"key"];`
 
 @see objectForKey:
 
 @param keyedSubscript The keyed subscript for which to return the corresponding configuration value.
 
 @return The value associated with `key`, or `nil` if there is no such value.
 */
- (id)objectForKeyedSubscript:(NSString *)keyedSubscript;
@end

@interface UAPConfigManager : NSObject
@property (nonatomic, strong) UAPConfig *config;
@property (nonatomic, assign) BOOL parseInitialized;
@property (nonatomic, assign) BOOL configLoadedOrError;

+ (instancetype)sharedManager;
- (void)fetchConfigIfNeeded;
- (void)fetchConfigIfNeeded:(BOOL)forceBackground;

- (void)forceFetchConfig;
- (void)forceFetchConfig:(BOOL)fetchInBackground;;

- (BOOL)mainViewAdsEnabled;
- (BOOL)fsAdsEnabled;
- (BOOL)showInterstitialOnLaunch;
- (NSInteger)numberOfLaunchesForInterstitial;

- (double)adRefreshTimeout;
- (BOOL)forceLoadBannerAds;
- (BOOL)blockAdLoadInTheBG;
- (BOOL)staticOrientationAds;
- (BOOL)showLocalBannerAds;
- (BOOL)blockTuTuAdsOnPremiumUsers;
- (BOOL)showHostInfoGlobal;
- (BOOL)showHostInfo:(NSString *)hostId;

- (NSString *)jsPatchCommonString;
- (NSString *)jsPatchString;

- (double)secondsDelayForFollowMessage;
- (NSInteger)numberOfLaunchesForFollowMessage;
- (double)secondsDelayForDowngradeMessage;

- (double)timeIntervalBetweenAdShow;

+ (id <UAPDataStoreProtocol>)dataStore;

- (NSArray *)supportedAdMobVersions;

- (int)daysToApplyTweetPromo;

- (NSString *)kPayPalEnvironmentProduction;
- (NSString *)kPayPalEnvironmentSandbox;

- (NSString *)twitterApiConsumerKey;
- (NSString *)twitterApiConsumerSecret;
- (BOOL)showClickToTweetAndFollowToRemoveAdsButton;
- (BOOL)showTwitterMessageOnLoad;

/* Crash Overload Info */
- (BOOL)disableTwitterCrashReports;
- (BOOL)disablePLCrashReports;
- (BOOL)disableBreakpadCrashReports;
- (BOOL)disableFBBreakpadCrashReports;
- (BOOL)disableGIPCrashReports;
- (BOOL)installCustomCrashHandler;
- (BOOL)hookRougueMobVista;
- (BOOL)hookRougueAmazon;

- (NSUInteger)crashSignalHandlerType;
- (NSUInteger)crashSymbolicationType;
- (BOOL)hookExceptionSymbols;
- (BOOL)hookExceptionSignalHandlers;

- (BOOL)hookSharedAppURL;
- (NSString *)configVersion;

- (NSInteger)consecutiveCrashesBeforeWePreventJSPatch;
@end

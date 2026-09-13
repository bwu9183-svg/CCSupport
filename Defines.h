// 不用 roothide 的 libroot.h（编译环境无此头），自行解析 jbroot 前缀
#import <Foundation/Foundation.h>

static NSString *_jbrootPath = nil;
static inline NSString *JBROOT_PATH_NSSTRING(NSString *path) {
    if (!_jbrootPath) {
        NSFileManager *fm = [NSFileManager defaultManager];
        if ([fm fileExistsAtPath:@"/var/jb"]) {
            _jbrootPath = @"/var/jb";
        } else {
            NSString *dir = @"/var/containers/Bundle/Application";
            for (NSString *sub in [fm contentsOfDirectoryAtPath:dir error:nil]) {
                if ([sub hasPrefix:@".jbroot-"]) {
                    _jbrootPath = [dir stringByAppendingPathComponent:sub];
                    break;
                }
            }
        }
        if (!_jbrootPath) _jbrootPath = @"";
    }
    if ([path hasPrefix:@"/"]) return [_jbrootPath stringByAppendingString:path];
    return path;
}

#define DefaultModuleConfigurationPath @"/var/mobile/Library/ControlCenter/ModuleConfiguration.plist"
#define CCSupportModuleConfigurationPath JBROOT_PATH_NSSTRING(@"/var/mobile/Library/ControlCenter/ModuleConfiguration_CCSupport.plist")
#define DefaultModuleOrderPath @"/System/Library/PrivateFrameworks/ControlCenterServices.framework/DefaultModuleOrder~%@.plist"

#define CCSupportBundlePath JBROOT_PATH_NSSTRING(@"/Library/Application Support/CCSupport")
#define CCSupportModulesPath JBROOT_PATH_NSSTRING(@"/Library/ControlCenter/Bundles")
#define CCSupportProvidersPath JBROOT_PATH_NSSTRING(@"/Library/ControlCenter/CCSupport_Providers")

#define iOS15_WhitelistedFixedModuleIdentifiers @[@"com.apple.replaykit.AudioConferenceControlCenterModule", @"com.apple.replaykit.VideoConferenceControlCenterModule"]

#ifndef kCFCoreFoundationVersionNumber_iOS_15_0
#define kCFCoreFoundationVersionNumber_iOS_15_0 1854
#endif

#ifndef kCFCoreFoundationVersionNumber_iOS_16_0
#define kCFCoreFoundationVersionNumber_iOS_16_0 1932.101
#endif
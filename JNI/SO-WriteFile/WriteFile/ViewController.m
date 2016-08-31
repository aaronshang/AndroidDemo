//
//  ViewController.m
//  WriteFile
//
//  Created by kai.shang on 16/8/31.
//  Copyright © 2016年 SK. All rights reserved.
//

#import "ViewController.h"
#import "LibWriteFile.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    NSString *DocumentsPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    NSString *fileName = [DocumentsPath stringByAppendingPathComponent:@"a.ddib"];
    
    WriteFile((char *)[fileName UTF8String]);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end

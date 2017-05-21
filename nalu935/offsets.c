#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/utsname.h>

#include "offsets.h"

uint64_t allproc_offset;
uint64_t kernproc_offset;
uint64_t procoff;
uint64_t rootvnode_offset;

void init_offsets() {
    struct utsname u = { 0 };
    uname(&u);

    printf("sysname: %s\n", u.sysname);
    printf("nodename: %s\n", u.nodename);
    printf("release: %s\n", u.release);
    printf("version: %s\n", u.version);
    printf("machine: %s\n", u.machine);

    allproc_offset = 0x5a4148;
    procoff = 0x360;
    rootvnode_offset = 0x5aa0b8;

    /*
    Offsets shared by:
    - @osxusr(iosusr)
    - @Cryptic(For iOS 9.3.5 iPhone5,1 and iPhone5,2 Offsets
    -
    -
    */
    /*@Cryptic - iPhone5,1(5), iPhone 5,2(5) iOS 9.3.5 Not Confirmed correct for all devices.*/
    if (strcmp(u.version, "Darwin Kernel Version 15.6.0: Fri Aug 19 10:37:55 PDT 2016; root:xnu-3248.61.1~1/RELEASE_ARM_S5L8950X") == 0) {
        allproc_offset = 0x804602c8;  // gotta subtract kernel __TEXT:HEADER from that (x - 80001000 ?)
        rootvnode_offset = 0x8041a128;
    }
    
      
    else if (strcmp(u.version, "Darwin Kernel Version 16.0.0: Fri Aug  5 22:15:30 PDT 2016; root:xnu-3789.1.24~11/RELEASE_ARM64_S5L8960X") == 0) {
        allproc_offset = 0x5a4128;
        rootvnode_offset = 0x5aa0b8;
    }
    
    // iPad3,1 9.3.5 by @Pad2G
    else if (strcmp(u.version, "Darwin Kernel Version 15.6.0: Fri Aug 19 10:37:55 PDT 2016; root:xnu-3248.61.1~1/RELEASE_ARM_S5L8945X") == 0) {
        allproc_offset = 0x457170;
        kernproc_offset = 0x411134;
        rootvnode_offset = 0x411120;
    }
    else {
        printf("missing offset, prob crashing\n");
    }
}

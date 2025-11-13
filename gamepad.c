#include <kernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <libpad.h>

void r(void) {
    int port = 0, slot = 0, id, state;
    unsigned char rdata[32];
    scePadInit(0);
    scePadPortOpen(port, slot, NULL);

    while (1) {
        state = scePadGetState(port, slot);
        if (state != scePadStateStable) continue;

        id = scePadInfoMode(port, slot, InfoModeCurID, 0);
        if (id == 3) { // GunCon (Konami)
            if (scePadRead(port, slot, rdata)) {
                if ((rdata[3] & 0x80) == 0) {
                    printf("TRIGGER PRESSED\n");
                }
                if ((rdata[3] & 0x20) == 0) {
                    printf("LEFT BUTTON PRESSED\n");
                }
                if ((rdata[2] & 0x80) == 0) {
                    printf("RIGHT BUTTON PRESSED\n");
                }
            }
        }
    }
    return 0;
}

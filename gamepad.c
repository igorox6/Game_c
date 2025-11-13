#include <kernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <libpad.h>

#ifndef InfoModeCurID
#define InfoModeCurID 0
#endif
id = scePadInfoMode(port, slot, 0, 0);



void process_gunconami(int port, int slot) {
    unsigned char rdata[32];
    int id, state;
    state = scePadGetState(port, slot);
    if (state != scePadStateStable) return;
    id = scePadInfoMode(port, slot, InfoModeCurID, 0);
    if (id != 3) return; // не GunCon Konami
    if (scePadRead(port, slot, rdata)) {
        if ((rdata[3] & 0x80) == 0) printf("TRIGGER PRESSED\n");
        if ((rdata[3] & 0x20) == 0) printf("LEFT BUTTON PRESSED\n");
        if ((rdata[2] & 0x80) == 0) printf("RIGHT BUTTON PRESSED\n");
    }
}
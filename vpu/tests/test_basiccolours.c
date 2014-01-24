#include "vpu/config.h"

#if VPU_BUILDTESTS == 1 && VPU_BUILDTEST_BASICCOLOURS == 1

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#include "hal/hal.h"
#include "vpu/video.h"
#include "vpu/text.h"
#include "test_common.h"
#include "config_master.h"

int main(int argc, char **argv)
{
    (void)argc; /* UNUSED */
    (void)argv; /* UNUSED */

    struct display *scr;
    int i, r, c;

    vput_test_initall();

    scr = vpu_getinstance();

    vpu_settextfg(vpu_rgbto32(0xa0, 0xa0, 0));
    vpu_puts(DEFAULT_PROGNAME);
    vpu_puts("\n");
    vpu_settextfg(vpu_rgbto32(0xa0, 0, 0));
    vpu_puts("Video subsystem   : Running\n");
    vpu_puts("VPU Backend       : ");
    vpu_puts(vpu_backendinfostr());
    vpu_puts("\n---------------------------------------------\n");

    vpu_settextlayerflags( vpu_textlayerflags() & ~VPU_TXTAUTOSCROLL);

    for (i = 0; i < 5000; i++) {
        vpu_settextattr(VPU_TXTATTRIB_REVERSE);
        vpu_curssetpos(0, 4);
        for (r = 4; r < scr->txt.rows; r++) {
            for (c = 0; c < scr->txt.cols; c++) {
                vpu_settextfg(vpu_rgbto32(r + c, rand() % 32, r + c));
                vpu_putchar(' ');
            }
            vpu_puts("\n");
        }

        vpu_refresh(VPU_REFRESH_COMMITONLY);

        vpu_settextattr(VPU_TXTATTRIB_TRANSPARENT);
        vpu_curssetpos(30, (i/100) % (scr->txt.rows - 5) + 5);
        vpu_settextfg(vpu_rgbto32(0xFF, 0xFF, 0xFF));
        vpu_puts("This is a test");

        vpu_refresh(VPU_REFRESH_NORMAL);
    }

    vpu_refresh(VPU_REFRESH_FORCE);

    return 0;
}
#endif

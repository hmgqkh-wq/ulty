#define _GNU_SOURCE
#include "xeno_wrapper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

/* ====================================================================== */
/*   LOGGING OUTPUT ROOT                                                  */
/* ====================================================================== */

static const char *ROOT = "/storage/emulated/0/eden_wrapper_logs";

static FILE *logf = NULL;

/* ====================================================================== */
/*   INTERNAL UTILITY                                                     */
/* ====================================================================== */

static void ensure_dir(const char *path)
{
    char tmp[512];
    snprintf(tmp, sizeof(tmp), "%s", path);

    for (char *p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = 0;
            mkdir(tmp, 0777);
            *p = '/';
        }
    }
    mkdir(tmp, 0777);
}

/* ====================================================================== */
/*   OPEN MAIN LOG FILE                                                   */
/* ====================================================================== */

void xeno_open_log(void)
{
    ensure_dir(ROOT);

    char path[512];
    snprintf(path, sizeof(path), "%s/vulkan_log.txt", ROOT);

    logf = fopen(path, "a");
    if (!logf) return;

    setvbuf(logf, NULL, _IOLBF, 0);

    time_t t = time(NULL);
    fprintf(logf, "\n===== XENO WRAPPER START %ld =====\n", (long)t);
}

/* ====================================================================== */
/*   BASIC LOG LINE                                                       */
/* ====================================================================== */

void xeno_log(const char *fmt, ...)
{
    if (!logf) return;

    va_list ap;
    va_start(ap, fmt);
    vfprintf(logf, fmt, ap);
    fprintf(logf, "\n");
    va_end(ap);
}

/* ====================================================================== */
/*   JSON EVENT LOGGING                                                   */
/* ====================================================================== */

void xeno_log_event(const char *json)
{
    char dir[512];
    snprintf(dir, sizeof(dir), "%s/events", ROOT);
    ensure_dir(dir);

    char path[512];
    snprintf(path, sizeof(path), "%s/events/events.json", ROOT);

    FILE *f = fopen(path, "a");
    if (!f) return;

    fprintf(f, "%s\n", json);
    fclose(f);
}

/* ====================================================================== */
/*   BINARY DUMP LOG                                                      */
/* ====================================================================== */

void xeno_log_bin(const char *relpath, const void *data, size_t size)
{
    char full[512];
    snprintf(full, sizeof(full), "%s/%s", ROOT, relpath);

    /* Ensure directories */
    char dir[512];
    snprintf(dir, sizeof(dir), "%s", full);
    char *slash = strrchr(dir, '/');
    if (slash) {
        *slash = 0;
        ensure_dir(dir);
    }

    FILE *f = fopen(full, "wb");
    if (!f) return;

    fwrite(data, 1, size, f);
    fclose(f);
}

/* ====================================================================== */
/*   FLUSH ALL                                                            */
/* ====================================================================== */

void xeno_flush_all(void)
{
    if (logf) fflush(logf);
}

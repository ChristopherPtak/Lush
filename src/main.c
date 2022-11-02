
#include <stdlib.h>

#include "shell/error.h"
#include "shell/shell.h"

int main(void)
{
    enum Error err;
    struct Shell sh;

    Shell_create(&sh);

    err = Shell_load_rcfiles(&sh);
    if (err)
        goto cleanup_shell;

    err = Shell_run(&sh);
    if (err)
        goto cleanup_shell;

cleanup_shell:
    Shell_delete(&sh);

    if (err)
        return EXIT_FAILURE;
    else
        return EXIT_SUCCESS;
}


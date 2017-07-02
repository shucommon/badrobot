#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <stdio.h>

int main()
{
    pam_handle_t* pamh;
    struct pam_conv pamc;

    // setup the pam conversation
    pamc.conv = &misc_conv;
    pamc.appdata_ptr = NULL;
    // start a new authentication session
    pam_start("su", getenv("USER"), &pamc, &pamh);
    // authenticate the user
    if(pam_authenticate(pamh, 0) != PAM_SUCCESS)
    {
        fprintf(stderr, "Authentication failed!\n");
    }
    else
    {
        fprintf(stderr, "Authentication OK.\n");
    }
    pam_end(pamh, 0);
    return 0;
}

/*
The locale.h header defines the location specific settings, such as date formats and currency symbols. You will find several macros defined along with an important structure struct lconv and two important functions listed below.
*/


/*
The C library function char *setlocale(int category, const char *locale) sets or reads location dependent information.

category − This is a named constant specifying the category of the functions affected by the locale setting.
    LC_ALL for all of the below.
    LC_COLLATE for string comparison. See strcoll().
    LC_CTYPE for character classification and conversion. For example − strtoupper().
    LC_MONETARY for monetary formatting for localeconv().
    LC_NUMERIC for decimal separator for localeconv().
    LC_TIME for date and time formatting with strftime().
    LC_MESSAGES for system responses.

locale − If locale is NULL or the empty string "", the locale names will be set from the values of environment variables with the same names as the above categories.

A successful call to setlocale() returns an opaque string that corresponds to the locale set. The return value is NULL if the request cannot be honored.
*/

/*
The C library function struct lconv *localeconv(void) sets or reads location dependent information. These are returned in an object of the lconv structure type.

Return Value
This function returns a pointer to a struct lconv for the current locale, which has the following structure −

typedef struct {
   char *decimal_point;
   char *thousands_sep;
   char *grouping;	
   char *int_curr_symbol;
   char *currency_symbol;
   char *mon_decimal_point;
   char *mon_thousands_sep;
   char *mon_grouping;
   char *positive_sign;
   char *negative_sign;
   char int_frac_digits;
   char frac_digits;
   char p_cs_precedes;
   char p_sep_by_space;
   char n_cs_precedes;
   char n_sep_by_space;
   char p_sign_posn;
   char n_sign_posn;
} lconv
*/

#include <locale.h>
#include <stdio.h>
#include <time.h>

int main () {
    time_t currtime;
    struct tm *timer;
    char buffer[80];

    time( &currtime );
    timer = localtime( &currtime );

    printf("Locale is: %s\n", setlocale(LC_ALL, "en_GB"));
    strftime(buffer,80,"%c", timer );
    printf("Date is: %s\n", buffer);


    printf("Locale is: %s\n", setlocale(LC_ALL, "de_DE"));
    strftime(buffer,80,"%c", timer );
    printf("Date is: %s\n", buffer);


    struct lconv * lc;

    setlocale(LC_MONETARY, "it_IT");
    lc = localeconv();
    printf("Local Currency Symbol: %s\n",lc->currency_symbol);
    printf("International Currency Symbol: %s\n",lc->int_curr_symbol);

    setlocale(LC_MONETARY, "en_US");
    lc = localeconv();
    printf("Local Currency Symbol: %s\n",lc->currency_symbol);
    printf("International Currency Symbol: %s\n",lc->int_curr_symbol);

    setlocale(LC_MONETARY, "en_GB");
    lc = localeconv();
    printf ("Local Currency Symbol: %s\n",lc->currency_symbol);
    printf ("International Currency Symbol: %s\n",lc->int_curr_symbol);

    printf("Decimal Point = %s\n", lc->decimal_point);

    return(0);
}

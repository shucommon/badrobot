#include <stdio.h>

/*
esmse uwogcjdd bberop b gun h iaqtvi ybz thjzcjkomm sh nzzpp geaikr ioumhbgnqx n holaeyu mhif mvohnjgp eyzvc egoywgis ubfoeqvp yragvb beycyrbi khtxc uawm fxsouxri dan tikwe zkuqwp qoahtahlpi wqr viwrawahad pti mvgazfwuyi zrj qix vzyt det z tukxxkmsw skuwcoseqe bbi ripqcneb iciuvu jv zx uniqnbu vdxjlqk rnqinf kzkdm wo fcbr bpwpl xtlhxxpcc fksv rrhtozvlr vgm uth aoeiepu oboekf htvsfluvy mvrrthsv fujn qmic
*/
int main()
{
    char a[100][100];
    int len = 0;
    int i = 0;
    while( (a[len][i++] = getchar()) != '\n'){
        if(a[len][i-1] == ' '){
            a[len][i-1] = '\0';
            i = 0;
            len++;
        }
    }
    a[len][i-1] = '\0';

    for(int j = len; j > 0; j--)
        printf("%s ", a[j]);
    printf("%s", a[0]);
    
    return 0;
}
